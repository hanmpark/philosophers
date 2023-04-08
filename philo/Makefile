# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 17:03:40 by hanmpark          #+#    #+#              #
#    Updated: 2023/04/08 18:12:59 by hanmpark         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---------------------------------- COLORS ---------------------------------- #
DEF = \033[0m
BOLD = \033[1m
CUR = \033[3m
UL = \033[4m
UP = \033[A

ORANGE = \033[38;5;216m
LBLUE = \033[38;5;153m
LYELLOW = \033[38;5;222m
BEIGE = \033[38;5;223m
LGREEN = \033[38;5;155m

# ---------------------------- SOURCES / OBJECTS ----------------------------- #
SRC.PATH = ./src/
SRC = ${addprefix ${SRC.PATH}, philosophers.c}

OBJ = ${SRC:.c=.o}

# --------------------------------- COMPILER --------------------------------- #
CC = gcc
CFLAGS = -Wall -Werror -Wextra
ifdef DEBUG
	CFLAGS += -fsanitize=address -g
endif
PTHREAD = -lpthread

HEADER.PATH = ./inc/
SRCS.COUNT = 0
SRCS.TOT = ${shell find ${SRC.PATH} -type f -name '*.c' | wc -l}
SRCS.PRCT = ${shell expr 100 \* ${SRCS.COUNT} / ${SRCS.TOT}}
BAR = ${shell expr 23 \* ${SRCS.COUNT} / ${SRCS.TOT}}

${SRC.PATH}%.o: ${SRC.PATH}%.c ${HEADER.PATH}
	@${eval SRCS_COUNT = ${shell expr ${SRCS.COUNT} + 1}}
	@${CC} ${CFLAGS} -I ${HEADER.PATH} -c $< -o ${<:.c=.o}
	@echo ""
	@echo " ${BOLD}${CUR}${BEIGE}-> Compiling ${DEF}${BOLD}${LYELLOW}[PHILO]${DEF}"
	@printf " ${BEIGE}   [${LGREEN}%-23.${BAR}s${BEIGE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRCS_COUNT} ${SRCS_TOT} ${SRCS_PRCT}
	@echo "${UP}${UP}${UP}"

# ---------------------------------- RULES ----------------------------------- #
NAME = philo

all: ${NAME}

${NAME}: ${OBJ}
	@echo "\n\n\n"
	@${CC} ${CFLAGS} ${PTHREAD} ${OBJ} -o ${NAME}
	@echo "\n\n\n   ${BOLD}${CUR}${LYELLOW}PHILO COMPILED ✨${DEF}\n"

debug:
	@{MAKE} DEBUG=1

clean:
	@rm -f ${OBJ}
	@echo "${ORANGE}${BOLD}\tCLEANING${DEF}"
	@echo "${LBLUE}${BOLD}${CUR} - Deleted object files${DEF}"

fclean: clean
	@rm -f ${NAME}
	@echo "${LBLUE}${BOLD}${CUR} - Deleted ${NAME}${DEF}"

re: fclean
	@{MAKE} all

.PHONY: all clean fclean re debug