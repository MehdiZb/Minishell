/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/15 16:08:07 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**lst_getenv(t_ms *ms, char *key)
{
	t_env	**tmp;

	tmp = &(ms->env_list);
	while (*tmp)
	{
		if (!ft_strcmp(key, (*tmp)->key))
			return (tmp);
		tmp = &((*tmp)->next);
	}
	return (tmp);
}

int	set_path(t_ms *ms)
{
	t_env	*tmp;
	int		idx;

	if (ms->path)
	{
		idx = 0;
		while (ms->path[idx])
			xfree(ms->path[idx++]);
		xfree(ms->path);
		ms->path = NULL;
	}
	tmp = *lst_getenv(ms, "PATH");
	if (tmp)
	{
		ms->path = ft_split(tmp->data, ':');
		if (!ms->path)
			return (1);
	}
	return (0);
}

/*
** check_key(char *key)
**
** return case :
** -1 = not a valid identifier
**  1 = valid key + data assignation
**  2 = valid key + data concatenation
**  3 = valid key
*/
int	check_key(char *key)
{
	int		cmpt;

	if (key[0] == 0)
		return (-1);
	if (key[0] >= '0' && key[0] <= '9')
		return (-1);
	cmpt = -1;
	while (key[++cmpt])
	{
		if (cmpt > 0 && key[cmpt] == '=')
			return (1);
		if (cmpt > 0 && key[cmpt] == '+' && key[cmpt + 1] == '=')
			return (2);
		if (!ft_isalnum(key[cmpt]) && key[cmpt] != '_')
			return (-1);
	}
	return (3);
}

int	set_keydata(t_env *var, char *key, char *data)
{
	char	*tmp_str;

	if (var->key)
		var->key = 0;
	if (var->data)
		var->data = 0;
	if (var->key_data)
		var->key_data = 0;
	var->key = key;
	var->data = data;
	if (!var->data)
		return (0);
	tmp_str = ft_strjoin(var->key, "=");
	if (!tmp_str)
		return (1);
	var->key_data = ft_strjoin(tmp_str, var->data);
	xfree(tmp_str);
	if (!var->key_data)
		return (1);
	return (0);
}

int	add_var(t_ms *ms, char *key, char *data)
{
	t_env	**tmp;

	if (!key)
	{
		if (data)
			xfree(data);
		return (1);
	}
	tmp = lst_getenv(ms, key);
	if (!*tmp)
		*tmp = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!*tmp)
		return (1);
	if ((*tmp)->key)
		xfree((*tmp)->key);
	if ((*tmp)->data)
		xfree((*tmp)->data);
	if ((*tmp)->key_data)
		xfree((*tmp)->key_data);
	return (set_keydata(*tmp, key, data));
}
