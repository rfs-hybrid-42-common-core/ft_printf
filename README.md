*This project has been created as part of the 42 curriculum by maaugust.*

<div align="center">
  <img src="https://raw.githubusercontent.com/rfs-hybrid/42-Common-Core/main/assets/covers/cover-ft_printf-bonus.png" alt="ft_printf Cover" width="100%" />
</div>

<div align="center">
  <h1>🖨️ ft_printf: Because ft_putnbr() and ft_putstr() aren't enough</h1>
  <img src="https://img.shields.io/badge/Language-C-blue" />
  <img src="https://img.shields.io/badge/Grade-125%2F100-success" />
  <img src="https://img.shields.io/badge/Norminette-Passing-success" />
</div>

---

> [!WARNING] 
> **⚠️ 42 Evaluation & Moulinette Disclaimer**
> 
> This repository contains a fully modular, separated directory structure for the Mandatory (`./srcs`) and Bonus (`./bonus/srcs`) parts of the project. This was done for portfolio organization and to maintain clean, separated logic.
> 
> **However, this specific folder structure and `Makefile` were NOT what I submitted to the official 42 repository.** > 
> Due to the extremely strict (and sometimes conflicting) ways Moulinette, Francinette (`paco`), and third-party testers handle `make bonus` overrides and dependencies, submitting this exact split structure can result in a `0` or a relink failure during evaluation. 
> 
> **For my actual submission that scored 125%:** I placed only the bonus `.c` and `.h` files into the root directory and used a standard, simplified `Makefile`. Because the bonus fully covers the mandatory requirements, this bypassed all automated testing conflicts. 
> 
> *If you are a 42 student using this repo for reference, please be careful with how you structure your final submission!*

---

## 💡 Description
**ft_printf** is a project in the 42 curriculum that requires recoding the standard C library `printf` function. 

The primary goal of this project is to learn how to use **variadic arguments** in C (functions that accept an indefinite number of arguments) while building a robust, extensible formatting engine. The key to a successful `ft_printf` is well-structured and extensible code, which lays the groundwork for handling complex string formatting without relying on the original function's buffer management. This custom `ft_printf` is fully integrated with my `libft`.

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

To keep the codebase clean and adhere strictly to the 42 Norm, this repository is split into two distinct engines: a lightweight Mandatory parser, and a complex Bonus parser. 

### 1. The Mandatory Engine (`./srcs`)
The mandatory version is built for pure speed and simplicity. It uses a linear `while` loop to parse the format string. When a `%` is encountered, a modular dispatcher routes the variadic argument directly to the appropriate printing function. 

### 2. The Bonus Engine (`./bonus/srcs`)
To efficiently manage the bonus flags (`-`, `0`, `.`, `#`, `+`, `space`, and width) without passing a dozen variables between functions, the bonus architecture utilizes a centralized `t_flags` structure. 
Whenever a `%` is encountered, the parser initializes this struct, reads the intermediate characters, and activates the corresponding boolean values and integer widths before passing the struct to the final conversion dispatch.

```c
typedef struct s_flags
{
    bool    minus;
    bool    plus;
    bool    space;
    bool    hash;
    bool    zero;
    int     width;
    int     prec;
}   t_flags;
```

### Algorithm: Unified Base Conversion & Dispatch
*Per the subject requirements, here is the justification for the architecture used in this project.*

1. **Linear Parsing:** The algorithm iterates linearly through the format string using a `while` loop. When a `%` character is found, the parser enters a "flag reading" state.
2. **Variadic Extraction:** Using `<stdarg.h>` macros (`va_start`, `va_arg`, `va_end`), the corresponding arguments are dynamically extracted based on the final conversion specifier.
3. **Modular Dispatch:** A dispatcher routes the argument and the populated `t_flags` struct to specific formatting functions (e.g., `ft_puthex_cnt`, `ft_putnbr_cnt`).
4. **Universal String Conversion (`ft_utoa_base`):** Instead of duplicating logic for integer, hexadecimal, and pointer conversions, the architecture converts signed numbers to positive `unsigned long` values. These are all routed through a single, custom utility function (`ft_utoa_base`) that handles dynamic base conversion, drastically reducing code duplication and adhering strictly to the 42 Norm. Memory is dynamically allocated, printed with proper padding, and immediately freed.

---

## 🛠️ Instructions

### 📦 Installation
Because this repository is separated into two parts, the `Makefile` builds them independently based on your needs.

To compile the **Mandatory** library (`./srcs`):
```bash
make
```

To compile the **Bonus** library with full flag support (`./bonus/srcs`):
```bash
make bonus
```

Both commands will output a `libftprintf.a` archive file in the root directory.

### 🧹 Cleaning
* `make clean`: Removes object files (`.o`) and stamp files.
* `make fclean`: Removes object files and the `libftprintf.a` library.
* `make re`: Performs a clean re-build.

