/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lguarda <lguarda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:19:37 by lguarda           #+#    #+#             */
/*   Updated: 2016/09/26 18:21:25 by lguarda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_putsn(char *str, int *fd)
{
	size_t len;

	len = 0;
	while (str[len] && str[len] != '%')
		++len;
	write(*fd, str, len);
	return (len);
}

static void		print_s(va_list *ap, char **str, int *fd)
{
	if (**str == 's')
		ft_putstr_fd(va_arg(*ap, char*), *fd);
	if (**str == 'c')
		ft_putchar_fd(va_arg(*ap, int), *fd);
	else if (**str == 'b')
		ft_putnbr_base_uint(*fd, va_arg(*ap, unsigned int), 2);
	else if (**str == 'x')
		ft_putnbr_base_uint(*fd, va_arg(*ap, unsigned int), 16);
	else if (**str == 'u')
		ft_putnbr_base_uint(*fd, va_arg(*ap, unsigned int), 10);
	else if (**str == 'd' || **str == 'i')
		ft_putnbr_base_uint(*fd, va_arg(*ap, unsigned int), 10);
	else if (**str == 'f')
		ft_putnbr_float(*fd, va_arg(*ap, double));
	else if (**str == '%')
		write(*fd, "%", 1);
	else if (**str == '2')
		*fd = 2;
	else if (**str == '1')
		*fd = 1;
}

void			print(char *str, ...)
{
	va_list	ap;
	int		tmp;
	int		fd;

	va_start(ap, str);
	fd = 1;
	while (*str)
	{
		tmp = ft_putsn(str, &fd);
		str += tmp;
		if (*str == '%')
		{
			++str;
			print_s(&ap, &str, &fd);
		}
		str += (*str) ? 1 : 0;
	}
	va_end(ap);
}
