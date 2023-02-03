/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 20:47:58 by lomeniga          #+#    #+#             */
/*   Updated: 2022/07/31 20:47:59 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEX_H
# define LEX_H

_Bool	delimit(t_lex *lex);
_Bool	less(t_lex *lex);
_Bool	over(t_lex *lex);
_Bool	delim_pipe(t_lex *lex);

#endif
