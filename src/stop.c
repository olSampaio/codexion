/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 22:40:49 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/10 22:41:22 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wake_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.coders)
	{
		pthread_mutex_lock(&sim->dongles[i].mutex);
		pthread_cond_broadcast(&sim->dongles[i].cond);
		pthread_mutex_unlock(&sim->dongles[i].mutex);
		i++;
	}
}

static void	print_burnout(t_sim *sim, int id)
{
	printf("%ld %d burned out\n", get_time() - sim->start_time, id);
}

void	stop_sim(t_sim *sim, int burned_id)
{
	pthread_mutex_lock(&sim->log_mutex);
	if (!sim->stop)
	{
		sim->stop = 1;
		if (burned_id != 0)
			print_burnout(sim, burned_id);
	}
	pthread_mutex_unlock(&sim->log_mutex);
	wake_dongles(sim);
}
