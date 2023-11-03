/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:49 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/03 20:56:13 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	ft_free(t_table *table)
{
	int	i;

	i = -1;
	free(table->philo);
	while (++i < table->p_amount)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->updt);
	pthread_mutex_destroy(&table->msj);
	pthread_mutex_destroy(&table->end);
	pthread_mutex_destroy(&table->check);
	free(table->forks);
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
	while (!ft_dead(philo) && !food_rep(philo))
	{
		pthread_mutex_lock(&philo->table->check);
		if (!philo->table->stop)
		{
			pthread_mutex_unlock(&philo->table->check);
			return NULL;
		}
		pthread_mutex_unlock(&philo->table->check);
		ft_eat(philo);
		ft_think(philo);
		ft_sleep(philo);
	}
	return (NULL);
}
