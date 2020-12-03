/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 14:54:13 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/03 10:02:56 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		file_extention_check(char *filename, char *ext, char split)
{
	char *ptr;

	if ((ptr = ft_strrchr(filename, split)) != NULL)
	{
		if (ft_strncmp(ptr, ext, ft_strlen(filename)) == 0)
			return (1);
	}
	return (0);
}

int		flag_check(char *flag)
{
	if (ft_strcmp(flag, "--save") == 0)
		return (1);
	return (0);
}

void	args_check(int argc, char **argv)
{
	if (argc < 2 || argc > 3)
	{
		write(1, "Error\nYou have more than 3", 26);
		write(1, " parameters or less than 1 !!\n", 30);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (!file_extention_check(argv[1], ".cub", '.'))
		{
			write(1, "Error\nYou have to add a file '.cub' as argument\n", 54);
			exit(EXIT_FAILURE);
		}
		if (argc == 3 && flag_check(argv[2]))
			g_file.save_flag = 1;
		else if (argc == 3 && !flag_check(argv[2]))
		{
			write(1, "Error\nEnter a valid flag like --save !!\n", 52);
			exit_cub(EXIT_FAILURE);
		}
	}
}
