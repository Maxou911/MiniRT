/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:14:44 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "raytracing.h"
# include "ray.h"

void	camera_init(t_camera *cam, int width, int height);
void	camera_generate_ray(t_camera *cam, double u, double v, t_ray *out);
t_vec3	vec3_cross_val(t_vec3 a, t_vec3 b);
t_vec3	vec3_sub_val(t_vec3 a, t_vec3 b);
t_vec3	vec3_add_val(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale_val(t_vec3 a, double s);

#endif
