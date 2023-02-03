/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 15:37:55 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_exit_atoi(const char *str)
{
	unsigned char	res;
	int				idx;

	idx = 0;
	res = 0;
	if (str[idx] == '+' || str[idx] == '-')
		idx++;
	while (str[idx] >= '0' && str[idx] <= '9')
	{
		res = (res * 10) + (str[idx++] - 48);
	}
	if (((str[0] == '+' || str[0] == '-') && idx == 1) || !idx || str[idx])
		return (-2);
	if (str[0] == '-')
		return ((unsigned char)(res * -1));
	return (res);
}

void	free_minishell(t_ms *ms, int status, void *ptr)
{
	rl_clear_history();
	if (ptr)
		xfree(ptr);
	if (ms->env)
		xfree(ms->env);
	while (ms->env_list)
		delete_var(ms, &(ms->env_list));
	if (ms->path)
		xfree(ms->path);
	if (ms->cmd)
		free_cmd(ms->cmd, 0);
	if (ms->tok)
		free_tok(ms->tok);
	if (ms->cwd)
		free(ms->cwd);
	if (ms->exit_status)
		free(ms->exit_status);
	if (ms->line_read)
		free(ms->line_read);
	close(0);
	close(1);
	exit(status);
}

int	builtin_exit(t_ms *ms, char **cmd)
{
	int	ret;

	if (ms->ispiped == 0)
		ft_putstr_fd("exit\n", 2);
	if (!cmd[1] || !ft_strcmp(cmd[1], "--"))
		ret = 0;
	else if (cmd[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	else
		ret = ft_exit_atoi(cmd[1]);
	if (ret == -2)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ret = 2;
	}
	free_minishell(ms, ret, 0);
	return (0);
}
