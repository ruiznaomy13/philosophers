NAME		= philo
HEADER		= inc/philo.h

INCLUDE		= -I./ -I lib/libft -I lib/printf
SRCS_DIR 	= src
SRCS 		= $(SRCS_DIR)/main.c $(SRCS_DIR)/error_checker.c
RUTAS		= lib/libft/libft.a lib/printf/libftprintf.a

OBJ_DIR		= obj
OBJS		= $(patsubst $(SRCS_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS		= $(addsuffix .d,$(basename ${OBJS}))
CFLAGS		= -Wall -Wextra -Werror

######## COLORS ########
GREEN		= \033[1;92m
RED			= \033[1;91m
NC			= \033[0m

${OBJ_DIR}/%.o: $(SRCS_DIR)/%.c Makefile
	@mkdir -p ${OBJ_DIR}
	@${CC} -MT $@ ${CFLAGS} -MMD -MP ${INCLUDE} -c $< -o $@

all:
	@${MAKE} -C lib/libft
	@${MAKE} -C lib/printf
	@${MAKE} ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${RUTAS} -o ${NAME}
	@echo "$(GREEN)philosopher compiled 🍽$(NC)"

-include ${DEPS}

clean:
	@${MAKE} clean -C lib/libft
	@${MAKE} clean -C lib/printf
	rm -rf ${OBJ_DIR}
	@echo "$(RED)\nDestruction successful\n$(NC)"

fclean: clean
	@${MAKE} fclean -C lib/libft
	@${MAKE} fclean -C lib/printf
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re