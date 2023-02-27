.PHONY:     			all $(NAME) clear mkbuild lib clear clean fclean re sanitize

NAME					= minishell

BUILD_DIR				= build/
	
HEADER_DIR				= header/
HEADER_FILE				= minishell.h	\
							exec.h	\
							typedef.h	\
							pipes.h

DIR						=	src/
SRC						=	ms_utils.c	ms_utils_list.c main_exec.c memory_management.c	\
                            builtins/cd.c    builtins/pwd.c    builtins/builtins_utils.c    builtins/echo.c builtins/env.c    builtins/unset.c builtins/export.c	builtins/exit.c	\
							pipes/pipex_error.c	pipes/pipex_exec.c	pipes/pipex_main.c	pipes/pipex_utils.c	\
							parsing/builtins_parsing.c	parsing/cut_cmd.c	parsing/list_utils.c	parsing/parsing_utils.c	parsing/parsing.c
							
OBJECTS			    	= $(SRC:%.c=$(BUILD_DIR)%.o)
	
LIBFT					= libft.a
LIB_DIR					= libft/

	
GCC						= cc
CFLAGS					= -Wall -Werror -Wextra
SANITIZE				= $(CFLAGS) -g3 -fsanitize=address

RM 						= rm -rf
CLEAR					= clear

$(BUILD_DIR)%.o:		$(DIR)%.c $(HEADER_DIR) libft
						@mkdir -p $(@D)
						$(GCC) $(CFLAGS) -I$(HEADER_DIR) -I$(LIB_DIR) -I/usr/include -O3 -c $< -o $@

all: 					clear mkbuild lib  $(HEADER_DIR) $(NAME) 
						
mkbuild:
						@mkdir -p build

clear:
						$(CLEAR)
						
$(NAME): 				$(OBJECTS) $(LIB_DIR)$(LIBFT) Makefile
						$(GCC) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) -lreadline

sanit :					$(OBJECTS) $(LIB_DIR)$(LIBFT)
						$(GCC) $(SANITIZE) $(OBJECTS) -o $(NAME) $(LIB_DIR)$(LIBFT) -lreadline

lib:
						@make -C $(LIB_DIR)
						
clean:					
						@${RM} $(OBJECTS)
						@make clean -C $(LIB_DIR)
						@${RM} $(BUILD_DIR)

fclean:					clean
						@${RM} ${NAME}
						@make fclean -C $(LIB_DIR)

re:						fclean all
						$(MAKE) all