/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_reflect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:45:32 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:15:04 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "operations.h"
#include <math.h>

t_vec3	vec3_reflect(t_vec3 *i, t_vec3 *n)
{
	t_vec3	result;
	double	dot;
	t_vec3	scaled_n;

	dot = vec3_dot(i, n);
	scaled_n = vec3_scale(n, 2 * dot);
	result = vec3_sub(i, &scaled_n);
	return (result);
}
