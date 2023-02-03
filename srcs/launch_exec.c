/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 09:12:45 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "expand.h"
#include <signal.h>

char	**list_to_array(t_list *list)
{
	void	*to_free;
	char	**array;
	t_word	*it;
	int		i;

	i = 0;
	array = xmalloc(sizeof(char *) * (list->count + 2));
	it = list->head;
	while (it)
	{
		array[i] = it->word;
		to_free = it;
		it = it->next;
		xfree(to_free);
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	(*builtin_match(char *cmd))(t_ms*b, char**a)
{
	if (!cmd)
		return (NULL);
	if (!ft_strcmp(cmd, ECHO_CMD))
		return (&builtin_echo);
	if (!ft_strcmp(cmd, CD_CMD))
		return (&builtin_cd);
	if (!ft_strcmp(cmd, PWD_CMD))
		return (&builtin_pwd);
	if (!ft_strcmp(cmd, EXPORT_CMD))
		return (&builtin_export);
	if (!ft_strcmp(cmd, UNSET_CMD))
		return (&builtin_unset);
	if (!ft_strcmp(cmd, ENV_CMD))
		return (&builtin_env);
	if (!ft_strcmp(cmd, EXIT_CMD))
		return (&builtin_exit);
	return (NULL);
}

extern volatile sig_atomic_t	g_isinted;

void	launch_control(t_ms *ms, t_cmd *cmd)
{
	int		exit_status;
	t_list	list;
	t_cmd	*it;

	it = cmd;
	while (it && !g_isinted)
	{
		list = word_expand(ms, it->whead);
		it->words = list_to_array(&list);
		redir_expand(ms, it->redir);
		if (g_isinted)
		{
			free_cmd(it->next, 1);
			it->next = NULL;
			xfree(ms->exit_status);
			ms->exit_status = ft_itoa(130);
			return ;
		}
		it = it->next;
	}
	exit_status = pipex(cmd, ms);
	xfree(ms->exit_status);
	ms->exit_status = ft_itoa(exit_status);
}

int	always_true(void)
{
	if (g_isinted)
		return (1);
	else
		return (0);
}
