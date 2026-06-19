/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:15:23 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/01 19:55:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "ray.h"
# include "camera.h"
# include "light.h"
# include "intersect.h"
# include "color_utils.h"

typedef struct s_image
{
	void	*img;
	char	*data;
	int		bpp;
	int		endian;
	int		size_line;
}	t_image;

t_color	raytrace(t_ray *ray, t_scene *scene);
void	put_pixel(t_image *img, int x, int y, t_color c);

#endif
