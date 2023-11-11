/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:15:00 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/10 23:32:26 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

/* COLORS */
# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define WHITE		"\e[1;37m"
# define CYAN		"\x1b[36m"
# define MAGENTA	"\033[95m"

typedef struct s_table	t_table;

typedef struct s_philo
{
	pthread_t	th_id;
	int			id;
	int			left_f;
	int			right_f;
	long int	last_eat;
	int			n_food;
	int			finish;
	int			dead;
	int			l_fork;
	int			r_fork;
	t_table		*table;
}	t_philo;

struct s_table
{
	long int		t_die;
	long int		t_eat;
	long int		t_sleep;
	int				rep_eat;
	int				p_amount;
	int				stop;
	long int		t_start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	msj;
	pthread_mutex_t	updt;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	food_count;
	t_philo			*philo;
};

/* Checkers */
int		check_nums(char *s);
int		food_rep(t_philo *p);
int		ft_dead(t_philo *philo);
int		all_eat(t_table *table);
int		arg_checker(int ac, char **av);

/* Utils */
long	get_time(void);
int		ft_isdigit(int i);
void	ft_usleep(long time);
long	ft_atol(const char *str);
long	diff_time(long start_time, long end_time);

/* Routine */
void	*ft_routine(void *arg);
int		ft_eat(t_philo *philo);
int		ft_sleep(t_philo *philo);
int		ft_think(t_philo *philo);
void	updt_last_eat(t_philo *philo);

/* Threads */
void	check_philos(t_table *table);
int		check_if_stop(t_table *table);
int		create_threads(t_table *table);
void	print_msj(t_philo *philo, char *msj);
void	stop_prog(t_table *table, int i, int type);

/* Inits */
int		init_mutex(t_table *table);
int		start_philos(t_table *table);
int		error_msj(int error, int ac);
int		init_table(t_table *table, char **av);
void	ft_free(t_table *table);

#endif
