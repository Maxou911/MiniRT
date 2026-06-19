/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:46:50 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/14 19:11:25 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/camera.h"
#include "../../include/operations.h"
#include "../../superlibft/includes/superlibft.h"

static void	lst_add_back(t_list **lst, void *content)
{
	t_list	*node;
	t_list	*it;

	node = (t_list *)malloc(sizeof(*node));
	if (!node)
		return ;
	node->content = content;
	node->next = NULL;
	if (!*lst)
		*lst = node;
	else
	{
		it = *lst;
		while (it->next)
			it = it->next;
		it->next = node;
	}
}

int	parse_ambient_tokens(char **tok, t_scene *scene)
{
	double	intensity;
	t_color	color;

	if (!tok[1] || !tok[2] || tok[3])
		return (ft_printf("Error\nBad ambient format\n"), 0);
	if (scene->amb.intensity >= 0.0)
		return (ft_printf("Error\nAmbient defined more than once\n"), 0);
	if (!parse_double(tok[1], &intensity) || intensity < 0.0 || intensity > 1.0)
		return (ft_printf("Error\nAmbient intensity out of range\n"), 0);
	if (!parse_color(tok[2], &color))
		return (ft_printf("Error\nAmbient color invalid\n"), 0);
	scene->amb.intensity = intensity;
	scene->amb.color = color;
	return (1);
}

int	parse_camera_tokens(char **tok, t_scene *scene)
{
	t_camera	*cam;

	if (!tok[1] || !tok[2] || !tok[3] || tok[4])
		return (ft_printf("Error\nBad camera format\n"), 0);
	cam = (t_camera *)malloc(sizeof(*cam));
	if (!cam)
		return (ft_printf("Error\nAlloc camera failed\n"), 0);
	if (!parse_vec3(tok[1], &cam->pos))
		return (free(cam), ft_printf("Error\nCamera position invalid\n"), 0);
	if (!parse_vec3(tok[2], &cam->dir))
		return (free(cam), ft_printf("Error\nCamera direction invalid\n"), 0);
	if (!parse_double(tok[3], &cam->fov) || cam->fov < 0.0 || cam->fov > 180.0)
		return (free(cam), ft_printf("Error\nCamera FOV invalid\n"), 0);
	cam->dir = vec3_normalize(&cam->dir);
	camera_init(cam, scene->width, scene->height);
	lst_add_back(&scene->cameras, cam);
	return (1);
}

int	parse_light_tokens(char **tok, t_scene *scene)
{
	t_light	*li;

	if (!tok[1] || !tok[2])
		return (ft_printf("Error\nBad light format\n"), 0);
	li = (t_light *)malloc(sizeof(*li));
	if (!li)
		return (ft_printf("Error\nAlloc light failed\n"), 0);
	if (!parse_vec3(tok[1], &li->pos))
		return (free(li), ft_printf("Error\nLight position invalid\n"), 0);
	if (!parse_double(tok[2], &li->intensity) || li->intensity < 0.0 || \
li->intensity > 1.0)
		return (free(li), ft_printf("Error\nLight intensity invalid\n"), 0);
	if (tok[3])
	{
		if (!parse_color(tok[3], &li->color))
			return (free(li), ft_printf("Error\nLight color invalid\n"), 0);
	}
	else
		li->color = (t_color){255, 255, 255};
	lst_add_back(&scene->lights, li);
	return (1);
}
