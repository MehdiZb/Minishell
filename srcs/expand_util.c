/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:42 by lomeniga          #+#    #+#             */
/*   Updated: 2022/07/31 20:47:43 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

void	count(t_exp *exp)
{
	if (exp->param)
		exp->count += ft_strlen(exp->param);
	else
	{
		exp->count++;
		exp->i++;
	}
}

void	copy(t_exp *exp)
{
	int		i;

	i = 0;
	if (exp->param)
	{
		while (exp->param[i])
		{
			exp->d[exp->j] = exp->param[i];
			if (exp->d[exp->j] == '\'' || exp->d[exp->j] == '\"')
				exp->d[exp->j] *= -1;
			exp->j++;
			i++;
		}
	}
	else
	{
		exp->d[exp->j] = exp->s[exp->i];
		exp->j++;
		exp->i++;
	}
}

char	*search_env(t_env *env, char *key, int n)
{
	int		i;

	while (env)
	{
		i = 0;
		while (i < n && key[i] == env->key[i])
			i++;
		if (i == n && !env->key[i])
			return (env->data);
		env = env->next;
	}
	return (NULL);
}

void	quote_remove(char *src, char *dst, char *end)
{
	while (src < end)
	{
		if (*src == '"')
		{
			src++;
			while (src < end && *src != '"')
				*dst++ = *src++;
		}
		else if (*src == '\'')
		{
			src++;
			while (src < end && *src != '\'')
				*dst++ = *src++;
		}
		else if (*src == '\'' * -1 || *src == '"' * -1)
			*dst++ = *src * -1;
		else
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
}
