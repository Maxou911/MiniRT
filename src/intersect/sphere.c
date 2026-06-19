/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:46:02 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/intersect.h"
#include "../../include/operations.h"
#include <math.h>

/*
But:
	Initialiser le contexte: rayon de la sphère, vecteur centre->origine (oc)
	et coefficients (a, half_b, c) de l'équation d'intersection.
Détails:
	- r: rayon (diamètre / 2).
	- oc: vecteur de l'origine du rayon vers le centre de la sphère.
	- a, half_b, c: coefficients pour déterminer 0/1/2 intersections potentielles
Utilité:
	Centraliser l'initialisation pour alléger hit_sphere
*/
static void	sph_init_ctx(t_sphere *s, t_ray *ray, t_sph_ctx *ctx)
{
	ctx->r = s->diameter * 0.5;
	ctx->oc = vec3_sub(&ray->origin, &s->center);
	ctx->a = vec3_dot(&ray->direction, &ray->direction);
	ctx->half_b = vec3_dot(&ctx->oc, &ray->direction);
	ctx->c = vec3_dot(&ctx->oc, &ctx->oc) - ctx->r * ctx->r;
}

/*
But:
	Déterminer s'il y a 0/1/2 intersections en calculant le discriminant,
	et remplir root0/root1 si elles existent.
Détails:
	- disc < 0: aucune intersection réelle.
	- sinon: deux distances candidates root0 et root1 le long du rayon.
Utilité:
	Séparer la résolution mathématique de la validation des hits.
*/
static int	sph_solve_quad(t_sph_ctx *ctx)
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
	Mettre à jour le hit record pour une distance t valide (point, normale,
	couleur, type, pointeur d'objet).
Détails:
	- p: point d'impact.
	- n: normale géométrique, orientée vers l'extérieur.
Utilité:
	Séparer la mise à jour du record pour garder hit_sphere concis.
*/
static int	sph_try_hit(double t, t_sphere *s, t_ray *ray)
{
	t_vec3	p;
	t_vec3	n;

	p = ray_at(ray, t);
	ray->record.t = t;
	ray->record.p = p;
	n = vec3_sub(&p, &s->center);
	n = vec3_normalize(&n);
	if (vec3_dot(&ray->direction, &n) > 0.0)
		n = vec3_scale(&n, -1.0);
	ray->record.normal = n;
	ray->record.color = s->color;
	ray->record.type = 2;
	ray->record.object = s;
	return (1);
}

/*
But:
	Tester l'intersection d'un rayon avec une sphère.
Détails:
	- Initialise le contexte (r, oc, a, half_b, c).
	- Résout pour obtenir 0/1/2 distances candidates.
	- Tente de valider chaque distance (t > EPSILON et t minimal).
	- Met à jour le hit record et retourne 1 en cas de succès.
Utilité:
	Point d'entrée utilisé par le moteur de rendu pour les sphères.
*/
int	hit_sphere(t_ray *ray, t_sphere *s)
{
	t_sph_ctx	ctx;
	int			i;
	double		t;
	int			solved;

	sph_init_ctx(s, ray, &ctx);
	solved = sph_solve_quad(&ctx);
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
			if (sph_try_hit(t, s, ray))
				return (1);
		}
		i++;
	}
	return (0);
}
