/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_entry.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:09:29 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:09:46 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pass_quote(t_gbl *sg, int *i, char quote)
{
	(*i)++;
	while (sg->i_v[sg->st + (*i)] != quote)
	{
		if (sg->i_v[sg->st + (*i)] == '\0')
		{
			break ;
		}
		(*i)++;
	}
	(*i)++;
}

void	basic_entry2(int k, char *str_tempo, t_gbl *gbl, t_lst *lst)
{
	str_tempo[k] = 0;
	add_token(lst, str_tempo, 2, gbl);
	free(str_tempo);
}

void	basic_entry(int *i, t_gbl *gbl, t_lst *lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc(sizeof(char) * 32768);
	if (gbl->i_v[gbl->st + (*i)] == '>' && gbl->i_v[gbl->st + (*i) + 1] != '>')
		add_list_exec_error(gbl, lst, 0);
	if (gbl->i_v[gbl->st + (*i) + 1] == '>')
		(*i)++;
	(*i)++;
	while (gbl->i_v[gbl->st + (*i)] == ' ' && gbl->i_v[gbl->st + (*i)] != 0)
		(*i)++;
	while (gbl->i_v[gbl->st + (*i)] != ' ' && gbl->i_v[gbl->st + (*i)] != 0
		&& gbl->i_v[gbl->st + (*i)] != '<' && gbl->i_v[gbl->st + (*i)] != '>'
		&& gbl->i_v[gbl->st + (*i)] != '|')
	{
		str_tempo[k++] = gbl->i_v[gbl->st + (*i)];
		(*i)++;
	}
	if ((gbl->i_v[gbl->st + (*i)] == '<' && gbl->i_v[gbl->st + (*i) - 1]
			== '<') || (gbl->i_v[gbl->st + (*i)] == '>'
			&& gbl->i_v[gbl->st + (*i) - 1] == '>'))
		(*i)--;
	basic_entry2(k, str_tempo, gbl, lst);
}

void	entry_delimiteur(int *i, t_gbl *gbl, t_lst *t_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc(sizeof(char) * 32768);
	(*i) = (*i) + 2;
	while (gbl->i_v[gbl->st + (*i)] == ' ' && gbl->i_v[gbl->st + (*i)] != 0)
		(*i)++;
	while (gbl->i_v[gbl->st + (*i)] != ' ' && gbl->i_v[gbl->st + (*i)] != 0
		&& gbl->i_v[gbl->st + (*i)] != '>' && gbl->i_v[gbl->st + (*i)] != '<'
		&& gbl->i_v[gbl->st + (*i)] != '|')
	{
		str_tempo[k] = gbl->i_v[gbl->st + (*i)];
		(*i)++;
		k++;
	}
	if (gbl->i_v[gbl->st + (*i)] == '>'
		|| gbl->i_v[gbl->st + (*i)] == '<')
		(*i)--;
	str_tempo[k] = 0;
	add_token(t_lst, str_tempo, 4, gbl);
	free(str_tempo);
}

int	put_entry(t_gbl *gbl, t_lst *lst)
{
	int	i;

	i = 0;
	while (i < gbl->lg_str && gbl->i_v[gbl->st] != '\0')
	{
		if (gbl->i_v[gbl->st + i] == '\"' || gbl->i_v[gbl->st + i] == '\'')
			pass_quote(gbl, &i, gbl->i_v[gbl->st + i]);
		if (gbl->st + i <= gbl->lg_str && gbl->i_v[gbl->st + i] == '<'
			&& gbl->i_v[gbl->st + i + 1] == '<')
		{
			if (gbl->i_v[gbl->st + i + 2] == '>' || gbl->i_v[gbl->st + i + 2]
				== '<' || gbl->i_v[gbl->st + i + 2] == '|')
				return (0);
			entry_delimiteur(&i, gbl, lst);
		}
		else if (gbl->st + i <= gbl->lg_str && gbl->i_v[gbl->st + i] == '<')
		{
			if (gbl->i_v[gbl->st + i + 1] == '|')
				return (0);
			basic_entry(&i, gbl, lst);
		}
		i++;
	}
	return (1);
}
