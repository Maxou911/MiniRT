/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:50:11 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/camera.h"
#include "../../include/operations.h"
#include <math.h>

void	camera_generate_ray(t_camera *cam, double u, double v, t_ray *out)
{
	t_vec3	dir;

	out->origin = cam->pos;
	dir = vec3_add_val(vec3_scale_val(cam->horizontal, u),
			vec3_scale_val(cam->vertical, v));
	dir = vec3_add_val(dir, cam->llc);
	dir = vec3_sub_val(dir, out->origin);
	out->direction = vec3_normalize(&dir);
	out->record.object = NULL;
	out->record.t = 0.0;
	out->record.color = (t_color){0, 0, 0};
}
