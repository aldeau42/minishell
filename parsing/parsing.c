/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:03:50 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:05:36 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quit_exit_pars(t_gbl *gbl, t_lst *lst)
{
	gc_clean(&gbl->gc);
	clear_t_lst(lst);
}

int	check_files_exist(t_lst *lst, t_gbl *gbl)
{
	t_token	*current;

	current = lst->head;
	while (current != NULL)
	{
		if (current->type == 2)
		{
			if (access(current->prompt, F_OK) == -1)
			{
				gbl->exit_ret = 1;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(current->prompt, 2);
				ft_putstr_fd(": no such file or directory\n", 2);
				quit_exit_pars(gbl, lst);
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	check_empty_prompt(t_lst *t_lst)
{
	int		i;
	t_token	*current;
	int		is_empty;

	current = t_lst->head;
	while (current != NULL)
	{
		is_empty = 0;
		i = 0;
		while (current->prompt[i] != 0)
		{
			if (current->prompt[i] != ' ')
				is_empty = 1;
			i++;
		}
		if (is_empty == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

int	parsing2(t_gbl *gbl, t_lst *lst)
{
	add_list_exec(gbl, lst);
	if (check_empty_prompt(lst) == 0)
	{
		gbl->exit_ret = 127;
		return (0);
	}
	if (check_files_exist(lst, gbl) == 0)
		return (0);
	return (1);
}

int	parsing(t_gbl *gbl, t_lst *lst)
{
	if (quote_check(gbl->input) == 0)
	{
		gbl->exit_ret = 2;
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putstr_fd("near unexpected token \' or \"\n", 2);
		return (0);
	}
	if (var_env_chang(gbl, lst) == 0)
		return (0);
	if (check_pipe_at_start(gbl) == 0)
	{
		gbl->exit_ret = 2;
		ft_putstr_fd("minishell: syntax error ", 2);
		ft_putstr_fd("near unexpected token \'|\'\n", 2);
		return (0);
	}
	if (parsing2(gbl, lst) == 0)
		return (0);
	return (1);
}
