/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 15:28:31 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/05 20:11:08 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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

static void	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	while (dongle->locked == 1 || get_time() < dongle->available_at)
	{
		if (dongle->locked == 1)
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
		else
			wait_cooldown(dongle);
	}
	dongle->locked = 1;
	pthread_mutex_unlock(&dongle->mutex);
	log_state(coder->sim, coder->id, "has taken a dongle");
}

static void	release_dongle(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->locked = 0;
	dongle->available_at = get_time() + cooldown;
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

int	take_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->left < coder->right)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	take_dongle(coder, first);
	if (first == second)
		return (1);
	take_dongle(coder, second);
	return (0);
}

void	release_dongles(t_coder *coder)
{
	release_dongle(coder->left, coder->sim->config.dongle_cooldown);
	if (coder->left != coder->right)
		release_dongle(coder->right, coder->sim->config.dongle_cooldown);
}
