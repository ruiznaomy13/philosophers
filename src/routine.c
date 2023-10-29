/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:38:28 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/29 02:17:50 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	ft_eat(t_philo *philo)
{
	if ((philo->id % 2) != 0)
		usleep(philo->table->t_eat * 10);
	pthread_mutex_lock(&philo->table->updt);

    pthread_mutex_lock(&philo->table->forks[philo->id]);
    print_msj(philo, "has taken left fork");
	pthread_mutex_lock(&philo->table->forks[(philo->id - 1) % philo->table->p_amount]);
    print_msj(philo, "has taken right fork");

    print_msj(philo, "is eating");
	philo->last_eat = get_time();

    pthread_mutex_unlock(&philo->table->forks[philo->id]);
    print_msj(philo, "has put down left fork");
    pthread_mutex_unlock(&philo->table->forks[(philo->id - 1) % philo->table->p_amount]);
    print_msj(philo, "has put down right fork");
	
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

int	ft_dead(t_philo *philo)
{
	long int	current_time;

	current_time = get_time();
	if ((current_time - philo->last_eat) > philo->table->t_die)
		return (1);
	return (0);
}
