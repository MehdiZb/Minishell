/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 13:57:17 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

static void	ft_putnbr_buf(char *str, int idx, int n)
{
	if (!n)
	{
		str[idx] = '0';
		str[idx + 1] = 0;
		return ;
	}
	if (n > 9)
		ft_putnbr_buf(str, idx + 1, n / 10);
	else
		str[idx + 1] = 0;
	str[idx] = "0123456789"[n % 10];
}

int	write_redir(t_redir *redir, int *fd_write)
{
	if (*fd_write > 1)
		close (*fd_write);
	if (redir->type == 3)
		*fd_write = create_file(redir->file, O_TRUNC
				| O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (redir->type == 4)
		*fd_write = create_file(redir->file, O_APPEND
				| O_CREAT | O_WRONLY,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (*fd_write < 0)
		return (redir_err(redir));
	return (0);
}

int	open_redir(t_redir *redir, int *fd_open)
{
	char	buf[32];
	int		idx;

	if (*fd_open > 0)
		close (*fd_open);
	if (redir->type == 2)
		*fd_open = open(redir->file, O_RDONLY | O_CLOEXEC);
	else if (redir->type == 5)
	{
		idx = -1;
		while ("/proc/self/fd/"[++idx])
			buf[idx] = "/proc/self/fd/"[idx];
		ft_putnbr_buf(buf, idx, redir->fd);
		*fd_open = open(buf, O_RDONLY);
	}
	if (*fd_open < 0)
		return (redir_err(redir));
	return (0);
}

int	redir_open_close(t_redir *redir, int fd_open, int fd_write)
{
	while (redir)
	{
		if (redir->type == 2 || redir->type == 5)
			if (open_redir(redir, &fd_open) != 0)
				return (1);
		if (redir->type == 3 || redir->type == 4)
			if (write_redir(redir, &fd_write))
				return (1);
		redir = redir->next;
	}
	if (fd_write > 2)
	{
		dup2(fd_write, 1);
		close(fd_write);
	}
	if (fd_open > 0)
	{
		dup2(fd_open, 0);
		close(fd_open);
	}
	return (0);
}
