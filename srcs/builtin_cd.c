/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/10 18:12:20 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static int	try_cd(t_ms *ms, char *path, char *print_path)
{
	if (!path)
		return (perror_i("minishell: cd: failed malloc", 1, 0, 0));
	if (!chdir(path))
	{
		xfree(path);
		if (set_env(ms))
			return (1);
		return (0);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(print_path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	xfree(path);
	return (1);
}

static int	add_home(t_ms *ms, char **path)
{
	char	*tmp_path;
	char	*tmp;

	if (*lst_getenv(ms, "HOME"))
	{
		tmp_path = ft_strdup(*path + 1);
		if (!tmp_path)
			return (perror_i("minishell: cd: failed malloc: ", 1, 0, 0));
		tmp = ft_strjoin((*lst_getenv(ms, "HOME"))->data, tmp_path);
		xfree(tmp_path);
		if (!tmp)
			return (perror_i("minishell: cd: failed malloc: ", 1, 0, 0));
		return (try_cd(ms, tmp, *path));
	}
	ft_putstr_fd("cd: HOME not set\n", 2);
	return (1);
}

static int	select_path(t_ms *ms, char **path)
{
	char	*tmp;
	char	*tmp_path;

	tmp = 0;
	if (!ft_strncmp(*path, "~/", 2))
		return (add_home(ms, path));
	if (ft_strncmp(*path, "/", 1))
	{
		tmp_path = ft_strjoin(ms->cwd, "/");
		if (!tmp_path)
			return (perror_i("minishell: cd: failed malloc: ", 1, 0, 0));
		tmp = ft_strjoin(tmp_path, *path);
		xfree(tmp_path);
		if (!tmp)
			return (perror_i("minishell: cd: failed malloc: ", 1, 0, 0));
	}
	if (!tmp)
		tmp = ft_strdup(*path);
	return (try_cd(ms, tmp, *path));
}

int	set_env(t_ms *ms)
{
	char	*str;

	str = ft_strjoin("OLDPWD=", ms->cwd);
	if (!str)
		return (perror_i("minishell: cd: failed malloc: ", 1, 0, 0));
	if (parse_add_cmd(ms, str, 1) == 1)
		return (perror_i("minishell: cd: failed malloc: ", 1, str, 0));
	xfree(str);
	if (ms->cwd)
		xfree(ms->cwd);
	ms->cwd = getcwd(NULL, 0);
	if (!ms->cwd)
		return (perror_i("minishell: cd: failed malloc: ", 1, 0, 0));
	str = ft_strjoin("PWD=", ms->cwd);
	if (!str)
		return (perror_i("minishell: cd: failed malloc: ", 1, 0, 0));
	if (parse_add_cmd(ms, str, 1) == 1)
		return (perror_i("minishell: cd: failed malloc: ", 1, str, 0));
	xfree(str);
	return (0);
}

int	builtin_cd(t_ms *ms, char **cmd)
{
	if (!cmd)
		return (1);
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd(ERR_CD_ARGS, STDERR_FILENO);
		return (1);
	}
	if (!cmd[1] || (!ft_strcmp(cmd[1], "~") || !ft_strcmp(cmd[1], "--")))
	{
		if (*(lst_getenv(ms, "HOME")))
			return (try_cd(ms, ft_strdup((*lst_getenv(ms, "HOME"))->data),
					(*lst_getenv(ms, "HOME"))->data));
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	return (select_path(ms, &cmd[1]));
}
