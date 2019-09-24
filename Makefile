# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhazelnu <vhazelnu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/16 11:34:51 by vhazelnu          #+#    #+#              #
#    Updated: 2019/09/24 19:18:40 by vhazelnu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARCHIVE = lem-in.a

NAME = lem-in

LIB = libft/ft_printf
LIB_A = libft/libft.a $(LIB)/libftprintf.a 
VISUAL = ./vizualizer

INCLUDES = -I ./libft -I ./libft/ft_printf/ -I ./includes

SRC = lem_in.c hash_func.c validation/validate_coords.c validation/find_and_connect_rooms.c bfs.c bellman_ford.c run_ants.c find_shortest_path.c delete_dup_rooms.c print_graph.c \
		validation/isint.c validation/validation.c validation/validate_rooms.c validation/write_data_in_sroom.c validation/validate_links.c validation/validate_ants.c \
		validation/work_with_data.c qsort.c work_with_path.c push_ants_from_start.c push_ants_to_end.c create_paths_new.c create_dup_rooms.c reverse_edges.c \

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
	@gcc -Wall -Wextra -Werror -o $(NAME) $(ARCHIVE) $(LIB_A) -g

clean:
	@make clean -C $(LIB)
	@rm -f $(ARCHIVE)
	@rm -f $(NAME)
	@rm -f $(OBJ)

fclean: clean
	@make fclean -C $(LIB)
	@make fclean -C $(VISUAL)

re: fclean all
