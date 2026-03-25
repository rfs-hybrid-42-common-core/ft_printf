/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:39:12 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:19:36 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn int ft_putunbr_cnt(unsigned int n)
 * @brief Converts and prints an unsigned integer.
 * @details Transforms the unsigned variable into a base-10 allocated string 
 * before printing and freeing it.
 * @param n The unsigned integer to print.
 * @return  The total number of characters printed, or -1 on error.
 */
int	ft_putunbr_cnt(unsigned int n)
{
	char	*str;
	int		cnt;

	str = ft_utoa_base(n, HEX_LOWER, DEC_LEN);
	if (!str)
		return (-1);
	cnt = ft_putstr_cnt(str);
	free(str);
	return (cnt);
}
