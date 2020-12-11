/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:38:20 by aes-salm          #+#    #+#             */
/*   Updated: 2020/12/11 13:24:40 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SQUARE 512
# define BUFFER_SIZE 2048

# define PI 3.14159265358979323846
# define FOV_ANGLE 60 * (PI / 180)
# define DEG(a)	((float)((a) * 180) / PI)

# define INT_MAX 2147483647

# define W 13
# define S 1
# define A 0
# define D 2
# define ESC 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123

typedef struct			s_struct
{
	void				*window_id;
	void				*connection_id;

	void				*image;
	int					*img_matrix;

	void				*image_td;
	int					*img_matrix_td;

	int					bits_per_pixel;
	int					size_line;
	int					endian;

	float				px;
	float				py;
	float				walk_direction;
	float				move_speed;
	float				turn_direction;
	float				turn_speed;
	float				rotation;
	float				rotation_speed;
	float				side;

}						t_struct;

typedef struct			s_rays
{
	float				ray_angle;
	float				wall_hit_x;
	float				wall_hit_y;
	float				wall_distance;
	int					was_hit_vertical;
	int					ray_facing_up;
	int					ray_facing_down;
	int					ray_facing_r;
	int					ray_facing_l;
}						t_rays;

typedef struct			s_tr_project
{
	float				real_distance;
	float				distance_project_plane;
	float				project_wall_height;
	int					wall_top_pixel;
	int					wall_bottom_pixel;
}						t_tr_project;

typedef struct			s_texture
{
	void				*img;
	char				*path;
	int					*colors;
	int					width;
	int					height;
	int					a;
	int					b;
	int					c;

	int					color;
	int					*wall;
}						t_texture;

typedef struct			s_sprite
{
	float				x;
	float				y;
	float				distance;
	float				angle;
	float				scale;
	float				offset_x;
	float				offset_y;
}						t_sprites;

typedef struct			s_file
{
	int					i;
	int					num_rows;
	int					num_cols;

	int					window_heigth;
	int					window_width;

	int					window_w_td;
	int					window_h_td;

	char				no_texture[200];
	char				so_texture[200];
	char				we_texture[200];
	char				ea_texture[200];
	char				sprite_texture[200];
	int					number_of_sprites;

	int					floor_color;
	int					sky_color;

	char				**map;
	int					map_tour;
	int					row;

	float				px;
	float				py;
	float				player_view;
	int					player_found;
	int					save_flag;

	int					r;
	int					g;
	int					b;

	int					max_int;
}						t_file;

typedef struct			s_rays_norm
{
	float				xinter_cept;
	float				yinter_cept;
	float				xstep;
	float				ystep;

	float				next_horz_x;
	float				next_horz_y;
	int					found_horz_wall;
	float				wall_horz_hit_x;
	float				wall_horz_hit_y;
	float				horz_hit_distance;

	float				next_vert_x;
	float				next_vert_y;
	int					found_vert_wall;
	float				wall_vert_hit_x;
	float				wall_vert_hit_y;
	float				vert_hit_distance;

}						t_rays_norm;

typedef struct			s_norm
{
	int					s_rx;
	int					s_ry;

	int					tx;
	int					tx_offset_x;
	int					tx_offset_y;
	float				tx_distance_ft;

	int					rows;
	int					cols;

	int					x;
	int					y;
}						t_norm;

typedef struct			s_bitmap
{
	uint16_t			bit_per_pxl;
	int					width_in_pxl;
	uint32_t			info_header_size;
	uint32_t			image_size;
	uint32_t			bf_off_bits;
	uint32_t			file_size;
	uint16_t			biplanes;
	unsigned char		*buf;
	int					fd;
	int					row;
	int					col;
}						t_bitmap;

typedef struct			s_rgb
{
	int					r;
	int					g;
	int					b;
}						t_rgb;

t_struct				g_data;
t_rays					*g_rays;
t_tr_project			g_tr_project;
t_texture				g_texture[5];
t_sprites				*g_sprites;
t_file					g_file;
t_rays_norm				g_rnorm;
t_norm					g_norm;
t_bitmap				g_bitmap;

void					draw_map(t_struct *data);
void					draw_player(void);
void					draw_rays(void);
void					horizontal_wall_hint_find(int colume_id);
void					vertical_wall_hint_find(int colume_id);
int						update(void);
int						keypress(int keycode);
int						keyrelease(int keycode);
int						wall_check(float x, float y);
int						sprite_check(float x, float y);
float					distance_between_points(float x1, float y1,
							float x2, float y2);
float					normalize_angle(float angle);
void					draw_td_project(void);
void					draw_sprites(void);

void					args_check(int argc, char **argv);
void					file_handle();
void					file_components_check();
void					handle_resolution(char *text);
void					handle_texture_path(char *text);
void					handle_floor_sky_color(char *text);
void					handle_map(char *line, int row);
void					handle_map_error(void);
void					init_sprites();
float					normalize_sprite(float angle);
void					create_bmp_file();

int						my_atoi(const char *str);
char					*convert_to_hexa(unsigned long decimal, char c);
char					*ft_strdup(const char *str);
char					*ft_strrev(char *str);
char					*ft_strjoin(const char *s1, const char *s2);
void					*ft_memset(void *str, int c, size_t n);
char					*ft_strnstr(const char *str, const char *chr,
							size_t len);
char					*ft_strrchr(const char *str, int c);
int						ft_strncmp(const char *str1, const char *str2,
							size_t n);
int						ft_strcmp(char *s1, char *s2);
void					ft_putnbr(int n);
size_t					ft_strlen(const char *str);
void					*ft_memcpy(void *dest, const void *src, size_t n);

int						get_next_line(int fd, char **line);
size_t					get_strlen(const char *str);
char					*get_strdup(const char *str);
char					*get_substr(char const *s, unsigned int start,
							size_t len);
char					*get_strjoin(char **line, char *tmp);
void					free_all(char **tmp);

void					exit_cub(int status);
void					print_errors(char *message);
int						destroy_window_button();

#endif
