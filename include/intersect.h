/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:14:59 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/19 16:38:44 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "ray.h"

/*
But:
	Contient tous les éléments intermédiaires nécessaires au calcul
	d'intersection rayon/cylindre et à la mise à jour du hit record.
*/
typedef struct s_cy_ctx
{
	t_vec3	n;
	double	r;
	t_vec3	d;
	t_vec3	ox;
	double	a;
	double	half_b;
	double	c;
	double	root0;
	double	root1;
}	t_cy_ctx;

/*
But:
	Rassembler les éléments intermédiaires nécessaires au calcul
	de l'intersection rayon/sphère, afin de limiter le nombre
	de variables locales dans les fonctions.
*/
typedef struct s_sph_ctx
{
	double	r;
	t_vec3	oc;
	double	a;
	double	half_b;
	double	c;
	double	root0;
	double	root1;
}	t_sph_ctx;

/*
But:
	regrouper les valeurs intermédiaires utiles à l'intersection
	pour limiter le nombre de variables locales par fonction.
*/
typedef struct s_pl_ctx
{
	double	den;
	double	t;
	t_vec3	diff;
	t_vec3	local_normal;
}	t_pl_ctx;

int		hit_sphere(t_ray *ray, t_sphere *s);
int		hit_plane(t_ray *ray, t_plane *p);
int		hit_cylinder(t_ray *ray, t_cylinder *c);

#endif
