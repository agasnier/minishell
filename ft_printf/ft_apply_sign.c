/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_sign.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:48:17 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/03 20:52:48 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_apply_sign(t_data *data)
{
	char	*tmp;

	if (data->result[0] == '-')
		return ;
	if (data->plus)
	{
		tmp = ft_strjoin("+", data->result);
		free(data->result);
		data->result = tmp;
	}
	else if (data->space)
	{
		tmp = ft_strjoin(" ", data->result);
		free(data->result);
		data->result = tmp;
	}
}
