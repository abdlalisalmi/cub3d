# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 22:27:33 by aes-salm          #+#    #+#              #
#    Updated: 2020/12/08 17:04:30 by aes-salm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
AR = ar
LIBS = -l mlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Werror -Wextra
SRC = 	main.c \
		src/draw/create_bmp_file.c src/draw/draw_map.c src/draw/draw_player.c \
		src/draw/draw_rays.c src/draw/draw_rays_utils.c src/draw/draw_sprites.c \
		src/draw/draw_td_project.c src/draw/init_sprites.c \
		src/file_handle/file_components_check.c src/file_handle/file_handle.c \
		src/file_handle/handle_floor_sky_color.c src/file_handle/handle_map.c \
		src/file_handle/handle_map_error.c src/file_handle/handle_resolution.c \
		src/file_handle/handle_texture_path.c \
		src/ft/ft_memcpy.c src/ft/ft_memset.c src/ft/ft_putnbr.c src/ft/ft_strcmp.c \
		src/ft/ft_strdup.c src/ft/ft_strjoin.c src/ft/ft_strlen.c src/ft/ft_strncmp.c \
		src/ft/ft_strnstr.c src/ft/ft_strrchr.c src/ft/ft_strrev.c \
		src/utils/args_check.c src/utils/convert_to_hexa.c src/utils/cub3d_functions.c \
		src/utils/events.c src/utils/exit_cub.c src/utils/get_next_line.c \
		src/utils/get_next_line_utils.c src/utils/print_errors.c src/utils/update.c


all:$(NAME)

$(NAME):
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS)

clean:
	@ rm -rf *.o

fclean: clean
	@ rm -rf $(NAME)
	
re:fclean all


run:
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS)
	./cub3D MAP.cub
save:
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS) -g
	./cub3D MAP.cub --save
norm:
	norminette main.c cub3d.h src/draw/*.c src/file_handle/*.c src/ft/*.c src/utils/*.c