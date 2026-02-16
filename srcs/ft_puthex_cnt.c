/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:51:14 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:46:51 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn static void ft_print_hash(t_flags flags, char c)
 * @brief Prints the alternate form hash prefix.
 * @details Outputs "0x" or "0X" depending on the specifier character if the
 * hash flag is active.
 * @param flags The formatting flags containing the hash boolean.
 * @param c The specifier character ('x' or 'X') to determine case.
 */
static void	ft_print_hash(t_flags flags, char c)
{
	if (flags.hash)
	{
		if (c == 'x')
			ft_putstr_fd("0x", 1);
		else
			ft_putstr_fd("0X", 1);
	}
}

/**
 * @fn static void ft_parse_string(char *s, t_flags flags, int *cnt, char c)
 * @brief Applies width and alignment flags to a hexadecimal string.
 * @details Handles left and right justification, padding with spaces up to
 * the specified minimum width.
 * @param s The hexadecimal string to print.
 * @param flags The formatting flags structure.
 * @param cnt Pointer to the character count.
 * @param c The specifier character ('x' or 'X').
 */
static void	ft_parse_string(char *s, t_flags flags, int *cnt, char c)
{
	if (flags.minus)
	{
		ft_print_hash(flags, c);
		ft_putstr_fd(s, 1);
		while ((*cnt)++ < flags.width)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while ((*cnt)++ < flags.width)
			ft_putchar_fd(' ', 1);
		ft_print_hash(flags, c);
		ft_putstr_fd(s, 1);
	}
}

/**
 * @fn static void ft_parse_prec(char *s, t_flags *flags, int *cnt, char c)
 * @brief Applies precision requirements to a hexadecimal string.
 * @details Pads the hexadecimal output with leading zeros to meet precision,
 * while still respecting width and left/right justification rules.
 * @param s The hexadecimal string to print.
 * @param flags Pointer to the format flags structure.
 * @param cnt Pointer to the character count.
 * @param c The specifier character ('x' or 'X').
 */
static void	ft_parse_prec(char *s, t_flags *flags, int *cnt, char c)
{
	if (flags->minus)
	{
		ft_print_hash(*flags, c);
		while ((*cnt)++ < flags->prec)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
		while ((flags->prec)++ < flags->width)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		if (*cnt < flags->prec)
			*cnt = flags->prec;
		while ((*cnt)++ < flags->width)
			ft_putchar_fd(' ', 1);
		ft_print_hash(*flags, c);
		*cnt = ft_strlen(s) + 2 * ((int) flags->hash);
		while ((*cnt)++ < flags->prec)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	*cnt = flags->width;
}

/**
 * @fn static void ft_parse_hex(char *s, t_flags *flags, int *cnt, char c)
 * @brief Routes the hexadecimal string to the appropriate formatting function.
 * @details Evaluates the priority of precision, zero-padding, and width flags
 * to determine the correct printing sequence.
 * @param s The hexadecimal string to print.
 * @param flags Pointer to the format flags structure.
 * @param cnt Pointer to the character count.
 * @param c The specifier character ('x' or 'X').
 */
static void	ft_parse_hex(char *s, t_flags *flags, int *cnt, char c)
{
	if (flags->prec > -1 && flags->prec < flags->width && *cnt < flags->width)
	{
		if (flags->prec < *cnt)
			flags->prec = *cnt;
		ft_parse_prec(s, flags, cnt, c);
		return ;
	}
	else if (flags->prec > -1)
	{
		ft_print_hash(*flags, c);
		while ((*cnt)++ < flags->prec)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	else if (flags->zero && !(flags->minus))
	{
		ft_print_hash(*flags, c);
		while ((*cnt)++ < flags->width)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	else
		ft_parse_string(s, *flags, cnt, c);
	(*cnt)--;
}

/**
 * @fn int ft_puthex_cnt(long nbr, t_flags *flags, char c)
 * @brief Converts a long number to hexadecimal and prints it with formatting.
 * @details Generates the base-16 string and calculates the necessary layout
 * lengths before passing it down for flagged formatting.
 * @param nbr The number to convert and print.
 * @param flags Pointer to the format flags structure.
 * @param c The format specifier ('x' or 'X').
 * @return The total number of characters printed, or -1 on error.
 */
int	ft_puthex_cnt(long nbr, t_flags *flags, char c)
{
	char	*str;
	int		cnt;

	if (!nbr && flags->prec > -1)
		str = ft_strdup("");
	else if (c == 'x')
		str = ft_utoa_base((unsigned long) nbr, HEX_LOWER, HEX_LEN);
	else
		str = ft_utoa_base((unsigned long) nbr, HEX_UPPER, HEX_LEN);
	if (!str)
		return (-1);
	cnt = ft_strlen(str);
	if (nbr == 0)
		flags->hash = false;
	if (flags->hash)
	{
		cnt += 2;
		if (flags->prec > -1)
			flags->prec += 2;
	}
	ft_parse_hex(str, flags, &cnt, c);
	reset_flags(flags);
	return (free(str), cnt);
}
