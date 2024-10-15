# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jopfeiff <jopfeiff@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/01 09:56:33 by jopfeiff          #+#    #+#              #
#    Updated: 2024/10/04 07:50:38 by jopfeiff         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c srcs/monitoring.c srcs/routine.c srcs/utils.c srcs/free.c srcs/error_handler.c srcs/utils2.c
CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror -pthread -I ./includes/
RM = rm -rf
EXEC = philo
NAME = philo.a
OBJS = $(SRCS:.c=.o)

RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
MAGENTA= \033[35m
CYAN   = \033[36m
RESET  = \033[0m

.SILENT:

all: philo 

philo: $(OBJS)
	echo "${CYAN}Compiling philo...${RESET}"
	$(CC) $(OBJS) -o $(EXEC)
	echo "${GREEN}Success!!!${RESET}"

clean:
	echo "${RED}Cleaning object files and executable...${RESET}"
	$(RM) $(OBJS)
	$(RM) $(EXEC)
	echo "${GREEN}Success!!!${RESET}"
	
fclean: clean
	echo "${RED}Cleaning executable files...${RESET}"
	$(RM) $(NAME) $(EXEC)
	echo "${GREEN}Success!!!${RESET}"
re: fclean all

.PHONY: all clean fclean re