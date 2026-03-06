/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:58:18 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/03 15:01:38 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_numb(int num)
{
	char	*c_num;

	c_num = ft_itoa(num);
	if (!c_num)
		return (NULL);
	return (c_num);
}

int	ft_num_len(unsigned long int num, int base_size)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		num /= base_size;
		len++;
	}
	return (len);
}

char	*ft_unsigned(unsigned int num)
{
	int		len;
	char	*c_num;

	len = ft_num_len((unsigned long int)num, 10);
	c_num = malloc(sizeof(char) * (len + 1));
	if (!c_num)
		return (NULL);
	c_num[len] = '\0';
	if (num == 0)
		c_num[0] = '0';
	while (num > 0)
	{
		c_num[--len] = (num % 10) + '0';
		num /= 10;
	}
	return (c_num);
}
