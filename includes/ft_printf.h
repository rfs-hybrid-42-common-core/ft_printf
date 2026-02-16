/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:01:09 by maaugust          #+#    #+#             */
/*   Updated: 2025/05/19 19:38:44 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <stdbool.h>
# include <stdlib.h>

# define HEX_LOWER	"0123456789abcdef"
# define HEX_UPPER	"0123456789ABCDEF"
# define HEX_LEN	16
# define DEC_LEN	10

typedef struct s_flags
{
	bool	minus;
	bool	plus;
	bool	space;
	bool	hash;
	bool	zero;
	int		width;
	int		prec;
}	t_flags;

int		ft_printf(const char *s, ...);
int		ft_putchar_cnt(char c, t_flags *flags);
int		ft_putstr_cnt(char *s, t_flags *flags);
int		ft_putptr_cnt(void *s, t_flags *flags);
int		ft_putnbr_cnt(int n, t_flags *flags);
int		ft_putunbr_cnt(unsigned int n, t_flags *flags);
int		ft_puthex_cnt(long nbr, t_flags *flags, char c);
char	*ft_utoa_base(unsigned long nbr, char *base, size_t base_len);
void	reset_flags(t_flags *flags);
void	update_flags(const char *s, t_flags *flags);
bool	is_specifier(char c);

#endif
