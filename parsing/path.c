/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:46:49 by aderouin          #+#    #+#             */
/*   Updated: 2023/12/21 01:46:50 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	absolute_path2(char *path, int i)
{
	while (path[i] != '/' && i >= 0)
		i--;
	if (path[i] == '/' && i >= 0)
	{
		i--;
		if (path[i] == '.' && i >= 0)
		{
			i--;
			if (path[i] == '.' && i >= 0)
				i--;
		}
		else
			i++;
	}
	return (i);
}

char	*absolute_path(char *path)
{
	int		i;
	int		j;
	char	*new;

	i = ft_strlen(path);
	i = absolute_path2(path, i);
	j = i + 1;
	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(path) - j) + 1);
	while (path[j])
	{
		new[i] = path[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
