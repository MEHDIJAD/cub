/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_pixel_put.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymazini <ymazini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:15:20 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/17 19:20:00 by ymazini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void    my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dest;

    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT){

	// if (x >= 0 && x < MINIMAP_WIDTH_IN_PIXELS &&
		// y >= 0 && y < MINIMAP_HEIGHT_IN_PIXELS)
		// {
			dest = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
			*(unsigned int *)dest = color;
		// }
    }
}

