# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 22:27:33 by aes-salm          #+#    #+#              #
#    Updated: 2020/10/22 13:59:20 by aes-salm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= cub3d.a

SRC= main.c \
	draw_map.c \

all: $(NAME)

$(NAME) : $(SRC)
	@gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit -c $(SRC)
	@ar rc $(NAME) *.o

clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME)

re: fclean all

run:
	gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit *.c
	./a.out map.cub
de:
	gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit *.c -g
s:
	gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit *.c -fsanitize=address -g3
# gcc *.c -L/usr/local/lib -l mlx /usr/local/lib/libmlx.a -lXext -lX11 -lm