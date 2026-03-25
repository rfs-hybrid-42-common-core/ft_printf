/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:11:33 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:17:49 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn static int ft_check_arg(char c, va_list args)
 * @brief Routes the variadic argument to the appropriate printing function.
 * @details Checks the format specifier character and calls the corresponding 
 * print function, passing along the variadic argument.
 * @param c    The format specifier character.
 * @param args The variadic argument list.
 * @return     The number of characters printed, or -1 on error.
 */
static int	ft_check_arg(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar_cnt(va_arg(args, int)));
	else if (c == 's')
		return (ft_putstr_cnt(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_putptr_cnt(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_cnt(va_arg(args, int)));
	else if (c == 'u')
		return (ft_putunbr_cnt(va_arg(args, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex_cnt((long)va_arg(args, unsigned int), c));
	else if (c == '%')
		return (ft_putchar_cnt('%'));
	return (-1);
}

/**
 * @fn static void ft_parse_str(const char *s, va_list args, int *cnt)
 * @brief Iterates through the format string, processing text and format tags.
 * @details Advances through the string. If a '%' is found, it evaluates the 
 * next character as a specifier; otherwise, it prints the standard characters.
 * @param s    The format string to parse.
 * @param args The variadic argument list.
 * @param cnt  Pointer to the total printed character count.
 */
static void	ft_parse_str(const char *s, va_list args, int *cnt)
{
	int	n;

	while (*s)
	{
		if (*s == '%')
		{
			s++;
			n = ft_check_arg(*s, args);
			if (n < 0)
			{
				*cnt = -1;
				return ;
			}
			*cnt += n;
		}
		else
		{
			ft_putchar_fd(*s, STDOUT_FILENO);
			(*cnt)++;
		}
		s++;
	}
}

/**
 * @fn int ft_printf(const char *s, ...)
 * @brief Produces output according to a format string.
 * @details Mimics the behavior of the standard C library printf function, 
 * supporting mandatory specifiers (c, s, p, d, i, u, x, X, %).
 * @param s   The format string containing text and format specifiers.
 * @param ... Variadic arguments to be formatted and printed.
 * @return    The total number of characters printed, or -1 on error.
 */
int	ft_printf(const char *s, ...)
{
	int		cnt;
	va_list	args;

	cnt = 0;
	if (!s)
		return (-1);
	va_start(args, s);
	ft_parse_str(s, args, &cnt);
	va_end(args);
	return (cnt);
}
