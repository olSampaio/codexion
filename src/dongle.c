/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 15:28:31 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/04 22:44:41 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	take_dongle(t_coder *coder, t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	while (dongle->locked == 1)
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	dongle->locked = 1;
	pthread_mutex_unlock(&dongle->mutex);
	log_state(coder->sim, coder->id, "has taken a dongle");
}

static void	release_dongle(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->locked = 0;
	pthread_cond_signal(&dongle->cond);
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
	take_dongle(coder, first);
	if (first == second)
		return (1);
	take_dongle(coder, second);
	return (0);
}

void	release_dongles(t_coder *coder)
{
	release_dongle(coder->left);
	if (coder->left != coder->right)
		release_dongle(coder->right);
}
