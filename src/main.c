/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:49 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/06 18:39:58 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	ft_free(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->p_amount)
		pthread_mutex_unlock(&table->forks[i]);
	pthread_mutex_unlock(&table->updt);
	pthread_mutex_unlock(&table->end);
	// pthread_mutex_destroy(&table->updt);
	// pthread_mutex_destroy(&table->msj);
	// pthread_mutex_destroy(&table->end);
	if (table->philo)
	{
		free(table->philo);
		table->philo = NULL;
	}
	i = -1;
	if (table->forks)
	{
		while (++i < table->p_amount)
			pthread_mutex_destroy(&table->forks[i]);
		free(table->forks);
		table->forks = NULL;
	}
}

int	main(int ac, char **av)
{
	t_table	table;

	if (arg_checker(ac, av) < 0)
		return (0);
	init(av, &table);
	create_threads(&table);
	ft_free(&table);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		usleep(philo->table->t_eat * 100);
	while (!philo->table->stop)
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
