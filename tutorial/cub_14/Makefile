NAME			=	result
LIBFT_DIR		=	./../libft
MINILIB_DIR		=	./../minilibx

SRCS			=	window_resize4.c

OBJS			=	$(SRCS:.c=.o)

LIBS			=	-Lmlx -lmlx -framework OpenGL -framework AppKit -lm

CC				=	gcc

CFLAG			=	-g

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
