# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/06 13:19:40 by maalwis           #+#    #+#              #
#    Updated: 2026/06/19 13:32:40 by maalwis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \033[1;93m
BLUE = \033[1;96m
RESET = \033[0m

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = object_files

# OS detection (Linux vs macOS) and MiniLibX flags
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
# Default MiniLibX directory for macOS (prefer the C opengl version to avoid Swift toolchain issues)
MLX_DIR ?= minilibx_opengl_20191021
MLX_LDFLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
MLX_INC = -I$(MLX_DIR)
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_RPATH =
else
# Default MiniLibX directory for Linux
MLX_DIR ?= minilibx-linux
MLX_LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext
MLX_INC = -I$(MLX_DIR)
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_RPATH =
endif

SRC = \
	src/color/color_utils.c \
	src/ray/ray.c \
	src/camera/camera.c \
	src/camera/generate_ray.c \
	src/mlx_compat.c \
	src/operations/operations.c \
	src/operations/operations_utils.c \
	src/operations/operations_reflect.c \
	src/intersect/sphere.c \
	src/intersect/plane.c \
	src/intersect/cylinder.c \
	src/light/light.c \
	src/parser/parser.c \
	src/parser/parse_utils.c \
	src/parser/parse_scene.c \
	src/parser/parse_figures.c \
	src/parser/sanitize_utils.c \
	src/parser/sanitize.c \
	src/parser/strto_utils.c \
	src/parser/triplets.c \
	src/render/render.c \
	src/main.c \
	src/main_utils.c \
	src/free.c

LIBFT_PATH = superlibft
LIBFT = $(LIBFT_PATH)/libft.a

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Include directories
INCLUDES = $(MLX_INC) -I$(LIBFT_PATH)/includes -I. -Iinclude

all: $(OBJ_DIR) $(NAME)
	@printf " $(GREEN)✅ Compilation terminée avec succès$(RESET)\n"

$(NAME): $(OBJ) $(LIBFT) $(MLX_LIB)
	@printf " $(BLUE)🔗 Liaison des objets$(RESET)\n"
	@$(CC) $(OBJ) $(LIBFT) $(MLX_LDFLAGS) $(MLX_RPATH) -lm -o $(NAME)
	@printf " $(GREEN)🎯 Exécutable $(NAME) créé$(RESET)\n"

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(OBJ_DIR):
	@printf " $(YELLOW)📁 Création des dossiers objets$(RESET)\n"
	@mkdir -p $(OBJ_DIR)


	@printf " $(BLUE)⚙️  Compilation des fichiers$(RESET)\n"
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	@printf " 📚 Compilation de la MiniLibX\n"
	-@$(MAKE) -C $(MLX_DIR) CC=$(CC) CFLAGS="-O3 -std=gnu89"
	@test -f $(MLX_LIB) || (printf "MiniLibX: libmlx.a introuvable\n"; exit 1)

clean:
	@printf " $(YELLOW)🧹 Nettoyage des fichiers objets$(RESET)\n"
	@rm -rf $(OBJ_DIR)
	@printf " $(GREEN)✨ Nettoyage terminé$(RESET)\n"
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@printf " $(RED)🗑️ Suppression de l'exécutable $(NAME) et de l'archive libft.a$(RESET)\n"
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@printf " $(GREEN)🧽 Nettoyage complet terminé$(RESET)\n"

re: fclean all
	@printf " $(BLUE)🔄 Recompilation terminée$(RESET)\n"

.PHONY: all clean fclean re