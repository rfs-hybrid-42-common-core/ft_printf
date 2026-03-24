# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 21:11:29 by maaugust          #+#    #+#              #
#    Updated: 2026/03/24 18:43:05 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
NAME           = libftprintf.a

# ============================== COMPILER FLAGS ============================== #
CC             = cc
CFLAGS         = -Wall -Wextra -Werror -MMD -MP
INCLUDES       = -Iincludes -Ilibft/includes
AR             = ar rcs
RM             = rm -rf

# ================================== COLORS ================================== #
GREEN          := \033[32m
RED            := \033[31m
YELLOW         := \033[33m
CYAN           := \033[36m
RESET          := \033[0m
BOLD           := \033[1m

# ================================== LIBFT =================================== #
LIBFT_PATH     = ./libft
LIBFT_LIB      = $(LIBFT_PATH)/libft.a

# =============================== SOURCE FILES =============================== #
SRC_PATH       = ./srcs
SRC            = $(shell find $(SRC_PATH) -name '*.c')

OBJ_PATH       = ./objs
OBJ            = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

# ============================ COMPILATION RULES ============================= #
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling:$(RESET) $(YELLOW)$<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============================== BUILD TARGETS ============================== #
all: $(NAME)

bonus: all

$(NAME): $(LIBFT_LIB) $(OBJ)
	@printf "$(GREEN)✔ ft_printf objects built successfully.$(RESET)\n"
	@cp $(LIBFT_LIB) $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@printf "$(GREEN)$(BOLD)✔ Library created → $(NAME)$(RESET)\n"

$(LIBFT_LIB):
	@printf "$(CYAN)→ Building Libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH) >/dev/null \
	  || { printf "$(RED)✖ Libft build failed!$(RESET)\n"; exit 1; }
	@printf "$(GREEN)✔ Libft built.$(RESET)\n"
	
# ============================== CLEAN TARGETS =============================== #
clean:
	@$(RM) $(OBJ_PATH)
	@$(MAKE) -C $(LIBFT_PATH) clean >/dev/null
	@printf "$(YELLOW)• Cleaned object files.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean >/dev/null
	@printf "$(RED)• Full clean complete.$(RESET)\n"

re: fclean all

# ============================== PHONY TARGETS =============================== #
.PHONY: all clean fclean re bonus

# =============================== DEPENDENCIES =============================== #
-include $(OBJ:.o=.d)
-include $(B_OBJ:.o=.d)
