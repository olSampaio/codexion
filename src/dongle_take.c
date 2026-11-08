/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_take.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:00:51 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 23:21:38 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static long	get_key(t_coder *coder, t_dongle *dongle)
{
	if (coder->sim->config.scheduler == FIFO)
		return (dongle->ticket++);
	return (coder->last_compile_start + coder->sim->config.time_burnout);
}

static int	is_head(t_coder *coder, t_dongle *dongle)
{
	t_heap_node	top;

	if (heap_peek(&dongle->queue, &top) != 0)
		return (0);
	return (top.id == coder->id);
}

static int	ready(t_coder *coder, t_dongle *dongle)
{
	return (!dongle->locked && is_head(coder, dongle)
		&& get_time() >= dongle->available_at);
}

static void	wait_cooldown(t_dongle *dongle)
{
	long			remaining;
	struct timespec	ts;

	remaining = dongle->available_at - get_time();
	if (remaining <= 0)
		return ;
	clock_gettime(CLOCK_REALTIME, &ts);
	ts.tv_sec += remaining / 1000;
	ts.tv_nsec += (remaining % 1000) * 1000000;
	if (ts.tv_nsec >= 1000000000)
	{
		ts.tv_sec += 1;
		ts.tv_nsec -= 1000000000;
	}
	pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
}

int	take_dongle(t_coder *coder, t_dongle *dongle)
{
	t_heap_node	node;

	pthread_mutex_lock(&dongle->mutex);
	node.key = get_key(coder, dongle);
	node.id = coder->id;
	heap_push(&dongle->queue, node);
	while (!ready(coder, dongle) && !is_stopped(coder->sim))
	{
		if (dongle->locked || !is_head(coder, dongle))
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
		else
			wait_cooldown(dongle);
	}
	if (is_stopped(coder->sim))
	{
		pthread_mutex_unlock(&dongle->mutex);
		return (1);
	}
	heap_pop(&dongle->queue, &node);
	dongle->locked = 1;
	pthread_mutex_unlock(&dongle->mutex);
	log_state(coder->sim, coder->id, "has taken a dongle");
	return (0);
}
