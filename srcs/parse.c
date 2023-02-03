/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:48:06 by lomeniga          #+#    #+#             */
/*   Updated: 2022/08/14 20:24:13 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parse.h"
#include "minishell.h"

int	append_word(t_cmd *cmd, char *word)
{
	t_word	*new;

	new = xmalloc(sizeof(t_word));
	new->word = word;
	new->next = NULL;
	if (cmd->wtail)
		cmd->wtail->next = new;
	else
		cmd->whead = new;
	cmd->wtail = new;
	cmd->wcount++;
	return (1);
}

int	redir(t_parse *state, t_cmd *cmd, t_redir **tail)
{
	t_redir		*new;

	if (!state->curr->next || state->curr->next->type != TOKEN)
	{
		ft_putstr_fd("minishell: syntax error expecting TOKEN\n", 2);
		return (0);
	}
	new = xmalloc(sizeof(*new));
	new->next = NULL;
	new->type = state->curr->type;
	state->curr = state->curr->next;
	new->file = state->curr->s;
	new->fd = -1;
	if (*tail)
		(*tail)->next = new;
	else
		cmd->redir = new;
	*tail = new;
	return (1);
}

int	command(t_parse *state, t_cmd *cmd)
{
	t_redir		*tail;

	tail = NULL;
	*cmd = (t_cmd){};
	while (state->curr && state->curr->type != PIPE)
	{
		if (state->curr->type == TOKEN)
			append_word(cmd, state->curr->s);
		else if (state->curr->type > PIPE && state->curr->type <= IO_HERE
			&& !redir(state, cmd, &tail))
			return (0);
		state->curr = state->curr->next;
	}
	if (cmd->whead || cmd->redir)
		return (1);
	ft_putstr_fd("minishell: syntax error expecting command\n", 2);
	return (0);
}

int	pipeline(t_parse *state, t_cmd *last)
{
	t_cmd	tmp;

	while (state->curr && state->curr->type == PIPE)
	{
		state->curr = state->curr->next;
		if (!command(state, &tmp))
			return (0);
		last->next = xmalloc(sizeof(t_cmd));
		*last->next = tmp;
		last = last->next;
	}
	return (1);
}

t_cmd	*parse(t_ms *ms, char *line)
{
	static t_cmd	cmd;
	t_parse			state;

	ms->line_read = line;
	ms->tok = lex(line);
	if (!ms->tok)
		return (NULL);
	state = (t_parse){};
	state.curr = ms->tok;
	if (command(&state, &cmd) && pipeline(&state, &cmd))
	{
		launch_control(ms, &cmd);
		free_tok(ms->tok);
	}
	else
		free_tokfail(ms->tok, state.curr);
	free_cmd(&cmd, 0);
	ms->tok = NULL;
	return (&cmd);
}
