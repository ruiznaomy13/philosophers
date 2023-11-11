/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 20:34:53 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/11 13:13:52 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->updt);
	while (++i < table->p_amount)
	{
		if (pthread_create(&table->philo[i].th_id, NULL, \
			ft_routine, &table->philo[i]) != 0)
			return (-1);
	}
	pthread_mutex_unlock(&table->updt);
	check_philos(table);
	i = 0;
	while (i < table->p_amount)
		pthread_join(table->philo[i++].th_id, NULL);
	return (0);
}

void	stop_prog(t_table *table, int i, int type)
{
	if (!type)
		return ;
	pthread_mutex_lock(&table->m_stop);
	table->stop = 1;
	pthread_mutex_unlock(&table->m_stop);
	pthread_mutex_lock(&table->msj);
	if (type == 1)
		printf(GREEN" 🍴🍝 ALL PHILOSOPHERS FINISHED EATING 🍝🍴\n");
	else if (type == 2)
		printf(RED" ❌ PHILOSOPHER %d DIED at %ldms. ❌\n", table->philo[i].id, \
		diff_time(table->t_start, get_time()));
	pthread_mutex_unlock(&table->msj);
	ft_free(table);
}

void	check_philos(t_table *table)
{
	int	i;

	while (!check_if_stop(table))
	{
		i = -1;
		while (++i < table->p_amount)
		{
			if (all_eat(table))
			{
				stop_prog(table, i, 1);
				break ;
			}
			else if (ft_dead(&table->philo[i]))
			{
				stop_prog(table, i, 2);
				break ;
			}
		}
	}
}

void	print_msj(t_philo *philo, char *msj)
{
	pthread_mutex_lock(&philo->table->msj);
	if (!check_if_stop(philo->table))
		printf(WHITE"[%ld]\t%d\t%s\n", diff_time(philo->table->t_start, \
		get_time()), philo->id, msj);
	pthread_mutex_unlock(&philo->table->msj);
}

int	check_if_stop(t_table *table)
{
	int	ret;

	pthread_mutex_lock(&table->m_stop);
	ret = table->stop;
	pthread_mutex_unlock(&table->m_stop);
	return (ret);
}
