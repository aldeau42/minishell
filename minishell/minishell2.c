/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:06:53 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:06:55 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	modif_exp(t_gbl *gbl, int i)
{
	int	len;

	len = 0;
	if (is_equal(gbl->exp_env[i]) == 1)
	{
		len = ft_strlen(gbl->exp_env[i]) + 2;
		gbl->exp_env[i][len] = '\0';
		gbl->exp_env[i][len - 1] = 34;
		len--;
		while (gbl->exp_env[i][len--] != '=')
			gbl->exp_env[i][len] = gbl->exp_env[i][len - 1];
		gbl->exp_env[i][len + 1] = 34;
	}
}

void	clone_env(t_gbl *gbl, char **env)
{
	int	i;

	gbl->mini_env = gc_malloc (&gbl->gc, sizeof(char) * 32768);
	gbl->exp_env = gc_malloc (&gbl->gc, sizeof(char) * 32768);
	i = 0;
	while (env[i])
	{
		gbl->mini_env[i] = ft_gcstrdup(env[i], gbl);
		gbl->exp_env[i] = ft_gcstrdup(env[i], gbl);
		modif_exp(gbl, i);
		i++;
	}
	gbl->mini_env[i] = NULL;
	gbl->exp_env[i] = NULL;
}
