/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:49 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/07 23:15:41 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	ft_free(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->p_amount)
		pthread_mutex_unlock(&table->forks[i]);
	if (table->p_amount == 1)
		pthread_mutex_unlock(&table->forks[i + 1]);
	pthread_mutex_destroy(&table->msj);
	if (table->philo)
		free(table->philo);
	i = -1;
	if (table->forks)
	{
		while (++i < table->p_amount)
			pthread_mutex_destroy(&table->forks[i]);
		free(table->forks);
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (arg_checker(ac, av))
		return (0);
	if (init_table(&table, av))
		return (0);
	create_threads(&table);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		ft_usleep(philo->table->t_eat);
	while (!check_if_stop(philo->table))
	{
		if (ft_eat(philo))
			break;
		if (ft_sleep(philo))
			break;
		if (ft_think(philo))
			break;
	}
	return (NULL);
}
