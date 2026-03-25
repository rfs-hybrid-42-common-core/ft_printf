/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_cnt_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:07:18 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:13:45 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/**
 * @fn int ft_putchar_cnt(char c, t_flags *flags)
 * @brief Prints a single character while applying width and alignment flags.
 * @details Uses the minus flag to determine left or right justification and 
 * pads with spaces up to the required minimum width.
 * @param c     The character to print.
 * @param flags Pointer to the format flags structure.
 * @return      The total number of characters printed.
 */
int	ft_putchar_cnt(char c, t_flags *flags)
{
	int	cnt;

	cnt = 1;
	if (flags->minus)
	{
		ft_putchar_fd(c, STDOUT_FILENO);
		while (cnt++ < flags->width)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	else
	{
		while (cnt++ < flags->width)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putchar_fd(c, STDOUT_FILENO);
	}
	cnt--;
	return (cnt);
}
