/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:20:21 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 17:11:15 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	write_echo(int n, char **args, t_gbl *gbl, int m)
{
	int	i;

	i = 0;
	if (n == 1)
		i = m;
	while (args[++i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] && args[i][0] != '\0')
			write(1, " ", 1);
	}
	if (n == 0)
		printf("\n");
	if (gbl->exit_ret != 0)
		gbl->exit_ret = 0;
	ft_free_tab(args);
}

int	own_echo2(t_gbl *gbl, char **args, int m, int i)
{
	int		n;

	n = 1;
	if (!args[2])
	{
		ft_free_tab(args);
		return (0);
	}
	if (check_arg(args[i]) == -1)
	{
		write_echo(n, args, gbl, m);
		return (0);
	}
	m += check_arg(args[i]);
	return (m);
}

void	own_echo(char *input, t_gbl *gbl)
{
	char	**args;
	int		i;
	int		n;
	int		m;

	i = 0;
	n = 0;
	m = 0;
	args = ft_split(input, ' ');
	while (args[++i])
	{
		if (args[1][0] == '-' && args[1][1] == 'n')
		{
			m = own_echo2(gbl, args, m, i);
			if (m == 0)
				return ;
		}
		else if (ft_strncmp(args[i], "$?", 2) == 0)
			printf("%d", gbl->exit_ret);
	}
	write_echo(n, args, gbl, m);
}

int	check_arg(char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (-1);
		i++;
	}
	return (1);
}
