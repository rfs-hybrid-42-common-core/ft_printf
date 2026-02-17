*This project has been created as part of the 42 curriculum by maaugust.*

<div align="center">
  <img src="assets/cover-ft_printf-bonus.png" alt="ft_printf Cover" width="100%" />
</div>

<div align="center">
  <h1>🖨️ ft_printf: Because ft_putnbr() and ft_putstr() aren’t enough</h1>
  <img src="https://img.shields.io/badge/Language-C-blue" />
  <img src="https://img.shields.io/badge/Grade-125%2F100-success" />
  <img src="https://img.shields.io/badge/Norminette-Passing-success" />
</div>

---

## 💡 Description
**ft_printf** is a project in the 42 curriculum that requires recoding the standard C library `printf` function. 

The primary goal of this project is to learn how to use **variadic arguments** in C (functions that accept an indefinite number of arguments) while building a robust, extensible formatting engine. This custom `ft_printf` is fully integrated with my `libft` and handles complex formatting flags for a maximum bonus grade.

---

## 📑 Features & Conversions

### 🔹 Mandatory Conversions
The function successfully parses and formats the following specifiers:

| Specifier | Description |
| :---: | :--- |
| `%c` | Prints a single character. |
| `%s` | Prints a string. |
| `%p` | Prints a `void *` pointer argument in hexadecimal format. |
| `%d` | Prints a decimal (base 10) number. |
| `%i` | Prints an integer in base 10. |
| `%u` | Prints an unsigned decimal (base 10) number. |
| `%x` | Prints a number in hexadecimal (base 16) lowercase format. |
| `%X` | Prints a number in hexadecimal (base 16) uppercase format. |
| `%%` | Prints a literal percent sign. |

### 🚀 Bonus Flags
This implementation handles the following advanced formatting flags and their combinations:

| Flag | Description |
| :---: | :--- |
| `-` | Left-justifies the output within the given field width. |
| `0` | Left-pads the output with zeros instead of spaces. |
| `.` *(Precision)* | Specifies the minimum number of digits for numbers, or maximum string length. |
| *Width* | Specifies the minimum field width for the output. |
| `#` | Prefixes `0x` or `0X` for hexadecimal conversions (`%x`, `%X`). |
| `+` | Forces a `+` or `-` sign to precede the result. |
| ` ` *(Space)* | Leaves a blank space before a positive number. |

---

## 🧠 Algorithm & Data Structure

*Per the subject requirements, here is the justification for the architecture used in this project.*

### Data Structure: The Flag Struct
To efficiently manage the bonus flags (`-`, `0`, `.`, `#`, `+`, `space`, and width) without passing a dozen variables between functions, I utilized a centralized `t_flags` structure. 
Whenever a `%` is encountered, the parser initializes this struct, reads the intermediate characters, and activates the corresponding boolean values and integer widths before passing the struct to the final conversion dispatch.

### Algorithm: Unified Base Conversion & Dispatch
1. **Linear Parsing:** The algorithm iterates linearly through the format string using a `while` loop. When a `%` character is found, the parser enters a "flag reading" state.
2. **Variadic Extraction:** Using `<stdarg.h>` macros (`va_start`, `va_arg`, `va_end`), the corresponding arguments are dynamically extracted based on the final conversion specifier.
3. **Modular Dispatch:** A dispatcher routes the argument and the populated `t_flags` struct to specific formatting functions (e.g., `ft_puthex_cnt`, `ft_putnbr_cnt`).
4. **Universal String Conversion (`ft_utoa_base`):** Instead of duplicating logic for integer, hexadecimal, and pointer conversions, the architecture converts signed numbers to positive `unsigned long` values. These are all routed through a single, custom utility function (`ft_utoa_base`) that handles dynamic base conversion, drastically reducing code duplication and adhering strictly to the 42 Norm. Memory is dynamically allocated, printed with proper padding, and immediately freed.

---

## 🛠️ Instructions

### 📦 Installation
This implementation natively includes all bonus flags in the standard build. To compile the complete library, run the following command in the root of the repository:

```bash
make
```

The `make bonus` rule is also included to satisfy 42's evaluation scripts and performs the same complete build:

```bash
make bonus
```

This will generate the `libftprintf.a` archive file.

### 🧹 Cleaning
* `make clean`: Removes object files (`.o`).
* `make fclean`: Removes object files and the `libftprintf.a` library.
* `make re`: Performs a clean re-build.

### 💻 Usage
To use this function in your code, include the header and link the archive during compilation:

**1. Include header:**
```c
#include "ft_printf.h"

int main()
{
    ft_printf("Hello %s! The magic number is %05d.\n", "42", 42);
    return (0);
}
```

**2. Compile:**
```bash
cc main.c -L. -lftprintf -o my_program
```

---

## 📚 Resources & References
* [Secrets of printf](https://www.cypress.com/file/54441/download)
* [C Variadic Functions (va_list)](https://en.cppreference.com/w/c/variadic)
* `man 3 printf`

### 🤖 AI Usage Guidelines
*Per the subject requirements:*
* **Tasks:** AI tools were used exclusively for generating portfolio-ready documentation templates and brainstorming structural layouts for the `t_flags` parsing algorithm.
* **Code:** No AI-generated code was directly copied into the project source files. The variadic logic, string manipulation, and base conversions were entirely manually coded to ensure complete mastery of the underlying C mechanics.
