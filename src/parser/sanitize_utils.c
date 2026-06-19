/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:50:55 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/12 15:06:13 by ulyssezyber      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../superlibft/includes/superlibft.h"
#include <fcntl.h>

/*
But:
	Vérifier si la chaîne commence par l'UTF-8 BOM (EF BB BF).
Utilité:
	Permet d'ignorer proprement le Byte Order Mark au début des fichiers.
*/
int	has_bom(const unsigned char *s)
{
	if (s[0] == 0xEF && s[1] == 0xBB && s[2] == 0xBF)
		return (1);
	return (0);
}

/*
But:
	Convertir 0xC2 0xA0 (NBSP) en espace ASCII et avancer l'index.
Utilité:
	Uniformiser les espaces non-breakables en simple espace.
*/
int	handle_c2_nbsp(const char *s, int *i, char *out)
{
	unsigned char	b;

	b = (unsigned char)s[*i + 1];
	if (b == 0xA0)
	{
		*out = ' ';
		*i += 1;
		return (1);
	}
	return (0);
}

/*
But:
	Convertir certaines espaces fines/figures (E2 80 xx) en espace ASCII.
Utilité:
	Rendre homogènes plusieurs variantes d'espaces Unicode.
*/
int	handle_e2_space(const char *s, int *i, char *out)
{
	unsigned char	b;
	unsigned char	c3;

	b = (unsigned char)s[*i + 1];
	c3 = (unsigned char)s[*i + 2];
	if ((b == 0x80 && c3 == 0xAF) || (b == 0x80 && c3 >= 0x80 && c3 <= 0x8B))
	{
		*out = ' ';
		*i += 2;
		return (1);
	}
	return (0);
}

/*
But:
	Transformer certains caractères "espaces" (ASCII/UTF-8) en espace ASCII
	et avancer l'index si nécessaire (séquences multi-octets).
Utilité:
	Uniformiser les espaces pour simplifier le parsing.
*/
char	map_char_and_advance(const char *s, int *i)
{
	unsigned char	a;
	char			out;

	a = (unsigned char)s[*i];
	out = s[*i];
	if (out == '\t' || out == '\r' || out == '\v' || out == '\f')
		return (' ');
	if (a == 0xC2 && handle_c2_nbsp(s, i, &out))
		return (out);
	if (a == 0xE2 && handle_e2_space(s, i, &out))
		return (out);
	return (out);
}

/*
But:
	Apposer un caractère ou un espace compacté dans s, en mettant à jour j
	et le flag prev_space.
Utilité:
	Factoriser la logique d'écriture pour sanitize_line.
*/
void	append_char_or_space(char *s, int *j, int *prev_space, char ch)
{
	if (ch == ' ')
	{
		if (!*prev_space)
		{
			s[*j] = ' ';
			(*j)++;
			*prev_space = 1;
		}
	}
	else
	{
		s[*j] = ch;
		(*j)++;
		*prev_space = 0;
	}
}
