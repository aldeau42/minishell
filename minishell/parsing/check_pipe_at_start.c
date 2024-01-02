/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe_at_start.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:03:42 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:05:42 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_at_start(t_gbl *gbl)
{
	int	i;

	i = 0;
	while (gbl->input[i] == ' '
		|| gbl->input[i] == '\n' || gbl->input[i] == '\t')
		i++;
	if (gbl->i_v[i] == '|')
		return (0);
	return (1);
}

int	check_pipe_at_end(t_gbl *gbl)
{
	int	i;

	i = ft_strlen(gbl->input);
	i--;
	while (gbl->input[i] == ' ' || gbl->input[i] == '\n'
		|| gbl->input[i] == '\t')
		i--;
	if (gbl->input[i] == '|')
	{
		gbl->pipe_end = 1;
		return (0);
	}
	return (1);
}
