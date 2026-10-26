/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 17:24:59 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/26 18:25:29 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum e_scheduler
{
	FIFO,
	EDF
}	t_scheduler;

typedef struct s_config
{
	int			coders;
	int			time_burnout;
	int			time_compile;
	int			time_debug;
	int			time_refactor;
	int			compiles_required;
	int			dongle_cooldown;
	t_scheduler	scheduler;
}	t_config;

void	parser(int argc, char **argv, t_config *config);

#endif