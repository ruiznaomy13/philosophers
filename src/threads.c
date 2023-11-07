/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:34:53 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/07 23:23:00 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int check_if_stop(t_table *table)
{
	int ret;

	pthread_mutex_lock(&table->m_stop);
	ret = table->stop;
	pthread_mutex_unlock(&table->m_stop);
	return ret;
}

void	check_philos(t_table *table)
{
	int	i;

	while (!check_if_stop(table))
	{
		i = -1;
		while (++i < table->p_amount)
		{
			if (all_eat(table))
			{
				pthread_mutex_lock(&table->m_stop);
				table->stop = 1;
				pthread_mutex_unlock(&table->m_stop);
				pthread_mutex_lock(&table->msj);
				printf(GREEN" 🍴🍝 ALL PHILOSOPHERS FINISHED EATING 🍝🍴\n");
				pthread_mutex_unlock(&table->msj);
				ft_free(table);
				break;
			}
			else if (ft_dead(&table->philo[i]))
			{
				pthread_mutex_lock(&table->m_stop);
				table->stop = 1;
				pthread_mutex_unlock(&table->m_stop);
				pthread_mutex_lock(&table->msj);
				printf(RED" ❌ PHILOSOPHER %d DIED at %ldms. ❌\n", table->philo[i].id, diff_time(table->t_start, get_time()));
				pthread_mutex_unlock(&table->msj);
				ft_free(table);
				break;
			}
		}
	}
}

void    print_msj(t_philo *philo, char *msj)
{
	pthread_mutex_lock(&philo->table->msj);
	if (!check_if_stop(philo->table))
		printf("%ld\t%d\t%s\n", diff_time(philo->table->t_start, get_time()), philo->id, msj);
	pthread_mutex_unlock(&philo->table->msj);
}

int create_threads(t_table *table)
{
	int i;

	i = -1;
	while (++i < table->p_amount)
	{
		if (pthread_create(&table->philo[i].th_id, NULL, ft_routine, &table->philo[i]) != 0)
			return (-1);
	}
	check_philos(table);
	i = -1;
	while (++i < table->p_amount)
		pthread_join(table->philo[i].th_id, NULL);
	return (0);
}