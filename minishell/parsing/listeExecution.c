/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeExecution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:06:10 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 16:19:05 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_token(t_lst *t_lst, char *prompt, int type, t_gbl *gbl)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	new_node->prompt = ft_gcstrdup(prompt, gbl);
	new_node->type = type;
	new_node->next = NULL;
	last_node = t_lst->head;
	if (last_node == NULL)
	{
		t_lst->head = new_node;
		gbl->t_lst = t_lst;
	}
	else
	{
		while (last_node->next != NULL)
			last_node = last_node->next;
		last_node->next = new_node;
	}
	gbl->cmd_num++;
}

void	afficher_tokens(t_lst *t_lst)
{
	t_token	*current;

	current = t_lst->head;
	while (current != NULL)
	{
		printf("Token: %s, Type: %d\n",
			current->prompt, current->type);
		current = current->next;
	}
}

void	clear_t_lst(t_lst *t_lst)
{
	t_token	*current;
	t_token	*temp;

	current = t_lst->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	t_lst->head = NULL;
}
