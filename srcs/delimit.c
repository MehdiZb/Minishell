/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:28 by lomeniga          #+#    #+#             */
/*   Updated: 2022/07/31 20:47:30 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

_Bool	delimit(t_lex *lex)
{
	if (lex->start < lex->i)
		push_token(lex, TOKEN);
	lex->start = lex->i + 1;
	return (1);
}

_Bool	less(t_lex *lex)
{
	delimit(lex);
	if (lex->str[lex->i + 1] == '<')
	{
		push_token(lex, IO_HERE);
		lex->i++;
	}
	else
		push_token(lex, IO_IN);
	lex->start = lex->i + 1;
	return (0);
}

_Bool	over(t_lex *lex)
{
	delimit(lex);
	if (lex->str[lex->i + 1] == '>')
	{
		push_token(lex, IO_APPEND);
		lex->i++;
	}
	else
		push_token(lex, IO_OUT);
	lex->start = lex->i + 1;
	return (0);
}

_Bool	delim_pipe(t_lex *lex)
{
	delimit(lex);
	push_token(lex, PIPE);
	lex->state = START;
	lex->start = lex->i + 1;
	return (0);
}
