/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:53:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/07/31 20:42:53 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

typedef struct s_doc	t_doc;
struct s_doc
{
	t_doc	*next;
	int		size;
	char	doc[];
};

typedef struct s_word	t_word;
struct s_word
{
	t_word	*next;
	char	*word;
};

typedef struct s_redir	t_redir;
struct s_redir
{
	t_redir	*next;
	char	*file;
	int		type;
	int		fd;
};

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	t_cmd	*next;
	t_word	*whead;
	t_word	*wtail;
	t_redir	*redir;
	char	**words;
	int		wcount;
};

typedef struct s_tok	t_tok;
typedef struct s_parse	t_parse;
struct s_parse
{
	t_tok	*curr;
	t_cmd	*head;
	t_cmd	*tail;
};

typedef struct s_lex	t_lex;
typedef enum e_type		t_type;
void	push_token(t_lex *lex, t_type type);
#endif
