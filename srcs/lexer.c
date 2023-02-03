/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:54 by lomeniga          #+#    #+#             */
/*   Updated: 2022/08/10 12:34:22 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "lex.h"

_Bool	squoteon(t_lex *lex)
{
	lex->state = SQUOTE;
	return (0);
}

_Bool	end(t_lex *lex)
{
	lex->state = START;
	return (0);
}

_Bool	dquoteon(t_lex *lex)
{
	lex->state = DQUOTE;
	return (0);
}

_Bool	operator(t_lex *lex)
{
	lex->state = INOP;
	return (0);
}

t_tok	*lex(char *str)
{
	t_lex			lex;
	static t_fn		g_trans [SSIZE][256] = {
	[START] = {[' '] = delimit, ['\t'] = delimit, ['\''] = squoteon,
	['"'] = dquoteon, ['<'] = less, ['>'] = over, ['|'] = delim_pipe},
	[SQUOTE]['\''] = end,
	[DQUOTE]['"'] = end,
	};

	lex = (t_lex){};
	lex.str = str;
	while (str[lex.i])
	{
		if (g_trans[lex.state][(unsigned char)str[lex.i]])
			g_trans[lex.state][(unsigned char)str[lex.i]](&lex);
		lex.i++;
	}
	if (lex.state == START)
	{
		delimit(&lex);
		return (lex.head);
	}
	ft_putstr_fd("minishell unexpected EOF\n", 2);
	return (NULL);
}
