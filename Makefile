SRCS	=	main.c get_next_line.c \
			parser.c parse_map.c parse_before_map.c \
			cub2d.c

SRCS_DIR = src/

OBJS	=	${addprefix ${SRCS_DIR}, ${SRCS:.c=.o}}

NAME = cub3D

HEADER = ./cub3D.h ./libft/libft.h

LIB			=	./libft/libft.a

MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit

LOGDATE		=	$(shell date)

CC = gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

# COLORS

GREEN	= \033[0;32m
YELO	= \033[0;33m
BLUE	= \033[0;34m
NEW		= \033[0;35m
SHALLOW = \033[0m

# END COLORS

.PHONY: all clean fclean re bonus norm libft pull push

all:		${NAME}

%.o: %.c
	@${CC} ${CFLAGS} -Imlx -c $< -o $@

libft:		
			@make -C ./libft/

bonus:		${NAME}

${NAME}:	${OBJS} ${HEADER}
			@make -C ./libft/
			@echo "${GREEN}Libft compile!${SHALLOW}"
			@${CC} ${CFLAGC} ${LIB} ${MLX} libmlx.dylib ${OBJS} -o ${NAME}
			@echo "${GREEN}${NAME} compile!${SHALLOW}"

test:
			@bash test.sh all

norm:
			@echo "${GREEN}|-----Chek NORMs!-----|${NEW}"
			@norminette ./src/
			@norminette ./libft/
			@echo "${GREEN}|-----Chek ended!-----|${SHALLOW}"

clean:		
			@${RM} ${OBJS} ${BONUS_OBJS}
			@make clean -C ./libft/
			@echo "${BLUE}clean done!${SHALLOW}"

fclean:		
			@${RM} ${OBJS} ${BONUS_OBJS} ${NAME} ${B_NAME}
			@make fclean -C ./libft/
			@echo "${YELO}fclean done!${SHALLOW}"

pull:		fclean
			@git pull
			@echo "${GREEN}---Pull done!---${SHALLOW}"

push:		fclean
			@git pull
			@git add .
			@git commit -m "${LOGDATE}"
			@git push
			@echo "${GREEN}---Push done!---${SHALLOW}"

re:			fclean all
