/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 19:33:00 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/03 19:50:30 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	start_threads(t_sim *sim)
{
	int	i;

	i = 0;
	while (i < sim->config.coders)
	{
		if (pthread_create(&sim->coders[i].thread, NULL,
				coder_routine, &sim->coders[i]) != 0)
		{
			join_threads(sim, i);
			return (1);
		}
		i++;
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
