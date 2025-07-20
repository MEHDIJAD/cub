#include "includes/cub3D.h"

void	minimap(t_game *game)
{
	int player_grid_x;
	int player_grid_y;

	int	start_grid_x;
	int	end_grid_x;

	int	start_grid_y;
	int	end_grid_y;

	int x;
	int y;

	int offset_x;
	int offset_y;

	int offset_pixel_x;
	int offset_pixel_y;

	int screen_x;
	int screen_y;

	player_grid_x = game->player.x / TILE_SIZE;
	player_grid_y = game->player.y / TILE_SIZE;
	//? we can just put 
	// player_grid_x = game->map.map_player_x;
	// player_grid_y = game->map.map_player_y;

	//1- get the gird start end for x, y
	start_grid_x = player_grid_x - MINIMAP_VIEW_RADIUS_IN_TILES;
	if (start_grid_x < 0)
		start_grid_x = 0;
	end_grid_x = player_grid_x + MINIMAP_VIEW_RADIUS_IN_TILES;
	if (end_grid_x > WINDOW_WIDTH)
		end_grid_x = WINDOW_WIDTH;
	
	start_grid_y = player_grid_y - MINIMAP_VIEW_RADIUS_IN_TILES;
	if (start_grid_y < 0)
		start_grid_y = 0;
	end_grid_y = player_grid_y + MINIMAP_VIEW_RADIUS_IN_TILES;
	if (end_grid_y > WINDOW_HEIGHT)
		end_grid_y = WINDOW_HEIGHT;

	y = start_grid_y;
	x = start_grid_y;

	while (y < end_grid_y)
	{
		while (x < end_grid_x)
		{
			// 2- offset
			offset_x = x - player_grid_x;
			offset_y = y - player_grid_y;

			offset_pixel_x = offset_x * MINIMAP_TILE_SIZE;
			offset_pixel_y = offset_y * MINIMAP_TILE_SIZE;

			screen_x = MINIMAP_CENTER_X + offset_pixel_x;
			screen_y = MINIMAP_CENTER_Y + offset_pixel_y;

		if (game->map.grid[y][x] == '1') 
            draw_square(game, screen_x, screen_y, WALL_COLOR);
        else 
        	draw_square(game, screen_x, screen_y, FLOOR_COLOR);

		}
	// draw_player_icon(game, MINIMAP_CENTER_X, MINIMAP_CENTER_Y);
	}
}
