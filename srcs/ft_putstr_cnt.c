/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:10:11 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:19:22 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn int ft_putstr_cnt(char *s)
 * @brief Prints a string and returns its length.
 * @details If the string is NULL, it safely prints "(null)". Leverages libft 
 * for optimized string writing.
 * @param s The string to print.
 * @return  The total number of characters printed.
 */
int	ft_putstr_cnt(char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", STDOUT_FILENO);
		return (6);
	}
	ft_putstr_fd(s, STDOUT_FILENO);
	return (ft_strlen(s));
}
