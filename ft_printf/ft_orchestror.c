/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_orchestror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:59:02 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/06 11:06:40 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_apply_struct(t_data *data)
{
	if (!data->result || data->spec == '\0')
		return ;
	if (data->minus)
		data->zero = 0;
	if (data->plus)
		data->space = 0;
	if (data->is_prec && (data->spec == 'd' || data->spec == 'i'
			|| data->spec == 'u' || data->spec == 'x' || data->spec == 'X'))
		data->zero = 0;
	if (data->result && data->is_prec)
		ft_apply_preci(data);
	if (data->result && (data->plus || data->space)
		&& (data->spec == 'd' || data->spec == 'i'))
		ft_apply_sign(data);
	if (data->result && data->hash)
		ft_apply_hash(data);
	if (data->result && data->width)
		ft_apply_width(data);
}

void	ft_create_str(t_data *data, va_list args)
{
	if (data->spec == 'c')
		data->result = ft_char_str(va_arg(args, int));
	else if (data->spec == '%')
		data->result = ft_char_str('%');
	else if (data->spec == 's')
		data->result = ft_string(va_arg(args, char *));
	else if (data->spec == 'x' || data->spec == 'X')
		data->result = ft_hex((unsigned long int)va_arg(args,
					unsigned int), data->spec);
	else if (data->spec == 'p')
		data->result = ft_hex((unsigned long int)va_arg(args, void *), 'p');
	else if (data->spec == 'd' || data->spec == 'i')
		data->result = ft_numb(va_arg(args, int));
	else if (data->spec == 'u')
		data->result = ft_unsigned(va_arg(args, unsigned int));
}

int	ft_operator(int fd, char *str, int *i, va_list args)
{
	int		len;
	t_data	data;

	len = 0;
	(*i)++;
	ft_init_struct(&data);
	ft_pars_flags(str, i, &data);
	ft_pars_width(str, i, &data);
	ft_pars_preci(str, i, &data);
	ft_pars_speci(str, i, &data);
	ft_create_str(&data, args);
	if (!data.result)
		return (-1);
	ft_apply_struct(&data);
	if (!data.result)
		return (-1);
	if (data.spec == 'c' && !data.width)
		len = 1;
	else
		len = ft_strlen(data.result);
	if (write(fd, data.result, len) == -1)
		return (-1);
	free(data.result);
	return (len);
}
