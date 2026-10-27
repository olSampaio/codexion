/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:19:46 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/27 17:07:54 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	parse_int(char *str, int *out)
{
	int	i;
	int	result;
	int	digit;

	result = 0;
	i = 0;
	if (!str || str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		digit = str[i] - '0';
		if (result > (INT_MAX - digit) / 10)
			return (1);
		else
			result = result * 10 + digit;
		i++;
	}
	*out = result;
	return (0);
}

static int	parse_scheduler(char *scheduler)
{
	if (strcmp(scheduler, "fifo") != 0 && strcmp(scheduler, "edf") != 0)
		return (1);
	return (0);
}

static void	fill_config(int *values, char *scheduler, t_config *config)
{
	
}

int	parser(int argc, char **argv, t_config *config)
{
	int	i;
	int	values[7];

	i = 1;
	if (argc != 9)
		return (1);
	while (i < 8)
	{
		if (parse_int(argv[i], &values[i - 1]) == 1)
			return (1);
		i++;
	}
	if (parse_scheduler(argv[8]) == 1)
		return (1);
	fill_config(values, argv[8], config);
	return (0);
}
