/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:07:36 by ncastell          #+#    #+#             */
/*   Updated: 2023/10/06 13:19:19 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/philo.h"

int error_msj(int error)
{
    if (error == 1)
        printf("Invaliud number of arguments\n");
    if (error == 2)
        printf("Invalid number on argument %d\n", error - 1);
    return (-1);
}

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
			if ((s[i] == '-' || s[i] == '+') && ft_isdigit(s[i + 1]) == 1 \
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

int arg_checker(int ac, char **av)
{
    int checker;
    int i;

    i = 0;
    checker = 0;
    if (ac < 5)
        checker = error_msj(1);
    while (++i < ac)
    {
        if (!check_nums(av[i]))
            error_msj(i + 1);
    }
    return (checker);
}
