CC = cc
CFLAGS = -Wall -Wextra -Werror -ggdb3 #-fsanitize=addressi
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC = execution/builtins/do_cd.c execution/builtins/do_echo.c execution/builtins/do_env.c execution/builtins/do_exit.c execution/builtins/do_export.c \
	  execution/builtins/do_pwd.c execution/builtins/do_unset.c execution/builtins/print_env.c execution/builtins/create_env.c \
      execution/pipe_ex_helpers.c execution/utils.c execution/dup_utils.c execution/redirections.c execution/pipe_executor.c execution/main.c execution/main_helpers.c\
      lexer/error.c lexer/expand.c lexer/lexer_help.c lexer/main.c lexer/parce.c lexer/t_cmd_helpers.c lexer/token_help.c lexer/tokenizing.c \
      lexer/signals.c lexer/herdoc_handler.c lexer/exit_status.c


OBJ = $(SRC:%.c=%.o)
NAME = minishell
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)


clean:
	@$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBFT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

re: fclean all

.SECONDARY: $(OBJ)
.PHONY: all clean fclean re bonus
