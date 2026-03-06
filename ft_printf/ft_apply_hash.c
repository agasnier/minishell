/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:50:01 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/03 18:49:14 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_apply_hash(t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (data->result[0] == '0' && data->result[1] == '\0')
		return ;
	if (data->spec == 'x')
		tmp = ft_strjoin("0x", data->result);
	else if (data->spec == 'X')
		tmp = ft_strjoin("0X", data->result);
	free(data->result);
	data->result = tmp;
}
