/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:10:01 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:20:20 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATIONS_H
# define OPERATIONS_H

# include "raytracing.h"

t_vec3	vec3_add(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_sub(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_scale(t_vec3 *a, double s);
t_vec3	vec3_cross(t_vec3 *a, t_vec3 *b);
double	vec3_dot(t_vec3 *a, t_vec3 *b);
double	vec3_length(t_vec3 *a);
t_vec3	vec3_normalize(t_vec3 *a);
t_vec3	vec3_mul(t_vec3 *a, t_vec3 *b);
double	vec3_distance(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_negate(t_vec3 *a);
t_vec3	vec3_reflect(t_vec3 *i, t_vec3 *n);

#endif
