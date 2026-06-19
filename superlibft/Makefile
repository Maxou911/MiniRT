# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/04 16:42:45 by maalwis           #+#    #+#              #
#    Updated: 2026/06/19 13:33:23 by maalwis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[32m
RED = \033[31m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

NAME = libft.a
CC := cc
CFLAGS := -Wall -Wextra -Werror
SRCS_DIR := sources
OBJ_DIR = object_files_superlibft

LIBFT_SRCS = \
				sources/libft/ft_isalpha.c \
				sources/libft/ft_isdigit.c \
				sources/libft/ft_isalnum.c \
				sources/libft/ft_isascii.c \
				sources/libft/ft_isprint.c \
				sources/libft/ft_strlen.c \
				sources/libft/ft_memset.c \
				sources/libft/ft_bzero.c \
				sources/libft/ft_memcpy.c \
				sources/libft/ft_memmove.c \
				sources/libft/ft_strlcpy.c \
				sources/libft/ft_strlcat.c \
				sources/libft/ft_toupper.c \
				sources/libft/ft_tolower.c \
				sources/libft/ft_strchr.c \
				sources/libft/ft_strrchr.c \
				sources/libft/ft_strncmp.c \
				sources/libft/ft_memchr.c \
				sources/libft/ft_memcmp.c \
				sources/libft/ft_strnstr.c \
				sources/libft/ft_atoi.c \
				sources/libft/ft_strdup.c \
				sources/libft/ft_calloc.c \
				sources/libft/ft_substr.c \
				sources/libft/ft_striteri.c \
				sources/libft/ft_putchar_fd.c \
				sources/libft/ft_putstr_fd.c \
				sources/libft/ft_putendl_fd.c \
				sources/libft/ft_putnbr_fd.c \
				sources/libft/ft_strjoin.c \
				sources/libft/ft_strtrim.c \
				sources/libft/ft_itoa.c \
				sources/libft/ft_strmapi.c \
				sources/libft/ft_split.c \
				sources/libft/ft_lstnew.c \
				sources/libft/ft_lstadd_front.c \
				sources/libft/ft_lstsize.c \
				sources/libft/ft_lstlast.c \
				sources/libft/ft_lstadd_back.c \
				sources/libft/ft_lstdelone.c \
				sources/libft/ft_lstclear.c \
				sources/libft/ft_lstiter.c \
				sources/libft/ft_lstmap.c \
				sources/libft/ft_strcmp.c \

FT_printf_SRCS = \
				sources/ft_printf/ft_printf.c \
				sources/ft_printf/ft_printf_format.c \
				sources/ft_printf/ft_printf_utils.c \

GNL_SRCS = \
				sources/get_next_line/get_next_line.c \
				sources/get_next_line/get_next_line_utils.c \

SRCS = $(LIBFT_SRCS) $(FT_printf_SRCS) $(GNL_SRCS)

OBJ = $(patsubst $(SRCS_DIR)/%, $(OBJ_DIR)/%, $(SRCS:.c=.o))

all: $(OBJ_DIR)/libft $(OBJ_DIR)/ft_printf $(OBJ_DIR)/get_next_line $(NAME)
	@printf "$(GREEN)📚 libft compilée avec succès$(RESET)\n"

compilationlibft: 
	@printf "$(BLUE)📚 Compilation de la libft$(RESET)\n"
	
$(NAME): compilationlibft $(OBJ)
	@printf "$(BLUE)🔗 Création de l'archive libft.a$(RESET)\n"
	@ar -rcs $(NAME) $(OBJ)
	
$(OBJ_DIR)/libft:
	@mkdir -p $@

$(OBJ_DIR)/ft_printf:
	@mkdir -p $@

$(OBJ_DIR)/get_next_line:
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@printf "$(YELLOW)🧹 Nettoyage des objets libft$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)✨ Nettoyage libft terminé$(RESET)\n"

fclean: clean
	@printf "$(RED)🗑️  Suppression de libft.a$(RESET)\n"
	@rm -f $(NAME) a.out
	@printf "$(GREEN)🧽 Nettoyage complet libft terminé$(RESET)\n"

re:	fclean all
	@printf "$(BLUE)🔄 Recompilation libft terminée$(RESET)\n"

.PHONY: all clean fclean re
