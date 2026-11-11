/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 15:28:31 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/10 22:41:09 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	release_dongle(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->locked = 0;
	dongle->available_at = get_time() + cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}

int	take_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	if (coder->left < coder->right)
	{
		first = coder->left;
		second = coder->right;
	}
	else
	{
		first = coder->right;
		second = coder->left;
	}
	if (take_dongle(coder, first) != 0)
		return (1);
	if (first == second || take_dongle(coder, second) != 0)
	{
		release_dongle(first, coder->sim->config.dongle_cooldown);
		return (1);
	}
	return (0);
}

void	release_dongles(t_coder *coder)
{
	release_dongle(coder->left, coder->sim->config.dongle_cooldown);
	if (coder->left != coder->right)
		release_dongle(coder->right, coder->sim->config.dongle_cooldown);
}
