/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:12:43 by aderouin          #+#    #+#             */
/*   Updated: 2024/01/27 19:12:49 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	pipe_handler2(t_gbl *gbl)
{
	if (STDOUT_FILENO != gbl->out_fd)
	{
		if (dup2(gbl->out_fd, STDOUT_FILENO) == -1)
			dprintf(2, "minishell: error with pipe_fd3 dup2\n");
		close(gbl->out_fd);
	}
}

void	pipe_handler(t_gbl *gbl, int *pipe_fd)
{
	if (STDIN_FILENO != gbl->prev_fd)
	{
		if (dup2(gbl->prev_fd, STDIN_FILENO) == -1)
			dprintf(2, "minishell: error with pipe_fd1 dup2\n");
		close(gbl->prev_fd);
	}
	if (((gbl->cmd_num > 1) && gbl->cmd_ind \
		!= (gbl->cmd_num - 1) && ((gbl->flag != 1))))
	{
		close(pipe_fd[0]);
		if (gbl->pipe_limiter == 1 && gbl->next_pipe != 1)
		{
			if (dup2(gbl->out_fd, STDOUT_FILENO) == -1)
				dprintf(2, "minishell: error with limiter dup2\n");
		}
		else
		{
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				dprintf(2, "minishell: error with pipe_fd2 dup2\n");
		}
		gbl->flag = 0;
		gbl->pipe_limiter = 0;
		close(pipe_fd[1]);
	}
	pipe_handler2(gbl);
}
