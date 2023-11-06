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

int	food_rep(t_philo *p)
{
	if (p->n_food == p->table->rep_eat && p->table->rep_eat)
	{
		// pthread_mutex_lock(&p->table->end);
		p->finish = 1;
		// pthread_mutex_unlock(&p->table->end);
		return (1);
	}
	return (0);
}

int	ft_eat(t_philo *philo)
{
	if (philo->table->stop)
		return (1);
	pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
	// pthread_mutex_lock(&philo->table->msj);
	// printf(BLUE"%d Ha cogido el tenedor derecho = %d\n", philo->id, philo->id - 1);
	// pthread_mutex_unlock(&philo->table->msj);
	print_msj(philo, "has taken right fork");
	pthread_mutex_lock(&philo->table->forks[philo->id % philo->table->p_amount]);
	print_msj(philo, "has taken left fork");
	// pthread_mutex_lock(&philo->table->msj);
	// printf(BLUE"%d Ha cogido el tenedor izquierdo = %d\n",philo->id, philo->id % philo->table->p_amount);
	// pthread_mutex_unlock(&philo->table->msj);

    print_msj(philo, "is eating");
	philo->last_eat = get_time();
	ft_usleep(philo->table->t_eat);
	philo->n_food++;

    pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
    print_msj(philo, "has put down right fork");
    pthread_mutex_unlock(&philo->table->forks[philo->id % philo->table->p_amount]);
    print_msj(philo, "has put down left fork");
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (philo->table->stop)
		return (1);
	print_msj(philo, "is sleeping");
    ft_usleep(philo->table->t_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (philo->table->stop)
		return (1);
	print_msj(philo, "is thinking");
	return (0);
}

int	ft_dead(t_philo *philo)
{
	long int	time;
	
	// pthread_mutex_lock(&philo->table->updt);
	time = get_time() - philo->last_eat;
	if (time > philo->table->t_die || philo->finish)
	{
		// pthread_mutex_lock(&philo->table->end);
		philo->dead = 1;
		// pthread_mutex_unlock(&philo->table->end);
		if (!philo->finish)
			print_msj(philo,  "died");
		// pthread_mutex_unlock(&philo->table->updt);
		return (1);
	}
	// pthread_mutex_unlock(&philo->table->updt);
	return (0);
}
