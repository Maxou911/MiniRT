/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:15:11 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 13:15:49 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "raytracing.h"

typedef struct s_triplet
{
	char	*a;
	char	*b;
	char	*c;
}	t_triplet;

int		parse_scene_file(const char *path, t_scene *scene);

// Helpers
int		parse_vec3(const char *s, t_vec3 *out);
int		parse_color(const char *s, t_color *out);
int		parse_double(const char *s, double *out);
int		parse_int(const char *s, int *out);
int		parse_ambient_tokens(char **tok, t_scene *scene);
int		parse_camera_tokens(char **tok, t_scene *scene);
int		parse_light_tokens(char **tok, t_scene *scene);
int		parse_sphere_tokens(char **tok, t_scene *scene);
int		parse_plane_tokens(char **tok, t_scene *scene);
int		parse_cylinder_tokens(char **tok, t_scene *scene);

// Parser utils
int		has_bom(const unsigned char *s);
int		handle_c2_nbsp(const char *s, int *i, char *out);
int		handle_e2_space(const char *s, int *i, char *out);
char	map_char_and_advance(const char *s, int *i);
void	append_char_or_space(char *s, int *j, int *prev_space, char ch);
void	sanitize_line(char *s);
int		skip_empty_or_comment(char *line);
int		compact_tokens(char **tok);

int		ft_isspace_local(char c);
long	ft_strtol(const char *nptr, char **endptr, int base);
double	ft_strtod(const char *nptr, char **endptr);

int		extract_three(char **parts, char **a, char **b, char **c);
int		parse_triplet(const char *s, char sep, t_triplet *out);

int		parse_double(const char *s, double *out);
int		parse_int(const char *s, int *out);
void	replace_sep_to_space(char *copy, char sep);
void	free_str_array(char **arr);

#endif
