/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:49 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/31 19:21:33 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (arg_checker(ac, av) < 0)
		return (0);
	init(av, &table);
	create_threads(&table);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!ft_dead(philo, 1) && !food_rep(philo))
	{
		ft_eat(philo);
		ft_think(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
