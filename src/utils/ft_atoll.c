/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 16:57:57 by masenche          #+#    #+#             */
/*   Updated: 2026/03/09 18:15:21 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_over(long long nbr, int next_digit, int sign)
{
	if (sign == 1 && (nbr > LLONG_MAX / 10
			|| (nbr == LLONG_MAX / 10 && next_digit > 7)))
		return (1);
	if (sign == -1 && (nbr > LLONG_MAX / 10
			|| (nbr == LLONG_MAX / 10 && next_digit > 8)))
		return (1);
	return (0);
}

long long int	ft_atoll_check(const char *nptr, int *error)
{
	long long int	nbr;
	int				i;
	int				sign;

	nbr = 0;
	i = 0;
	sign = 1;
	*error = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		if (nptr[i++] == '-')
			sign = -1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (is_over(nbr, nptr[i] - '0', sign))
		{
			*error = 1;
			return (0);
		}
		nbr = nbr * 10 + (nptr[i++] - '0');
	}
	return (nbr * sign);
}
