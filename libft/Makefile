# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/03 18:21:29 by maaugust          #+#    #+#              #
#    Updated: 2026/03/25 06:04:26 by maaugust         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ============================ PROJECT FILE NAMES ============================ #
NAME           = libft.a

# ============================== COMPILER FLAGS ============================== #
CC             = cc
CFLAGS         = -Wall -Wextra -Werror -MMD -MP
INCLUDES       = -Iincludes
AR             = ar rcs
RM             = rm -rf

# ================================== COLORS ================================== #
GREEN          := \033[32m
RED            := \033[31m
YELLOW         := \033[33m
CYAN           := \033[36m
RESET          := \033[0m
BOLD           := \033[1m

# =============================== SOURCE FILES =============================== #
SRC_PATH       = ./srcs
SRC_FILES      = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
                 ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
				 ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c \
				 ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
				 ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
				 ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
				 ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
				 ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c \
				 ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
				 ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c
SRC            = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

# =============================== OBJECT FILES =============================== #
OBJ_PATH       = ./objs
OBJ            = $(patsubst $(SRC_PATH)/%.c, $(OBJ_PATH)/%.o, $(SRC))

# ============================ COMPILATION RULES ============================= #
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(dir $@)
	@printf "$(CYAN)Compiling libft:$(RESET) $(YELLOW)$<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# =============================== BUILD TARGETS ============================== #
all: $(NAME)

$(NAME): $(OBJ)
	@printf "$(GREEN)✔ Libft objects built successfully.$(RESET)\n"
	@$(AR) $(NAME) $(OBJ)
	@printf "$(GREEN)$(BOLD)✔ Library created → $(NAME)$(RESET)\n"

# ============================== CLEAN TARGETS =============================== #
clean:
	@$(RM) $(OBJ_PATH)
	@printf "$(YELLOW)• Cleaned libft object files.$(RESET)\n"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)• Libft full clean complete.$(RESET)\n"

re: fclean all

# ============================== PHONY TARGETS =============================== #
.PHONY: all clean fclean re

# =============================== DEPENDENCIES =============================== #
-include $(OBJ:.o=.d)
