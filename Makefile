NAME		= philo
HEADER		= inc/philo.h

INCLUDE		= -I./
SRCS_DIR 	= src
SRCS 		= $(SRCS_DIR)/main.c $(SRCS_DIR)/inits.c $(SRCS_DIR)/error_checker.c \
			$(SRCS_DIR)/threads.c $(SRCS_DIR)/routine.c $(SRCS_DIR)/utils.c
# RUTAS		= lib/libft/libft.a lib/printf/libftprintf.a

OBJ_DIR		= obj
OBJS		= $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS		= $(addsuffix .d,$(basename ${OBJS}))
CFLAGS		= -Wall -Wextra -Werror# -g -fsanitize=thread

######## COLORS ########
GREEN		= \033[1;92m
RED			= \033[1;91m
NC			= \033[0m

${OBJ_DIR}/%.o: $(SRCS_DIR)/%.c Makefile
	@mkdir -p ${OBJ_DIR}	
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${INCLUDE} -c $< -o $@

all:
	@${MAKE} ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "$(GREEN)\n🍽    T H E    R E S T A U R A N T   I S   O P E N E D   🍽\n$(NC)"

-include ${DEPS}

clean:
	rm -rf ${OBJ_DIR}
	@echo "$(RED)\n ❌    T H E    R E S T A U R A N T    I S    C L O S E D   ❌\n$(NC)"

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
