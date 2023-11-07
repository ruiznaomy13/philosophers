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
	pthread_mutex_lock(&p->table->food_count);
	if (p->n_food == p->table->rep_eat && p->table->rep_eat)
	{
		pthread_mutex_unlock(&p->table->food_count);
		// pthread_mutex_lock(&p->table->end);
		p->finish = 1;
		// pthread_mutex_unlock(&p->table->end);
		return (1);
	}
	pthread_mutex_unlock(&p->table->food_count);
	return (0);
}

void updt_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->updt);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->updt);
}

long int	get_last_eat(t_philo *philo)
{
	long int	ret;

	pthread_mutex_lock(&philo->table->updt);
	ret = philo->last_eat;
	pthread_mutex_unlock(&philo->table->updt);

	return(ret);
}

int	ft_eat(t_philo *philo)
{
	if (check_if_stop(philo->table))
		return (1);
	pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	// pthread_mutex_lock(&philo->table->msj);
	// printf(BLUE"%d Ha cogido el tenedor derecho = %d\n", philo->id, philo->id - 1);
	// pthread_mutex_unlock(&philo->table->msj);
	print_msj(philo, "has taken right fork");
	if (philo->table->p_amount == 1)
			pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	print_msj(philo, "has taken left fork");
	// pthread_mutex_lock(&philo->table->msj);
	// printf(BLUE"%d Ha cogido el tenedor izquierdo = %d\n",philo->id, philo->id % philo->table->p_amount);
	// pthread_mutex_unlock(&philo->table->msj);

    print_msj(philo, "is eating");
	// pthread_mutex_lock(&philo->table->updt);
	updt_last_eat(philo);
	// pthread_mutex_unlock(&philo->table->updt);
	ft_usleep(philo->table->t_eat);
	pthread_mutex_lock(&philo->table->food_count);
	philo->n_food++;
	pthread_mutex_unlock(&philo->table->food_count);
    pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
    print_msj(philo, "has put down right fork");
    pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
    print_msj(philo, "has put down left fork");
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (check_if_stop(philo->table))
		return (1);
	print_msj(philo, "is sleeping");
    ft_usleep(philo->table->t_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (check_if_stop(philo->table))
		return (1);
	print_msj(philo, "is thinking");
	return (0);
}

int	ft_dead(t_philo *philo)
{
	long int	time;
	
	pthread_mutex_lock(&philo->table->updt);
	time = get_time() - philo->last_eat;
	pthread_mutex_unlock(&philo->table->updt);
	if (time > philo->table->t_die || philo->finish)
	{
		// if (!philo->finish)
		// 	print_msj(philo,  "died");
		return (1);
	}
	return (0);
}
