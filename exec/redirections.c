/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:13:00 by aderouin          #+#    #+#             */
/*   Updated: 2024/01/27 19:13:05 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	single_entry(char *infile, t_gbl *gbl)
{
	int	infile_fd;

	infile_fd = open(infile, O_RDWR, 0777);
	if (infile_fd < 0)
		error_mnger("minishell: error with single_entry open\n", 0);
	if (gbl->prev_fd != STDIN_FILENO)
		close(gbl->prev_fd);
	gbl->flag = 0;
	return (infile_fd);
}

int	single_exit(char *outfile, t_gbl *gbl)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (outfile_fd < 0)
		error_mnger("minishell: error with single_exit open\n", 0);
	if (gbl->out_fd != STDOUT_FILENO)
		close(gbl->out_fd);
	return (outfile_fd);
}

int	limiter_fd2(char *input, char *limiter, t_gbl *gbl, int *limit_pipe_fd)
{
	if (g_signal_flag == 130)
	{
		free(input);
		gbl->out_fd = limit_pipe_fd[1];
		printf("\n");
		return (-1);
	}
	else if (gbl->next_pipe == 1
		&& (strncmp(input, limiter, ft_strlen(limiter)) \
		== 0 && ft_strlen(input) == ft_strlen(limiter)))
	{
		return (-2);
	}
	else if (strncmp(input, limiter, ft_strlen(limiter)) \
		== 0 && ft_strlen(input) == ft_strlen(limiter))
	{
		return (-2);
	}
	return (0);
}

int	limiter_fd(char *limiter, t_gbl *gbl)
{
	int		limit_pipe_fd[2];
	char	*input;

	pipe(limit_pipe_fd);
	g_signal_flag = 43;
	signal(SIGQUIT, SIG_IGN);
	while ("Kendrick Lamar - The Heart Part V")
	{
		input = readline ("> ");
		if (limiter_fd2(input, limiter, gbl, limit_pipe_fd) == -2)
			break ;
		else if (limiter_fd2(input, limiter, gbl, limit_pipe_fd) == -1)
			return (-1);
		else
			ft_heredoc_input(input, limit_pipe_fd);
	}
	gbl->pipe_limiter = 1;
	close(limit_pipe_fd[1]);
	return (limit_pipe_fd[0]);
}

int	double_exit(char *outfile, t_gbl *gbl)
{
	int	outfile_fd;

	outfile_fd = open(outfile, O_CREAT | O_RDWR | O_APPEND, 0777);
	if (outfile_fd < 0)
		error_mnger("minishell: error with double_exit open\n", 0);
	if (gbl->out_fd != STDOUT_FILENO)
		close(gbl->out_fd);
	return (outfile_fd);
}
