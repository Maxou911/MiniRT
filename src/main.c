/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:19:45 by maalwis           #+#    #+#             */
/*   Updated: 2025/11/14 20:40:27 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parser.h"
#include "render.h"
#include "camera.h"

/*
But:
	Créer le contexte MLX et la fenêtre d'affichage.
Utilité:
	Préparer la cible d'affichage avant le rendu.
*/
static void	init_mlx_and_window(t_scene *scene, void **mlx, void **win)
{
	*mlx = mlx_init();
	*win = mlx_new_window(*mlx, scene->width, scene->height, "miniRT");
}

/*
But:
	Créer l'image MLX et récupérer son buffer.
Utilité:
	Permettre l'écriture directe des pixels.
*/
static void	init_image(void *mlx, t_scene *scene, void **img, t_image *image)
{
	*img = mlx_new_image(mlx, scene->width, scene->height);
	image->img = *img;
	image->data = mlx_get_data_addr(*img, &image->bpp, \
&image->size_line, &image->endian);
}

/*
But:
	Réaliser le rendu pixel par pixel (boucles y/x).
Utilité:
	Découpler la boucle de rendu du reste de l'initialisation.
*/
static void	render_pixels(t_scene *scene, t_image *image)
{
	int		y;
	int		x;
	double	u;
	double	v;
	t_ray	ray;

	y = 0;
	while (y < scene->height)
	{
		x = 0;
		while (x < scene->width)
		{
			u = (double)x / (double)scene->width;
			v = (double)(scene->height - 1 - y) / (double)scene->height;
			camera_generate_ray((t_camera *)scene->cameras->content, \
u, v, &ray);
			put_pixel(image, x, y, raytrace(&ray, scene));
			x++;
		}
		y++;
	}
}

/*
But:
	Charger et préparer l’application pour un rendu unique.
Étapes:
	1) Initialiser la scène avec des valeurs sûres.
	2) Parser et valider le fichier .rt (retour 0 si invalide).
	3) Créer le contexte MLX et la fenêtre.
	4) Allouer l’image, récupérer son buffer et lancer le rendu CPU.
	5) Afficher l’image rendue dans la fenêtre.
*/
static int	bootstrap(const char *path, t_app_ctx *app, t_image *image)
{
	int	ok;

	ok = 0;
	init_scene_defaults(&app->scene);
	if (!parse_and_validate_scene(path, &app->scene))
	{
		free_scene(&app->scene);
		return (0);
	}
	init_mlx_and_window(&app->scene, &app->mlx, &app->win);
	init_image(app->mlx, &app->scene, &app->img, image);
	render_pixels(&app->scene, image);
	mlx_put_image_to_window(app->mlx, app->win, app->img, 0, 0);
	ok = 1;
	return (ok);
}

/*
But:
	Point d’entrée du programme.
Étapes:
	1) Vérifier les arguments (exiger un fichier scène).
	2) Vérifier l’extension du fichier (.rt).
	3) Déléguer l’initialisation et le rendu à `bootstrap`.
	4) Installer les hooks (fermeture fenêtre et touches) avec le
	   contexte, puis entrer dans la boucle MLX.
*/
int	main(int argc, char **argv)
{
	t_app_ctx	app;
	t_image		image;
	int			ok;

	if (argc != 2)
		return (ft_printf("Error\nUsage: %s <scene.rt>\n", argv[0]), 1);
	if (!has_rt_extension(argv[1]))
		return (ft_printf("Error\nFile must end with .rt\n"), 1);
	ok = bootstrap(argv[1], &app, &image);
	if (!ok)
		return (1);
	mlx_hook_destroy_compat(app.win, 0, close_hook, &app);
	mlx_key_hook_compat(app.win, handle_key, &app);
	mlx_loop(app.mlx);
	return (0);
}
