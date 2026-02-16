/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:11:33 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:45:51 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn static int ft_check_arg(char c, va_list args, t_flags *flags)
 * @brief Routes the variadic argument to the appropriate printing function.
 * @details Checks the format specifier character and calls the corresponding
 * print function, passing along the argument and active format flags.
 * @param c The format specifier character.
 * @param args The variadic argument list.
 * @param flags Pointer to the current flags structure.
 * @return The number of characters printed, or -1 on error.
 */
static int	ft_check_arg(char c, va_list args, t_flags *flags)
{
	if (c == 'c')
		return (ft_putchar_cnt(va_arg(args, int), flags));
	else if (c == 's')
		return (ft_putstr_cnt(va_arg(args, char *), flags));
	else if (c == 'p')
		return (ft_putptr_cnt(va_arg(args, void *), flags));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr_cnt(va_arg(args, int), flags));
	else if (c == 'u')
		return (ft_putunbr_cnt(va_arg(args, unsigned int), flags));
	else if (c == 'x' || c == 'X')
		return (ft_puthex_cnt((long)(va_arg(args, unsigned int)), flags, c));
	else if (c == '%')
		return (write(1, "%%", 1));
	return (-1);
}

/**
 * @fn static void ft_parse_str(const char *s, va_list args, t_flags *flags,
 * int *cnt)
 * @brief Iterates through the format string, processing text and format tags.
 * @details Advances through the string. If a '%' is found, it parses flags
 * and specifiers; otherwise, it prints the standard characters directly.
 * @param s The format string to parse.
 * @param args The variadic argument list.
 * @param flags Pointer to the flags structure.
 * @param cnt Pointer to the total printed character count.
 */
static void	ft_parse_str(const char *s, va_list args, t_flags *flags, int *cnt)
{
	int	n;

	while (*s)
	{
		if (*s == '%')
		{
			s++;
			while (*s && !(is_specifier(*s)))
				update_flags(s++, flags);
			n = ft_check_arg(*s, args, flags);
			if (n < 0)
			{
				*cnt = -1;
				return ;
			}
			*cnt += n;
			reset_flags(flags);
		}
		else
		{
			ft_putchar_fd(*s, 1);
			(*cnt)++;
		}
		s++;
	}
}

/**
 * @fn int ft_printf(const char *s, ...)
 * @brief Produces output according to a format string.
 * @details Mimics the behavior of the standard C library printf function,
 * supporting various specifiers and formatting flags.
 * @param s The format string containing text and format specifiers.
 * @param ... Variadic arguments to be formatted and printed.
 * @return The total number of characters printed, or -1 on error.
 */
int	ft_printf(const char *s, ...)
{
	int		cnt;
	va_list	args;
	t_flags	flags;

	cnt = 0;
	if (!s)
		return (-1);
	va_start(args, s);
	reset_flags(&flags);
	ft_parse_str(s, args, &flags, &cnt);
	va_end(args);
	return (cnt);
}
