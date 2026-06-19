/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:15:17 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:15:04 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "raytracing.h"

# define EPSILON 1e-4

typedef struct s_hit
{
	t_vec3	normal;
	t_vec3	p;
	double	t;
	void	*object;
	t_color	color;
	int		type;
}			t_hit;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_hit	record;
}	t_ray;

t_vec3	ray_at(t_ray *ray, double t);

#endif
