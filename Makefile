# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 21:11:29 by maaugust          #+#    #+#              #
#    Updated: 2026/02/16 23:39:37 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
LIBFTPRINTF           = libftprintf.a

# ============================== COMPILER FLAGS ============================== #
CC                    = cc
CFLAGS                = -Wall -Wextra -Werror
INCLUDES              = -Iincludes -Ilibft/includes
AR                    = ar rcs
RM                    = rm -rf

# ================================== LIBFT =================================== #
LIBFT_DIR             = libft
LIBFT_LIB             = $(LIBFT_DIR)/libft.a

# ================================== COLORS ================================== #
GREEN                 := \033[32m
RED                   := \033[31m
YELLOW                := \033[33m
CYAN                  := \033[36m
RESET                 := \033[0m
BOLD                  := \033[1m

# =============================== SOURCE FILES =============================== #
LIBFTPRINTF_SRC_PATH  = ./srcs
LIBFTPRINTF_SRC       = $(shell find $(LIBFTPRINTF_SRC_PATH) -name '*.c')

LIBFTPRINTF_OBJ_PATH  = ./objs
LIBFTPRINTF_OBJ       = $(patsubst $(LIBFTPRINTF_SRC_PATH)/%.c, \
                          $(LIBFTPRINTF_OBJ_PATH)/%.o, $(LIBFTPRINTF_SRC))

# ============================ COMPILATION RULES ============================= #
$(LIBFTPRINTF_OBJ_PATH)/%.o: $(LIBFTPRINTF_SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling:$(RESET) $(YELLOW)$<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============================== BUILD TARGETS ============================== #
all: $(LIBFTPRINTF)

bonus: all

$(LIBFTPRINTF): $(LIBFT_LIB) $(LIBFTPRINTF_OBJ)
	@printf "$(GREEN)✔ Mandatory objects built successfully.$(RESET)\n"
	@cp $(LIBFT_LIB) $(LIBFTPRINTF)
	@$(AR) $(LIBFTPRINTF) $(LIBFTPRINTF_OBJ)
	@printf "$(GREEN)$(BOLD)✔ Build complete → $(LIBFTPRINTF)$(RESET)\n"

$(LIBFT_LIB):
	@printf "$(CYAN)→ Building Libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) >/dev/null \
	  || { printf "$(RED)✖ Libft build failed!$(RESET)\n"; exit 1; }
	@printf "$(GREEN)✔ Libft built.$(RESET)\n"
	
# ============================== CLEAN TARGETS =============================== #
clean:
	@$(RM) $(LIBFTPRINTF_OBJ_PATH)
	@$(MAKE) -C $(LIBFT_DIR) clean >/dev/null
	@printf "$(YELLOW)• Cleaned object files.$(RESET)\n"

fclean: clean
	@$(RM) $(LIBFTPRINTF)
	@$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null
	@printf "$(RED)• Full clean complete.$(RESET)\n"

re: fclean all

# ============================== PHONY TARGETS =============================== #
.PHONY: all clean fclean re bonus
