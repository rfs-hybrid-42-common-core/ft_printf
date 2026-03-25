# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/28 21:11:29 by maaugust          #+#    #+#              #
#    Updated: 2026/03/25 05:09:46 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
NAME           = libftprintf.a

# ============================== COMPILER FLAGS ============================== #
CC             = cc
CFLAGS         = -Wall -Wextra -Werror -MMD -MP
INCLUDES       = -Iincludes -Ilibft/includes
B_INCLUDES     = -Ibonus/includes -Ilibft/includes
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
# Mandatory files
SRC_PATH       = ./srcs
SRC_FILES      = ft_printf.c ft_putchar_cnt.c ft_puthex_cnt.c ft_putnbr_cnt.c \
                 ft_putptr_cnt.c ft_putstr_cnt.c ft_putunbr_cnt.c ft_utoa_base.c
SRC            = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

# Bonus files
B_SRC_PATH     = ./bonus/srcs
B_SRC_FILES    = ft_flags_bonus.c ft_printf_bonus.c ft_putchar_cnt_bonus.c \
                 ft_puthex_cnt_bonus.c ft_putnbr_cnt_bonus.c ft_putptr_cnt_bonus.c \
                 ft_putstr_cnt_bonus.c ft_putunbr_cnt_bonus.c ft_utoa_base_bonus.c
B_SRC          = $(addprefix $(B_SRC_PATH)/, $(B_SRC_FILES))

# =============================== OBJECT FILES =============================== #
# Mandatory files
OBJ_PATH       = ./objs
OBJ            = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

# Bonus files
B_OBJ_PATH     = ./bonus/objs
B_OBJ          = $(patsubst $(B_SRC_PATH)/%.c, $(B_OBJ_PATH)/%.o, $(B_SRC))

# ============================ COMPILATION RULES ============================= #
# Mandatory files
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling:$(RESET) $(YELLOW)$<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Bonus files
$(B_OBJ_PATH)/%.o: $(B_SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling:$(RESET) $(YELLOW)$<$(RESET)\n"
	@$(CC) $(CFLAGS) $(B_INCLUDES) -c $< -o $@

# =============================== BUILD TARGETS ============================== #
all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJ)
	@printf "$(GREEN)✔ ft_printf mandatory objects built successfully.$(RESET)\n"
	@cp $(LIBFT_LIB) $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@printf "$(GREEN)$(BOLD)✔ Library created → $(NAME)$(RESET)\n"

bonus: .bonus

.bonus: $(LIBFT_LIB) $(B_OBJ)
	@printf "$(GREEN)✔ ft_printf bonus objects built successfully.$(RESET)\n"
	@cp $(LIBFT_LIB) $(NAME)
	@$(AR) $(NAME) $(B_OBJ)
	@touch .bonus
	@printf "$(GREEN)$(BOLD)✔ Library created → $(NAME) (Bonus version)$(RESET)\n"

$(LIBFT_LIB):
	@printf "$(CYAN)→ Building Libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_PATH) >/dev/null \
	  || { printf "$(RED)✖ Libft build failed!$(RESET)\n"; exit 1; }
	@printf "$(GREEN)✔ Libft built.$(RESET)\n"
	
# ============================== CLEAN TARGETS =============================== #
clean:
	@$(RM) $(OBJ_PATH) $(B_OBJ_PATH) .bonus
	@rmdir -p --ignore-fail-on-non-empty $(OBJ_PATH) $(B_OBJ_PATH) 2>/dev/null || true
	@$(MAKE) -C $(LIBFT_PATH) clean >/dev/null
	@printf "$(YELLOW)• Cleaned object files.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean >/dev/null
	@printf "$(RED)• Full clean complete.$(RESET)\n"

re: fclean all

# ============================== PHONY TARGETS =============================== #
.PHONY: all bonus clean fclean re clean_bonus

# =============================== DEPENDENCIES =============================== #
-include $(OBJ:.o=.d)
-include $(B_OBJ:.o=.d)
