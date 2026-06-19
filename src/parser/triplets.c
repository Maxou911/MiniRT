/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triplets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:34:42 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/14 19:11:58 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../superlibft/includes/superlibft.h"

/*
But:
	Valider qu'il y a exactement 3 éléments et les dupliquer.
Utilité:
	Récupérer a, b, c pour les parseurs vec3/couleur.
*/
int	extract_three(char **parts, char **a, char **b, char **c)
{
	int	ok;

	ok = 0;
	if (parts && parts[0] && parts[1] && parts[2] && parts[3] == NULL)
	{
		*a = ft_strdup(parts[0]);
		*b = ft_strdup(parts[1]);
		*c = ft_strdup(parts[2]);
		if (*a && *b && *c)
			ok = 1;
		if (!ok)
		{
			if (*a)
				free(*a);
			if (*b)
				free(*b);
			if (*c)
				free(*c);
		}
	}
	return (ok);
}

/*
But:
	Extraire 3 chaînes séparées par sep et les écrire dans out->a,b,c.
Utilité:
	Support des formats "x,y,z" et "r,g,b".
*/
int	parse_triplet(const char *s, char sep, t_triplet *out)
{
	char	*copy;
	char	**parts;
	int		ok;

	copy = ft_strdup(s);
	if (!copy)
		return (0);
	replace_sep_to_space(copy, sep);
	parts = ft_split(copy, ' ');
	free(copy);
	if (!parts)
		return (0);
	ok = extract_three(parts, &out->a, &out->b, &out->c);
	free_str_array(parts);
	return (ok);
}

/*
But:
	Parser un vecteur 3D "x,y,z".
Détails:
	- Convertit chaque composante en double, dans un seul tampon v.
Utilité:
	Chargement des positions/directions depuis le fichier.
*/
int	parse_vec3(const char *s, t_vec3 *out)
{
	t_triplet	t;
	double		v;

	if (!parse_triplet(s, ',', &t))
		return (0);
	if (!parse_double(t.a, &v))
		return (free(t.a), free(t.b), free(t.c), 0);
	out->x = v;
	if (!parse_double(t.b, &v))
		return (free(t.a), free(t.b), free(t.c), 0);
	out->y = v;
	if (!parse_double(t.c, &v))
		return (free(t.a), free(t.b), free(t.c), 0);
	out->z = v;
	free(t.a);
	free(t.b);
	free(t.c);
	return (1);
}

/*
But:
	Parser une couleur "r,g,b" (0..255).
Détails:
	- Convertit chaque composante en int via un seul tampon buffer.
Utilité:
	Chargement des couleurs depuis le fichier.
*/
int	parse_color(const char *s, t_color *out)
{
	t_triplet	t;
	int			v;

	if (!parse_triplet(s, ',', &t))
		return (0);
	if (!parse_int(t.a, &v))
		return (free(t.a), free(t.b), free(t.c), 0);
	out->r = v;
	if (!parse_int(t.b, &v))
		return (free(t.a), free(t.b), free(t.c), 0);
	out->g = v;
	if (!parse_int(t.c, &v))
		return (free(t.a), free(t.b), free(t.c), 0);
	out->b = v;
	free(t.a);
	free(t.b);
	free(t.c);
	if (out->r < 0 || out->r > 255 || out->g < 0 || out->g > 255 || \
out->b < 0 || out->b > 255)
		return (0);
	return (1);
}
