/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 17:59:09 by algasnie          #+#    #+#             */
/*   Updated: 2025/11/03 21:09:29 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_hex_pointeur(char *c_num)
{
	char	*hex;

	if (c_num[0] == '0' && c_num[1] == '\0')
		hex = ft_strdup("(nil)");
	else
		hex = ft_strjoin("0x", c_num);
	free(c_num);
	return (hex);
}

char	*ft_hex(unsigned long int num, char spec)
{
	char	*base;
	char	*c_num;
	int		len;

	if (spec == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	len = ft_num_len((unsigned long int)num, 16);
	c_num = malloc(sizeof(char) * (len + 1));
	if (!c_num)
		return (NULL);
	c_num[len] = '\0';
	if (num == 0)
		c_num[0] = base[0];
	while (num > 0)
	{
		c_num[--len] = base[num % 16];
		num /= 16;
	}
	if (spec == 'p')
		c_num = ft_hex_pointeur(c_num);
	return (c_num);
}
