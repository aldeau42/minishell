/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:13:15 by aderouin          #+#    #+#             */
/*   Updated: 2024/01/27 19:13:17 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirections_fd(t_gbl *gbl, t_token *lst_ptr)
{
	if ((lst_ptr->next != NULL && lst_ptr->next->next != NULL
			&& lst_ptr->next->next->type == 1)
		|| (lst_ptr->next != NULL && lst_ptr->next->type == 1))
		gbl->next_pipe = 1;
	while (lst_ptr->next != NULL
		&& (lst_ptr->next->type == 2 || lst_ptr->next->type == 4))
	{
		if (lst_ptr->next->type == 2 && lst_ptr->next != NULL)
			gbl->prev_fd = single_entry(lst_ptr->next->prompt, gbl);
		if (lst_ptr->next->type == 4 && lst_ptr->next != NULL)
			gbl->prev_fd = limiter_fd(lst_ptr->next->prompt, gbl);
		lst_ptr = lst_ptr->next;
	}
	while (lst_ptr->next != NULL && lst_ptr->next->type != 1)
	{
		if (lst_ptr->next->type == 3 && lst_ptr->next != NULL)
			gbl->out_fd = single_exit(lst_ptr->next->prompt, gbl);
		if (lst_ptr->next->type == 5 && lst_ptr->next != NULL)
			gbl->out_fd = double_exit(lst_ptr->next->prompt, gbl);
		lst_ptr = lst_ptr->next;
	}
}

t_token	*start_exec4(t_gbl *gbl, t_lst *lst, t_token *lst_ptr)
{
	if (lst_ptr->type == 2 && lst_ptr->next
		!= NULL && lst_ptr->next->type == 1)
		lst_ptr = lst_ptr->next->next;
	redirections_fd(gbl, lst_ptr);
	if (gbl->prev_fd == -1)
	{
		lst_ptr = NULL;
		return (lst_ptr);
	}
	gbl->prev_fd = core_exec(gbl, lst_ptr->prompt, lst);
	lst_ptr = cat_exception2(gbl, lst_ptr);
	lst_ptr = next_prompt(gbl, lst_ptr);
	lst_ptr = lst_ptr->next;
	if (lst_ptr == NULL)
	{
		lst_ptr = NULL;
		return (lst_ptr);
	}
	lst_ptr = lst_ptr->next;
	return (lst_ptr);
}

int	start_exec3(char *prompt, t_gbl *gbl)
{
	if (ft_strncmp(prompt, "unset", 5) == 0
		&& gbl->cmd_num != 1)
		return (1);
	return (0);
}

void	start_exec2(t_gbl *gbl, t_lst *lst)
{
	t_token	*lst_ptr;

	lst_ptr = lst->head;
	while (gbl->cmd_ind < gbl->cmd_num)
	{
		gbl->next_pipe = 0;
		lst_ptr = cat_exception(gbl, lst_ptr);
		if (lst_ptr->type == 0 && lst_ptr->next != NULL
			&& lst_ptr->next->type == 2)
			lst_ptr = remove_chev(lst_ptr, gbl);
		if (lst_ptr == NULL)
			break ;
		if (start_exec3(lst_ptr->prompt, gbl) == 1)
			lst_ptr = lst_ptr->next;
		if (lst_ptr == NULL)
			break ;
		if (if_builtin_no_redir(gbl, lst_ptr->prompt, lst) == 1)
		{
			lst_ptr = start_exec4(gbl, lst, lst_ptr);
			if (lst_ptr == NULL)
				break ;
		}
		gbl->cmd_ind++;
	}
}

void	start_exec(t_gbl *gbl, t_lst *lst)
{
	t_token	*lst_ptr;

	lst_ptr = lst->head;
	gbl->pipe_limiter = 0;
	gbl->used_limiter = 0;
	cmd_pipe_counter(gbl, lst);
	gbl->prev_fd = STDIN_FILENO;
	gbl->out_fd = STDOUT_FILENO;
	while (ft_strcmp(lst_ptr->prompt, "cat") == 0 && lst_ptr->next != NULL
		&& lst_ptr->next->type == 1)
	{
		gbl->cat += 2;
		lst_ptr = lst_ptr->next;
		lst_ptr = lst_ptr->next;
	}
	start_exec2(gbl, lst);
	gbl->cmd_ind = 0;
}
