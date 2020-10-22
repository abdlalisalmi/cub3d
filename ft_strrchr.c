/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:21:16 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/22 12:21:38 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strrchr(const char *str, int c)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == (unsigned char)c)
			return ((char*)(str + i));
		i--;
	}
	return (NULL);
}