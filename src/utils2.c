// void	ft_free(t_table *table)
// {
// 	int	i;

// 	free(table->philo);
// 	i = -1;
// 	while (++i < table->p_amount)//destruim totes les forks
// 		pthread_mutex_destroy(&table->forks[i]);//totes les variables pthread_mutex_t deven 
// 	pthread_mutex_destroy(&table->msj);
// 	pthread_mutex_destroy(&table->updt);
// 	pthread_mutex_destroy(&table->end);
// 	free(table->forks);
// }