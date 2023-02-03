/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/11 14:00:43 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	export_declare(t_ms *ms)
{
	t_env	*tmp_env;

	tmp_env = ms->env_list;
	while (tmp_env)
	{
		if (!ft_strcmp(tmp_env->key, "_"))
			;
		else if (tmp_env->data)
			printf("export %s=\'%s\'\n", tmp_env->key, tmp_env->data);
		else
			printf("export %s\n", tmp_env->key);
		tmp_env = tmp_env->next;
	}
	return (0);
}

/*
** set_concat_key_data(t_ms *ms, char **key, char **data)
**
** remove the '+' at the end of key
** concat data with previous data if it exist
*/
static int	set_concat_key_data(t_ms *ms, char **key, char **data)
{
	t_env	*tmp_env;
	char	*concat_data;
	size_t	key_len;

	key_len = ft_strlen(*key);
	(*key)[key_len - 1] = 0;
	tmp_env = *lst_getenv(ms, *key);
	if (!tmp_env)
		return (0);
	concat_data = ft_strjoin(tmp_env->data, *data);
	xfree(*data);
	if (!concat_data)
	{
		xfree(*key);
		return (1);
	}
	*data = concat_data;
	return (0);
}

int	parse_add_cmd(t_ms *ms, char *cmd, int check)
{
	char	*key;
	char	*data;

	key = ft_substr(cmd, 0, ft_chr_in_str(cmd, '=') - 1);
	if (!key)
		return (perror_i("minishell: export: failed key malloc:", 1, 0, 0));
	data = ft_substr(cmd, ft_chr_in_str(cmd, '='), ft_strlen(cmd));
	if (!data)
		return (perror_i("minishell: export: failed data malloc:", 1, key, 0));
	if (check == 2 && set_concat_key_data(ms, &key, &data))
		return (perror_i("minishell: export: failed concat keydata malloc:"
				, 1, 0, 0));
	if (add_var(ms, key, data))
		return (perror_i("minishell: export: failed concat keydata malloc:"
				, 1, key, data));
	if (!ft_strcmp("PATH", key))
		return (set_path(ms));
	return (0);
}

int	builtin_export(t_ms *ms, char **cmd)
{
	int		check;
	int		ret;

	ret = 0;
	if (!cmd[1])
		return (export_declare(ms));
	while (++cmd && *cmd)
	{
		check = check_key(*cmd);
		if (check == -1)
		{
			ret = 1;
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(*cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else if (check == 1 || check == 2)
			parse_add_cmd(ms, *cmd, check);
		else if (check == 3)
			if (add_var(ms, ft_strdup(*cmd), NULL))
				ret = perror_i("minishell: export: failed malloc:", 1, 0, 0);
	}
	if (set_env_table(ms))
		return (perror_i("minishell: export: failed malloc", 1, 0, 0));
	return (ret);
}
