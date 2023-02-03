/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_ident.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:48:02 by lomeniga          #+#    #+#             */
/*   Updated: 2022/08/02 08:05:32 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

_Bool	is_ident(char c)
{
	return (c == '_' || (c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

_Bool	is_special(char c)
{
	return (c == '$' || c == '@' || c == '*' || c == '#' || c == '-' || c == '!'
		|| c == '\'' || c == '"' || (c >= '0' && c <= '9'));
}

_Bool	is_start(char c)
{
	return (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void	expand_var(t_exp *exp, char *match)
{
	if (match)
	{
		exp->param = match;
		exp->act(exp);
		exp->param = NULL;
	}
}

void	match_ident(t_exp *exp)
{
	int		start;
	char	*match;

	match = NULL;
	if (exp->s[exp->i + 1] == '?')
	{
		match = exp->ms->exit_status;
		exp->i += 2;
	}
	else if (is_start(exp->s[exp->i + 1]))
	{
		start = ++exp->i;
		while (is_ident(exp->s[exp->i]))
			exp->i++;
		match = search_env(exp->ms->env_list, exp->s + start, exp->i - start);
	}
	else if (is_special(exp->s[exp->i + 1]))
		exp->i += 2;
	else
		exp->act(exp);
	expand_var(exp, match);
}
