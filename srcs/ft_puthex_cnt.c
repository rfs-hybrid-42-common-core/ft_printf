/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:51:14 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:18:34 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn int ft_puthex_cnt(long nbr, char c)
 * @brief Converts a long number to hexadecimal and prints it.
 * @details Generates the base-16 string in either lowercase or uppercase 
 * depending on the provided format specifier.
 * @param nbr The number to convert and print.
 * @param c   The format specifier ('x' or 'X') determining the case.
 * @return    The total number of characters printed, or -1 on error.
 */
int	ft_puthex_cnt(long nbr, char c)
{
	char	*str;
	int		cnt;

	if (c == 'x')
		str = ft_utoa_base((unsigned long) nbr, HEX_LOWER, HEX_LEN);
	else
		str = ft_utoa_base((unsigned long) nbr, HEX_UPPER, HEX_LEN);
	if (!str)
		return (-1);
	cnt = ft_strlen(str);
	ft_putstr_fd(str, STDOUT_FILENO);
	free(str);
	return (cnt);
}
