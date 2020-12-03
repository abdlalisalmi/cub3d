# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 22:27:33 by aes-salm          #+#    #+#              #
#    Updated: 2020/12/03 11:36:06 by aes-salm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d.out
AR = ar
LIBS = -l mlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Werror -Wextra
SRC = *.c src/ft/*.c src/file_handle/*.c src/utils/*.c src/draw/*.c

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
	./Cub3d.out MAP.cub
save:
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS)
	./Cub3d.out MAP.cub --save
de:
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS) -g
s:
	@ $(CC) $(FLAGS) $(SRC) -o $(NAME) $(LIBS) -fsanitize=address -g3
	./Cub3d.out MAP.cub
	
# gcc *.c -L/usr/local/lib -l mlx /usr/local/lib/libmlx.a -lXext -lX11 -lm