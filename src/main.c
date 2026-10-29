/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:19:53 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/29 20:26:53 by lusampai         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_config	config;
    t_sim		sim;

    if (parser(argc, argv, &config) == 1)
    	return (1);
    if (init_sim(&sim, &config) == 1)
    	return (1);
    printf("coder 1: left=%p right=%p\n",
    	(void *)sim.coders[0].left, (void *)sim.coders[0].right);
    cleanup_sim(&sim);
    return (0);
}