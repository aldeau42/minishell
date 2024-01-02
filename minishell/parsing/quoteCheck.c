/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoteCheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:04:23 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:04:26 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_check(char *input)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				if (input[i++] == 0)
					return (0);
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"')
				if (input[i++] == 0)
					return (0);
		}
		i++;
	}
	return (1);
}

void	quote_var_env2(t_gbl *gbl, int *i, int *j)
{
	gbl->i_v[(*j)++] = gbl->input[(*i)++];
	while (gbl->input[(*i)] != '\"')
		gbl->i_v[(*j)++] = gbl->input[(*i)++];
	gbl->i_v[(*j)++] = gbl->input[(*i)++];
}

void	quote_var_env(t_gbl *gbl, int *i, int *j)
{
	gbl->i_v[(*j)++] = gbl->input[(*i)++];
	while (gbl->input[(*i)] != '\'')
		gbl->i_v[(*j)++] = gbl->input[(*i)++];
	gbl->i_v[(*j)++] = gbl->input[(*i)++];
}
