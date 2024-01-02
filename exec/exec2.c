/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:14:26 by mgourlai          #+#    #+#             */
/*   Updated: 2023/10/04 15:14:29 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

void	pathfinder_errors(t_gbl *gbl, char *prompt)
{
	char	*path_line;

	gbl->exit_ret = 127;
	if (gbl->path == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(prompt, 2);
		if ((prompt[0] == '.' && prompt[1] == '/') || prompt[0] == '/')
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		return ;
	}
	path_line = ft_gcstrdup(prompt, gbl);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path_line, 2);
	ft_putstr_fd(": command not found\n", 2);
}

char	*pathfinder2(char **arg, char **tabpath)
{
	char	*realpath;
	char	*temppath;
	int		i;

	i = -1;
	while (tabpath[++i])
	{
		temppath = ft_strjoin(tabpath[i], "/");
		realpath = ft_strjoin(temppath, arg[0]);
		free(temppath);
		if (access(realpath, F_OK) == 0)
		{
			free(tabpath);
			return (realpath);
		}
		free(realpath);
	}
	ft_free_tab(tabpath);
	return (0);
}

char	*pathfinder(t_gbl *gbl, char **arg, char *prompt)
{
	char	**tabpath;
	char	*ret;
	int		i;

	i = 0;
	i = check_path(gbl);
	if (gbl->path == 0)
	{
		pathfinder_errors(gbl, prompt);
		return (0);
	}
	tabpath = ft_split(gbl->mini_env[i] + 5, ':');
	ret = pathfinder2(arg, tabpath);
	if (ret)
		return (ret);
	if (access(prompt, F_OK) == 0)
		return (prompt);
	pathfinder_errors(gbl, prompt);
	return (0);
}

void	execute_2(t_gbl *gbl, char *prompt)
{
	char	**argtab;
	char	*path;

	argtab = ft_split_max(prompt, ' ');
	path = pathfinder(gbl, argtab, prompt);
	if (gbl->path == 0)
	{
		ft_free_tab(argtab);
		return ;
	}
	if (path != NULL)
	{
		access(argtab[0], F_OK);
		if (execve(path, argtab, gbl->mini_env) == -1)
		{
			gbl->exit_ret = 126;
			ft_putstr_fd("minishell: ./", 2);
			ft_putstr_fd(argtab[0], 2);
			ft_putstr_fd(": is not a binary\n", 2);
			ft_free_tab(argtab);
			return ;
		}
	}
	ft_free_tab(argtab);
}

void	execute(t_gbl *gbl, char *prompt)
{
	char	**argtab;
	char	*path;

	argtab = ft_split_max(prompt, ' ');
	path = pathfinder(gbl, argtab, prompt);
	if (gbl->path == 0)
	{
		ft_free_tab(argtab);
		return ;
	}
	if (path != 0)
	{
		if (execve(path, argtab, gbl->mini_env) == -1)
		{
			ft_putstr_fd("minishell: error could not execute binary\n", 2);
			free(path);
		}
	}
	ft_free_tab(argtab);
}
