/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:38:28 by ncastell          #+#    #+#             */
/*   updtd: 2023/10/30 17:26:23 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	ft_eat(t_philo *philo)
{
	if ((philo->id % 2) == 0)
		usleep(philo->table->t_eat * 10);
	pthread_mutex_lock(&philo->table->updt);

    pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
    print_msj(philo, "has taken right fork");
	pthread_mutex_lock(&philo->table->forks[philo->id % philo->table->p_amount]);
    print_msj(philo, "has taken left fork");

    print_msj(philo, "is eating");
	philo->last_eat = get_time();
	ft_usleep(philo, philo->table->t_eat)
	// usleep(philo->table->t_eat * 1000);

    pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
    print_msj(philo, "has put down right fork");
    pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->p_amount]);
    print_msj(philo, "has put down left fork");

    pthread_mutex_unlock(&philo->table->updt);
}

void	ft_sleep(t_philo *philo)
{
	print_msj(philo, "is sleeping");
    usleep(philo->table->t_sleep);
}

void	ft_think(t_philo *philo)
{
	print_msj(philo, "is thinking");
	usleep(philo->table->t_eat);
}

int	ft_dead(t_philo *philo, int i)
{
	long int	time;
	
	pthread_mutex_lock(&philo->table->updt);
	time = get_time() - philo->last_eat;
	if (time > philo->table->t_die)
	{
		pthread_mutex_lock(&philo->table->waiter);
		philo->dead = 1;
		pthread_mutex_unlock(&philo->table->waiter);
		if (i == 1)
			print_msj(philo, "died");
		pthread_mutex_unlock(&philo->table->updt);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->updt);	
	return (0);
}
