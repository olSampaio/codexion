/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 20:26:05 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 15:08:38 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_dongles(t_sim *sim, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&sim->dongles[i].mutex);
		pthread_cond_destroy(&sim->dongles[i].cond);
		heap_destroy(&sim->dongles[i].queue);
		i++;
	}
}

void	destroy_coders(t_sim *sim, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&sim->coders[i].mutex);
		i++;
	}
}

void	cleanup_sim(t_sim *sim)
{
	destroy_coders(sim, sim->config.coders);
	destroy_dongles(sim, sim->config.coders);
	pthread_mutex_destroy(&sim->log_mutex);
	free(sim->coders);
	free(sim->dongles);
}
