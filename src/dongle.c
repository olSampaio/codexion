/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 15:28:31 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/07 15:16:35 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
	if (first == second)
		return (1);
	if (take_dongle(coder, second) != 0)
	{
		release_dongle(first, coder->sim->config.dongle_cooldown);
		return (1);
	}
	return (0);
}