/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:57:49 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/14 16:04:37 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int main(int ac, char **av)
{
    t_table table;
    if (arg_checker(ac, av) < 0)
        return (0);
    init(av, &table);
    create_threads(&table);
}

void    print_msj(t_philo *philo, char *msj)
{
    pthread_mutex_lock(&philo->table->msj);
    printf("%d %s\n", philo->id, msj);
    pthread_mutex_unlock(&philo->table->msj);
}


void *ft_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1) {
        print_msj(philo, "is thinking");
        usleep(philo->table->t_eat);

        ft_eat(philo);

        print_msj(philo, "is sleeping");
        usleep(philo->table->t_sleep);
    }

    return NULL;
}

//mutex de los procesos de los tenedores
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->updt);
    pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
    print_msj(philo, "has taken left fork");
    while (pthread_mutex_trylock(&philo->table->forks[philo->id]) != 0)
        pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
    print_msj(philo, "has taken right fork");
    print_msj(philo, "is eating");
    pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
    print_msj(philo, "has put down left fork");
    pthread_mutex_unlock(&philo->table->forks[philo->id]);
    print_msj(philo, "has put down right fork");
    pthread_mutex_unlock(&philo->table->updt);
}

int create_threads(t_table *table)
{
    int i;

    i = -1;
    // pthread_mutex_lock(&table->updt);
    while (++i < table->p_amount)
    {
        table->philo[i].id = i + 1;
        if (pthread_create(&table->philo[i].th_id, NULL, ft_routine, &table->philo[i]) != 0)
            return (-1);
    }
    i = -1;
    while (++i < table->p_amount)
        pthread_join(table->philo[i].th_id, NULL);
    // pthread_mutex_unlock(&table->updt);
    return (0);
}
