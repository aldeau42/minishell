/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_at_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:36:43 by aderouin          #+#    #+#             */
/*   Updated: 2023/12/03 18:36:45 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_at_end2(t_gbl *gbl, t_lst *lst)
{
	if (g_signal_flag == 130)
	{
		gbl->exit_ret = 130;
		g_signal_flag = 0;
		printf("\n");
		return ;
	}
	gbl->cmd_ind++;
	if (gbl->input[0] != '\0')
	{
		add_history(gbl->input);
		if ((parsing(gbl, lst) == 1) && (check_pipe_at_end(gbl) == 1))
			start_exec(gbl, lst);
	}
	clear_t_lst(lst);
}

void	pipe_at_end(t_gbl *gbl, t_lst *lst)
{
	t_token	*lst_ptr;

	lst_ptr = lst->head;
	cmd_pipe_counter(gbl, lst);
	gbl->pipe_num -= 1;
	gbl->prev_fd = STDIN_FILENO;
	gbl->out_fd = STDOUT_FILENO;
	redirections_fd(gbl, lst_ptr);
	lst_ptr = lst_ptr->next;
	signal(SIGQUIT, SIG_IGN);
	gbl->input = readline ("> ");
	pipe_at_end2(gbl, lst);
}

void	ft_heredoc_input(char *input, int *pipe_fd)
{
	write(pipe_fd[1], input, ft_strlen(input));
	write(pipe_fd[1], "\n", 1);
	free(input);
}

int	check_path(t_gbl *gbl)
{
	int	i;

	i = 0;
	while (gbl->mini_env[i] != NULL)
	{
		if (ft_strncmp(gbl->mini_env[i], "PATH=", 5) == 0)
		{
			gbl->path = 1;
			break ;
		}
		i++;
	}
	return (i);
}
