/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_precision.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:47:20 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/06 16:59:16 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_apply_preci_numb_pos(t_data *data, int len_padding)
{
	char	*padding;
	char	*tmp;

	padding = malloc(len_padding + 1);
	if (!padding)
	{
		free(data->result);
		data->result = NULL;
		return ;
	}
	ft_memset(padding, '0', len_padding);
	padding[len_padding] = '\0';
	tmp = ft_strjoin(padding, data->result);
	free(data->result);
	data->result = tmp;
}

void	ft_apply_preci_numb_neg(t_data *data, int len_padding)
{
	char	*padding;
	char	*tmp;

	padding = malloc(len_padding + 1);
	if (!padding)
	{
		free(data->result);
		data->result = NULL;
		return ;
	}
	ft_memset(padding, '0', len_padding);
	padding[len_padding] = '\0';
	tmp = ft_strjoin("-", padding);
	free(padding);
	padding = ft_strjoin(tmp, data->result + 1);
	free(data->result);
	data->result = padding;
	free(tmp);
}

void	ft_apply_preci_numb(t_data *data)
{
	int		len_padding;

	if (data->prec == 0 && data->result[0] == '0' && data->result[1] == '\0')
	{
		free(data->result);
		data->result = ft_strdup("");
	}
	if (data->result[0] == '-')
	{
		len_padding = data->prec - (int)ft_strlen(data->result) + 1;
		if (len_padding <= 0)
			return ;
		ft_apply_preci_numb_neg(data, len_padding);
	}
	else
	{
		len_padding = data->prec - (int)ft_strlen(data->result);
		if (len_padding <= 0)
			return ;
		ft_apply_preci_numb_pos(data, len_padding);
	}
}

void	ft_apply_preci_str(t_data *data)
{
	char	*tmp;

	if (data->prec >= (int)ft_strlen(data->result))
		return ;
	tmp = malloc(sizeof(char) * (data->prec + 1));
	if (!tmp)
	{
		free(data->result);
		data->result = NULL;
		return ;
	}
	ft_memcpy(tmp, data->result, data->prec);
	tmp[data->prec] = '\0';
	free(data->result);
	data->result = tmp;
}

void	ft_apply_preci(t_data *data)
{
	if (data->spec == 's')
		ft_apply_preci_str(data);
	else if (data->spec == 'd' || data->spec == 'i' || data->spec == 'u'
		|| data->spec == 'x' || data->spec == 'X')
		ft_apply_preci_numb(data);
}
