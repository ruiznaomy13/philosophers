/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:27:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/10 23:55:39 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&table->msj, NULL) != 0 \
	|| pthread_mutex_init(&table->food_count, NULL) != 0 \
	|| pthread_mutex_init(&table->m_stop, NULL) != 0 \
	|| pthread_mutex_init(&table->updt, NULL) != 0)
		return (1);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* table->p_amount);
	if (!table->forks)
		return (1);
	while (++i < table->p_amount)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (1);
	}
	return (0);
}

int	start_philos(t_table *table)
{
	int	i;

	i = -1;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * (table->p_amount + 1));
	if (!table->philo)
		return (1);
	while (++i < table->p_amount)
	{
		table->philo[i].table = table;
		table->philo[i].id = i + 1;
		table->philo[i].dead = 0;
		table->philo[i].n_food = 0;
		table->philo[i].finish = 0;
		table->philo[i].dead = 0;
		table->philo[i].r_fork = i;
		table->philo[i].l_fork = (i + 1) % table->p_amount;
		table->philo[i].last_eat = table->t_start;
	}
	return (0);
}

int	init_table(t_table *table, char **av)
{
	table->p_amount = ft_atol(av[1]);
	table->t_die = ft_atol(av[2]);
	table->t_eat = ft_atol(av[3]);
	table->t_sleep = ft_atol(av[4]);
	table->rep_eat = 0;
	if (av[5])
		table->rep_eat = ft_atol(av[5]);
	table->t_start = 0;
	table->stop = 0;
	table->t_start = get_time();
	if (init_mutex(table))
		return (1);
	if (start_philos(table))
		return (1);
	return (0);
}

int	error_msj(int error, int ac)
{
	if (error == 1)
		printf(RED" Invalid number of arguments \n");
	if (error == 2)
		printf(YELLOW" Invalid argument [%d] ⚠️ \n", ac);
	return (1);
}

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
