/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:50 by lomeniga          #+#    #+#             */
/*   Updated: 2022/08/15 02:51:51 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	free_tok(t_tok *tok)
{
	void	*to_free;

	while (tok)
	{
		to_free = tok;
		xfree(tok->s);
		tok = tok->next;
		xfree(to_free);
	}
}

void	free_tokfail(t_tok *tok, t_tok *curr)
{
	void	*to_free;

	while (tok != curr)
	{
		to_free = tok;
		tok = tok->next;
		xfree(to_free);
	}
	free_tok(curr);
}

void	free_word(t_word *word, char **words, int inted)
{
	void	*to_free;

	while (!words && word)
	{
		to_free = word;
		if (!inted)
			xfree(word->word);
		word = word->next;
		xfree(to_free);
	}
	if (!words)
		return ;
	while (word)
	{
		to_free = word;
		word = word->next;
		xfree(to_free);
	}
	while (*words)
	{
		xfree(*words);
		words++;
	}
}

void	free_redir(t_redir *redir, int inted)
{
	void	*to_free;

	while (redir)
	{
		if (redir->type == IO_HERE && redir->fd >= 0)
			close(redir->fd);
		if (!inted)
			xfree(redir->file);
		to_free = redir;
		redir = redir->next;
		xfree(to_free);
	}
}

void	free_cmd(t_cmd *cmd, int inted)
{
	void	*to_free;

	if (!inted)
	{
		free_word(cmd->whead, cmd->words, inted);
		xfree(cmd->words);
		free_redir(cmd->redir, inted);
		cmd = cmd->next;
	}
	while (cmd)
	{
		free_word(cmd->whead, cmd->words, inted);
		xfree(cmd->words);
		free_redir(cmd->redir, inted);
		to_free = cmd;
		cmd = cmd->next;
		xfree(to_free);
	}
}
