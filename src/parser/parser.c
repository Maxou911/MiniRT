/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:34:15 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 12:04:23 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../superlibft/includes/superlibft.h"
#include <fcntl.h>

/*
** get_identifier
** But:
** 	Pointer vers le premier caractère alphabétique de l'identifiant.
** Utilité:
** 	Tolérer des caractères non alpha avant l'identifiant (espaces, etc).
*/
static char	*get_identifier(char *s)
{
	while (*s && !ft_isalpha((unsigned char)*s))
		s++;
	if (!*s)
		return (NULL);
	return (s);
}

/*
But:
	Router une ligne tokenisée vers le parseur adéquat (A, C, L, sp, pl, cy).
*/
static int	dispatch_line(char **tok, t_scene *scene)
{
	char	*id;

	if (!tok[0] || tok[0][0] == '\0')
		return (1);
	id = get_identifier(tok[0]);
	if (!id)
		return (1);
	if (ft_strncmp(id, "A", 2) == 0)
		return (parse_ambient_tokens(tok, scene));
	if (ft_strncmp(id, "C", 2) == 0)
		return (parse_camera_tokens(tok, scene));
	if (ft_strncmp(id, "L", 2) == 0)
		return (parse_light_tokens(tok, scene));
	if (ft_strncmp(id, "sp", 3) == 0)
		return (parse_sphere_tokens(tok, scene));
	if (ft_strncmp(id, "pl", 3) == 0)
		return (parse_plane_tokens(tok, scene));
	if (ft_strncmp(id, "cy", 3) == 0)
		return (parse_cylinder_tokens(tok, scene));
	return (ft_printf("Error\nUnknown identifier: %s\n", tok[0]), 0);
}

/*
But:
	Libérer tous les tokens et le tableau associé.
Utilité:
	Éviter les fuites mémoire quelles que soient les branches.
*/
static void	free_tokens(char **tok)
{
	int	i;

	i = 0;
	if (!tok)
		return ;
	while (tok[i])
	{
		free(tok[i]);
		i++;
	}
	free(tok);
}

/*
But:
	Nettoyer, tokeniser, compacter puis dispatcher une ligne.
*/
static int	process_line(char *line, t_scene *scene)
{
	char	**tok;
	int		ok;

	sanitize_line(line);
	if (!*line || skip_empty_or_comment(line))
		return (1);
	tok = ft_split(line, ' ');
	if (!tok)
		return (ft_printf("Error\nAlloc split failed\n"), 0);
	ok = compact_tokens(tok);
	if (!ok)
		return (free(tok), 1);
	ok = dispatch_line(tok, scene);
	free_tokens(tok);
	return (ok);
}

/*
But:
	Lire le fichier de scène et parser chaque ligne.
Détails:
	- Nettoie la ligne, split en tokens, route vers le parseur adapté.
Utilité:
	Construire la scène (lumière, caméra, objets) depuis un fichier.
*/
int	parse_scene_file(const char *path, t_scene *scene)
{
	int		fd;
	char	*line;
	int		ok;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\nCannot open scene file\n"), 0);
	line = get_next_line(fd, 0);
	while (line)
	{
		ok = process_line(line, scene);
		if (!ok)
		{
			free(line);
			get_next_line(fd, 1);
			close(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	get_next_line(fd, 1);
	close(fd);
	return (1);
}
