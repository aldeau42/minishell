/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sortie.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:11:48 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:11:56 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	basic_out(int *i, t_gbl *gbl, t_lst *lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 32768);
	(*i)++;
	while (gbl->i_v[gbl->st + (*i)] == ' '
		&& gbl->i_v[gbl->st + (*i)] != 0)
		(*i)++;
	while (gbl->i_v[gbl->st + (*i)] != ' '
		&& gbl->i_v[gbl->st + (*i)] != 0
		&& gbl->i_v[gbl->st + (*i)] != '>'
		&& gbl->i_v[gbl->st + (*i)] != '<'
		&& gbl->i_v[gbl->st + (*i)] != '|')
	{
		str_tempo[k] = gbl->i_v[gbl->st + (*i)];
		(*i)++;
		k++;
	}
	if (gbl->i_v[gbl->st + (*i)] == '>'
		|| gbl->i_v[gbl->st + (*i)] == '<')
		(*i)--;
	str_tempo[k] = '\0';
	add_token(lst, str_tempo, 3, gbl);
	free(str_tempo);
}

void	sorti_append(int *i, t_gbl *gbl, t_lst *t_lst)
{
	char	*str_tempo;
	int		k;

	k = 0;
	str_tempo = malloc (sizeof(char) * 32768);
	(*i) = (*i) + 2;
	while (gbl->i_v[gbl->st + (*i)] == ' '
		&& gbl->i_v[gbl->st + (*i)] != 0)
		(*i)++;
	while (gbl->i_v[gbl->st + (*i)] != ' '
		&& gbl->i_v[gbl->st + (*i)] != 0
		&& gbl->i_v[gbl->st + (*i)] != '>'
		&& gbl->i_v[gbl->st + (*i)] != '<'
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
	add_token(t_lst, str_tempo, 5, gbl);
	free(str_tempo);
}

int	put_sorti(t_gbl *gbl, t_lst *t_lst)
{
	int	i;

	i = 0;
	while (i < gbl->lg_str)
	{
		if (gbl->i_v[gbl->st + i] == '"' || gbl->i_v[gbl->st + i] == '\'')
			pass_quote(gbl, &i, gbl->i_v[gbl->st + i]);
		if (gbl->i_v[gbl->st + i] == '>' && gbl->i_v[gbl->st + i + 1] != '>')
		{
			if (gbl->i_v[gbl->st + i + 1] == '<'
				|| gbl->i_v[gbl->st + i + 1] == '|')
				return (0);
			basic_out(&i, gbl, t_lst);
		}
		else if (gbl->i_v[gbl->st + i] == '>'
			&& gbl->i_v[gbl->st + i + 1] == '>')
		{
			if (gbl->i_v[gbl->st + i + 2] == '>'
				|| gbl->i_v[gbl->st + i + 2] == '<')
				return (0);
			sorti_append(&i, gbl, t_lst);
		}
		i++;
	}
	return (1);
}
