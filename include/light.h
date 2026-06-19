/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:15:05 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 09:41:41 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "ray.h"
# include "color_utils.h"
# include "intersect.h"

# define ALBEDO 1000.0

t_color	color_component(t_light light, t_hit record);
int		in_shadow(t_light light, t_list *figures, t_hit record);

#endif
