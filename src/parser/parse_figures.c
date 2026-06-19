/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_figures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:46:33 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:47 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/operations.h"
#include "../../superlibft/includes/superlibft.h"

static void	lst_add_back(t_list **lst, void *content)
{
	t_list	*it;
	t_list	*node;

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

int	parse_sphere_tokens(char **tok, t_scene *scene)
{
	t_sphere	*sp;
	double		diam;

	if (!tok[1] || !tok[2] || !tok[3] || tok[4])
		return (ft_printf("Error\nBad sphere format\n"), 0);
	sp = (t_sphere *)malloc(sizeof(*sp));
	if (!sp)
		return (ft_printf("Error\nAlloc sphere failed\n"), 0);
	sp->type = 2;
	if (!parse_vec3(tok[1], &sp->center))
		return (free(sp), ft_printf("Error\nSphere center invalid\n"), 0);
	if (!parse_double(tok[2], &diam) || diam <= 0.0)
		return (free(sp), ft_printf("Error\nSphere diameter invalid\n"), 0);
	sp->diameter = diam;
	if (!parse_color(tok[3], &sp->color))
		return (free(sp), ft_printf("Error\nSphere color invalid\n"), 0);
	lst_add_back(&scene->objs, sp);
	return (1);
}

int	parse_plane_tokens(char **tok, t_scene *scene)
{
	t_plane	*pl;

	if (!tok[1] || !tok[2] || !tok[3] || tok[4])
		return (ft_printf("Error\nBad plane format\n"), 0);
	pl = (t_plane *)malloc(sizeof(*pl));
	if (!pl)
		return (ft_printf("Error\nAlloc plane failed\n"), 0);
	pl->type = 1;
	if (!parse_vec3(tok[1], &pl->point))
		return (free(pl), ft_printf("Error\nPlane point invalid\n"), 0);
	if (!parse_vec3(tok[2], &pl->normal))
		return (free(pl), ft_printf("Error\nPlane normal invalid\n"), 0);
	pl->normal = vec3_normalize(&pl->normal);
	if (!parse_color(tok[3], &pl->color))
		return (free(pl), ft_printf("Error\nPlane color invalid\n"), 0);
	lst_add_back(&scene->objs, pl);
	return (1);
}

int	parse_cylinder_tokens(char **tok, t_scene *scene)
{
	t_cylinder	*cy;
	double		diam;
	double		height;

	if (!tok[1] || !tok[2] || !tok[3] || !tok[4] || !tok[5] || tok[6])
		return (ft_printf("Error\nBad cylinder format\n"), 0);
	cy = (t_cylinder *)malloc(sizeof(*cy));
	if (!cy)
		return (ft_printf("Error\nAlloc cylinder failed\n"), 0);
	cy->type = 3;
	if (!parse_vec3(tok[1], &cy->center))
		return (free(cy), ft_printf("Error\nCylinder center invalid\n"), 0);
	if (!parse_vec3(tok[2], &cy->axis))
		return (free(cy), ft_printf("Error\nCylinder axis invalid\n"), 0);
	cy->axis = vec3_normalize(&cy->axis);
	if (!parse_double(tok[3], &diam) || diam <= 0.0)
		return (free(cy), ft_printf("Error\nCylinder diameter invalid\n"), 0);
	if (!parse_double(tok[4], &height) || height <= 0.0)
		return (free(cy), ft_printf("Error\nCylinder height invalid\n"), 0);
	cy->diameter = diam;
	cy->height = height;
	if (!parse_color(tok[5], &cy->color))
		return (free(cy), ft_printf("Error\nCylinder color invalid\n"), 0);
	lst_add_back(&scene->objs, cy);
	return (1);
}
