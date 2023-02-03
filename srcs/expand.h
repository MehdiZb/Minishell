/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:38 by lomeniga          #+#    #+#             */
/*   Updated: 2022/08/05 14:17:37 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# define _GNU_SOURCE 
# include "minishell.h"

typedef struct s_exp
{
	t_ms	*ms;
	int		i;
	char	*s;
	char	*d;
	char	*param;
	int		j;
	int		state;
	int		count;
	void	(*act)(struct s_exp *exp);
}				t_exp;

void	match_ident(t_exp *exp);
void	copy(t_exp *exp);
void	count(t_exp *exp);
char	*search_env(t_env *env, char *key, int n);
void	field_split(char *ifs, char *str, t_list *lst);
void	quote_remove(char *src, char *dst, char *end);

#endif
