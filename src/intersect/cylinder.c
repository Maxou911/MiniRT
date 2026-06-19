/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:45:39 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/intersect.h"
#include "../../include/operations.h"
#include <math.h>

/*
But:
	Pré-calculer toutes les grandeurs nécessaires à l'intersection rayon/cylindre
Détails:
	- Normalise l'axe du cylindre.
	- Calcule le rayon (diamètre / 2).
	- Décompose la direction du rayon et l'origine relative au centre du cylindre
	en composantes perpendiculaires à l'axe, afin de ramener le problème en 2D.
	- Remplit les coefficients du polynôme quadratique (a, half_b, c).
Utilité:
	Centraliser l'initialisation afin d'alléger et normer hit_cylinder.
*/
static void	cy_init_ctx(t_cylinder *cy, t_ray *ray, t_cy_ctx *ctx)
{
	t_vec3	proj_d;
	t_vec3	ox_temp;
	t_vec3	proj_ox;

	ctx->n = vec3_normalize(&cy->axis);
	ctx->r = cy->diameter * 0.5;
	proj_d = vec3_scale(&ctx->n, vec3_dot(&ray->direction, &ctx->n));
	ctx->d = vec3_sub(&ray->direction, &proj_d);
	ox_temp = vec3_sub(&ray->origin, &cy->center);
	proj_ox = vec3_scale(&ctx->n, vec3_dot(&ox_temp, &ctx->n));
	ctx->ox = vec3_sub(&ox_temp, &proj_ox);
	ctx->a = vec3_dot(&ctx->d, &ctx->d);
	ctx->half_b = vec3_dot(&ctx->ox, &ctx->d);
	ctx->c = vec3_dot(&ctx->ox, &ctx->ox) - ctx->r * ctx->r;
}

/*
But:
	Résoudre le polynôme quadratique issu de l'intersection du rayon avec
	l'enveloppe latérale du cylindre.
Détails:
	- Calcule le discriminant et retourne 0 s'il est négatif
	(pas de racines réelles).
	- Stocke les deux solutions (root0, root1) dans le contexte.
Utilité:
	Séparer la résolution mathématique de la logique de filtrage/validation.
*/
static int	cy_solve_quad(t_cy_ctx *ctx)
{
	double	disc;

	disc = ctx->half_b * ctx->half_b - ctx->a * ctx->c;
	if (disc < 0.0)
		return (0);
	ctx->root0 = (-ctx->half_b - sqrt(disc)) / ctx->a;
	ctx->root1 = (-ctx->half_b + sqrt(disc)) / ctx->a;
	return (1);
}

/*
But:
	Valider une solution t (racine) et, si elle est admissible, mettre à jour
	l'enregistrement d'intersection du rayon.
Détails:
	- Calcule le point d'impact p et la hauteur m projetée sur l'axe du cylindre.
	- Vérifie que m est dans les bornes [0, height] (cylindre fini).
	- Calcule la normale géométrique et l'oriente à l'opposé
	de la direction du rayon.
	- Met à jour t, p, normal, color, type et object dans le record.
Utilité:
	Séparer la logique d'acceptation d'une racine
	et la mise à jour du hit record.
*/
static int	cy_try_hit(double t, t_cylinder *cy, t_ray *ray, t_cy_ctx *ctx)
{
	t_vec3	p;
	t_vec3	v;
	t_vec3	axis_comp;
	t_vec3	normal;
	double	m;

	p = ray_at(ray, t);
	v = vec3_sub(&p, &cy->center);
	m = vec3_dot(&v, &ctx->n);
	if (m < -EPSILON || m > cy->height + EPSILON)
		return (0);
	ray->record.t = t;
	ray->record.p = p;
	axis_comp = vec3_scale(&ctx->n, m);
	normal = vec3_sub(&v, &axis_comp);
	normal = vec3_normalize(&normal);
	if (vec3_dot(&ray->direction, &normal) > 0.0)
		normal = vec3_scale(&normal, -1.0);
	ray->record.normal = normal;
	ray->record.color = cy->color;
	ray->record.type = 3;
	ray->record.object = cy;
	return (1);
}

/*
But:
	Tester l'intersection d'un rayon avec un cylindre fini
Détails:
	- Initialise le contexte (axe normalisé, rayon, coefficients quadratiques).
	- Résout l'équation quadratique;
	si pas de solution réelle, pas d'intersection.
	- Parcourt les deux racines et tente de les valider via cy_try_hit.
	- Retourne 1 en cas de succès (hit enregistré), sinon 0.
Utilité:
	Point d'entrée appelé par le moteur de lancer de rayons
	pour gérer les cylindres.
*/
int	hit_cylinder(t_ray *ray, t_cylinder *cy)
{
	t_cy_ctx	ctx;
	int			i;
	double		t;
	int			solved;

	cy_init_ctx(cy, ray, &ctx);
	solved = cy_solve_quad(&ctx);
	if (!solved)
		return (0);
	i = 0;
	while (i < 2)
	{
		t = ctx.root0;
		if (i == 1)
			t = ctx.root1;
		if (t > EPSILON && (ray->record.t == 0.0 || t < ray->record.t))
		{
			if (cy_try_hit(t, cy, ray, &ctx))
				return (1);
		}
		i++;
	}
	return (0);
}
