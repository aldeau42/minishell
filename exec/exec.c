/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:12:14 by aderouin          #+#    #+#             */
/*   Updated: 2024/01/27 19:12:18 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	child_process_exec(t_gbl *gbl, char *prompt, char *input, t_lst *lst)
{
	char	*path;

	if (if_builtin_redir(gbl, prompt) == 0)
		quit_exit_exec(gbl, input, lst);
	else if (access(input, F_OK) == 0)
	{
		path = absolute_path(prompt);
		execute_2(gbl, path);
		free(path);
	}
	else
		execute(gbl, prompt);
	quit_exit_exec(gbl, input, lst);
}

int	core_exec3(t_gbl *gbl, char *input, int *fd)
{
	waitpid(gbl->pid, &gbl->status, 0);
	free(input);
	handle_exit_status(gbl);
	if (gbl->out_fd != STDOUT_FILENO)
		close(gbl->out_fd);
	if (gbl->prev_fd != STDIN_FILENO)
		close(gbl->prev_fd);
	if (gbl->cmd_ind != gbl->cmd_num - 1)
		close(fd[1]);
	if (gbl->cmd_ind != gbl->cmd_num - 1)
		return (fd[0]);
	return (0);
}

void	core_exec2(t_gbl *gbl, int *fd)
{
	if (gbl->pid == -1)
		ft_putstr_fd("minishell: error with fork\n", 2);
	if (gbl->pid == 0)
	{
		if (g_signal_flag == 1)
		{
			printf("\n");
			return ;
		}
		pipe_handler(gbl, fd);
	}
}

int	core_exec(t_gbl *gbl, char *prompt, t_lst *lst)
{
	char	*input;
	int		fd[2];
	int		ret;

	ret = 0;
	input = malloc(sizeof(char) * (ft_strlen_max(prompt) + 1));
	if (!input)
		ft_putstr_fd("minishell: error with input malloc\n", 2);
	input = ft_remove_option(prompt, input);
	if (gbl->cmd_ind != gbl->cmd_num - 1)
		pipe(fd);
	g_signal_flag = 42;
	gbl->pid = fork();
	core_exec2(gbl, fd);
	if (gbl->pid == 0)
		child_process_exec(gbl, prompt, input, lst);
	ret = core_exec3(gbl, input, fd);
	return (ret);
}
