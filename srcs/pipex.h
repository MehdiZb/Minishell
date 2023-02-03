/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/08/03 07:04:19 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "parse.h"
# include "minishell.h"

typedef struct s_pair
{
	int		in;
	int		out;
}				t_pair;

void	signaal(void);
void	panic(void);
int		redir_err(t_redir *redir);
int		panic_open(char *path, int flags);
int		create_file(char *path, int flags, int mode);
int		open_redir(t_redir *redir, int *fd_open);
int		write_redir(t_redir *redir, int *fd_write);

#endif
