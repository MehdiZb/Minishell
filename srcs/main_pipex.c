/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 16:35:13 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int	wait_all(int pid_ret, int inted)
{
	int		wstatus;
	int		pid;
	int		ret;

	ret = 0;
	while (42)
	{
		pid = waitpid(0, &wstatus, 0);
		if (pid <= 0)
			break ;
		if (pid == pid_ret && WIFEXITED(wstatus))
			ret = WEXITSTATUS(wstatus);
		if (pid == pid_ret && WIFSIGNALED(wstatus))
			ret = 128 + WTERMSIG(wstatus);
		if (WIFSIGNALED(wstatus) && WCOREDUMP(wstatus))
		{
			ft_putnbr_fd(WTERMSIG(wstatus), 2);
			ft_putstr_fd(" (core dumped)\n", 2);
		}
		if (!inted && WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGINT)
			write(2, "\n", inted = 1);
	}
	return (ret);
}

void	pipe_w(int *fds)
{
	if (pipe(fds) < 0)
	{
		perror("pipe");
		exit (1);
	}
}

static pid_t	spawn(t_pair pair, int fdclose, t_cmd *cmd, t_ms *ms)
{
	pid_t	pid;
	int		ret;

	pid = fork();
	ret = 0;
	if (!pid)
	{
		signaal();
		if (redir_open_close(cmd->redir, pair.in, pair.out))
			free_minishell(ms, 1, 0);
		if (fdclose > 2)
			close(fdclose);
		if (cmd->words && cmd->words[0])
			prep_exec(cmd->words, ms, &ret);
		free_minishell(ms, ret, 0);
	}
	else if (pid < 0)
		panic();
	if (pair.in > 2)
		close(pair.in);
	if (pair.out > 2)
		close(pair.out);
	return (pid);
}

int	pipex(t_cmd *cmd, t_ms *ms)
{
	int		fd;
	int		fds[2];
	pid_t	pid_ret;

	ms->cmd = cmd;
	if (cmd && !cmd->next && cmd->words && builtin_match(cmd->words[0]))
		return (one_builtin(cmd, ms));
	ms->ispiped = 1;
	fd = 0;
	fds[0] = 0;
	while (cmd)
	{
		if (cmd->next)
			pipe_w(fds);
		else
			fds[1] = 1;
		pid_ret = spawn((t_pair){fd, fds[1]}, fds[0], cmd, ms);
		fd = fds[0];
		fds[0] = 0;
		cmd = cmd->next;
	}
	ms->ispiped = 0;
	ms->cmd = NULL;
	return (wait_all(pid_ret, 0));
}
