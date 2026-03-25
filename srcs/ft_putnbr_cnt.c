/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:10:41 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:18:48 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn int ft_putnbr_cnt(int n)
 * @brief Converts and prints a signed integer.
 * @details Retrieves the absolute value string via ft_utoa_base and handles 
 * the printing of the negative sign if required.
 * @param n The integer to print.
 * @return  The total number of characters printed, or -1 on error.
 */
int	ft_putnbr_cnt(int n)
{
	char	*str;
	long	nbr;
	int		cnt;

	nbr = (long) n;
	nbr *= (nbr > 0) - (nbr < 0);
	str = ft_utoa_base((unsigned long) nbr, HEX_LOWER, DEC_LEN);
	if (!str)
		return (-1);
	cnt = 0;
	if (n < 0)
		cnt += ft_putchar_cnt('-');
	cnt += ft_putstr_cnt(str);
	free(str);
	return (cnt);
}
