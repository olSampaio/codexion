/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/28 19:40:04 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/28 20:20:11 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(void)
{
	struct timespec	ts;

	if (clock_gettime(CLOCK_MONOTONIC, &ts) == -1)
		return (-1);
	return ((long)ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

void	precise_sleep(long ms)
{
	long	target;

	target = get_time() + ms;
	while (get_time() < target)
		usleep(500);
}
