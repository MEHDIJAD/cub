/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:42:51 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/24 11:01:47 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void draw_square(t_game *game, int x, int y, int color)
{
	int i = 0;
	int j;
	int	minimap_tile_size;

	minimap_tile_size = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	while (i < minimap_tile_size - 1)
	{
		j = 0;
		while (j < minimap_tile_size - 1)
		{
			my_mlx_pixel_put_minimap(game, x + j, y + i, color);
			j++;
		}
		i++;
	}	
}

void	draw_map(t_game *game)
{
	int	x,y;
	int minimap_x, minimap_y;
	int color;
	
	y = 0;
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (x < game->map.width && game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				color = 0x37CACEFF;
			else if (game->map.grid[y][x] == '0')
				color = 0xFFFFFFFF;
			else if (game->map.grid[y][x] == ' ')
				color = 0x710000;
			minimap_x = (x * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
			minimap_y = (y * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
			draw_square(game, minimap_x, minimap_y, color);

			x++;
		}
		y++;	
	}
}



// void draw_player(t_game *game)
// {
// 	int y = -1;
// 	int x;
// 	int	player_minimap_x;
// 	int	player_minimap_y;

// 	int player_screen_x;
// 	int player_screen_y;

// 	player_minimap_x = game->player.x * MINIMAP_SCALE_FACTOR;
// 	player_minimap_y = game->player.y * MINIMAP_SCALE_FACTOR;
// 	while (y < 1)
// 	{
// 		x = -1;
// 		while (x < 1)
// 		{
// 			my_mlx_pixel_put(game, player_minimap_x + x, player_minimap_y + y, 0xFF0000);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void draw_minimap_rays(t_game *game)
// {
//     int i = 0;
//     while (i < WINDOW_WIDTH)
//     {
//         draw_line(
//             game,
//             game->player.x * MINIMAP_SCALE_FACTOR,
//             game->player.y * MINIMAP_SCALE_FACTOR,
//             game->rays[i].wall_hit_x * MINIMAP_SCALE_FACTOR,
//             game->rays[i].wall_hit_y * MINIMAP_SCALE_FACTOR
//         );
//         i++;
//     }
// }

void	render_minimap(t_game *game)
{
	int		mx;
	int		my;
	float	scale;

	scale = (MINIMAP_VIEW_RADIUS_IN_TILES * 2.0 * TILE_SIZE)
		/ (float)MINIMAP_WIDTH_IN_PIXELS;

	my = 0;
	while (my < MINIMAP_HEIGHT_IN_PIXELS)
	{
		mx = 0;
		while (mx < MINIMAP_WIDTH_IN_PIXELS)
		{
			float world_x = game->player.x + ((mx - MINIMAP_CENTER_X) * scale);
			float world_y = game->player.y + ((my - MINIMAP_CENTER_Y) * scale);
			int grid_x = (int)(world_x / TILE_SIZE);
			int grid_y = (int)(world_y / TILE_SIZE);
			if (fmod(world_x, TILE_SIZE) < scale || fmod(world_y, TILE_SIZE) < scale)
			{
				my_mlx_pixel_put_minimap(game, mx, my, 0x000000); // Black for grid lines
			}
			else if (grid_y >= 0 && grid_y < game->map.height && grid_x >= 0
				&& grid_x < game->map.width && game->map.grid[grid_y][grid_x] != ' ')
			{
				if (game->map.grid[grid_y][grid_x] == '1')
					my_mlx_pixel_put_minimap(game, mx, my, 0x37CACEFF); // Wall
				else
					my_mlx_pixel_put_minimap(game, mx, my, 0xFFFFFFFF); // Floor
			}
			else
				my_mlx_pixel_put_minimap(game, mx, my, 0x000000); // Void
			mx++;
		}
		my++;
	}
	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			my_mlx_pixel_put_minimap(game, MINIMAP_CENTER_X + x,
				MINIMAP_CENTER_Y + y, 0xFF0000); // Red dot
		}
	}
}

void	ft_render(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	update_player(game);
	cast_rays(game);
	render_3d_projaction(game);
	// draw_map(game);
	// minimap(game);
	// draw_player(game);
	// draw_minimap_rays(game);
	render_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}
