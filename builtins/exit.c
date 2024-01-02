/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:20:36 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 17:38:17 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quit_exit_exec(t_gbl *gbl, char *input, t_lst *lst)
{
	clear_t_lst(lst);
	gc_clean(&gbl->gc);
	free(input);
	exit(gbl->exit_ret);
}

void	quit_exit(t_gbl *gbl, char **args, t_lst *lst)
{
	gc_clean(&gbl->gc);
	free(gbl->input);
	ft_free_tab(args);
	clear_t_lst(lst);
	exit(gbl->exit_ret);
}

void	exit_num(t_gbl *gbl, char *arg)
{
	if (ft_atoi(arg) < 0)
		gbl->exit_ret = 255;
	else if (ft_atoi(arg) > 256)
		gbl->exit_ret = 127;
	else if (ft_atoi(arg) == 256)
		gbl->exit_ret = 0;
	else
		gbl->exit_ret = ft_atoi(arg);
}

void	own_exit(char *input, t_gbl *gbl, t_lst *lst)
{
	char	**args;

	args = ft_split(input, ' ');
	ft_putendl_fd("exit", 2);
	if (!args[1])
		quit_exit(gbl, args, lst);
	if (args[1] != 0 && ft_isnum(args[1]) == -1)
	{
		gbl->exit_ret = 2;
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		quit_exit(gbl, args, lst);
	}
	else if (args[1] && args[2])
	{
		gbl->exit_ret = 1;
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		ft_free_tab(args);
	}
	else if (args[1] != 0 && !args[2] && ft_isnum(args[1]) == 0)
	{
		exit_num(gbl, args[1]);
		quit_exit(gbl, args, lst);
	}
}
