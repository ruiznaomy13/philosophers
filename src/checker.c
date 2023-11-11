/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:20:39 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/10 23:33:21 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	check_nums(char *s)
{
	int	i;

	i = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (ft_isdigit(s[i]) == 0)
		{
			if (s[i] == '+' && ft_isdigit(s[i + 1]) == 1 \
			&& !ft_isdigit(s[i - 1]))
				i++;
			else
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	ft_dead(t_philo *philo)
{
	long int	time;

	pthread_mutex_lock(&philo->table->updt);
	time = get_time() - philo->last_eat;
	pthread_mutex_unlock(&philo->table->updt);
	if (time > philo->table->t_die)
		return (1);
	return (0);
}

int	all_eat(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->p_amount)
	{
		if (!food_rep(&table->philo[i]))
			return (0);
	}
	return (1);
}

int	food_rep(t_philo *p)
{
	pthread_mutex_lock(&p->table->food_count);
	if (p->table->rep_eat && p->n_food == p->table->rep_eat)
	{
		pthread_mutex_unlock(&p->table->food_count);
		return (1);
	}
	pthread_mutex_unlock(&p->table->food_count);
	return (0);
}

int	arg_checker(int ac, char **av)
{
	int	checker;
	int	i;

	i = 0;
	checker = 0;
	if (ac < 5 || ac > 6)
		checker = error_msj(1, 0);
	while (++i < ac)
	{
		if (!check_nums(av[i]))
			checker = error_msj(2, i);
	}
	return (checker);
}
