NAME			=	result
LIBFT_DIR		=	./../libft
MINILIB_DIR		=	./../minilibx

SRCS			=	cub_21.c\
					draw_player.c\
					raycasting.c\
					utils.c\
					bresenhem.c\
					map.c\
					move.c\
					draw_wall.c\
					./../get_next_line/get_next_line.c\
					./../get_next_line/get_next_line_utils.c\

# OBJS			=	$(SRCS:.c=.o)
# 위의 명령어로 돌리면 cub_17 에 get_next_line.o 가 생성되고 OBJS 명령어는 그 파일을 gnl 폴더에서 찾는다.
OBJS			=	cub_21.o\
					draw_player.o\
					raycasting.o\
					utils.o\
					bresenhem.o\
					map.o\
					move.o\
					draw_wall.o\
					get_next_line.o\
					get_next_line_utils.o\


CC				=	gcc

CFLAG			=	-g -Wall -Werror -Wextra

RM				=	rm -f

all 			:	$(NAME)

clean			:
					$(RM) $(OBJS) *.gch a.out

fclean			:	clean
					$(RM) $(NAME)

# L은 라이브러리 경로를 파일을 찾는 옵션, I는 같이 링크할 라이브러리를 찾는 옵션
$(NAME)			:	$(OBJS)
					$(CC) $(CFLAG) $(OBJS) -o $(NAME) -L $(LIBFT_DIR) -lft -L $(MINILIB_DIR) -lmlx -I $(MINILIB_DIR) -framework OpenGL -framework Appkit

$(OBJS)			:	$(SRCS)
					$(CC) -c $(SRCS)


.PHONY			:	all clean fclean
