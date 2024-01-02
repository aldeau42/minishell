/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:06:58 by aderouin          #+#    #+#             */
/*   Updated: 2023/04/13 17:06:59 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!little[i])
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (ft_strncmp(little, big + i, ft_strlen(little)) == 0
			&& i + ft_strlen(little) <= len)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
