/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:53:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 16:08:24 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
**	Includes
*/

# include "parse.h"
# include "pipex.h"
# include <stddef.h>

/*
**  Defines
*/

# define MS_PROMPT_NAME "minishell$ "
# define TRUE 1
# define FALSE 0
# define ERR_FD 2
# define MAX_LEN_CWD 4100

# define ERR_GNL_FAILED "Erreur lors de la lecture de la ligne.\n"
# define ERR_GET_CWD "Erreur lors de l'appel de la commande \"getcwd\".\n"

# define ERR_PWD_ARGS "pwd: too many arguments\n"
# define ERR_CD_ARGS "cd: too many arguments\n"
# define ERR_EXIT_ARGS_NUM "minishell: exit: numeric argument required\n"

# define ECHO_CMD "echo"
# define CD_CMD "cd"
# define PWD_CMD "pwd"
# define EXPORT_CMD "export"
# define UNSET_CMD "unset"
# define ENV_CMD "env"
# define EXIT_CMD "exit"

# define CD_ERR_CWD "minishell: cd: error retrieving current directory: \
getcwd: cannot access parent directories: \
No such file or directory\n"

/*
** Lexer
*/

typedef enum e_type		t_type;
enum	e_type
{
	TOKEN,
	PIPE,
	IO_IN,
	IO_OUT,
	IO_APPEND,
	IO_HERE,
};

enum	e_state
{
	START,
	INOP,
	SQUOTE,
	DQUOTE,
	END,
	SSIZE
};

typedef struct s_tok	t_tok;
struct	s_tok
{
	t_tok	*next;
	char	*s;
	t_type	type;
};

typedef struct s_lex	t_lex;
struct s_lex
{
	char	*str;
	t_tok	*head;
	t_tok	*tail;
	int		start;
	int		i;
	int		state;

};

typedef _Bool			(*t_fn)(t_lex *lex);

typedef struct s_env_list
{
	char				*key;
	char				*data;
	char				*key_data;
	struct s_env_list	*next;
}						t_env;

typedef struct s_minishell
{
	struct s_env_list	*env_list;
	char				**env;
	char				**path;
	t_cmd				*cmd;
	t_tok				*tok;
	char				*exit_status;
	char				*cwd;
	char				*line_read;
	int					isatty;
	int					ispiped;
}						t_ms;

typedef struct s_list
{
	t_word	*head;
	t_word	*tail;
	int		count;
}						t_list;

/*
**  Prototypes
*/

typedef struct s_cmd	t_cmd;
char					*ms_gets(char *prompt);
void					*xmalloc(size_t	size);
void					xfree(void *p);
void					tok_print(t_tok *lst);
void					free_tok(t_tok *tok);
void					free_tokfail(t_tok *tok, t_tok *curr);
void					free_cmd(t_cmd *cmd, int inted);
void					print_word(char **words);
void					word_print(t_word *lst);
void					print_all_cmd(t_cmd *cmd);
_Bool					delimit(t_lex *lex);
t_tok					*lex(char *str);
t_cmd					*parse(t_ms *ms, char *line);
void					pexpand(t_ms *ms, char *s, char **out);
t_list					word_expand(t_ms *ms, t_word *words);
void					redir_expand(t_ms *ms, t_redir *redir);
void					string_copy(char *src, char *dst, int start, int end);
char					**list_to_array(t_list *list);

int						(*builtin_match(char *cmd))(t_ms*b, char**a);

// libft_utils.c
int						ft_strcmp(const char *s1, const char *s2);
void					ft_putstr_fd(char *s, int fd);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_chr_in_str(const char *src, int chr);
int						ft_isalnum(int i);
int						perror_i(char *str, int i,
							void *ptr_one, void *ptr_two);
void					ft_putnbr_fd(int n, int fd);

// libft_calloc_itoa_strlen.c
void					ft_bzero(void *s, size_t n);
void					*ft_calloc(size_t count, size_t size);
char					*ft_itoa(int n);
size_t					ft_strlen(const char *str);

// libft_strdup_sub_join_new.c
char					*ft_strdup(const char *str);
char					*ft_strnew(size_t size);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strcat(char *dest, const char *src);

// libft_strcmp_ncmp_instr_alnum.c

// pipex
int						pipex(t_cmd *cmd, t_ms *ms);
int						redir_open_close(t_redir *redir,
							int fd_open, int fd_write);

//launch_exec.c
int						(*builtin_match(char *cmd))(t_ms*b, char**a);
void					launch_control(t_ms *ms, t_cmd *cmd);
int						always_true(void);

// pipex_spawn_exec.c
void					prep_exec(char **cmd, t_ms *ms, int *ret);
int						one_builtin(t_cmd *cmd, t_ms *ms);

// ft_split.c
char					**ft_split(char const *s, char c);

//BUILTINS
int						init_cwd(t_ms *ms);

// builtin_echo.c
int						builtin_echo(t_ms *ms, char **cmd);

// builtin_cd.c
int						set_env(t_ms *ms);
int						builtin_cd(t_ms *ms, char **cmd);

// builtin_pwd.c
int						case_error(t_ms *ms, char **path, size_t idx);
int						builtin_pwd(t_ms *ms, char **cmd);

// builtin_env_utils.c
t_env					**lst_getenv(t_ms *ms, char *key);
int						check_key(char *key);
int						set_keydata(t_env *var, char *key, char *data);
int						add_var(t_ms *ms, char *key, char *data);

// builtin_export.c
int						builtin_export(t_ms *ms, char **cmd);
int						parse_add_cmd(t_ms *ms, char *cmd, int check);

// builtin_unset.c
int						builtin_unset(t_ms *ms, char **cmd);
int						delete_var(t_ms *ms, t_env **var);

// builtin_env.c
int						init_env_list(t_ms *ms, char **envv);
int						builtin_env(t_ms *ms, char **cmd);
int						set_env_table(t_ms *ms);
int						set_path(t_ms *ms);

// builtin_exit.c
int						builtin_exit(t_ms *ms, char **cmd);
void					free_minishell(t_ms *ms, int status, void *ptr);
int						ft_exit_atoi(const char *str);

#endif
