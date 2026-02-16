/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:07:18 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:46:01 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn int ft_putchar_cnt(char c, t_flags *flags)
 * @brief Prints a single character while applying width and alignment flags.
 * @details Uses the minus flag to determine left or right justification and
 * pads with spaces up to the required minimum width.
 * @param c The character to print.
 * @param flags Pointer to the format flags structure.
 * @return The total number of characters printed.
 */
int	ft_putchar_cnt(char c, t_flags *flags)
{
	int	cnt;

	cnt = 1;
	if (flags->minus)
	{
		ft_putchar_fd(c, 1);
		while (cnt++ < flags->width)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (cnt++ < flags->width)
			ft_putchar_fd(' ', 1);
		ft_putchar_fd(c, 1);
	}
	cnt--;
	reset_flags(flags);
	return (cnt);
}
