/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:39:10 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:44:51 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn void reset_flags(t_flags *flags)
 * @brief Resets all fields in the flags structure to their default values.
 * @details Sets all boolean formatting flags to false, width to 0, and
 * precision to -1 (indicating no precision specified).
 * @param flags Pointer to the t_flags structure to reset.
 */
void	reset_flags(t_flags *flags)
{
	flags->minus = false;
	flags->plus = false;
	flags->space = false;
	flags->hash = false;
	flags->zero = false;
	flags->width = 0;
	flags->prec = -1;
}

/**
 * @fn void update_flags(const char *s, t_flags *flags)
 * @brief Parses formatting characters and updates the flags structure.
 * @details Iterates through the current position of the format string to
 * identify and set flags ('-', '+', ' ', '#', '0'), width, and precision.
 * @param s Pointer to the current character in the format string.
 * @param flags Pointer to the t_flags structure to update.
 */
void	update_flags(const char *s, t_flags *flags)
{
	if (!(flags->minus) && *s == '-')
		flags->minus = true;
	if (!(flags->plus) && *s == '+')
		flags->plus = true;
	if (!(flags->space) && *s == ' ')
		flags->space = true;
	if (!(flags->hash) && *s == '#')
		flags->hash = true;
	if (!(flags->zero) && flags->width == 0 && flags->prec < 0 && *s == '0')
		flags->zero = true;
	else if (flags->width == 0 && flags->prec < 0 && *s > '0' && *s <= '9')
	{
		while (*s >= '0' && *s <= '9')
			flags->width = flags->width * 10 + (*s++ - '0');
	}
	if (flags->prec < 0 && *s == '.')
	{
		flags->prec = 0;
		if (*(s + 1) >= '0' && *(s + 1) <= '9')
		{
			s++;
			while (*s >= '0' && *s <= '9')
				flags->prec = flags->prec * 10 + (*s++ - '0');
		}
	}
}

/**
 * @fn bool is_specifier(char c)
 * @brief Checks if a character is a valid format specifier.
 * @details Compares the character against the standard printf specifiers
 * supported by the project (c, s, p, d, i, u, x, X, %).
 * @param c The character to check.
 * @return true if the character is a specifier, false otherwise.
 */
bool	is_specifier(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (true);
	return (false);
}
