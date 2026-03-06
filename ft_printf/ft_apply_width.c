/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:51:17 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/07 11:01:59 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_apply_width_right(t_data *data, char *padding,
	size_t len_padding)
{
	char	*tmp;

	ft_memset(padding, ' ', len_padding);
	padding[len_padding] = '\0';
	tmp = ft_strjoin(data->result, padding);
	free(padding);
	free(data->result);
	data->result = tmp;
}

static void	ft_padding_flags(t_data *data, char *padding)
{
	char	*tmp;

	if (data->result[0] == ' ')
		tmp = ft_strjoin(" ", padding);
	else if (data->result[0] == '+')
		tmp = ft_strjoin("+", padding);
	else if (data->result[0] == '-')
		tmp = ft_strjoin("-", padding);
	else
		tmp = ft_strjoin("0x", padding);
	free(padding);
	if (data->hash)
		padding = ft_strjoin(tmp, data->result + 2);
	else
		padding = ft_strjoin(tmp, data->result + 1);
	free(tmp);
	free(data->result);
	data->result = padding;
}

static void	ft_apply_width_left(t_data *data, char *padding, size_t len_padding)
{
	char	*tmp;

	if (data->zero)
		ft_memset(padding, '0', len_padding);
	else
		ft_memset(padding, ' ', len_padding);
	padding[len_padding] = '\0';
	if (data->zero && (data->result[0] == ' ' || data->result[0] == '+'
			|| data->result[0] == '-' || data->hash))
	{
		ft_padding_flags(data, padding);
		return ;
	}
	tmp = ft_strjoin(padding, data->result);
	free(padding);
	free(data->result);
	data->result = tmp;
}

void	ft_apply_width(t_data *data)
{
	int		len_padding;
	char	*padding;

	len_padding = data->width - (int)ft_strlen(data->result);
	if (len_padding <= 0)
		return ;
	padding = malloc(sizeof(char) * (len_padding + 1));
	if (!padding)
	{
		free(data->result);
		data->result = NULL;
		return ;
	}
	if (data->minus)
		ft_apply_width_right(data, padding, len_padding);
	else
		ft_apply_width_left(data, padding, len_padding);
}
