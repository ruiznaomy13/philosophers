/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:00 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/27 21:44:28 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_table t_table;

typedef struct s_philo
{
    pthread_t   th_id;
    int     	id;
    int     	left_f;
    int			right_f;
    // int         num_eats;
    // int         dead;
    t_table     *table;
}               t_philo;

struct s_table
{
    long int        t_die;
    long int        t_eat;
    long int        t_sleep;
    int             rep_eat;
    int             p_amount;
	long int		t_start;
    pthread_mutex_t *forks;
    pthread_mutex_t updt;
	pthread_mutex_t	msj;
    t_philo         *philo;
};

/* Threads */
void        *ft_routine(void *arg);
int         create_threads(t_table *table);
void        print_msj(t_philo *philo, char *msj);

/* Checkers */
int         error_msj(int error);
int         arg_checker(int ac, char **av);
int	        check_nums(char *s);

/* Inicializers */
int         init(char **av, t_table *table);
int         start_philos(t_table *table);

/* Utils */
long int	get_time(void);
int	        ft_isdigit(int i);
long int    ft_atol(const char *str);
void	    *ft_calloc(size_t count, size_t size);

/* Routine */
void		ft_eat(t_philo *philo);
#endif