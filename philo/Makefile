# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghanquer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/15 13:44:31 by ghanquer          #+#    #+#              #
#    Updated: 2022/06/10 14:19:45 by ghanquer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INC_DIR =		inc
OBJ_DIR = 		obj
SRC_DIR	= 		src

SRC =			$(SRC_FT:%=$(SRC_DIR)/%.c)

OBJ =			$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_DIRS =		$(OBJ_DIR)

CC = cc $(CFLAGS)

RM = rm -fr

CFLAGS = -Wall -Wextra -Werror -pthread -Iinc/philo.h -g #3 -fsanitize=address

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

#HOW TO LIST .c 
#	ls -l | awk '{print $9}' | grep -E ".c$"| sed "s/\.c/ \\\/g" | sed '$s/\\$//g'

SRC_FT = 	free_func \
			ft_atoi \
			main \
			start_routine \
			reaper \
			routine_utils \
			check_arg \
			ft_putstr \
			ulltoa \
			norme \
			routine_tools

all: $(NAME)

$(OBJ_DIRS): inc/philo.h
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ_DIRS) $(SRC)
	$(MAKE) $(OBJ)
	$(CC) $(OBJ) -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@echo "Cleaned object"

fclean: clean
	@$(RM) $(NAME)
	@echo "Cleaned program"

re: fclean all

define print_aligned_coffee
    @t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "             \0033[1;32m\033[3C\033[$${i}CAnd Your program \"$(NAME)\" "
endef

coffee: all clean
	@echo ""
	@echo "                                {"
	@echo "                             {   }"
	@echo "                              }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "                           \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "                          \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "                          \0033[1;34m| -.._____..- |"
	@echo "                          |             ;--."
	@echo "                          |            (__  \ "
	@echo "                          |             | )  )"
	@echo "                          |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "                          |             /  / "
	@echo "                          |            (  / "
	@echo "                          \             | "
	@echo "                            -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C                    Take Your Coffee"
	$(call print_aligned_coffee)

.SECONDARY: $(OBJ) $(OBJ_DIR) $(BNS_OBJ) $(BNS_OBJ_DIR)
.PHONY: all bonus clean fclean re coffee clean_bonus
