/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 22:27:29 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/14 14:27:20 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int start_philos(t_table *table)
{
    int i;

    i = -1;
    table->philo = (t_philo *)malloc(sizeof(t_philo) * (table->p_amount + 1));
    if (!table->philo)
        return (-1);
    while (++i < table->p_amount)
    {
        table->philo[i].table = table;
        table->philo[i].id = i + 1;
        pthread_mutex_init(&table->philo[i].left_f, NULL);
    }
    return (0);
}

int init(char **av, t_table *table)
{
    int i;

    i = 0;
    table->p_amount = ft_atol(av[1]);
    table->t_die = ft_atol(av[2]);
    table->t_eat = ft_atol(av[3]);
    table->t_sleep = ft_atol(av[4]);
    if (av[5])
        table->rep_eat = ft_atol(av[5]);

    // Inicializa el array de mutexes para los tenedores
    table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->p_amount);
    if (!table->forks)
        return (-1);

    start_philos(table);

    // Asigna los mutexes de los tenedores a los filósofos
    for (i = 0; i < table->p_amount; i++) {
        // pthread_mutex_init(&table->philo[i].left_f, NULL);
        pthread_mutex_init(&table->forks[i], NULL); // Inicializa el tenedor actual
        table->philo[i].right_f = &table->forks[(i + 1) % table->p_amount];  // Asigna el tenedor derecho
    }
    return (0);
}

