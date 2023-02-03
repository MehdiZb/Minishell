/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:34 by lomeniga          #+#    #+#             */
/*   Updated: 2022/08/03 08:49:48 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse.h"
#include "expand.h"
#include <readline/readline.h>

void	skip(t_exp *exp)
{
	exp->act(exp);
	while (exp->s[exp->i] && exp->s[exp->i] != '\'')
	{
		exp->act(exp);
	}
	exp->act(exp);
}

void	quote_expand(t_exp *exp)
{
	exp->act(exp);
	while (exp->s[exp->i] && exp->s[exp->i] != '\"')
	{
		if (exp->s[exp->i] == '$')
			match_ident(exp);
		exp->act(exp);
	}
	exp->act(exp);
}

int	parse_expand(t_exp *exp)
{
	while (exp->s[exp->i])
	{
		if (exp->s[exp->i] == '$')
			match_ident(exp);
		else if (exp->s[exp->i] == '\'')
		{
			skip(exp);
		}
		else if (exp->s[exp->i] == '"')
			quote_expand(exp);
		else
			exp->act(exp);
	}
	return (0);
}

void	pexpand(t_ms *ms, char *s, char **out)
{
	t_exp	exp;

	exp.param = NULL;
	exp.count = 0;
	exp.ms = ms;
	exp.s = s;
	exp.i = 0;
	exp.state = 0;
	exp.act = count;
	parse_expand(&exp);
	exp.d = xmalloc(exp.count + 3);
	exp.j = 0;
	exp.i = 0;
	exp.act = copy;
	parse_expand(&exp);
	exp.d[exp.j] = '\0';
	*out = exp.d;
}

t_list	word_expand(t_ms *ms, t_word *words)
{
	char	*out;
	char	*ifs;
	t_list	list;

	list = (t_list){};
	ifs = search_env(ms->env_list, "IFS", 3);
	if (!ifs)
		ifs = " \t\n";
	while (words)
	{
		pexpand(ms, words->word, &out);
		field_split(ifs, out, &list);
		xfree(out);
		words = words->next;
	}
	return (list);
}
