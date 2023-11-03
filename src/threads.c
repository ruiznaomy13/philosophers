/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:34:53 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/03 20:49:47 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	check_philos(t_table *table)
{
	int	i;
	int	j;

	while (table->stop == 0)
	{
		i = -1;
		j = -1;
		while (++i < table->p_amount && !ft_dead(&table->philo[i]))
			;
		while (++j < table->p_amount && table->philo[j].finish)
			;
		if (i != table->p_amount || j == table->p_amount)
		{
			pthread_mutex_lock(&table->check);
			table->stop = 1;
			pthread_mutex_unlock(&table->check);
		}
	}
}

void    print_msj(t_philo *philo, char *msj)
{
	pthread_mutex_lock(&philo->table->msj);
	printf(WHITE" %05ld   %d   %s\n", diff_time(philo->table->t_start, get_time()), philo->id, msj);
	pthread_mutex_unlock(&philo->table->msj);
}

int create_threads(t_table *table)
{
    int i;

    i = -1;
    // pthread_mutex_lock(&table->updt);
    while (++i < table->p_amount)
    {
        if (pthread_create(&table->philo[i].th_id, NULL, ft_routine, &table->philo[i]) != 0)
            return (-1);
    }
	check_philos(table);
	pthread_mutex_lock(&table->check);
	if (table->stop)
	{
		pthread_mutex_unlock(&table->check);
		return (1);
	}
	pthread_mutex_unlock(&table->check);
    i = -1;
    while (++i < table->p_amount)
        pthread_join(table->philo[i].th_id, NULL);
    // pthread_mutex_unlock(&table->updt);
    return (0);
}