/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:48:21 by lomeniga          #+#    #+#             */
/*   Updated: 2022/07/31 20:48:21 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append(t_tok **tail, t_tok *new)
{
	new->next = NULL;
	if (*tail)
		(*tail)->next = new;
	*tail = new;
}

void	string_copy(char *src, char *dst, int start, int end)
{
	int		i;

	i = 0;
	while (start < end)
	{
		dst[i] = src[start];
		start++;
		i++;
	}
	dst[i] = '\0';
}

void	push_token(t_lex *lex, t_type type)
{
	t_tok	*tok;

	tok = xmalloc(sizeof(t_tok));
	tok->type = type;
	tok->s = NULL;
	if (type == TOKEN)
	{
		tok->s = xmalloc(lex->i - lex->start + 2);
		string_copy(lex->str, tok->s, lex->start, lex->i);
	}
	if (lex->head == NULL)
	{
		lex->head = tok;
	}
	append(&lex->tail, tok);
}
