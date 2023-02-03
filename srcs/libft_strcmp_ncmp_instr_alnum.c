/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_strcmp_ncmp_instr_alnum.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/07/26 15:13:33 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
		{
			if ((s1[i] > s2[i]))
				return (1);
			return (-1);
		}
		i++;
	}
	if (i == n)
		return (0);
	return (s1[i] + s2[i]);
}

int	ft_chr_in_str(const char *src, int chr)
{
	int	i;

	i = -1;
	if (!src)
		return (0);
	while (src[++i])
		if (src[i] == chr)
			return (i + 1);
	return (0);
}

int	ft_isalnum(int i)
{
	if ((i >= '0' && i <= '9') || (i >= 'a' && i <= 'z')
		|| (i >= 'A' && i <= 'Z'))
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
	{
		if (s1 == s2)
			return (0);
		return (1);
	}
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
