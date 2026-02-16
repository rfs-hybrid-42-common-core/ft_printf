/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_cnt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:10:41 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:47:39 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn static void ft_print_sign(t_flags flags, bool neg)
 * @brief Prints the appropriate sign or space prefix for a numeric value.
 * @details Assesses whether a minus sign, plus sign, or space should be
 * printed based on the number's negativity and active flags.
 * @param flags Formatting flags to check for '+' or space priority.
 * @param neg Boolean indicating if the number is negative.
 */
static void	ft_print_sign(t_flags flags, bool neg)
{
	if (neg)
		ft_putchar_fd('-', 1);
	else if (flags.plus)
		ft_putchar_fd('+', 1);
	else if (flags.space)
		ft_putchar_fd(' ', 1);
}

/**
 * @fn static void ft_parse_prec(char *s, t_flags *flags, int *cnt, bool neg)
 * @brief Handles width and precision formatting for numeric strings.
 * @details Pads the string with zeros to meet precision limits while ensuring
 * overall width and alignment constraints are respected.
 * @param s The numeric string to format.
 * @param flags Pointer to the formatting flags structure.
 * @param cnt Pointer to the tracking character count.
 * @param neg Boolean indicating if the number is negative.
 */
static void	ft_parse_prec(char *s, t_flags *flags, int *cnt, bool neg)
{
	if (flags->minus)
	{
		ft_print_sign(*flags, neg);
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
		ft_print_sign(*flags, neg);
		*cnt = ft_strlen(s) + (neg || flags->plus || flags->space);
		while ((*cnt)++ < flags->prec)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	*cnt = flags->width;
}

/**
 * @fn static void ft_parse_string(char *s, t_flags flags, int *cnt, bool neg)
 * @brief Handles width and alignment formatting for basic numeric strings.
 * @details Justifies the numeric string to the left or right, filling the
 * remaining width with spaces.
 * @param s The numeric string to format.
 * @param flags The formatting flags structure.
 * @param cnt Pointer to the tracking character count.
 * @param neg Boolean indicating if the number is negative.
 */
static void	ft_parse_string(char *s, t_flags flags, int *cnt, bool neg)
{
	if (flags.minus)
	{
		ft_print_sign(flags, neg);
		ft_putstr_fd(s, 1);
		while ((*cnt)++ < flags.width)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while ((*cnt)++ < flags.width)
			ft_putchar_fd(' ', 1);
		ft_print_sign(flags, neg);
		ft_putstr_fd(s, 1);
	}
}

/**
 * @fn static void ft_parse_nbr(char *s, t_flags *flags, int *cnt, bool neg)
 * @brief Routes the numeric string to the correct parsing sub-function.
 * @details Decides whether precision, zero-padding, or standard width rules
 * should be applied based on the flags structure.
 * @param s The numeric string to format.
 * @param flags Pointer to the formatting flags structure.
 * @param cnt Pointer to the tracking character count.
 * @param neg Boolean indicating if the number is negative.
 */
static void	ft_parse_nbr(char *s, t_flags *flags, int *cnt, bool neg)
{
	if (flags->prec > -1 && flags->prec < flags->width && *cnt < flags->width)
	{
		if (flags->prec < *cnt)
			flags->prec = *cnt;
		ft_parse_prec(s, flags, cnt, neg);
		return ;
	}
	else if (flags->prec > -1)
	{
		ft_print_sign(*flags, neg);
		while ((*cnt)++ < flags->prec)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	else if (flags->zero && !(flags->minus))
	{
		ft_print_sign(*flags, neg);
		while ((*cnt)++ < flags->width)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	else
		ft_parse_string(s, *flags, cnt, neg);
	(*cnt)--;
}

/**
 * @fn int ft_putnbr_cnt(int n, t_flags *flags)
 * @brief Converts and prints a signed integer, applying all format flags.
 * @details Retrieves the absolute value string via ft_utoa_base and calculates
 * the padding lengths required for the sign and precision.
 * @param n The integer to print.
 * @param flags Pointer to the format flags structure.
 * @return The total number of characters printed, or -1 on error.
 */
int	ft_putnbr_cnt(int n, t_flags *flags)
{
	char	*str;
	long	nbr;
	int		cnt;

	nbr = (long) n;
	nbr *= (nbr > 0) - (nbr < 0);
	if (!nbr && flags->prec > -1)
		str = ft_strdup("");
	else
		str = ft_utoa_base((unsigned long) nbr, HEX_LOWER, DEC_LEN);
	if (!str)
		return (-1);
	cnt = ft_strlen(str);
	if ((n < 0) || flags->plus || flags->space)
	{
		cnt++;
		if (flags->prec > -1)
			(flags->prec)++;
	}
	ft_parse_nbr(str, flags, &cnt, (n < 0));
	reset_flags(flags);
	return (free(str), cnt);
}
