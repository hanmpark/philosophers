# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/08 17:03:40 by hanmpark          #+#    #+#              #
#    Updated: 2023/05/12 11:18:54 by hanmpark         ###   ########.fr        #
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
LYELLOW = \033[38;5;228m
LPURPLE = \033[38;5;189m
LGREEN = \033[38;5;155m

# ---------------------------- SOURCES / OBJECTS ----------------------------- #
SRC_PATH = ./src/

SRC_TABLE_PATH = ${SRC_PATH}table/
SRC_TABLE = ${addprefix ${SRC_TABLE_PATH}, check_arguments.c \
											init_global_mutexes.c \
											init_philosophers.c \
											init_table.c \
											exit.c}

SRC_SIMULATION_PATH = ${SRC_PATH}simulation/
SRC_SIMULATION = ${addprefix ${SRC_SIMULATION_PATH}, launch_routine.c \
														init_sim.c \
														print_status.c \
														watcher.c \
														time_utils.c}

SRC = ${SRC_TABLE} ${SRC_SIMULATION} ${SRC_PATH}main.c

OBJ = ${SRC:.c=.o}

# --------------------------------- COMPILER --------------------------------- #
CC = gcc
CFLAGS = -Wall -Werror -Wextra

ifdef DEBUG
	CFLAGS += -fsanitize=address -g
endif

ifdef THREAD
	CFLAGS += -fsanitize=thread -g
endif

PTHREAD = -lpthread

HEADER_PATH = ./inc/
SRCS_COUNT = 0
SRCS_TOT = ${shell find ${SRC_PATH} -type f -name '*.c' | wc -l}
SRCS_PRCT = ${shell expr 100 \* ${SRCS_COUNT} / ${SRCS_TOT}}
BAR = ${shell expr 23 \* ${SRCS_COUNT} / ${SRCS_TOT}}

${SRC_PATH}%.o: ${SRC_PATH}%.c ${HEADER_PATH}
	@${eval SRCS_COUNT = ${shell expr ${SRCS_COUNT} + 1}}
	@${CC} ${CFLAGS} -I ${HEADER_PATH} -c $< -o ${<:.c=.o}
	@echo ""
	@echo " ${BOLD}${CUR}${LPURPLE}-> Compiling ${DEF}${BOLD}${LYELLOW}[PHILO]${DEF}"
	@printf " ${LPURPLE}   [${LGREEN}%-23.${BAR}s${LPURPLE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRCS_COUNT} ${SRCS_TOT} ${SRCS_PRCT}
	@echo "${UP}${UP}${UP}"

# ---------------------------------- RULES ----------------------------------- #
NAME = philo

all: ${NAME}

${NAME}: ${OBJ}
	@echo ""
	@${CC} ${CFLAGS} ${PTHREAD} ${OBJ} -o ${NAME}
	@echo "\n\n\n   ${BOLD}${CUR}${LYELLOW}PHILO COMPILED ✨${DEF}\n"

debug:
	@${MAKE} DEBUG=1

thread:
	@${MAKE} THREAD=1

clean:
	@rm -f ${OBJ}
	@echo "${ORANGE}${BOLD}\tCLEANING${DEF}"
	@echo "${LBLUE}${BOLD}${CUR} - Deleted object files${DEF}"

fclean: clean
	@rm -f ${NAME}
	@echo "${LBLUE}${BOLD}${CUR} - Deleted ${NAME}${DEF}"

re: fclean
	@${MAKE} all

.PHONY: all clean fclean re debug thread