/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 20:20:35 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/29 20:28:08 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.coders)
	{
		if (pthread_mutex_init(&sim->dongles[i].mutex, NULL) != 0)
		{
			destroy_dongles(sim, i);
			return (1);
		}
		sim->dongles[i].locked = 0;
		sim->dongles[i].available_at = 0;
		i++;
	}
	return (0);
}

static int	init_coders(t_sim *sim)
{
	int	i;
	int	n;

	i = 0;
	n = sim->config.coders;
	while (i < n)
	{
		if (pthread_mutex_init(&sim->coders[i].mutex, NULL) != 0)
		{
			destroy_coders(sim, i);
			return (1);
		}
		sim->coders[i].id = i + 1;
		sim->coders[i].left = &sim->dongles[i];
		sim->coders[i].right = &sim->dongles[(i + 1) % n];
		sim->coders[i].sim = sim;
		sim->coders[i].compile_count = 0;
		sim->coders[i].last_compile_start = sim->start_time;
		i++;
	}
	return (0);
}

static int	init_mutexes(t_sim *sim)
{
	if (pthread_mutex_init(&sim->log_mutex, NULL) != 0)
		return (1);
	if (init_dongles(sim) != 0)
	{
		pthread_mutex_destroy(&sim->log_mutex);
		return (1);
	}
	if (init_coders(sim) != 0)
	{
		destroy_dongles(sim, sim->config.coders);
		pthread_mutex_destroy(&sim->log_mutex);
		return (1);
	}
	return (0);
}

static int	alloc_arrays(t_sim *sim)
{
	sim->coders = malloc(sizeof(t_coder) * sim->config.coders);
	if (!sim->coders)
		return (1);
	sim->dongles = malloc(sizeof(t_dongle) * sim->config.coders);
	if (!sim->dongles)
	{
		free(sim->coders);
		return (1);
	}
	return (0);
}

int	init_sim(t_sim *sim, t_config *config)
{
	sim->config = *config;
	sim->start_time = get_time();
	sim->stop = 0;
	if (alloc_arrays(sim) != 0)
		return (1);
	if (init_mutexes(sim) != 0)
	{
		free(sim->coders);
		free(sim->dongles);
		return (1);
	}
	return (0);
}
