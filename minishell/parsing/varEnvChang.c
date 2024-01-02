/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varEnvChang.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:04:44 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:08:54 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_var3(t_gbl *gbl, t_lst *lst)
{
	if (gbl->bot == 1)
	{
		quit_exit_pars(gbl, lst);
		gbl->exit_ret = 0;
		return (-1);
	}
	return (0);
}

int	add_var2(t_gbl *gbl, int i, int j, int k)
{
	while (gbl->mini_env[j][ft_strlen(gbl->path_temp) + k + 1] != ' '
		&& gbl->mini_env[j][ft_strlen(gbl->path_temp) + k + 1] != 0)
	{
		gbl->i_v[i + k] = gbl->mini_env[j]
		[ft_strlen(gbl->path_temp) + k + 1];
		k++;
	}
	gbl->i_v[i + k] = 0;
	return (k);
}

int	add_var(t_gbl *gbl, int i, int o, t_lst *lst)
{
	int	j;
	int	k;

	j = 0;
	while (gbl->mini_env[j] != NULL)
	{
		if ((ft_strnstr(gbl->mini_env[j], gbl->path_temp,
					ft_strlen(gbl->path_temp)) != NULL)
			&& gbl->mini_env[j][ft_strlen(gbl->path_temp)] == '=')
		{
			gbl->bot = 0;
			break ;
		}
		j++;
	}
	if (add_var3(gbl, lst) == -1)
		return (-1);
	k = 0;
	if (o == 0)
	{
		gbl->i_v[i + k] = 0;
		return (k);
	}
	k = add_var2(gbl, i, j, k);
	return (k);
}

int	var_env_chang2(t_gbl *gbl, int *i, int *j, t_lst *lst)
{
	if (gbl->input[*(i) + 1] == '?')
	{
		*(j) += add_var_interro(gbl, *(j));
		*(i) += 2;
	}
	else if (check_var(gbl, *(i)) == 0)
	{
		if (add_var(gbl, *(j), 0, lst) == -1)
			return (0);
		*(j) += add_var(gbl, *(j), 0, lst);
		*(i) += ft_strlen(gbl->path_temp) + 1;
	}
	else if (check_var(gbl, *(i)) != 0)
	{
		if (add_var(gbl, *(j), 0, lst) == -1)
			return (0);
		*(j) += add_var(gbl, *(j), 1, lst);
		*(i) += ft_strlen(gbl->path_temp) + 1;
	}
	else
		return (0);
	return (1);
}

int	var_env_chang(t_gbl *gbl, t_lst *lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	gbl->bot = 1;
	if (ft_strncmp(gbl->input, "$PATH", 5) == 0)
		gbl->path = 1;
	gbl->i_v = gc_malloc(&gbl->gc, sizeof(char) * 327689);
	while (gbl->input[i])
	{
		if (gbl->input[i] == '\'')
			quote_var_env(gbl, &i, &j);
		else if (gbl->input[i] == '$' && gbl->input[i + 1] != ' ')
		{
			if (var_env_chang2(gbl, &i, &j, lst) == 0)
				return (0);
		}
		else
			gbl->i_v[j++] = gbl->input[i++];
	}
	gbl->i_v[j] = '\0';
	return (1);
}
