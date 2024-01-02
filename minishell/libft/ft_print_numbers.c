/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:01:44 by aderouin          #+#    #+#             */
/*   Updated: 2023/04/18 17:36:30 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// %d, %i

void	ft_print_di(int nb, int *len)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*len) += 11;
	}
	else if (nb < 0)
	{
		ft_print_c('-', len);
		ft_print_di(nb * -1, len);
	}
	else
	{
		if (nb > 9)
			ft_print_di(nb / 10, len);
		ft_print_c(nb % 10 + '0', len);
	}
}

// %u

void	ft_print_u(unsigned int u, int *len)
{
	if (u >= 10)
		ft_print_u(u / 10, len);
	ft_print_c(u % 10 + '0', len);
}

// %x ou %X

void	ft_print_x(unsigned int nb, char x, int *len)
{
	unsigned int	i;
	char			s[25];
	char			*base;

	if (x == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	i = 0;
	if (nb == 0)
	{
		ft_print_c('0', len);
		return ;
	}
	while (nb != 0)
	{
		s[i] = base[nb % 16];
		nb = nb / 16;
		i++;
	}
	while (i--)
		ft_print_c(s[i], len);
}

// %p

void	ft_print_p(size_t ptr, int *len)
{
	int		i;
	char	s[25];
	char	*base;

	base = "0123456789abcdef";
	i = 0;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		(*len) += 5;
		return ;
	}
	write(1, "0x", 2);
	(*len) += 2;
	while (ptr != 0)
	{
		s[i] = base[ptr % 16];
		ptr = ptr / 16;
		i++;
	}
	while (i--)
		ft_print_c(s[i], len);
}
