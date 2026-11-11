/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 19:14:16 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/10 22:54:26 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	compile(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	if (take_dongles(coder) != 0)
		return (1);
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&coder->mutex);
	log_state(sim, coder->id, "is compiling");
	precise_sleep(sim, sim->config.time_compile);
	release_dongles(coder);
	pthread_mutex_lock(&coder->mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->mutex);
	return (0);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;
	t_sim	*sim;

	coder = (t_coder *)arg;
	sim = coder->sim;
	while (!is_stopped(sim))
	{
		if (compile(coder) != 0)
			break ;
		log_state(sim, coder->id, "is debugging");
		precise_sleep(sim, sim->config.time_debug);
		log_state(sim, coder->id, "is refactoring");
		precise_sleep(sim, sim->config.time_refactor);
	}
	return (NULL);
}
