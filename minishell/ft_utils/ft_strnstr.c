/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:01:04 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:08:59 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	if (big == 0 && len == 0)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	if (little[i] == 0)
		return ((char *) big);
	while (big[i] != 0 && k < len)
	{
		while (big[i] && little[j] && big[i] == little[j] && (k + j) < len)
		{
			i++;
			j++;
			if (little[j] == 0)
				return ((char *)big + i - j);
		}
		k++;
		i = k;
		j = 0;
	}
	return (NULL);
}
