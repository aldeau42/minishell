/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:01:43 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:05:29 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_isnum(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || '9' < str[i])
			return (-1);
		i++;
	}
	return (0);
}

int	is_same_var(char *envline, char *input)
{
	int	i;

	i = 0;
	while (envline[i] == input[i])
	{
		if (envline[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	free_split(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

char	*chaeck_var2(t_gbl *gbl, int opt)
{
	char	**args;
	int		i;

	i = get_env(gbl, opt);
	if (i == -1)
		return (0);
	args = ft_split(gbl->mini_env[i], '=');
	i = -1;
	while (args[1][++i])
	{
		if (args[1][i] != 34 || args[1][i] != 39)
		{
			printf("%c\n", args[1][i]);
			return (args[1]);
		}
	}
	return (0);
}
