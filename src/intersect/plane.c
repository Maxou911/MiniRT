/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:45:47 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:19:43 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/intersect.h"
#include "../../include/operations.h"

/*
But:
	calculer le dénominateur (test de parallélisme) et la distance t
	d'intersection potentielle avec le plan.
Détails:
	- si den == 0.0, le rayon est parallèle au plan -> pas d'intersection.
	- sinon, t = dot((point - origin), normal) / den.
Utilité:
	isoler le calcul pour garder hit_plane concis
*/
static int	pl_compute_t(t_ray *ray, t_plane *p, t_pl_ctx *ctx)
{
	double	den;
	double	t;
	t_vec3	diff;

	den = vec3_dot(&ray->direction, &p->normal);
	if (den == 0.0)
		return (0);
	diff = vec3_sub(&p->point, &ray->origin);
	t = vec3_dot(&diff, &p->normal) / den;
	ctx->den = den;
	ctx->t = t;
	ctx->diff = diff;
	return (1);
}

/*
But:
	valider t (devant la caméra et minimal) puis remplir le hit record:
	point d'impact, normale orientée, couleur, type, objet.
Utilité:
	séparer la mise à jour du record pour simplifier hit_plane.
*/
static int	pl_try_hit(t_ray *ray, t_plane *p, t_pl_ctx *ctx)
{
	t_vec3	local_normal;

	if (!(ctx->t > EPSILON && (ray->record.t == 0.0 || ctx->t < ray->record.t)))
		return (0);
	local_normal = p->normal;
	if (vec3_dot(&ray->direction, &local_normal) > 0.0)
		local_normal = vec3_scale(&local_normal, -1.0);
	ray->record.t = ctx->t;
	ray->record.p = ray_at(ray, ctx->t);
	ray->record.normal = local_normal;
	ray->record.color = p->color;
	ray->record.type = 1;
	ray->record.object = p;
	return (1);
}

/*
But:
	tester l'intersection d'un rayon avec un plan.
Détails:
	- calcule t (si non parallèle),
	- valide et remplit le record en cas de hit.
Utilité:
	point d'entrée utilisé par le moteur de rendu pour les plans.
*/
int	hit_plane(t_ray *ray, t_plane *p)
{
	t_pl_ctx	ctx;
	int			ok;

	ok = pl_compute_t(ray, p, &ctx);
	if (!ok)
		return (0);
	if (pl_try_hit(ray, p, &ctx))
		return (1);
	return (0);
}
