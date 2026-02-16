/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_cnt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:39:12 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:49:09 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn static void ft_parse_string(char *s, t_flags flags, int *cnt)
 * @brief Handles width and alignment formatting for unsigned numeric strings.
 * @details Justifies the numerical string left or right, padding with spaces.
 * @param s The numeric string to format.
 * @param flags The formatting flags structure.
 * @param cnt Pointer to the tracking character count.
 */
static void	ft_parse_string(char *s, t_flags flags, int *cnt)
{
	if (flags.minus)
	{
		ft_putstr_fd(s, 1);
		while ((*cnt)++ < flags.width)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while ((*cnt)++ < flags.width)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(s, 1);
	}
}

/**
 * @fn static void ft_parse_prec(char *s, t_flags *flags, int *cnt)
 * @brief Handles width and precision formatting for unsigned numeric strings.
 * @details Applies zero-padding to satisfy precision limits, combined with
 * spatial padding for width requirements.
 * @param s The numeric string to format.
 * @param flags Pointer to the formatting flags structure.
 * @param cnt Pointer to the tracking character count.
 */
static void	ft_parse_prec(char *s, t_flags *flags, int *cnt)
{
	if (flags->minus)
	{
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
		*cnt = ft_strlen(s);
		while ((*cnt)++ < flags->prec)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	*cnt = flags->width;
}

/**
 * @fn static void ft_parse_unbr(char *s, t_flags *flags, int *cnt)
 * @brief Routes the unsigned numeric string to the correct parsing sub-function.
 * @details Evaluates active flags to apply proper precision and padding rules.
 * @param s The unsigned numeric string to format.
 * @param flags Pointer to the formatting flags structure.
 * @param cnt Pointer to the tracking character count.
 */
static void	ft_parse_unbr(char *s, t_flags *flags, int *cnt)
{
	if (flags->prec > -1 && flags->prec < flags->width && *cnt < flags->width)
	{
		if (flags->prec < *cnt)
			flags->prec = *cnt;
		ft_parse_prec(s, flags, cnt);
		return ;
	}
	else if (flags->prec > -1)
	{
		while ((*cnt)++ < flags->prec)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	else if (flags->zero && !(flags->minus))
	{
		while ((*cnt)++ < flags->width)
			ft_putchar_fd('0', 1);
		ft_putstr_fd(s, 1);
	}
	else
		ft_parse_string(s, *flags, cnt);
	(*cnt)--;
}

/**
 * @fn int ft_putunbr_cnt(unsigned int n, t_flags *flags)
 * @brief Converts and prints an unsigned integer, applying all format flags.
 * @details Transforms the unsigned variable into a base-10 string before
 * passing it for flagged processing.
 * @param n The unsigned integer to print.
 * @param flags Pointer to the format flags structure.
 * @return The total number of characters printed, or -1 on error.
 */
int	ft_putunbr_cnt(unsigned int n, t_flags *flags)
{
	char	*str;
	int		cnt;

	if (!n && flags->prec > -1)
		str = ft_strdup("");
	else
		str = ft_utoa_base(n, HEX_LOWER, DEC_LEN);
	if (!str)
		return (-1);
	cnt = ft_strlen(str);
	ft_parse_unbr(str, flags, &cnt);
	reset_flags(flags);
	return (free(str), cnt);
}
