/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:43:20 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:15:04 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "operations.h"
#include <math.h>

double	vec3_length(t_vec3 *a)
{
	double	sqr_len;

	sqr_len = a->x * a->x + a->y * a->y + a->z * a->z;
	return (sqrt(sqr_len));
}

t_vec3	vec3_normalize(t_vec3 *a)
{
	t_vec3	result;
	double	norm;

	norm = vec3_length(a);
	if (norm == 0.0)
	{
		result.x = 0.0;
		result.y = 0.0;
		result.z = 0.0;
		return (result);
	}
	result.x = a->x / norm;
	result.y = a->y / norm;
	result.z = a->z / norm;
	return (result);
}

t_vec3	vec3_mul(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->x * b->x;
	result.y = a->y * b->y;
	result.z = a->z * b->z;
	return (result);
}

double	vec3_distance(t_vec3 *a, t_vec3 *b)
{
	t_vec3	diff;

	diff = vec3_sub(a, b);
	return (vec3_length(&diff));
}

t_vec3	vec3_negate(t_vec3 *a)
{
	t_vec3	result;

	result.x = -a->x;
	result.y = -a->y;
	result.z = -a->z;
	return (result);
}
