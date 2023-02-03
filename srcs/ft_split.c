/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:39:19 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/03 08:55:35 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	ft_strlen_split(char *str, char charset)
{
	int	len;

	len = 0;
	if (charset == '\0')
	{
		while (str[len])
			len++;
		return (len);
	}
	while (str[len])
	{
		if (str[len] == charset)
			break ;
		len++;
	}
	return (len);
}

static char	**ft_fill_tab(char *str, char c, char **tab)
{
	int	j;
	int	i;
	int	cmpt;

	cmpt = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			tab[j] = malloc(sizeof(char) * (ft_strlen_split((str + i), c) + 1));
			if (!(tab[j]))
				return ((void *) NULL);
			cmpt = 0;
			while (str[i] && str[i] != c)
				tab[j][cmpt++] = str[i++];
			tab[j++][cmpt] = '\0';
		}
	}
	tab[j] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		nbwords;
	int		i;

	if (!s)
		return (0);
	nbwords = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			nbwords++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	tab = ft_calloc(nbwords + 1, sizeof(char *));
	if (!tab)
		return (0);
	return (ft_fill_tab((char *)s, c, tab));
}
