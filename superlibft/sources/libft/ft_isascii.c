/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:36:33 by maalwis           #+#    #+#             */
/*   Updated: 2025/06/23 17:00:20 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/* int	main(int ac, char *av[])
{
	if (ac == 2)
	{
		printf("%d", ft_isalpha(atoi(av[1])));
		printf("%d", isalpha(atoi(av[1])));
	}
} */
