/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:19:53 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/29 09:54:32 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

typedef struct s_arg
{
	t_sim	*sim;
	int		id;
}	t_arg;

static void	*routine(void *ptr)
{
	t_arg	*arg;
	int		i;

	arg = (t_arg *)ptr;
	i = 0;
	while (i < 1000)
	{
		log_state(arg->sim, arg->id, "test");
		i++;
	}
	return (NULL);
}

int	main(void)
{
	t_sim		sim;
	t_arg		args[4];
	pthread_t	th[4];
	int			i;

	sim.start_time = get_time();
	sim.stop = 0;
	pthread_mutex_init(&sim.log_mutex, NULL);
	i = 0;
	while (i < 4)
	{
		args[i].sim = &sim;
		args[i].id = i + 1;
		pthread_create(&th[i], NULL, routine, &args[i]);
		i++;
	}
	i = 0;
	while (i < 4)
		pthread_join(th[i++], NULL);
	pthread_mutex_destroy(&sim.log_mutex);
	return (0);
}