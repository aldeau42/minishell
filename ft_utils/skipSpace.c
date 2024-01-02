/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipSpace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 00:01:27 by aderouin          #+#    #+#             */
/*   Updated: 2023/11/11 18:13:49 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space(char *string, int i)
{
	int	j;

	j = 0;
	while ((string[i + j] == ' ' || string[i + j] == '\b'
			|| string[i + j] == '\t'
			|| string[i + j] == '\n') && string[i + j] != 0)
		j++;
	return (j);
}

char	*change_inp(t_gbl *gbl)
{
	int		i;
	int		j;
	char	*inp;

	j = 0;
	i = skip_space(gbl->input, 0);
	inp = (char *)malloc(sizeof(char) * 99999);
	while (gbl->input[i])
	{
		inp[j] = gbl->input[i];
		j++;
		i++;
	}
	inp[j] = '\0';
	return (inp);
}

void	err_(char *temp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(temp, 2);
	ft_putstr_fd(": Is a directory\n", 2);
	free(temp);
}

int	check_dir2(char *temp, int i)
{
	if (temp[i] == '\0' || (temp[i] == ' ' || temp[i] == '\t'
			|| temp[skip_space(temp, i)] == '\0'))
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		ft_putstr_fd(".: usage: . filename [arguments]\n", 2);
		free(temp);
		return (0);
	}
	else if (temp[i] == '/')
	{
		i++;
		if (temp[i] == '\0' || (temp[i] == ' ' || temp[i] == '\t'
				|| temp[skip_space(temp, i)] == '\0'))
		{
			err_(temp);
			return (0);
		}
	}
	return (1);
}

int	check_dir(t_gbl *gbl)
{
	char	*temp;
	int		i;

	temp = change_inp(gbl);
	i = 0;
	if (temp[i] == '.')
	{
		i++;
		if (check_dir2(temp, i) == 0)
			return (0);
	}
	else if (temp[i] == '/')
	{
		i++;
		if (temp[i] == '\0' || (temp[i] == ' ' || temp[i] == '\t'
				|| temp[skip_space(temp, i)] == '\0'))
		{
			err_(temp);
			return (0);
		}
	}
	free(temp);
	return (1);
}
