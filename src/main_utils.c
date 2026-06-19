/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:56:04 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/24 15:04:32 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parser.h"

/*
But:
	Parser la scène puis vérifier la présence des éléments obligatoires.
Utilité:
	Empêcher le rendu d'une scène invalide.
*/
int	parse_and_validate_scene(const char *path, t_scene *scene)
{
	if (!parse_scene_file(path, scene))
		return (0);
	if (scene->amb.intensity < 0.0)
		return (ft_printf("Error\nAmbient missing\n"), 0);
	if (!scene->cameras)
		return (ft_printf("Error\nCamera missing\n"), 0);
	if (!scene->objs)
		return (ft_printf("Error\nNo objects in scene\n"), 0);
	return (1);
}

/*
But:
	Fermer proprement la fenêtre (hook bouton de fermeture).
Utilité:
	Permettre à l'utilisateur de quitter l'application.
*/
int	close_hook(void *p)
{
	t_app_ctx	*app;

	app = (t_app_ctx *)p;
	if (app)
		free_scene(&app->scene);
	destroy_mlx_all(app);
	exit(0);
	return (0);
}

/*
But:
	Gérer la touche ESC pour quitter l'application.
*/
int	handle_key(int key, void *p)
{
	t_app_ctx	*app;

	if (key == 53 || key == 65307)
	{
		app = (t_app_ctx *)p;
		if (app)
			free_scene(&app->scene);
		destroy_mlx_all(app);
		exit(0);
	}
	return (0);
}

/*
But:
	Vérifier que le fichier d'entrée se termine par ".rt".
*/
int	has_rt_extension(const char *path)
{
	size_t	len;

	if (!path)
		return (0);
	len = ft_strlen(path);
	if (len < 3)
		return (0);
	return (path[len - 3] == '.' && path[len - 2] \
		== 'r' && path[len - 1] == 't');
}

/*
But:
	Initialiser la scène avec des valeurs par défaut sûres.
Utilité:
	Garantir un état cohérent avant parsing.

void	init_scene_defaults(t_scene *scene)
{
	scene->width = 3840;
	scene->height = 2160;
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->objs = NULL;
	scene->amb.intensity = -1.0;
	scene->amb.color = (t_color){0, 0, 0};
}
*/

void	init_scene_defaults(t_scene *scene)
{
	scene->width = 1280;
	scene->height = 720;
	if (scene->width > 3840)
		scene->width = 3840;
	if (scene->height > 2160)
		scene->height = 2160;
	if (scene->width < 384)
		scene->width = 384;
	if (scene->height < 216)
		scene->height = 216;
	scene->cameras = NULL;
	scene->lights = NULL;
	scene->objs = NULL;
	scene->amb.intensity = -1.0;
	scene->amb.color = (t_color){0, 0, 0};
}
