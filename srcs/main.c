/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mzblah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/11 02:14:18 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

volatile sig_atomic_t	g_isinted;

void	sig_int(int sig)
{
	char	c;

	(void)sig;
	g_isinted = 1;
	rl_done = 1;
	c = 4;
	ioctl(0, TIOCSTI, &c);
	write(2, "\n", 1);
}

char	*ms_gets(char *prompt)
{
	static char			*line_read;

	if (prompt)
	{
		signal(SIGINT, sig_int);
		line_read = readline(prompt);
		if (line_read && *line_read)
			add_history(line_read);
		signal(SIGINT, SIG_IGN);
	}
	else
	{
		line_read = readline(prompt);
	}
	return (line_read);
}

static void	init_ms(t_ms *ms, char **envv, char **prompt)
{
	signal(SIGQUIT, SIG_IGN);
	ms->isatty = isatty(0);
	rl_outstream = NULL;
	if (ms->isatty)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		rl_outstream = stderr;
		*prompt = "minishell$ ";
	}
	if (init_env_list(ms, envv))
		exit(1);
}

int	main(int ac, char **av, char **envv)
{
	static t_ms	ms;
	static char	*prompt;

	(void)((void)ac, av);
	init_ms(&ms, envv, &prompt);
	while (42)
	{
		g_isinted = 0;
		ms.line_read = ms_gets(prompt);
		if (g_isinted)
		{
			xfree(ms.exit_status);
			ms.exit_status = ft_itoa(130);
			xfree(ms.line_read);
			continue ;
		}
		if (!ms.line_read)
		{
			ms.cmd = NULL;
			builtin_exit(&ms, (char *[]){"exit", NULL});
		}
		if (ms.line_read && *ms.line_read)
			parse(&ms, ms.line_read);
		xfree(ms.line_read);
	}
}
