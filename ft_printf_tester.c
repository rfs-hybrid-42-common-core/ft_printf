/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tester.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 04:34:15 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/20 04:34:21 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

/* ========================================================================== */
/* TOGGLE SWITCHES                                                            */
/* ========================================================================== */
// #define TEST_MANDATORY
// #define TEST_BONUS

/* ========================================================================== */
/* HELPER MACRO                                                               */
/* ========================================================================== */
/* Macro to cleanly print both libc and ft_printf outputs and return values   */
#define RUN_TEST(test_name, fmt, ...) \
	do { \
		int r1, r2; \
		printf("--- %s ---\n", test_name); \
		printf("libc : ["); r1 = printf(fmt, ##__VA_ARGS__); \
		printf("] (ret: %d)\n", r1); \
		printf("ft   : ["); r2 = ft_printf(fmt, ##__VA_ARGS__); \
		printf("] (ret: %d)\n\n", r2); \
	} while (0)

/* ========================================================================== */
/* MAIN FUNCTION                                                              */
/* ========================================================================== */
int	main(void)
{
	printf("============================================================\n");
	printf("                 FT_PRINTF COMPREHENSIVE TESTER             \n");
	printf("============================================================\n\n");

#ifdef TEST_MANDATORY
	printf("======================= MANDATORY ==========================\n\n");

	RUN_TEST("Characters (%c)", "Char: %c, %c", 'A', 'z');
	
	RUN_TEST("Strings (%s) - Normal", "String: %s", "42 Porto");
	RUN_TEST("Strings (%s) - NULL", "String: %s", (char *)NULL);
	RUN_TEST("Strings (%s) - Empty", "String: %s", "");

	RUN_TEST("Pointers (%p) - Normal", "Pointer: %p", "Hello");
	RUN_TEST("Pointers (%p) - NULL", "Pointer: %p", NULL);
	RUN_TEST("Pointers (%p) - Max", "Pointer: %p", (void *)UINTPTR_MAX);

	RUN_TEST("Decimals (%d) - Normal", "Dec: %d", 42);
	RUN_TEST("Decimals (%d) - Negative", "Dec: %d", -42);
	RUN_TEST("Decimals (%d) - INT_MIN", "Dec: %d", INT_MIN);
	RUN_TEST("Decimals (%d) - INT_MAX", "Dec: %d", INT_MAX);

	RUN_TEST("Integers (%i) - Normal", "Int: %i", 100);
	RUN_TEST("Integers (%i) - Zero", "Int: %i", 0);

	RUN_TEST("Unsigned (%u) - Normal", "Unsigned: %u", 42);
	RUN_TEST("Unsigned (%u) - Zero", "Unsigned: %u", 0);
	RUN_TEST("Unsigned (%u) - UINT_MAX", "Unsigned: %u", UINT_MAX);

	RUN_TEST("Hexadecimal (%x) - Lowercase", "Hex: %x", 255);
	RUN_TEST("Hexadecimal (%X) - Uppercase", "Hex: %X", 255);
	RUN_TEST("Hexadecimal (%x) - Zero", "Hex: %x", 0);

	RUN_TEST("Percent (%%)", "Percent: %%");
	RUN_TEST("Multiple Specifiers", "Mix: %c %s %p %d %x %%", 'X', "test", &main, 42, 42);
#endif

#ifdef TEST_BONUS
	printf("========================= BONUS ============================\n\n");

	RUN_TEST("Plus Flag (+)", "Plus: %+d, %+d", 42, -42);
	RUN_TEST("Space Flag ( )", "Space: % d, % d", 42, -42);
	RUN_TEST("Hash Flag (#)", "Hash: %#x, %#X, %#x", 255, 255, 0);

	RUN_TEST("Width - Numbers", "Width: %5d, %10s", 42, "hello");
	RUN_TEST("Width - Pointer", "Width: %20p", "test");

	RUN_TEST("Minus Flag (-) (Left Justify)", "Minus: %-10d%-10s|", 42, "hello");

	RUN_TEST("Zero Flag (0)", "Zero: %05d, %08x", 42, 255);
	RUN_TEST("Zero Flag (0) with Negative", "Zero Neg: %08d", -42);

	RUN_TEST("Precision (.) - Strings", "Prec: %.3s", "abcdef");
	RUN_TEST("Precision (.) - Numbers", "Prec: %.5d, %.5x", 42, 255);
	RUN_TEST("Precision (.) - Zero Value", "Prec Zero: %.0d, %.d", 0, 0);

	RUN_TEST("Combo: Space + Width", "Combo: % 5d, % 5d", 42, -42);
	RUN_TEST("Combo: Plus + Width + Zero", "Combo: %+08d, %+08d", 42, -42);
	RUN_TEST("Combo: Hash + Width + Zero", "Combo: %#08x, %#08X", 255, 255);
	RUN_TEST("Combo: Minus + Width + Prec", "Combo: %-10.5d|", 42);
	RUN_TEST("Combo: All the things", "Combo: %+-10.5d|", 42);
#endif

	return (0);
}