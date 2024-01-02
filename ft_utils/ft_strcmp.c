/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:08:20 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:08:23 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && ((s1[i] != '\0') && (s2[i] != '\0')))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	add_var_interro(t_gbl *gbl, int i)
{
	char	*var_interro;
	int		k;

	k = 0;
	var_interro = ft_itoa(gbl->exit_ret);
	while (var_interro[k])
	{
		gbl->i_v[i + k] = var_interro[k];
		k++;
	}
	gbl->i_v[i + k] = 0;
	free(var_interro);
	return (k);
}
