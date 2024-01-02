/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 21:32:37 by aderouin          #+#    #+#             */
/*   Updated: 2023/12/21 21:32:40 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*cat_exception2(t_gbl *gbl, t_token *lst_ptr)
{
	int	i;

	i = gbl->cat / 2;
	if (gbl->cat != 0)
	{
		while (i > 0)
		{
			readline("");
			i--;
		}
	}
	return (lst_ptr);
}

t_token	*cat_exception(t_gbl *gbl, t_token *lst_ptr)
{
	int	i;

	i = gbl->cat;
	if (gbl->cat > 0)
		gbl->cmd_num = 1;
	while (i > 0)
	{
		lst_ptr = lst_ptr->next;
		i--;
	}
	return (lst_ptr);
}

t_token	*remove_chev(t_token *lst_ptr, t_gbl *gbl)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	j = 0;
	temp = malloc(sizeof(char) * 9999);
	while (lst_ptr->prompt[++i])
		temp[i] = lst_ptr->prompt[i];
	temp[i] = ' ';
	i++;
	while (lst_ptr->next->prompt[j])
	{
		temp[i + j] = lst_ptr->next->prompt[j];
		j++;
	}
	temp[i + j] = '\0';
	lst_ptr = lst_ptr->next;
	lst_ptr->prompt = ft_gcstrdup(temp, gbl);
	lst_ptr->type = 0;
	gbl->cmd_ind = 1;
	free(temp);
	return (lst_ptr);
}

t_token	*next_prompt(t_gbl *gbl, t_token *lst_ptr)
{
	if (lst_ptr->next != NULL && lst_ptr->next->type == 2)
		lst_ptr = lst_ptr->next;
	if (lst_ptr->next != NULL && lst_ptr->next->type == 4)
		lst_ptr = lst_ptr->next;
	else if (lst_ptr->next != NULL && lst_ptr->next->type == 3)
	{
		gbl->out_fd = STDOUT_FILENO;
		lst_ptr = lst_ptr->next;
	}
	if (lst_ptr->next != NULL && lst_ptr->next->type == 5)
	{
		gbl->out_fd = STDOUT_FILENO;
		lst_ptr = lst_ptr->next;
	}
	return (lst_ptr);
}
