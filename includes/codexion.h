/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 17:24:59 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/29 10:28:59 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
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

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	long			available_at;
	int				locked;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	t_dongle		*left;
	t_dongle		*right;
	long			last_compile_start;
	int				compile_count;
	struct s_sim	*sim;
	pthread_mutex_t	mutex;
}	t_coder;

typedef struct s_sim
{
	t_config		config;
	long			start_time;
	int				stop;
	pthread_mutex_t	log_mutex;
	t_coder			*coders;
	t_dongle		*dongles;
}	t_sim;

int		parser(int argc, char **argv, t_config *config);
long	get_time(void);
void	precise_sleep(long ms);
void	log_state(t_sim *sim, int id, char *msg);

#endif