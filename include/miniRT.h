/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:33:00 by maalwis           #+#    #+#             */
/*   Updated: 2026/06/19 13:43:21 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "superlibft.h"
# include "raytracing.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>

/* Key codes: make portable across macOS (__APPLE__) and Linux (__linux__) */
# ifdef __APPLE__
#  define ESC 53
#  define LEFT 123
#  define UP 126
#  define RIGHT 124
#  define DOWN 125
# else
#  define ESC 65307
#  define LEFT 65361
#  define UP 65362
#  define RIGHT 65363
#  define DOWN 65364
# endif

typedef struct s_img
{
	void		*img;
	int			width;
	int			height;
}				t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
}				t_vars;

typedef struct s_rt
{
	t_vec3	vec3;
	t_vars	vars;
	t_img	img;
}	t_rt;

typedef struct s_app_ctx
{
	void	*mlx;
	void	*win;
	void	*img;
	t_scene	scene;
}	t_app_ctx;

/* Main utils */
int		close_hook(void *p);
int		handle_key(int key, void *p);
int		has_rt_extension(const char *path);
void	init_scene_defaults(t_scene *scene);
void	free_scene(t_scene *scene);
void	free_node(void *p);
void	destroy_mlx_all(t_app_ctx *app);
int		parse_and_validate_scene(const char *path, t_scene *scene);

/* MLX compat */
int		mlx_key_hook_compat(void *win_ptr,
			int (*funct_ptr)(int, void *), void *param);
int		mlx_hook_destroy_compat(void *win_ptr, int mask,
			int (*funct_ptr)(void *), void *param);

#endif