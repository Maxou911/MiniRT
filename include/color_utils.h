/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:14:51 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_UTILS_H
# define COLOR_UTILS_H

# include "raytracing.h"

// Addition de couleurs (composante par composante) avec clamp [0,255]
t_color	color_add(t_color a, t_color b);

// Multiplication par un scalaire [0..] avec clamp [0,255]
t_color	color_scale(t_color c, double s);

// Produit composante par composante, normalisé sur 255, clampé
t_color	color_mul(t_color a, t_color b);

// Construit une couleur clampée
t_color	color_make(int r, int g, int b);

#endif
