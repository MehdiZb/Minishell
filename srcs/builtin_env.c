/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 15:49:58 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

static int	set_shlvl(t_ms *ms)
{
	int		cmpt;
	char	*str_itoa;
	char	*str;

	if (!(*lst_getenv(ms, "SHLVL")) || !(*lst_getenv(ms, "SHLVL"))->data[0])
		return (parse_add_cmd(ms, "SHLVL=1", 1));
	cmpt = -1;
	while ((*lst_getenv(ms, "SHLVL"))->data[++cmpt])
		if ((*lst_getenv(ms, "SHLVL"))->data[cmpt] < '0'
			|| (*lst_getenv(ms, "SHLVL"))->data[cmpt] > '9')
			return (parse_add_cmd(ms, "SHLVL=1", 1));
	str_itoa = ft_itoa(ft_exit_atoi((*lst_getenv(ms, "SHLVL"))->data) + 1);
	if (!str_itoa)
		return (1);
	str = ft_strjoin("SHLVL=", str_itoa);
	xfree (str_itoa);
	if (!str)
		return (1);
	if (parse_add_cmd(ms, str, 1))
		return (1);
	xfree(str);
	return (0);
}

static int	init_pwd_oldpwd(t_ms *ms)
{
	char	*key_pwd;
	char	*pwd;

	delete_var(ms, lst_getenv(ms, "PWD"));
	delete_var(ms, lst_getenv(ms, "OLDPWD"));
	delete_var(ms, lst_getenv(ms, "_"));
	if (parse_add_cmd(ms, "_=/usr/bin/env", 1))
		return (1);
	if (!(*lst_getenv(ms, "OLDPWD")))
		if (add_var(ms, ft_strdup("OLDPWD"), 0))
			return (1);
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	key_pwd = ft_strdup("PWD");
	if (!key_pwd)
	{
		xfree(pwd);
		return (1);
	}
	if (add_var(ms, key_pwd, pwd))
		return (1);
	return (0);
}

int	set_env_table(t_ms *ms)
{
	t_env	*tmp;
	int		cmpt;

	if (ms->env)
		xfree(ms->env);
	ms->env = NULL;
	cmpt = 0;
	tmp = ms->env_list;
	while (tmp && ++cmpt)
		tmp = tmp->next;
	ms->env = (char **)ft_calloc(cmpt + 1, sizeof(char *));
	if (!ms->env)
		return (1);
	cmpt = 0;
	tmp = ms->env_list;
	while (tmp)
	{
		if (tmp->key_data)
			ms->env[cmpt++] = tmp->key_data;
		tmp = tmp->next;
	}
	return (0);
}

int	init_env_list(t_ms *ms, char **envv)
{
	int		idx;

	idx = -1;
	while (envv[++idx])
		if ((check_key(envv[idx]) == 1 || check_key(envv[idx]) == 3)
			&& parse_add_cmd(ms, envv[idx], 1))
			return (1);
	if (set_shlvl(ms))
		return (perror_i("minishell: set_shlvl: malloc failed:", 1, 0, 0));
	if (init_pwd_oldpwd(ms))
		return (perror_i("minishell: init PWD OLDPWD: malloc failed:"
				, 1, 0, 0));
	ms->exit_status = ft_itoa(0);
	if (!ms->exit_status)
		return (perror_i("minishell: init exit status: malloc failed:"
				, 1, 0, 0));
	if (set_env_table(ms))
		return (perror_i("minishell: init env table: malloc failed:"
				, 1, 0, 0));
	ms->cwd = getcwd(NULL, 0);
	if (!ms->cwd)
		return (perror_i("minishell: init getcwd: failed:", 1, 0, 0));
	return (0);
}

int	builtin_env(t_ms *ms, char **cmd)
{
	t_env	*tmp;

	if (!cmd || !cmd[0])
	{
		ft_putstr_fd("env: Error\n", 2);
		return (1);
	}
	if (cmd[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	tmp = ms->env_list;
	while (tmp)
	{
		if (tmp->key_data)
			printf("%s\n", tmp->key_data);
		tmp = tmp->next;
	}
	return (0);
}
