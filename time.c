#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include <sys/time.h>

long diff_time(long start_time, long end_time)
{
    return (end_time - start_time);
}

long int	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	t = get_time();
	while (8)
	{
		usleep(100);
		if ((get_time() - t) >= time)
			break ;
	}
}

int main()
{
	long	start_time;
	long	end_time;

    start_time = get_time();
	ft_usleep(5000);
    end_time = get_time();

    long time_difference = diff_time(start_time, end_time);
    printf("Diferencia de tiempo: %ld milisegundos\n", time_difference);

}
