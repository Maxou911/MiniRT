/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:43:36 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/camera.h"
#include "../../include/operations.h"
#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

t_vec3	vec3_cross_val(t_vec3 a, t_vec3 b)
{
	return (vec3_cross(&a, &b));
}

t_vec3	vec3_sub_val(t_vec3 a, t_vec3 b)
{
	return (vec3_sub(&a, &b));
}

t_vec3	vec3_add_val(t_vec3 a, t_vec3 b)
{
	return (vec3_add(&a, &b));
}

t_vec3	vec3_scale_val(t_vec3 a, double s)
{
	return (vec3_scale(&a, s));
}

void	camera_init(t_camera *cam, int width, int height)
{
	double	vp_w;
	double	vp_h;
	t_vec3	w;
	t_vec3	u;
	t_vec3	v;

	vp_w = 2.0 * tan((cam->fov * M_PI / 180.0) / 2.0);
	vp_h = vp_w * (double)height / (double)width;
	w = vec3_normalize(&cam->dir);
	w = vec3_scale_val(w, -1.0);
	u = vec3_cross_val((t_vec3){0, 1, 0}, w);
	v = vec3_cross_val(w, u);
	cam->horizontal = vec3_scale_val(u, vp_w);
	cam->vertical = vec3_scale_val(v, vp_h);
	cam->llc = vec3_sub_val(cam->pos, vec3_scale_val(cam->horizontal, 0.5));
	cam->llc = vec3_sub_val(cam->llc, vec3_scale_val(cam->vertical, 0.5));
	cam->llc = vec3_sub_val(cam->llc, w);
}
