/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:33:25 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/10 09:59:30 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*t;

	if (!s)
		return (NULL);
	t = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!t)
		return (NULL);
	ft_strlcpy(t, s, ft_strlen(s) + 1);
	return (t);
}
