# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qmanamel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/07 08:36:01 by qmanamel          #+#    #+#              #
#    Updated: 2017/09/25 09:15:50 by qmanamel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_read.a

SRC = ft_key.c  init_term.c navigation.c \
	  window.c history.c tc_print.c  \
	  cmove.c  input.c ft_read.c free.c \
	  auto_bins.c \
	  files_auto.c \
	  line_utils.c \
	  line_utils2.c \
	  cmd_history.c \
	  glob.c \
	  files_glob.c \
	  glob_match.c \

FLAG = -Wall -Werror -Wextra -g3
SILENT = --no-print-directory

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME):
	@make -C libft $(SILENT)
	@gcc $(FLAG) -c $(SRC)
	@ar rc $(NAME) $(OBJ) libft/*.o 
	@ranlib $(NAME)

clean:
	@make clean -C libft $(SILENT)
	@/bin/rm -f $(OBJ) $(LOBJ) *.o

fclean: clean
		@/bin/rm -f $(NAME)
		@make fclean -C libft $(SILENT)

re: fclean all
