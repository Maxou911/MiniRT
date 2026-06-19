/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:18:24 by uzyberaj          #+#    #+#             */
/*   Updated: 2025/11/14 19:30:41 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_node(void *p)
{
	if (p)
		free(p);
}

#ifdef __linux__

static void	destroy_display_if_needed(void *mlx)
{
	if (mlx)
		mlx_destroy_display(mlx);
}
#else

static void	destroy_display_if_needed(void *mlx)
{
	(void)mlx;
}
#endif

void	destroy_mlx_all(t_app_ctx *app)
{
	if (!app)
		return ;
	if (app->mlx && app->img)
		mlx_destroy_image(app->mlx, app->img);
	if (app->mlx && app->win)
		mlx_destroy_window(app->mlx, app->win);
	destroy_display_if_needed(app->mlx);
	if (app->mlx)
		free(app->mlx);
}

void	free_scene(t_scene *scene)
{
	if (!scene)
		return ;
	ft_lstclear(&scene->objs, free_node);
	ft_lstclear(&scene->lights, free_node);
	ft_lstclear(&scene->cameras, free_node);
}
