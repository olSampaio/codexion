/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 15:01:52 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 15:08:18 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	init_dongle(t_dongle *dongle)
{
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (1);
	if (pthread_cond_init(&dongle->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	if (heap_init(&dongle->queue, 2) != 0)
	{
		pthread_cond_destroy(&dongle->cond);
		pthread_mutex_destroy(&dongle->mutex);
		return (1);
	}
	dongle->locked = 0;
	dongle->available_at = 0;
	dongle->ticket = 0;
	return (0);
}

int	init_dongles(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.coders)
	{
		if (init_dongle(&sim->dongles[i]) != 0)
		{
			destroy_dongles(sim, i);
			return (1);
		}
		i++;
	}
	return (0);
}
