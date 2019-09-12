# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/09/12 19:50:02 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = lem-in.a

NAME = lem-in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a 
VISUAL = ./vizualizer

INCLUDES = -I ./libft -I ./libft/ft_printf/ -I ./includes

SRC = lem_in.c hash_func.c validation/validate_coords.c validation/find_and_connect_rooms.c bfs.c find_shortest_path.c \
		validation/isint.c validation/validation.c validation/validate_rooms.c validation/write_data_in_sroom.c validation/validate_links.c validation/validate_ants.c \
		helpful_func.c validation/work_with_data.c bellman_ford.c run_ants.c \

OBJ = $(SRC:.c=.o)

CCFL = -Wall -Wextra -Werror

.PHONY: all clean fclean re

all: $(ARCHIVE) $(NAME)

$(ARCHIVE): $(OBJ)
	@make -C $(LIB)
	@make -C $(VISUAL)
	@ar rc $(ARCHIVE) $(OBJ)
	@ranlib $(ARCHIVE)

%.o: %.c $(INCLUDES)
	@gcc -Wall -Wextra -Werror -c $<

$(NAME): $(OBJ)
	@gcc -Wall -Wextra -Werror -o $(NAME) $(SRC) $(LIB_A) $(SDL) -g

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@rm -f $(OBJ)
	@rm -f visual

fclean: clean
	@make fclean -C $(LIB)

re: fclean all
