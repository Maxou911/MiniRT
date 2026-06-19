/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:45:25 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/19 16:34:24 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/color_utils.h"

static int	clampi(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

t_color	color_make(int r, int g, int b)
{
	t_color	c;

	c.r = clampi(r);
	c.g = clampi(g);
	c.b = clampi(b);
	return (c);
}

t_color	color_add(t_color a, t_color b)
{
	return (color_make(a.r + b.r, a.g + b.g, a.b + b.b));
}

t_color	color_scale(t_color c, double s)
{
	return (color_make((int)(c.r * s), (int)(c.g * s), (int)(c.b * s)));
}

t_color	color_mul(t_color a, t_color b)
{
	return (color_make((a.r * b.r) / 255, (a.g * b.g) / 255, \
		(a.b * b.b) / 255));
}
