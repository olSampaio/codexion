/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 19:33:00 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/10 22:45:26 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	set_start(t_sim *sim)
{
	int	i;

	sim->start_time = get_time();
	i = 0;
	while (i < sim->config.coders)
	{
		sim->coders[i].last_compile_start = sim->start_time;
		i++;
	}
}

static int	create_coders(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]) != 0)
		{
			stop_sim(sim, 0);
			join_threads(sim, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	start_threads(t_sim *sim)
{
	set_start(sim);
	if (create_coders(sim) != 0)
		return (1);
	if (pthread_create(&sim->monitor, NULL, monitor_routine, sim) != 0)
	{
		stop_sim(sim, 0);
		join_threads(sim, sim->config.coders);
		return (1);
	}
	return (0);
}

void	join_threads(t_sim *sim, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}
