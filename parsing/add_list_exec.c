/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_list_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:03:25 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:10:37 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	seek_next_pipe(t_gbl *gbl, int st)
{
	int	lg_str;

	lg_str = 0;
	while (gbl->i_v[st + lg_str] != 0
		&& gbl->i_v[st + lg_str] != '|')
	{
		if (gbl->i_v[st + lg_str] == '\'')
		{
			lg_str++;
			while (gbl->i_v[st + lg_str] != '\'')
				lg_str++;
		}
		if (gbl->i_v[st + lg_str] == '"')
		{
			lg_str++;
			while (gbl->i_v[st + lg_str] != '"')
				lg_str++;
		}
		lg_str++;
	}
	return (lg_str);
}

void	add_list_exec_error(t_gbl *gbl, t_lst *lst, int c)
{
	gbl->exit_ret = 2;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token \'", 2);
	if (c == 0)
		ft_putstr_fd("<", 2);
	else
		ft_putstr_fd(">", 2);
	ft_putstr_fd("\'\n", 2);
	quit_exit_pars(gbl, lst);
}

int	add_list_exec(t_gbl *gbl, t_lst *lst)
{
	gbl->st = 0;
	gbl->lg_str = 0;
	while (gbl->i_v[gbl->st + gbl->lg_str] != 0)
	{
		gbl->st = gbl->st + gbl->lg_str;
		gbl->lg_str = seek_next_pipe(gbl, gbl->st);
		put_maillon_str(gbl, lst);
		if (put_entry(gbl, lst) == 0)
		{
			add_list_exec_error(gbl, lst, 0);
			return (0);
		}
		if (put_sorti(gbl, lst) == 0)
		{
			add_list_exec_error(gbl, lst, 1);
			return (0);
		}
		if (gbl->i_v[gbl->st + gbl->lg_str] == '|')
		{
			add_token(lst, "|", 1, gbl);
			gbl->st++;
		}
	}
	return (1);
}
