/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncastell <ncastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:48:44 by mmonpeat          #+#    #+#             */
/*   Updated: 2023/07/13 12:51:36 by ncastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!(unsigned char)c)
		return ((char *)s + ft_strlen(s));
	while (*((unsigned char *)s) != '\0')
	{
		if (*((unsigned char *)s) == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}
