/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:20:30 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:20:31 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env(t_gbl *gbl, int opt)
{
	size_t	i;

	i = -1;
	while (gbl->mini_env[++i])
	{
		if (opt == 2 && ft_strncmp("OLDPWD=", gbl->mini_env[i], 7) == 0)
			return (i);
		else if (opt == 3 && ft_strncmp("PWD=", gbl->mini_env[i], 4) == 0)
			return (i);
	}
	return (-1);
}

char	*ft_clear_env(char *str, t_gbl *gbl)
{
	int		i;
	char	*ret;

	ret = gc_malloc(&gbl->gc, sizeof(char) * 32768);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	own_env(t_gbl *gbl)
{
	int	i;

	i = -1;
	while (gbl->mini_env[++i])
		printf("%s\n", gbl->mini_env[i]);
}

void	modify_string_env(char *arg, t_gbl *gbl, int i)
{
	int		j;
	int		k;

	j = 0;
	k = 0;
	while (arg[j])
	{
		if (arg[j] == '\"' && arg[j + 1] != '\0')
			j++;
		if (arg[j] == '\"' && arg[j + 1] == '\0')
			break ;
		gbl->mini_env[i][k] = arg[j];
		k++;
		j++;
	}
	gbl->mini_env[i][k] = '\0';
}

void	add_env(char *arg, t_gbl *gbl)
{
	int	i;

	i = 0;
	if (is_equal(arg) == 1)
	{
		while (gbl->mini_env[i])
		{
			if (ft_strcmp(ft_clear_env(gbl->mini_env[i], gbl),
					ft_clear_env(arg, gbl)) == 0)
				break ;
			i++;
		}
		if (gbl->mini_env[i] == 0)
			gbl->mini_env[i] = gc_malloc(&gbl->gc, sizeof(char) * 32768);
		modify_string_env(arg, gbl, i);
		i++;
		gbl->mini_env[i] = 0;
	}
}
