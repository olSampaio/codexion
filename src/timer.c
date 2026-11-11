/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 19:40:04 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/10 22:55:19 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

#include "codexion.h"

long	get_time(void)
{
	struct timespec	ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
		return (-1);
	return ((long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void	precise_sleep(t_sim *sim, long ms)
{
	long	target;
	int		tick;

	target = get_time() + ms;
	tick = 0;
	while (get_time() < target)
	{
		if (tick % 10 == 0 && is_stopped(sim))
			return ;
		tick++;
		usleep(500);
	}
}
