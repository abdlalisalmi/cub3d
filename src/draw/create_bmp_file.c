/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 11:10:48 by aes-salm          #+#    #+#             */
/*   Updated: 2020/11/25 09:01:06 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_rgb	*g_rgb;

void screenshot_error(char *message)
{
	write(1, "Error:\n", 8);
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	exit_cub(EXIT_FAILURE);
}

void color_converter(int hex_value)
{
	if (!(g_rgb = malloc(sizeof(t_rgb))))
		screenshot_error("failed to alloc the RGB colors !!");
	g_rgb->r = (hex_value / pow(2, 16));
	g_rgb->g = (hex_value / pow(2, 8));
	g_rgb->b = (hex_value);
}

void	screen_data(int x)
{
	int index;

	index = bitmap.row * file.window_w_td + bitmap.col;
	index = index < 0 ? index * (-1) : index;
	color_converter((uint32_t)data->img_matrix_td[index]);
	bitmap.buf[x * bitmap.width_in_pxl
		+ bitmap.col * 3 + 0] = g_rgb->b;
	bitmap.buf[x * bitmap.width_in_pxl
		+ bitmap.col * 3 + 1] = g_rgb->g;
	bitmap.buf[x * bitmap.width_in_pxl
		+ bitmap.col * 3 + 2] = g_rgb->r;
	free(g_rgb);
}

void	screen_init(unsigned char *header)
{
	bitmap.bit_per_pxl = 24;
	bitmap.width_in_pxl = ((file.window_w_td *
				bitmap.bit_per_pxl + 31) / 32) * 4;
	bitmap.image_size = bitmap.width_in_pxl * file.window_h_td;
	bitmap.info_header_size = 40;
	bitmap.bf_off_bits = 54;
	bitmap.file_size = 54 + bitmap.image_size;
	bitmap.biplanes = 1;
	ft_memcpy(header, "BM", 2);
	ft_memcpy(header + 2, &(bitmap.file_size), 4);
	ft_memcpy(header + 10, &(bitmap.bf_off_bits), 4);
	ft_memcpy(header + 14, &(bitmap.info_header_size), 4);
	ft_memcpy(header + 18, &(file.window_w_td), 4);
	ft_memcpy(header + 22, &(file.window_h_td), 4);
	ft_memcpy(header + 26, &(bitmap.biplanes), 2);
	ft_memcpy(header + 28, &(bitmap.bit_per_pxl), 2);
}

void create_bmp_file()
{
	int				x;
	const char		*file_name = "screenshot.bmp";
	const int		len = 54;
	unsigned char	header[len];

	ft_memset(header, 0, len);
	screen_init(header);
	if (!(bitmap.buf = malloc((bitmap.image_size))))
		screenshot_error("failed to alloc the BITMAP buffer !!");
	x = 0;
	bitmap.row = file.window_h_td - 1;
	while (bitmap.row-- >= 0)
	{
		bitmap.col = 0;
		while (bitmap.col++ < file.window_w_td)
			screen_data(x);
		x++;
	}
	bitmap.fd = open(file_name, O_WRONLY | O_CREAT);
	write(bitmap.fd, header, len);
	write(bitmap.fd, bitmap.buf, bitmap.image_size);
	close(bitmap.fd);
	free(bitmap.buf);
	if (file.save_flag == 2)
		exit_cub(EXIT_SUCCESS);
}