/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:14:13 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 09:02:08 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

char	*ft_strnstr(const char *str, const char *chr, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (chr[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		if (str[i] == chr[0])
		{
			j = 0;
			while (str[i + j] == chr[j] && i + j < len)
			{
				if (chr[j + 1] == '\0')
					return ((char*)str + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}