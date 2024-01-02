/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:07:17 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:07:18 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg, t_gbl *gbl)
{
	gc_clean(&gbl->gc);
	free(gbl->input);
	perror(msg);
	exit(gbl->exit_ret);
}

void	handle_exit_status(t_gbl *gbl)
{
	if (WIFEXITED(gbl->status))
		gbl->exit_ret = (gbl->status / 256);
	else if (WIFSIGNALED(gbl->status))
		gbl->exit_ret = 128 + WTERMSIG(gbl->status);
	else
		gbl->exit_ret = 0;
}

void	signal_handler2(int sig)
{
	(void)sig;
	if (g_signal_flag == 42 && g_signal_flag != 130)
		g_signal_flag = 1;
	if (g_signal_flag == 43 && g_signal_flag != 130)
		exit(0);
	else
		g_signal_flag = 130;
}

void	signal_handler(int sig)
{
	(void)sig;
	if (g_signal_flag == 42)
		g_signal_flag = 1;
	if (g_signal_flag == 43)
	{
		g_signal_flag = 131;
		treat_signal();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		g_signal_flag = 130;
		treat_signal();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	treat_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

/*
		treat_signal();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
*/
