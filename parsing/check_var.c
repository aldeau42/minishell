/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:11:18 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:11:33 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(t_gbl *gbl, int i)
{
	int	j;

	gbl->path_temp = gc_malloc (&gbl->gc, sizeof(char) * 32768);
	i++;
	j = 0;
	while (gbl->input[i + j] != 0 && gbl->input[i + j] != ' '
		&& gbl->input[i + j] != '\"' && gbl->input[i + j] != '|')
	{
		gbl->path_temp[j] = gbl->input[i + j];
		j++;
	}
	gbl->path_temp[j] = 0;
	i = 0;
	while (gbl->mini_env[i])
	{
		if ((ft_strnstr(gbl->mini_env[i], gbl->path_temp,
					ft_strlen(gbl->path_temp)) != NULL)
			&& gbl->mini_env[i][ft_strlen(gbl->path_temp)] == '=')
			break ;
		i++;
	}
	if (gbl->mini_env[i] == 0)
		return (0);
	return (1);
}
