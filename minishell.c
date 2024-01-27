/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:06:27 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 17:34:29 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_flag = 0;

void	main_init(t_gbl *gbl)
{
	gbl->pipe_end = 0;
	gbl->status = 0;
	gbl->path = 0;
	gbl->next_pipe = 0;
	gbl->cat = 0;
	gbl->printexp = 0;
}

void	treat_input(t_gbl *gbl, t_lst *lst)
{
	add_history(gbl->input);
	if (check_dir(gbl) == 0)
	{
		gc_clean(&gbl->gc);
		free(gbl->input);
		clear_t_lst(lst);
		exit(gbl->exit_ret);
	}
	else if ((gbl->input[0] != '\0') && (parsing(gbl, lst) == 1)
		&& check_dir(gbl) == 1)
	{
		if (check_pipe_at_end(gbl) == 1)
			start_exec(gbl, lst);
		else if (check_pipe_at_end(gbl) == 0)
			pipe_at_end(gbl, lst);
	}
	free(gbl->input);
	clear_t_lst(lst);
}

void	main_loop(t_gbl *gbl, t_lst *lst)
{
	while (1)
	{
		main_init(gbl);
		if (g_signal_flag == 42 || g_signal_flag == 43)
			g_signal_flag = 0;
		gbl->input = readline("🤖 \033\e[1m\e[36mMinishell ➤ \033[0m");
		if (g_signal_flag == 130)
		{
			gbl->exit_ret = 130;
			g_signal_flag = 0;
		}
		if (!gbl->input)
		{
			free(gbl->input);
			gc_clean(&gbl->gc);
			exit(gbl->exit_ret);
		}
		treat_input(gbl, lst);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_gbl				gbl;
	t_lst				t_lst;
	char				cwd[PATH_MAX];

	(void)argc;
	(void)argv;
	gbl.exit_ret = 0;
	gbl.cmd_not_found = 0;
	if (getcwd(cwd, PATH_MAX))
		gbl.cur_pwd = cwd;
	gc_init(&gbl.gc);
	t_lst.head = NULL;
	treat_signal();
	clone_env(&gbl, env);
	main_loop(&gbl, &t_lst);
	rl_clear_history();
	gc_clean(&gbl.gc);
	return (0);
}
