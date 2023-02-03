SRCS_DIR	= ./srcs/

SRC			=									\
			./srcs/builtin_cd.c                    \
			./srcs/builtin_echo.c                  \
			./srcs/builtin_env.c                   \
			./srcs/builtin_env_utils.c             \
			./srcs/builtin_exit.c                  \
			./srcs/builtin_export.c                \
			./srcs/builtin_pwd.c                   \
			./srcs/builtin_unset.c                 \
			./srcs/delimit.c                       \
			./srcs/expand.c                        \
			./srcs/expand_util.c                   \
			./srcs/field_split.c                   \
			./srcs/free_parsing.c                  \
			./srcs/ft_split.c                      \
			./srcs/launch_exec.c                   \
			./srcs/lexer.c                         \
			./srcs/libft_calloc_itoa_strlen.c      \
			./srcs/libft_strcmp_ncmp_instr_alnum.c \
			./srcs/libft_strdup_sub_join_new.c     \
			./srcs/libft_utils.c                   \
			./srcs/main.c                          \
			./srcs/main_pipex.c                    \
			./srcs/match_ident.c                   \
			./srcs/parse.c                         \
			./srcs/pipex_redir.c                   \
			./srcs/pipex_spawn_exec.c              \
			./srcs/print.c                         \
			./srcs/push_token.c                    \
			./srcs/redir_expand.c                  \
			./srcs/safeutil.c                      \
			./srcs/xmalloc.c

HEADER		=\
				expand.h     \
				lex.h        \
				minishell.h  \
				parse.h      \
				pipex.h      \


OBJ		:= $(SRC:.c=.o)
CFLAGS	:= $(DEBUG) -g -Wall -Wextra -Werror
NAME	= minishell
CC		= clang
LFLAGS	= -lreadline

ERRORFILE	:= $(addprefix err/, $(addsuffix .err, $(SRC) $(HEADER)))

$(NAME) : $(OBJ) -lreadline
	$(CC)  -o $(NAME) $(CFLAGS) $^ $(LFLAGS)

all		: $(NAME)

fclean	: clean
		$(RM) $(NAME)

clean	:
		$(RM) srcs/*.o

re		: fclean
	$(MAKE)

norm	: errors.err

$(ERRORFILE) : err/%.err : %
	-norminette $< > $@

errors.err: $(ERRORFILE)
	cat $^ > errors.err | awk '! /OK/ {print}' | touch $@

.PHONY	: re clean fclean all norm
