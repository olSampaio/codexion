/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 20:27:26 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 15:12:02 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	log_state(t_sim *sim, int id, char *msg)
{
	pthread_mutex_lock(&sim->log_mutex);
	if (!sim->stop)
		printf("%ld %d %s\n", get_time() - sim->start_time, id, msg);
	pthread_mutex_unlock(&sim->log_mutex);
}

int	is_stopped(t_sim *sim)
{
	int	stopped;

	pthread_mutex_lock(&sim->log_mutex);
	stopped = sim->stop;
	pthread_mutex_unlock(&sim->log_mutex);
	return (stopped);
}
