/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 10:36:41 by aes-salm          #+#    #+#             */
/*   Updated: 2020/10/21 10:05:27 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char			*pstr;
	unsigned int	i;

	pstr = str;
	i = 0;
	while (i < n - 1)
	{
		pstr[i] = c;
		i++;
	}
	pstr[i] = '\0';
	return (pstr);
}