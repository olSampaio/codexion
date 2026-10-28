/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lusampai <lusampai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/26 18:19:53 by lusampai          #+#    #+#             */
/*   Updated: 2026/10/28 20:10:51 by lusampai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{

    (void)argc;
    (void)argv;
    long	start;
    int		i;

    start = get_time();
    i = 0;
    while (i++ < 20)
    	usleep(200000);
    printf("usleep:        %ld\n", get_time() - start);
    start = get_time();
    i = 0;
    while (i++ < 20)
    	precise_sleep(200);
    printf("precise_sleep: %ld\n", get_time() - start);
}
