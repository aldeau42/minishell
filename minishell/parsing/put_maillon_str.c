/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_maillon_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:03:59 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:09:12 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_single_quote(char *strtempo, int *i, int *redi_r, t_gbl *gbl)
{
	(*redi_r)++;
	while (gbl->i_v[gbl->st + *i + *redi_r] != '\'')
	{
		strtempo[*i] = gbl->i_v[gbl->st + *i + *redi_r];
		(*i)++;
	}
	(*redi_r)++;
	(*i)--;
}

void	process_double_quote(char *strtempo, int *i, int *redi_r, t_gbl *gbl)
{
	(*redi_r)++;
	while (gbl->i_v[gbl->st + *i + *redi_r] != '"')
	{
		strtempo[*i] = gbl->i_v[gbl->st + *i + *redi_r];
		(*i)++;
	}
	(*redi_r)++;
	(*i)--;
}

void	process_redi_rection(char *strtempo, int *i, int *redi_r, t_gbl *gbl)
{
	(*redi_r)++;
	while (gbl->i_v[gbl->st + (*i) + (*redi_r)] == ' '
		&& gbl->i_v[gbl->st + (*i) + (*redi_r)] != 0)
		(*redi_r)++;
	while (gbl->i_v[gbl->st + (*i) + (*redi_r)] != ' '
		&& gbl->i_v[gbl->st + (*i) + (*redi_r)] != 0
		&& gbl->i_v[gbl->st + (*i) + (*redi_r)] != '>'
		&& gbl->i_v[gbl->st + (*i) + (*redi_r)] != '<')
		(*redi_r)++;
	strtempo[(*i)] = ' ';
	(*redi_r)--;
}

void	put_maillon_str(t_gbl *gbl, t_lst *t_lst)
{
	char	*strtempo;
	int		i;
	int		redi_r;

	redi_r = 0;
	i = 0;
	strtempo = malloc (sizeof(char) * 32768);
	while (i + redi_r < gbl->lg_str)
	{
		if (gbl->i_v[gbl->st + i + redi_r] == '\'')
			process_single_quote(strtempo, &i, &redi_r, gbl);
		else if (gbl->i_v[gbl->st + i + redi_r] == '"')
			process_double_quote(strtempo, &i, &redi_r, gbl);
		else if (gbl->i_v[gbl->st + i + redi_r] == '>'
			|| gbl->i_v[gbl->st + i + redi_r] == '<')
			process_redi_rection(strtempo, &i, &redi_r, gbl);
		else
			strtempo[i] = gbl->i_v[gbl->st + i + redi_r];
		i++;
	}
	strtempo[i] = 0;
	trim_spaces(strtempo);
	add_token(t_lst, strtempo, 0, gbl);
	free (strtempo);
}
