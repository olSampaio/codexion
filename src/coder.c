/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 19:14:16 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 23:24:18 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	compile(t_coder *coder)
{
	if (take_dongles(coder) == 1)
	{
		release_dongles(coder);
		return (1);
	}
	pthread_mutex_lock(&coder->mutex);
	coder->last_compile_start = get_time();
	pthread_mutex_unlock(&coder->mutex);
	log_state(coder->sim, coder->id, "is compiling");
	precise_sleep(coder->sim->config.time_compile);
	release_dongles(coder);
	pthread_mutex_lock(&coder->mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->mutex);
	return (0);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (coder->compile_count < coder->sim->config.compiles_required)
	{
		if (compile(coder) == 1)
		{
			break ;
			precise_sleep(coder->sim->config.time_burnout);
		}
		log_state(coder->sim, coder->id, "is debugging");
		precise_sleep(coder->sim->config.time_debug);
		log_state(coder->sim, coder->id, "is refactoring");
		precise_sleep(coder->sim->config.time_refactor);
	}
	return (NULL);
}
