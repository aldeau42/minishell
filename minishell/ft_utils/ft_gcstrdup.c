/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gcstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:59:47 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:14:08 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_gcstrdup(const char *s, t_gbl *gbl)
{
	int		i;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (s[len])
		len++;
	dst = gc_malloc(&gbl->gc, sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	trim_spaces(char *str)
{
	int	start;
	int	end;
	int	i;

	start = 0;
	end = strlen(str) - 1;
	while (str[start] == ' ' || str[start] == '\t'
		|| str[start] == '\n' || str[start] == '\r')
	{
		start++;
	}
	while (end > start && (str[end] == ' ' || str[end] == '\t'
			|| str[end] == '\n' || str[end] == '\r'))
	{
		end--;
	}
	i = 0;
	while (start <= end)
	{
		str[i++] = str[start++];
	}
	str[i] = '\0';
}
