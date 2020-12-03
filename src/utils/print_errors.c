/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 10:31:54 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/03 10:36:02 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	print_errors(char *message)
{
	write(1, "Error:\n", 7);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}