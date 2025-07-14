/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_wall.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:15:29 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/14 16:15:51 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	hit_wall(t_game *game, float x, float y)
{
	int map_x;
	int map_y;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT){
		return (true);
	}
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x < 0 || map_x >= game->map.width
		|| map_y < 0 || map_y >= game->map.height){
		return (true);
	}
	return (game->map.grid[map_y][map_x] == '1');

}