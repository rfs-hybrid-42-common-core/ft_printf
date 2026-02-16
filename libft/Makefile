# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/03 18:21:29 by maaugust          #+#    #+#              #
#    Updated: 2026/01/11 14:45:37 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
LIBFT             = libft.a

# ============================== COMPILER FLAGS ============================== #
CC                = cc
CFLAGS            = -Wall -Wextra -Werror
INCLUDES          = -Iincludes
AR                = ar rcs
RM                = rm -rf

# ================================== COLORS ================================== #
GREEN             := \033[32m
RED               := \033[31m
YELLOW            := \033[33m
CYAN              := \033[36m
RESET             := \033[0m
BOLD              := \033[1m

# =============================== SOURCE FILES =============================== #
LIBFT_SRC_PATH    = srcs
LIBFT_SRC         = $(shell find $(LIBFT_SRC_PATH) -name '*.c')

LIBFT_OBJ_PATH    = objs
LIBFT_OBJ         = $(patsubst $(LIBFT_SRC_PATH)/%.c, $(LIBFT_OBJ_PATH)/%.o, $(LIBFT_SRC))

# ============================ COMPILATION RULES ============================= #
$(LIBFT_OBJ_PATH)/%.o: $(LIBFT_SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling libft:$(RESET) $(YELLOW)$<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============================== BUILD TARGETS ============================== #
all: $(LIBFT)

$(LIBFT): $(LIBFT_OBJ)
	@printf "$(GREEN)✔ Libft objects built successfully.$(RESET)\n"
	@$(AR) $(LIBFT) $(LIBFT_OBJ)
	@printf "$(GREEN)$(BOLD)✔ Library created → $(LIBFT)$(RESET)\n"

# ============================== CLEAN TARGETS =============================== #
clean:
	@$(RM) $(LIBFT_OBJ_PATH)
	@printf "$(YELLOW)• Cleaned libft object files.$(RESET)\n"

fclean: clean
	@$(RM) $(LIBFT)
	@printf "$(RED)• Libft full clean complete.$(RESET)\n"

re: fclean all

# ============================== PHONY TARGETS =============================== #
.PHONY: all clean fclean re
