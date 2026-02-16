/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:14 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/16 23:49:29 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/**
 * @fn static int ft_numlen(unsigned long nbr, size_t base_len)
 * @brief Calculates the length needed to represent a number in a given base.
 * @details Iteratively divides the number by the base length to determine
 * how many characters will be required for the final string representation.
 * @param nbr The number to evaluate.
 * @param base_len The length of the target numeral base.
 * @return The number of characters needed to represent the number.
 */
static int	ft_numlen(unsigned long nbr, size_t base_len)
{
	int	len;

	len = 0;
	while (nbr >= (unsigned long) base_len)
	{
		nbr /= base_len;
		len++;
	}
	return (len);
}

/**
 * @fn char *ft_utoa_base(unsigned long nbr, char *base, size_t base_len)
 * @brief Converts an unsigned long integer to an allocated string
 * representation.
 * @details Allocates memory for a string and populates it backwards using the
 * provided character set to represent the number in the specified base.
 * @param nbr The unsigned integer to convert.
 * @param base A string containing the characters of the numeral base.
 * @param base_len The length of the numeral base string.
 * @return A dynamically allocated string representing the number, or NULL if
 * allocation fails.
 */
char	*ft_utoa_base(unsigned long nbr, char *base, size_t base_len)
{
	char	*str;
	int		len;

	len = 1;
	len += ft_numlen(nbr, base_len);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = *(base + (nbr % base_len));
		nbr /= base_len;
	}
	return (str);
}
