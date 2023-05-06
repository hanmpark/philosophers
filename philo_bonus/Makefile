# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hanmpark <hanmpark@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 17:10:31 by hanmpark          #+#    #+#              #
#    Updated: 2023/05/06 17:19:51 by hanmpark         ###   ########.fr        #
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
SRC_PATH = ./src/

SRC_TABLE_PATH = ${SRC_PATH}table/
SRC_TABLE = ${addprefix ${SRC_TABLE_PATH}, parse_input_bonus.c prepare_table_bonus.c}

SRC_SIMULATION_PATH = ${SRC_PATH}simulation/
SRC_SIMULATION = ${addprefix ${SRC_SIMULATION_PATH}, philosophers.c \
														sim_manage.c \
														sim_switch.c \
														watcher.c}

SRC_TOOLS_PATH = ${SRC_PATH}tools/
SRC_TOOLS = ${addprefix ${SRC_TOOLS_PATH}, print.c time.c}

SRC = ${SRC_TABLE} ${SRC_SIMULATION} ${SRC_TOOLS} ${SRC_PATH}main.c

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
	@echo " ${BOLD}${CUR}${BEIGE}-> Compiling ${DEF}${BOLD}${LYELLOW}[PHILO]${DEF}"
	@printf " ${BEIGE}   [${LGREEN}%-23.${BAR}s${BEIGE}] [%d/%d (%d%%)]${DEF}" "***********************" ${SRCS_COUNT} ${SRCS_TOT} ${SRCS_PRCT}
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