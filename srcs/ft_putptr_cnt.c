/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:20:08 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:47:55 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn int ft_putptr_cnt(void *s, t_flags *flags)
 * @brief Prints a memory address in hexadecimal format.
 * @details Prefixes the generated hexadecimal address with "0x". If the pointer
 * is NULL, it falls back to printing "(nil)".
 * @param s A void pointer representing the memory address.
 * @param flags Pointer to the format flags structure.
 * @return The total number of characters printed, or -1 on error.
 */
int	ft_putptr_cnt(void *s, t_flags *flags)
{
	unsigned long	addr;
	char			*str;
	char			*tmp;
	int				cnt;

	if (!s)
		return (ft_putstr_cnt("(nil)", flags));
	addr = (unsigned long) s;
	tmp = ft_utoa_base(addr, HEX_LOWER, HEX_LEN);
	str = ft_strjoin("0x", tmp);
	free(tmp);
	if (!str)
		return (-1);
	cnt = ft_putstr_cnt(str, flags);
	return (free(str), cnt);
}
