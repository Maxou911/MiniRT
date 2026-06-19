/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 18:47:02 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 12:37:32 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../superlibft/includes/superlibft.h"

/*
But:
	Convertir une chaîne en double avec ft_strtod.
Détails:
	- Vérifie qu'au moins un caractère a été consommé.
Utilité:
	Parser les valeurs flottantes des fichiers de scène.
*/
int	parse_double(const char *s, double *out)
{
	char	*end;
	double	v;

	v = ft_strtod(s, &end);
	if (end == s)
		return (0);
	*out = v;
	return (1);
}

/*
But:
	Convertir une chaîne en int (base 10) avec ft_strtol.
Détails:
	- Vérifie qu'au moins un caractère a été consommé.
Utilité:
	Parser les entiers des fichiers de scène (couleurs, etc.).
*/
int	parse_int(const char *s, int *out)
{
	long	v;
	char	*end;

	v = ft_strtol(s, &end, 10);
	if (end == s)
		return (0);
	*out = (int)v;
	return (1);
}

/*
But:
	Remplacer le séparateur sep par des espaces dans la copie.
Utilité:
	Permettre un split unique sur l'espace.
*/
void	replace_sep_to_space(char *copy, char sep)
{
	int	i;

	i = 0;
	while (copy[i])
	{
		if (copy[i] == sep)
			copy[i] = ' ';
		i++;
	}
}

/*
But:
	Libérer un tableau de chaînes terminé par NULL.
Utilité:
	Nettoyage après ft_split.
*/
void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
