/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strto_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uzyberaj <uzyberaj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 12:22:34 by ulyssezyber       #+#    #+#             */
/*   Updated: 2025/11/14 19:11:45 by uzyberaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../superlibft/includes/superlibft.h"

int	ft_isspace_local(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || \
c == '\v' || c == '\f')
		return (1);
	return (0);
}

/*
But:
	Version locale de strtol en base 10.
Détails:
	- Ignore espaces initiaux, gère signe, lit chiffres décimaux.
	- Écrit endptr au dernier caractère lu.
*/
long	ft_strtol(const char *nptr, char **endptr, int base)
{
	int		i;
	int		sign;
	long	val;

	i = 0;
	sign = 1;
	val = 0;
	(void)base;
	while (ft_isspace_local(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		val = val * 10 + (nptr[i] - '0');
		i++;
	}
	if (endptr)
		*endptr = (char *)(nptr + i);
	return (val * sign);
}

/*
But:
	Avancer i sur espaces et récupérer le signe.
*/
static void	ft_strtod_skip(const char *nptr, int *i, int *sign)
{
	*sign = 1;
	while (ft_isspace_local(nptr[*i]))
		(*i)++;
	if (nptr[*i] == '+' || nptr[*i] == '-')
	{
		if (nptr[*i] == '-')
			*sign = -1;
		(*i)++;
	}
}

/*
But:
	Accumuler la partie fractionnaire si présente.
*/
static void	ft_strtod_frac(const char *nptr, int *i, double *val)
{
	double	div;

	div = 1.0;
	if (nptr[*i] == '.')
	{
		(*i)++;
		while (nptr[*i] >= '0' && nptr[*i] <= '9')
		{
			div = div * 10.0;
			*val = *val + (double)(nptr[*i] - '0') / div;
			(*i)++;
		}
	}
}

/*
But:
	Version locale de strtod (sans exposant).
*/
double	ft_strtod(const char *nptr, char **endptr)
{
	int		i;
	int		sign;
	double	val;

	i = 0;
	val = 0.0;
	ft_strtod_skip(nptr, &i, &sign);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		val = val * 10.0 + (double)(nptr[i] - '0');
		i++;
	}
	ft_strtod_frac(nptr, &i, &val);
	if (endptr)
		*endptr = (char *)(nptr + i);
	return (val * (double)sign);
}
