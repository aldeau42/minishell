/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:20:58 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:20:59 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	own_unset_exp(char **arg, int x, t_gbl *gbl)
{
	int	i;

	i = 0;
	while (gbl->exp_env[i])
	{
		if (ft_strncmp(gbl->exp_env[i], arg[1], x) == 0)
		{
			while (gbl->exp_env[i])
			{
				gbl->exp_env[i] = gbl->exp_env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
	ft_free_tab(arg);
}

void	own_unset2(char **args, t_gbl *gbl, int x)
{
	size_t	i;

	i = 0;
	while (gbl->mini_env[i])
	{
		if (ft_strncmp(gbl->mini_env[i], args[1], x) == 0)
		{
			while (gbl->mini_env[i])
			{
				gbl->mini_env[i] = gbl->mini_env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

void	own_unset(char *input, t_gbl *gbl)
{
	int		x;
	char	**args;

	args = ft_split(input, ' ');
	if (!args[1])
	{
		ft_free_tab(args);
		return ;
	}
	x = ft_strlen(args[1]);
	own_unset2(args, gbl, x);
	own_unset_exp(args, x, gbl);
}
