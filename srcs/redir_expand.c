/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:48:25 by lomeniga          #+#    #+#             */
/*   Updated: 2022/08/15 14:08:55 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void	line_expand(t_exp *exp)
{
	while (exp->s[exp->i])
	{
		if (exp->s[exp->i] == '$')
			match_ident(exp);
		else
			exp->act(exp);
	}
}

void	lexpand(t_ms *ms, char *s, char **out)
{
	t_exp	exp;

	exp.param = NULL;
	exp.count = 0;
	exp.ms = ms;
	exp.s = s;
	exp.i = 0;
	exp.state = 0;
	exp.act = count;
	line_expand(&exp);
	exp.d = xmalloc(exp.count + 3);
	exp.j = 0;
	exp.i = 0;
	exp.act = copy;
	line_expand(&exp);
	exp.d[exp.j] = '\0';
	*out = exp.d;
}

extern volatile sig_atomic_t	g_isinted;

void	here_expand(t_ms *ms, t_redir *redir, char *dlim, int isexpand)
{
	char	*str;
	char	*line;

	redir->fd = open("/tmp", O_TMPFILE | O_RDWR, S_IWUSR | S_IRUSR);
	if (redir->fd < 0)
		perror(NULL);
	str = NULL;
	while (!g_isinted)
	{
		str = ms_gets("> ");
		if (g_isinted || !str || !ft_strcmp(dlim, str))
			break ;
		if (isexpand)
			lexpand(ms, str, &line);
		else
			line = str;
		ft_putstr_fd(line, redir->fd);
		ft_putstr_fd("\n", redir->fd);
		if (isexpand)
			xfree(line);
		xfree(str);
	}
	if (!str && !g_isinted)
		ft_putstr_fd("minishell warning: here document delimited by EOF\n", 2);
	xfree(str);
}

void	redir_expand(t_ms *ms, t_redir *redir)
{
	char	*out;
	char	*new;

	while (redir)
	{
		if (redir->type != IO_HERE)
			pexpand(ms, redir->file, &out);
		else
			out = redir->file;
		new = xmalloc(ft_strlen(out) + 1);
		quote_remove(out, new, out + ft_strlen(out));
		if (redir->type == IO_HERE)
		{
			if (!ft_strcmp(new, out))
				here_expand(ms, redir, new, 1);
			else
				here_expand(ms, redir, new, 0);
		}
		else
			xfree(out);
		redir->file = new;
		redir = redir->next;
	}
}
