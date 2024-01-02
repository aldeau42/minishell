/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:20:14 by aderouin          #+#    #+#             */
/*   Updated: 2023/10/19 00:20:16 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd2(char **dir, int i, t_gbl *gbl)
{
	char	*new;
	char	*tmp;
	int		j;

	j = -1;
	gbl->new_pwd = "/";
	while (++j < i - 1)
	{
		tmp = ft_strjoin(dir[j], "/");
		new = ft_strjoin(gbl->new_pwd, tmp);
		gbl->new_pwd = ft_gcstrdup(new, gbl);
		free(tmp);
		free(new);
	}
}

void	change_pwd(t_gbl *gbl)
{
	int		i;
	char	**dir;
	char	*old;
	char	*new;

	i = 0;
	dir = ft_split(gbl->cur_pwd, '/');
	while (dir[i])
		i++;
	if (ft_strcmp(gbl->new_pwd, "..") == 0)
		change_pwd2(dir, i, gbl);
	else
	{
		old = ft_gcstrdup(gbl->cur_pwd, gbl);
		new = ft_strjoin(old, gbl->new_pwd);
		gbl->new_pwd = ft_gcstrdup(new, gbl);
		free(new);
	}
	ft_free_tab(dir);
}

void	modif_chdir(t_gbl *gbl, char *dir)
{
	int		i;
	char	*new;
	char	*cur;

	i = 0;
	if (chdir(dir) == -1)
		perror("minishell");
	else
	{
		gbl->new_pwd = dir;
		change_pwd(gbl);
		i = get_env(gbl, 3);
		new = ft_strjoin("PWD=", gbl->new_pwd);
		gbl->mini_env[i] = ft_gcstrdup(new, gbl);
		free(new);
		i = get_env(gbl, 2);
		cur = ft_strjoin("OLDPWD=", gbl->cur_pwd);
		gbl->mini_env[i] = ft_gcstrdup(cur, gbl);
		free(cur);
		gbl->cur_pwd = gbl->new_pwd;
	}
}

void	own_cd(char *str, t_gbl *gbl)
{
	char	**args;

	args = ft_split(str, ' ');
	if (!args[1])
	{
		chdir(getenv("HOME"));
		ft_free_tab(args);
		return ;
	}
	else if (args[2])
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	else if (args[1])
		modif_chdir(gbl, args[1]);
	else
		ft_putstr_fd("minishell: cd: usage: cd [-L|-P] [dir]\n", 2);
	ft_free_tab(args);
}
