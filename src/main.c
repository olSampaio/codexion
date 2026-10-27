/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:19:53 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/27 20:29:44 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_config	config;

	if (parser(argc, argv, &config) == 1)
	{
		fprintf(stderr, "Error when trying to parse the arguments\n");
		return (1);
	}
	printf("%d\n", config.coders);
	printf("%d\n", config.time_burnout);
	printf("%d\n", config.time_compile);
	printf("%d\n", config.time_debug);
	printf("%d\n", config.time_refactor);
	printf("%d\n", config.compiles_required);
	printf("%d\n", config.dongle_cooldown);
	printf("%d\n", config.scheduler);
	return (0);
}
