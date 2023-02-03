/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:53:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/07/31 12:09:23 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"
#include "parse.h"

static void	print_redir(t_redir *redir)
{
	while (redir)
	{
		printf("dir = \"%s\" type = %d\n", redir->file, redir->type);
		redir = redir->next;
	}
}

void	tok_print(t_tok *lst)
{
	t_tok	*it;

	it = lst;
	while (it)
	{
		printf("t:{%s}\n", it->s);
		it = it->next;
	}
}

void	word_print(t_word *lst)
{
	t_word	*it;

	it = lst;
	while (it)
	{
		printf("w:{%s}\n", it->word);
		it = it->next;
	}
}

void	print_word(char **words)
{
	int		i;

	i = 0;
	while (words[i])
	{
		printf("{%s}\n", words[i]);
		i++;
	}
}

void	print_all_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		printf("CMD %d :\n", i++);
		if (cmd->words)
			print_word(cmd->words);
		if (cmd->redir)
			print_redir(cmd->redir);
		printf("-----------\n\n");
		cmd = cmd->next;
	}
}
