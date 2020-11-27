# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 22:27:33 by aes-salm          #+#    #+#              #
#    Updated: 2020/11/26 20:54:56 by aes-salm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= cub3d.a

SRC= *.c src/ft/*.c src/file_handle/*.c src/utils/*.c src/draw/*.c

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
	gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit $(SRC)
	./a.out mohamed.cub
save:
	gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit $(SRC)
	./a.out map.cub --save
de:
	gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit $(SRC) -g
s:
	gcc -Wall -Werror -Wextra -l mlx -framework OpenGL -framework AppKit $(SRC) -fsanitize=address -g3
# gcc *.c -L/usr/local/lib -l mlx /usr/local/lib/libmlx.a -lXext -lX11 -lm