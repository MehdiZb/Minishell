/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_calloc_itoa_strlen.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/07/26 15:13:33 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned long	i;

	i = 0;
	while (i < n)
		((char *)s)[i++] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	if (size && (__SIZE_MAX__ / size) < count)
		return (NULL);
	tab = (void *)xmalloc(count * size);
	if (!tab)
		return (0);
	ft_bzero(tab, count * size);
	return (tab);
}

static char	*while_itoa(int nb, int cmpt, char *str)
{
	unsigned int	nb_cpy;

	if (!nb)
	{
		str[0] = '0';
		return (str);
	}
	if (nb < 0)
		nb_cpy = -nb;
	else
		nb_cpy = nb;
	while (nb_cpy != 0)
	{
		str[cmpt--] = (nb_cpy % 10) + 48;
		nb_cpy /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	nb_cpy;
	int				cmpt;

	cmpt = 0;
	if (n >= 0)
		nb_cpy = n;
	else
		nb_cpy = -n;
	while (nb_cpy != 0 && ++cmpt)
		nb_cpy = nb_cpy / 10;
	if (n == 0)
		cmpt = 1;
	if (n < 0)
		cmpt++;
	str = ft_calloc(cmpt + 1, sizeof(char));
	if (!str)
		return (0);
	str = while_itoa(n, --cmpt, str);
	if (n < 0)
		str[0] = '-';
	return (str);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
