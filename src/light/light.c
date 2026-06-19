/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:46:20 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/14 19:10:01 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/light.h"
#include "../../include/operations.h"
#include <math.h>
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

/*
But:
	Calculer l'intensité lumineuse reçue au point d'impact (Lambert + 1/r^2).
Détails:
	- ldir: direction du point vers la lumière (unitaire).
	- gain: cosinus de l'angle entre la normale et la lumière (dot clampé à > 0).
	- r2: distance au carré vers la lumière.
Utilité:
	Donner le facteur d'éclairement avant application de la couleur de l'objet.
*/
static double	light_intensity(t_light light, t_hit record)
{
	t_vec3	ldir;
	double	gain;
	double	r2;

	ldir = vec3_sub(&light.pos, &record.p);
	r2 = vec3_dot(&ldir, &ldir);
	ldir = vec3_normalize(&ldir);
	gain = vec3_dot(&ldir, &record.normal);
	if (gain <= 0.0)
		return (0.0);
	return ((light.intensity * gain * ALBEDO) / (4.0 * M_PI * r2));
}

/*
But:
	Calculer la contribution couleur d'une lumière sur un point.
Détails:
	- Récupère la couleur objet, applique l'intensité, puis la couleur lumière.
Utilité:
	Retourne la composante couleur à additionner aux autres contributions.
*/
t_color	color_component(t_light light, t_hit record)
{
	t_color	obj;
	t_color	out;
	double	inten;

	obj = record.color;
	inten = light_intensity(light, record);
	out = color_scale(obj, inten);
	out = color_mul(out, light.color);
	return (out);
}

/*
But:
	Teste l'intersection du rayon d'ombre avec la figure pointée par it.
Détails:
	- Sélectionne le bon test selon le champ type
	(1: plan, 2: sphère, 3: cylindre).
Utilité:
	Factoriser la logique pour garder in_shadow concis.
*/
static int	shadow_hit_one(t_list *it, t_ray *shadow)
{
	if (((t_plane *)it->content)->type == 1 && \
hit_plane(shadow, (t_plane *)it->content))
		return (1);
	if (((t_sphere *)it->content)->type == 2 && \
hit_sphere(shadow, (t_sphere *)it->content))
		return (1);
	if (((t_cylinder *)it->content)->type == 3 && \
hit_cylinder(shadow, (t_cylinder *)it->content))
		return (1);
	return (0);
}

/*
But:
	Déterminer si le point est dans l'ombre par rapport à une lumière.
Détails:
	- Génère un rayon d'ombre décalé d'EPSILON le long de la normale.
	- Parcourt les figures et retient la plus proche intersection,
	si elle existe.
	- Retourne 1 si un hit valide est situé entre le point et la lumière.
Utilité:
	Permet de bloquer la contribution diffuse/spéculaire si occulté.
*/
int	in_shadow(t_light light, t_list *figures, t_hit record)
{
	t_ray	shadow;
	t_vec3	eps_n;
	double	dist_l;
	int		hit_any;
	t_list	*it;

	eps_n = vec3_scale(&record.normal, EPSILON);
	shadow.origin = vec3_add(&record.p, &eps_n);
	shadow.direction = vec3_sub(&light.pos, &shadow.origin);
	dist_l = vec3_length(&shadow.direction);
	shadow.direction = vec3_normalize(&shadow.direction);
	shadow.record.object = record.object;
	shadow.record.t = 0.0;
	shadow.record.color = (t_color){0, 0, 0};
	hit_any = 0;
	it = figures;
	while (it)
	{
		if (it->content != record.object && shadow_hit_one(it, &shadow))
			hit_any = 1;
		it = it->next;
	}
	if (!hit_any)
		return (0);
	return (shadow.record.t > EPSILON && shadow.record.t < dist_l - EPSILON);
}
