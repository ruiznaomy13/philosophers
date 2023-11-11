/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:38:28 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/11 12:20:09 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
		ft_usleep(philo->table->t_eat);
	while (!check_if_stop(philo->table) || food_rep(philo))
	{
		if (ft_eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (ft_think(philo))
			break ;
	}
	return (NULL);
}

int	ft_eat(t_philo *philo)
{
	if (check_if_stop(philo->table) || food_rep(philo))
		return (1);
	pthread_mutex_lock(&philo->table->forks[philo->r_fork]);
	print_msj(philo, CYAN"⬆ right fork 🍴");
	pthread_mutex_lock(&philo->table->forks[philo->l_fork]);
	print_msj(philo, CYAN"⬆ left fork 🍴");
	print_msj(philo, YELLOW"is eating 🍝");
	updt_last_eat(philo);
	ft_usleep(philo->table->t_eat);
	pthread_mutex_lock(&philo->table->food_count);
	philo->n_food++;
	pthread_mutex_unlock(&philo->table->forks[philo->r_fork]);
	print_msj(philo, CYAN"⬇ right fork 🍴");
	pthread_mutex_unlock(&philo->table->forks[philo->l_fork]);
	print_msj(philo, CYAN"⬇ left fork 🍴");
	pthread_mutex_unlock(&philo->table->food_count);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (check_if_stop(philo->table) || food_rep(philo))
		return (1);
	print_msj(philo, GREEN"is sleeping 🌙");
	ft_usleep(philo->table->t_sleep);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (check_if_stop(philo->table) || food_rep(philo))
		return (1);
	print_msj(philo, MAGENTA"is thinking 💭");
	return (0);
}

void	updt_last_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->updt);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->table->updt);
}
