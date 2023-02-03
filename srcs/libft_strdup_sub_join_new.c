/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_strdup_sub_join_new.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lomeniga & mzblah                          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 12:51:03 by mzblah            #+#    #+#             */
/*   Updated: 2022/07/26 15:13:33 by lomeniga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strnew(0));
	str = ft_strnew(len);
	if (!str)
		return (0);
	i = 0;
	while (i < len && (s + start)[i])
	{
		str[i] = (s + start)[i];
		i++;
	}
	return (str);
}

char	*ft_strdup(const char *str)
{
	char	*ret_str;
	int		len_str;
	int		i;

	len_str = ft_strlen(str);
	i = 0;
	ret_str = ft_strnew(len_str);
	if (!(ret_str))
		return (0);
	while (i < len_str)
	{
		ret_str[i] = str[i];
		i++;
	}
	return (ret_str);
}

char	*ft_strnew(size_t size)
{
	char			*str;

	str = (char *)xmalloc(sizeof(char) * (size + 1));
	if (!(str))
		return (0);
	ft_bzero(str, (size + 1));
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	str_len;

	str_len = 0;
	if (!s1 && !s2)
		return (0);
	if (s1)
		str_len = (size_t)ft_strlen(s1);
	if (s2)
		str_len += (size_t)ft_strlen(s2);
	str = ft_strnew(str_len);
	if (!str)
		return (0);
	if (s1)
		ft_strcat(str, s1);
	if (s2)
		ft_strcat(str, s2);
	return (str);
}

char	*ft_strcat(char *dest, const char *src)
{
	int	i;
	int	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}
