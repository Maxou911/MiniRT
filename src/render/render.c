/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:50:50 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/19 16:34:14 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include "../../include/render.h"

/*
But:
	Teste si un rayon intersecte au moins un objet de la scène.
Détails:
	- Parcourt la liste des objets et appelle le test adéquat selon le type.
	- Retourne 1 si une intersection est trouvée, sinon 0.
Utilité:
	Accélérer le lancer de rayon en évitant des calculs inutiles
	si rien n'est touché.
*/
static int	intersect_any(t_ray *ray, t_list *objs)
{
	int		hit;
	t_list	*it;
	void	*obj;

	hit = 0;
	it = objs;
	while (it)
	{
		obj = it->content;
		if (((t_plane *)obj)->type == 1)
			hit |= hit_plane(ray, (t_plane *)obj);
		else if (((t_sphere *)obj)->type == 2)
			hit |= hit_sphere(ray, (t_sphere *)obj);
		else if (((t_cylinder *)obj)->type == 3)
			hit |= hit_cylinder(ray, (t_cylinder *)obj);
		it = it->next;
	}
	return (hit);
}

/*
But:
	Calculer la couleur accumulée (ambiante + lumières visibles) pour un rayon.
Détails:
	- Retourne noir si aucune intersection.
	- Multiplie la couleur d'objet par l'ambiante, puis ajoute chaque lumière.
Utilité:
	Séparer l'accumulation d'éclairage du reste du pipeline.
*/
static t_color	accumulate_lighting(t_ray *ray, t_scene *scene)
{
	t_color	color;
	t_list	*it;
	t_light	*l;
	t_color	amb_scaled;

	color = (t_color){0, 0, 0};
	if (!intersect_any(ray, scene->objs))
		return (color);
	amb_scaled = color_scale(scene->amb.color, scene->amb.intensity);
	color = color_mul(ray->record.color, amb_scaled);
	it = scene->lights;
	while (it)
	{
		l = (t_light *)it->content;
		if (!in_shadow(*l, scene->objs, ray->record))
			color = color_add(color, color_component(*l, ray->record));
		it = it->next;
	}
	return (color);
}

/*
But:
	Borner les composantes couleur entre 0 et 255.
Utilité:
	Assurer des couleurs valides avant affichage.
*/
static void	clamp_color(t_color *color)
{
	if (color->r < 0)
		color->r = 0;
	if (color->r > 255)
		color->r = 255;
	if (color->g < 0)
		color->g = 0;
	if (color->g > 255)
		color->g = 255;
	if (color->b < 0)
		color->b = 0;
	if (color->b > 255)
		color->b = 255;
}

/*
But:
	Calculer la couleur résultante pour un rayon primaire (orchestration).
Utilité:
	Point d'entrée pour la couleur d'un pixel.
*/
t_color	raytrace(t_ray *ray, t_scene *scene)
{
	t_color	color;

	color = accumulate_lighting(ray, scene);
	clamp_color(&color);
	return (color);
}

/*
But:
	Écrire un pixel dans le buffer d'image au format attendu par MLX.
Détails:
	- Calcule l'offset mémoire selon bpp et size_line.
	- Écrit la couleur au format 0x00RRGGBB quand bpp >= 32.
Utilité:
	Afficher le résultat du raytracer à l’écran.
*/
void	put_pixel(t_image *img, int x, int y, t_color c)
{
	char			*dst;
	int				offset;
	int				bpp;
	unsigned int	*p;

	bpp = img->bpp / 8;
	offset = y * img->size_line + x * bpp;
	dst = img->data + offset;
	if (bpp >= 4)
	{
		p = (unsigned int *)dst;
		*p = ((unsigned int)c.r << 16) | ((unsigned int)c.g << 8) \
		| (unsigned int)c.b;
	}
}
