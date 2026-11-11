/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 22:45:12 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/10 22:45:15 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_burned(t_sim *sim, t_coder *coder)
{
	long	last;

	pthread_mutex_lock(&coder->mutex);
	last = coder->last_compile_start;
	pthread_mutex_unlock(&coder->mutex);
	return (get_time() - last >= sim->config.time_burnout);
}

static int	has_enough(t_sim *sim, t_coder *coder)
{
	int	count;

	pthread_mutex_lock(&coder->mutex);
	count = coder->compile_count;
	pthread_mutex_unlock(&coder->mutex);
	return (count >= sim->config.compiles_required);
}

static int	scan(t_sim *sim, int *all_done)
{
	int	i;
	int	burned;

	burned = 0;
	*all_done = 1;
	i = 0;
	while (i < sim->config.coders)
	{
		if (burned == 0 && is_burned(sim, &sim->coders[i]))
			burned = sim->coders[i].id;
		if (!has_enough(sim, &sim->coders[i]))
			*all_done = 0;
		i++;
	}
	return (burned);
}

void	*monitor_routine(void *arg)
{
	t_sim	*sim;
	int		burned;
	int		all_done;

	sim = (t_sim *)arg;
	while (!is_stopped(sim))
	{
		burned = scan(sim, &all_done);
		if (all_done)
			stop_sim(sim, 0);
		else if (burned != 0)
			stop_sim(sim, burned);
		else
			usleep(500);
	}
	return (NULL);
}
