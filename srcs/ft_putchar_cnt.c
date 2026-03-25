/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:07:18 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:20:21 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn int ft_putchar_cnt(char c)
 * @brief Prints a single character to the standard output.
 * @details Acts as a wrapper around the libft ft_putchar_fd function, 
 * always returning 1 to simplify the character counting in the main parser.
 * @param c The character to print.
 * @return  1 (the number of characters printed).
 */
int	ft_putchar_cnt(char c)
{
	ft_putchar_fd(c, STDOUT_FILENO);
	return (1);
}
