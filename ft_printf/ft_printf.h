/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 11:36:10 by algasnie          #+#    #+#             */
/*   Updated: 2026/03/06 11:04:49 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include "libft.h"

typedef struct s_data
{
	int		hash;
	int		minus;
	int		zero;
	int		plus;
	int		space;
	int		width;
	int		is_prec;
	int		prec;
	char	spec;
	char	*result;
}	t_data;

int		ft_printf(int fd, const char *str, ...);
int		ft_operator(int fd, char *str, int *i, va_list args);
void	ft_create_str(t_data *data, va_list args);
void	ft_apply_struct(t_data *data);
char	*ft_char_str(char c);
char	*ft_string(char *s);
char	*ft_hex(unsigned long int num, char spec);
char	*ft_numb(int num);
int		ft_num_len(unsigned long int num, int base_size);
char	*ft_unsigned(unsigned int num);
void	ft_init_struct(t_data *data);
void	ft_pars_flags(char *str, int *i, t_data *data);
void	ft_pars_width(char *str, int *i, t_data *data);
void	ft_pars_preci(char *str, int *i, t_data *data);
void	ft_pars_speci(char *str, int *i, t_data *data);
void	ft_apply_preci(t_data *data);
void	ft_apply_sign(t_data *data);
void	ft_apply_hash(t_data *data);
void	ft_apply_width(t_data *data);

#endif
