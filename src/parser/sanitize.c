/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:58:30 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 12:01:39 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../superlibft/includes/superlibft.h"
#include <fcntl.h>

/*
But:
	Normaliser une ligne:
	- convertir divers espaces en ' '
	- supprimer les commentaires '#' inline
	- retirer espaces en tête/fin et compacter multiples espaces
Utilité:
	Faciliter le découpage en tokens.
*/
void	sanitize_line(char *s)
{
	int				i;
	int				j;
	int				prev_space;
	char			ch;
	int				has;

	if (!s)
		return ;
	i = 0;
	j = 0;
	prev_space = 1;
	has = has_bom((const unsigned char *)s);
	if (has)
		i = 3;
	while (s[i])
	{
		if (s[i] == '#')
			break ;
		ch = map_char_and_advance(s, &i);
		append_char_or_space(s, &j, &prev_space, ch);
		++i;
	}
	if (j > 0 && s[j - 1] == ' ')
		--j;
	s[j] = '\0';
}

/*
But:
	Indiquer si la ligne est vide ou commence par un commentaire.
Utilité:
	Permettre au parser d'ignorer proprement ces lignes.
*/
int	skip_empty_or_comment(char *line)
{
	if (!line || !*line)
		return (1);
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '#')
		return (1);
	return (0);
}

/*
But:
	Retirer les tokens vides du split et compacter le tableau en place.
Utilité:
	Nettoyer les tokens avant dispatch.
*/
int	compact_tokens(char **tok)
{
	int	r;
	int	w;

	r = 0;
	w = 0;
	while (tok[r])
	{
		if (tok[r][0] != '\0')
			tok[w++] = tok[r];
		else
			free(tok[r]);
		r++;
	}
	tok[w] = NULL;
	return (w != 0);
}
