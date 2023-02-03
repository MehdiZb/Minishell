/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:45 by lomeniga          #+#    #+#             */
/*   Updated: 2022/07/31 20:47:46 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

_Bool	is_field(char *ifs, char c)
{
	int		i;

	if (!ifs)
		return (0);
	i = 0;
	while (ifs[i])
	{
		if (ifs[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	split(char *str, int *start, int *i, t_list *lst)
{
	t_word	*new;

	new = xmalloc(sizeof(t_word));
	new->word = xmalloc(*i - *start + 1);
	new->next = NULL;
	quote_remove(str + *start, new->word, str + *i);
	if (lst->tail)
		lst->tail->next = new;
	else
		lst->head = new;
	lst->tail = new;
	lst->count++;
	*start = *i + 1;
}

void	field_split(char *ifs, char *str, t_list *lst)
{
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (is_field(ifs, str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '\'')
			while (str[++i] && str[i] != '\'')
				;
		else if (str[i] == '"')
			while (str[++i] && str[i] != '"')
				;
		else
			while (is_field(ifs, str[i]) && i - start > 0)
				split(str, &start, &i, lst);
		if (str[i])
			i++;
	}
	split(str, &start, &i, lst);
}
