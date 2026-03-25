/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_cnt_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:10:11 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/25 03:14:11 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

/**
 * @fn static void ft_parse_null(t_flags *flags, int *total)
 * @brief Handles the specific edge case of printing a NULL string pointer.
 * @details Prints "(null)" taking into account precision limits. If precision 
 * is less than 6, it may truncate the output.
 * @param flags Pointer to the formatting flags.
 * @param total Pointer to the tracking character count.
 */
static void	ft_parse_null(t_flags *flags, int *total)
{
	if (flags->prec < 0 || flags->prec > 5)
	{
		*total = 6;
		if (flags->minus)
		{
			ft_putstr_fd("(null)", STDOUT_FILENO);
			while ((*total)++ < flags->width)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		else
		{
			while ((*total)++ < flags->width)
				ft_putchar_fd(' ', STDOUT_FILENO);
			ft_putstr_fd("(null)", STDOUT_FILENO);
		}
	}
	else
	{
		while ((*total)++ < flags->width)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	(*total)--;
}

/**
 * @fn static void ft_parse_string(const char *s, t_flags *flags, int *cnt)
 * @brief Applies precision, width, and alignment rules to a valid string.
 * @details Creates a substring bounded by precision, then prints it with 
 * the requested width and justification padding.
 * @param s     The string to format and print.
 * @param flags Pointer to the formatting flags.
 * @param cnt   Pointer to the tracking character count.
 */
static void	ft_parse_string(const char *s, t_flags *flags, int *cnt)
{
	char	*str;

	if ((flags->prec >= 0) && (*cnt > flags->prec))
		*cnt = flags->prec;
	str = ft_substr(s, 0, *cnt);
	if (!str)
	{
		*cnt = -1;
		return ;
	}
	if (flags->minus)
	{
		ft_putstr_fd(str, STDOUT_FILENO);
		while ((*cnt)++ < flags->width)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	else
	{
		while ((*cnt)++ < flags->width)
			ft_putchar_fd(' ', STDOUT_FILENO);
		ft_putstr_fd(str, STDOUT_FILENO);
	}
	free(str);
	(*cnt)--;
}

/**
 * @fn int ft_putstr_cnt(char *s, t_flags *flags)
 * @brief Prints a string, applying all relevant formatting flags.
 * @details Routes execution based on whether the input string pointer is valid 
 * or NULL, ensuring edge cases are handled cleanly.
 * @param s     The string to print.
 * @param flags Pointer to the format flags structure.
 * @return      The total number of characters printed.
 */
int	ft_putstr_cnt(char *s, t_flags *flags)
{
	int	cnt;

	if (!s)
	{
		cnt = 0;
		ft_parse_null(flags, &cnt);
	}
	else
	{
		cnt = ft_strlen(s);
		ft_parse_string(s, flags, &cnt);
	}
	return (cnt);
}
