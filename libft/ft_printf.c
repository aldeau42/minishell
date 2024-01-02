/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderouin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 14:58:07 by aderouin          #+#    #+#             */
/*   Updated: 2023/05/01 16:49:47 by aderouin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	format(char fmt, va_list *ap, int *len, int *i)
{
	if (fmt == 's')
		ft_print_s(va_arg(*ap, char *), len);
	else if (fmt == 'd' || fmt == 'i')
		ft_print_di(va_arg(*ap, int), len);
	else if (fmt == 'u')
		ft_print_u(va_arg(*ap, unsigned int), len);
	else if (fmt == 'x')
		ft_print_x(va_arg(*ap, unsigned int), 'x', len);
	else if (fmt == 'X')
		ft_print_x(va_arg(*ap, unsigned int), 'X', len);
	else if (fmt == 'p')
		ft_print_p((size_t)va_arg(*ap, void *), len);
	else if (fmt == 'c')
		ft_print_c(va_arg(*ap, int), len);
	else if (fmt == '%')
		ft_print_c('%', len);
	else
		(*i)--;
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			format(str[i], &ap, &len, &i);
		}
		else
			ft_print_c((char)str[i], &len);
		i++;
	}
	va_end(ap);
	return (len);
}
