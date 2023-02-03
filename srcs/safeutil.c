/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safeutil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:53:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/03 13:51:11 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

void	panic(void)
{
	exit(1);
}

int	redir_err(t_redir *redir)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(redir->file, 2);
	ft_putstr_fd(": ", 2);
	perror(NULL);
	return (1);
}

int	panic_open(char *path, int flags)
{
	int	fd;

	fd = open(path, flags);
	if (fd < 0)
		panic();
	return (fd);
}

int	create_file(char *path, int flags, int mode)
{
	int	fd;

	fd = open(path, flags, mode);
	return (fd);
}
