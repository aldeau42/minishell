/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:20:42 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:02:32 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export(t_gbl *gbl)
{
	int	i;

	i = -1;
	while (gbl->exp_env[++i] != NULL)
	{
		printf("declare -x %s\n", gbl->exp_env[i]);
	}
}

void	swap_export(t_gbl *gbl)
{
	int		i;
	char	*tmp;

	i = 0;
	while (gbl->exp_env[i + 1])
	{
		if (ft_strcmp(gbl->exp_env[i], gbl->exp_env[i + 1]) > 0)
		{
			tmp = gbl->exp_env[i];
			gbl->exp_env[i] = gbl->exp_env[i + 1];
			gbl->exp_env[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

void	modify_string_exp(t_gbl *gbl, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (gbl->input[j] == ' ' || gbl->input[j] == '\t'
		|| gbl->input[j] == '\n')
		j++;
	while (gbl->input[j] != ' ' && gbl->input[j] != '\t'
		&& gbl->input[j] != '\n')
		j++;
	while (gbl->input[j] == ' ' || gbl->input[j] == '\t'
		|| gbl->input[j] == '\n')
		j++;
	while (gbl->input[j])
	{
		if (gbl->input[j] == '\"' && gbl->input[j + 1] != '\0')
			j++;
		if (gbl->input[j] == '\"' && gbl->input[j + 1] == '\0')
			break ;
		gbl->exp_env[i][k] = gbl->input[j];
		j++;
		k++;
	}
	gbl->exp_env[i][k] = '\0';
}

void	add_export(char *input, t_gbl *gbl)
{
	int	i;

	i = 0;
	while (gbl->exp_env[i])
	{
		if (ft_strcmp(ft_clear_env(gbl->exp_env[i], gbl),
				ft_clear_env(input, gbl)) == 0)
			break ;
		i++;
	}
	if (gbl->exp_env[i] == 0)
		gbl->exp_env[i] = gc_malloc(&gbl->gc, sizeof(char) * 32768);
	modify_string_exp(gbl, i);
	gbl->new_line = gbl->exp_env[i];
	modif_exp(gbl, i);
	i++;
	gbl->exp_env[i] = NULL;
	swap_export(gbl);
}

int	own_export(char *input, t_gbl *gbl)
{
	char	**args;

	args = ft_split(input, ' ');
	if (!args[1])
	{
		swap_export(gbl);
		if (!gbl->printexp)
			print_export(gbl);
		gbl->printexp = 1;
		ft_free_tab(args);
		return (0);
	}
	else if (('0' <= args[1][0] && args[1][0] <= '9') || args[1][0] == '=')
	{
		ft_putstr_fd("minishell: export: \'", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
		ft_free_tab(args);
		return (0);
	}
	add_export(args[1], gbl);
	add_env(gbl->new_line, gbl);
	ft_free_tab(args);
	return (0);
}
