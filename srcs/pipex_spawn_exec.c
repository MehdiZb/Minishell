/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_spawn_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:53:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 15:24:51 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipex.h"
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

static void	ft_putstr_prepexec(char *s1, char *s2, int type)
{
	struct stat	st;

	(void)st;
	if (type == 1)
	{
		stat(s1, &st);
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": ", 2);
		if (S_ISDIR(st.st_mode))
			ft_putstr_fd("Is a directory", 2);
		else
			ft_putstr_fd(s2, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (type == 2)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
}

void	signaal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

static char	*cmd_path(t_ms *ms, char *cmd, int i)
{
	char	*tmp;
	char	*command;

	if (!cmd[0])
		return (NULL);
	while (ms->path && ms->path[++i] && !ft_chr_in_str(cmd, '/'))
	{
		tmp = ft_strjoin(ms->path[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		xfree(tmp);
		if (!command)
			return (NULL);
		if (access(command, F_OK) == 0)
			return (command);
		xfree(command);
	}
	return (NULL);
}

void	prep_exec(char **cmd, t_ms *ms, int *ret)
{
	char	*str;
	int		(*builtin_cmd)(t_ms*, char **);

	str = NULL;
	builtin_cmd = builtin_match(cmd[0]);
	if (builtin_cmd)
		free_minishell(ms, builtin_cmd(ms, cmd), 0);
	else if (cmd && ft_chr_in_str(cmd[0], '/'))
		str = strdup(cmd[0]);
	else
		str = cmd_path(ms, cmd[0], -1);
	if (str)
	{
		execve(str, cmd, ms->env);
		if (errno == ENOEXEC)
			execve("/bin/sh", (char *[]){"/bin/sh", str, NULL}, ms->env);
		ft_putstr_prepexec(str, strerror(errno), 1);
		free_minishell(ms, 126 + (access(str, 0) * -1), str);
	}
	else if (!builtin_cmd)
		ft_putstr_prepexec(cmd[0], 0, 2);
	*ret = 127;
}

int	one_builtin(t_cmd *cmd, t_ms *ms)
{
	int		dup_fd_in;
	int		dup_fd_out;
	int		ret;
	int		(*builtin_cmd)(t_ms*, char **);

	ret = 0;
	builtin_cmd = builtin_match(cmd->words[0]);
	if (ft_strcmp(cmd->words[0], "exit"))
	{
		dup_fd_in = dup(0);
		dup_fd_out = dup(1);
	}
	if (redir_open_close(cmd->redir, 0, 1))
		return (1);
	ret = (*builtin_cmd)(ms, cmd->words);
	if (!ft_strcmp(cmd->words[0], "exit"))
		return (ret);
	close(0);
	close(1);
	dup2(dup_fd_in, 0);
	dup2(dup_fd_out, 1);
	close(dup_fd_in);
	close(dup_fd_out);
	return (ret);
}