### 💻 Usage
To use this library in your code, include the header and link the archive during compilation:

**1. Include header:**
*(Use `"ft_printf_bonus.h"` if you are compiling against the bonus library)*
```c
#include "ft_printf.h"

int main()
{
    ft_printf("Hello %s! The magic number is %05d.\n", "42", 42);
    return (0);
}
```

**2. Compile:**
Make sure to point the compiler to your headers directory.
```bash
cc main.c -I./includes -L. -lftprintf -o my_program
```

### 🧪 Testing
The 42 subject highly encourages creating test programs to verify your work before peer evaluations. 

**1. Using a Custom Tester**
If you are using the custom `ft_printf_tester.c` file, you must use preprocessor macros (`-D`) during compilation to tell the tester which suite of tests to run (`TEST_MANDATORY` and/or `TEST_BONUS`).

To compile and run all tests against the library:
```bash
cc -Wall -Wextra -Werror -I./includes -I./libft/includes -D TEST_MANDATORY -D TEST_BONUS ft_printf_tester.c libftprintf.a -o tester
./tester
```
> **⚠️ WARNING for 42 Students:** Do not push `ft_printf_tester.c` or any executable files to your final Moulinette repository! They are strictly for local testing purposes. Submitting unauthorized files will result in a 0.

**2. Third-Party Testers (Francinette)**
Francinette is a widely used testing framework within the 42 community that runs strict tests (including memory leak checks and edge cases) against your library.

* **Installation:** Follow the instructions on the [Francinette GitHub Repository](https://github.com/xicodomingues/francinette).
* **Usage:** Inside your repository root, run:
```bash
paco
```
*(Note: To include bonus functions, use `paco -b`. To enforce strict norm and timeout rules, use `paco -s`)*

### 🚨 The Norm
Moulinette relies on a program called `norminette` to check if your files comply with the 42 Norm. Every single `.c` and `.h` file, including bonus files, must pass this check. If there is a norm error, you will receive a 0.

**The 42 Header:**
Before writing any code, every file must start with the standard 42 header. `norminette` will automatically fail any file missing this specific signature.
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:11:33 by maaugust          #+#    #+#             */
/*   Updated: 2025/05/21 15:41:17 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
```

Run the following command in the root of your repository before pushing to check all your files at once:
```bash
norminette -R CheckForbiddenSourceHeader
```

---

## 📚 Resources & References

**System Manuals:**
* `man 3 printf` - Essential manual for understanding the original formatting specifications and flag behaviors.
* `man 3 stdarg` / `man 3 va_start` - Manuals detailing the macros used to handle variable argument lists.

**Articles & Guides:**
* **[C Variadic Functions (cppreference)](https://en.cppreference.com/w/c/variadic):** A comprehensive reference guide for `<stdarg.h>` and variadic function syntax.
* **[ft_printf Tutorial 42Project (CS Notes)](https://csnotes.medium.com/ft-printf-tutorial-42project-f09b6dc1cd0e):** An excellent Medium article explaining the core concepts, architecture, and edge cases of the `ft_printf` project.
* **[Makefile Tutorial](https://makefiletutorial.com/):** A complete, easy-to-read guide to understanding and building Makefiles.

**Video Tutorials:**
* **[Oceano - All you need to know about variadic functions](https://www.youtube.com/watch?v=7Sph8JlRo0g&list=PLc4DnsRQbs6YsGjxHE-UgoI0ZGsuD8VQY):** A detailed whiteboard and code walkthrough by Oceano explaining exactly how variadic arguments operate at the memory level.
* **[CodeVault - What are variadic functions (va_list) in C?](https://www.youtube.com/watch?v=oDC208zvsdg):** A very clear and concise explanation by CodeVault on implementing `va_list`, `va_start`, `va_arg`, and `va_end`.

**42 Standards:**
* **[42 Norm V4](https://cdn.intra.42.fr/pdf/pdf/96987/en.norm.pdf):** The strict coding standard for 42 C projects.
* **[Official 42 Norminette Repository](https://github.com/42School/norminette):** The open-source linter enforcing the strict 42 coding standard.

### 🤖 AI Usage & Transparency
In the spirit of transparency and the learning objectives of the 42 curriculum, here is how AI tools were utilized during this project:

* **Conceptual Validation:** Used as a sounding board to brainstorm structural layouts for the `t_flags` parsing algorithm and `Makefile` dependencies.
* **Documentation & Formatting:** Assisted in generating portfolio-ready documentation and Doxygen templates.
* **Zero Code Generation:** **No core logic was generated by AI**. All variadic parsing, memory management, base conversions, and flag routing were 100% manually coded. This strict boundary ensures a fundamental understanding of C and pointer manipulation.
