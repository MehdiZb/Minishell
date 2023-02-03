/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/06/22 13:55:50 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	echo_n_option(char *option)
{
	int	idx;

	idx = 0;
	while (option && option[idx])
	{
		if (idx == 0 && option[idx] != '-')
			return (0);
		else if (idx && option[idx] != 'n')
			return (0);
		idx++;
	}
	if (!idx)
		return (0);
	return (1);
}

int	builtin_echo(t_ms *ms, char **cmd)
{
	int	option_n;

	(void)ms;
	cmd++;
	option_n = 0;
	while (echo_n_option(*cmd))
	{
		option_n = 1;
		cmd++;
	}
	while (*cmd)
	{
		ft_putstr_fd(*cmd, 1);
		if (*(++cmd))
			ft_putstr_fd(" ", 1);
	}
	if (!option_n)
		ft_putstr_fd("\n", 1);
	return (0);
}
