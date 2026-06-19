/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 17:39:44 by maalwis           #+#    #+#             */
/*   Updated: 2025/11/12 15:20:28 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "libft.h"

/* x --> abscisses; y --> ordonnees; z --> cotes ou altitudes; */
typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_camera
{
	t_vec3	pos;
	t_vec3	dir;
	double	fov;
	t_vec3	horizontal;
	t_vec3	vertical;
	t_vec3	llc;
}	t_camera;

typedef struct s_ambient_lighting
{
	double	intensity;
	t_color	color;
}	t_ambient_lighting;

typedef struct s_light
{
	t_vec3	pos;
	double	intensity;
	t_color	color;
}	t_light;

typedef struct s_plane
{
	int		type;
	t_vec3	point;
	t_vec3	normal;
	t_color	color;
}	t_plane;

typedef struct s_sphere
{
	int		type;
	t_vec3	center;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_cylinder
{
	int		type;
	t_vec3	center;
	t_vec3	axis;
	double	height;
	double	diameter;
	t_color	color;
}	t_cylinder;

typedef struct s_scene
{
	int					width;
	int					height;
	t_list				*cameras;
	t_list				*lights;
	t_list				*objs;
	t_ambient_lighting	amb;
}	t_scene;

#endif
