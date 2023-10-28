/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:34:53 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/28 20:39:57 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void    print_msj(t_philo *philo, char *msj)
{
    pthread_mutex_lock(&philo->table->msj);
    printf("%ld %d %s\n", diff_time(philo->table->t_start, get_time()), philo->id, msj);
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
    i = -1;
    while (++i < table->p_amount)
        pthread_join(table->philo[i].th_id, NULL);
    // pthread_mutex_unlock(&table->updt);
    return (0);
}