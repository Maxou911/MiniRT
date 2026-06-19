/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:40:36 by maalwis           #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <math.h>

t_vec3	vec3_add(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

t_vec3	vec3_sub(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return (result);
}

t_vec3	vec3_scale(t_vec3 *a, double s)
{
	t_vec3	result;

	result.x = a->x * s;
	result.y = a->y * s;
	result.z = a->z * s;
	return (result);
}

t_vec3	vec3_cross(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->y * b->z - a->z * b->y;
	result.y = a->z * b->x - a->x * b->z;
	result.z = a->x * b->y - a->y * b->x;
	return (result);
}

double	vec3_dot(t_vec3 *a, t_vec3 *b)
{
	double	result1;
	double	result2;
	double	result3;

	result1 = a->x * b->x;
	result2 = a->y * b->y;
	result3 = a->z * b->z;
	return (result1 + result2 + result3);
}
