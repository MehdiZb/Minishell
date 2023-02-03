/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/11 13:57:28 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	delete_var(t_ms *ms, t_env **var)
{
	t_env	*tmp;
	int		ctrl;

	ctrl = 0;
	if (!(*var))
		return (0);
	tmp = ((*var)->next);
	if (var && *var && !ft_strcmp((*var)->key, "PATH"))
		ctrl = 1;
	if (var && *var && (*var)->key)
		xfree ((*var)->key);
	if (var && *var && (*var)->data)
		xfree ((*var)->data);
	if (var && *var && (*var)->key_data)
		xfree ((*var)->key_data);
	if (var && *var)
		xfree (*var);
	*var = tmp;
	if (ctrl)
		set_path(ms);
	return (0);
}

// tester unset avec des caracteres speciaux
int	builtin_unset(t_ms *ms, char **cmd)
{
	int		idx;
	int		ret;

	if (!cmd || !cmd[0])
		return (1);
	idx = 0;
	ret = 0;
	while (cmd[++idx])
	{
		if (check_key(cmd[idx]) != 3)
		{
			ret = 1;
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd[idx], 2);
			ft_putstr_fd("\': not a valid identifier\n", 2);
		}
		else
			delete_var(ms, lst_getenv(ms, cmd[idx]));
	}
	if (set_env_table(ms))
		return (perror_i("minishell: unset: failed malloc", 1, 0, 0));
	return (ret);
}
