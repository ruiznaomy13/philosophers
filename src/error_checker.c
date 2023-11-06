/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 12:07:36 by ncastell          #+#    #+#             */
/*   Updated: 2023/11/06 20:55:59 by ncastell         ###   ########.fr       */
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

int error_msj(int error, int ac)
{
    if (error == 1)
        printf(RED" Invalid number of arguments \n");
    if (error == 2)
        printf(YELLOW" Invalid argument [%d] ⚠️ \n", ac);
    return (1);
}

int arg_checker(int ac, char **av)
{
    int checker;
    int i;

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
