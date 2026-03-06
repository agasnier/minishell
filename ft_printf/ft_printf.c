/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 12:15:42 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/06 11:06:03 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_helper(int fd, char *str, va_list args)
{
	int		i;
	int		len_print;
	int		len_func;

	i = 0;
	len_print = 0;
	len_func = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len_func = ft_operator(fd, str, &i, args);
			if (len_func == -1)
				return (-1);
			len_print += len_func;
		}
		else
		{
			if (write(fd, &str[i], 1) == -1)
				return (-1);
			len_print++;
		}
		i++;
	}
	return (len_print);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	args;
	int		len_print;

	va_start(args, str);
	if (!str)
		return (-1);
	len_print = ft_printf_helper(fd, (char *)str, args);
	va_end(args);
	return (len_print);
}
