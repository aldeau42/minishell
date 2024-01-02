/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgourlai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:07:54 by mgourlai          #+#    #+#             */
/*   Updated: 2023/10/04 15:07:54 by mgourlai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_pipe_counter(t_gbl *gbl, t_lst *lst)
{
	t_token	*lst_ptr;

	lst_ptr = lst->head;
	gbl->pipe_num = 0;
	gbl->cmd_num = 0;
	gbl->cmd_ind = 0;
	gbl->flag = 0;
	while (lst_ptr != NULL)
	{
		if (lst_ptr->type == 1)
			gbl->pipe_num++;
		else
			gbl->cmd_num++;
		lst_ptr = lst_ptr->next;
	}
}

char	*ft_remove_option(char *prompt, char *input)
{
	int	i;

	i = 0;
	while (prompt[i] != ' ' && prompt[i] != '\0')
	{
		input[i] = prompt[i];
		i++;
	}
	input[i] = '\0';
	return (input);
}

char	*ft_strdup_max(const char *s)
{
	int		i;
	char	*dst;
	int		len;

	len = 0;
	i = 0;
	while (s[len])
		len++;
	dst = malloc (sizeof(char) * len + 1);
	if (dst == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*desti;
	char	*srci;

	desti = (char *) dest;
	srci = (char *) src;
	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		desti[i] = srci[i];
		i++;
	}
	return (desti);
}

int	ft_strncmp_max(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (((s1[i] != '\0') || (s2[i] != '\0')) && (i < n))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}
