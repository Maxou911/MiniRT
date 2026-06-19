/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_compat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalwis <maalwis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:06:20 by uzyberaj          #+#    #+#             */
/*   Updated: 2026/06/19 14:01:08 by maalwis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifdef __GNUC__
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wcast-function-type"
# pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#endif

int	mlx_key_hook_compat(void *win_ptr,
		int (*funct_ptr)(int, void *), void *param)
{
	return (mlx_key_hook(win_ptr, funct_ptr, param));
}

int	mlx_hook_destroy_compat(void *win_ptr, int mask,
		int (*funct_ptr)(void *), void *param)
{
	return (mlx_hook(win_ptr, 17, mask, funct_ptr, param));
}

#ifdef __GNUC__
# pragma GCC diagnostic pop
#endif