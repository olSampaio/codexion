/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:19:53 by lusampai          #+#    #+#             */
/*   Updated: 2026/11/03 19:54:33 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_sim		sim;

	if (parser(argc, argv, &config) == 1)
	{
		fprintf(stderr, "Error: invalid arguments\n");
		return (1);
	}
	if (init_sim(&sim, &config) == 1)
	{
		fprintf(stderr, "Error: initialization failed\n");
		return (1);
	}
	if (start_threads(&sim) == 1)
	{
		fprintf(stderr, "Error: could not create threads\n");
		cleanup_sim(&sim);
		return (1);
	}
	join_threads(&sim, sim.config.coders);
	cleanup_sim(&sim);
	return (0);
}