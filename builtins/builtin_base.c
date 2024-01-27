/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:59:10 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:01:33 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	if_builtin_no_redir(t_gbl *gbl, char *prompt, t_lst *lst)
{
	if (ft_strncmp(prompt, "export", 6) == 0 && gbl->cmd_num == 1)
		own_export(prompt, gbl);
	else if (ft_strncmp(prompt, "unset", 5) == 0 && gbl->cmd_num == 1)
		own_unset(prompt, gbl);
	else if (ft_strncmp(prompt, "exit", 4) == 0 && gbl->cmd_num == 1)
		own_exit(prompt, gbl, lst);
	else if (ft_strncmp(prompt, "cd", 2) == 0 && gbl->cmd_num == 1)
		own_cd(prompt, gbl);
	else
		return (1);
	return (0);
}

int	if_builtin_redir(t_gbl *gbl, char *input)
{
	if (ft_strncmp(input, "echo", 4) == 0)
		own_echo(input, gbl);
	else if (ft_strncmp(input, "export", 6) == 0)
		own_export(input, gbl);
	else if (ft_strcmp(input, "pwd") == 0)
		own_pwd(gbl);
	else if (ft_strcmp(input, "env") == 0)
		own_env(gbl);
	else
		return (1);
	return (0);
}
