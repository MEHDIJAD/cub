// #include "../../includes/cub3D.h"

// typedef struct s_minimap
// {
// 	int	start_grid_x;
// 	int	end_grid_x;
	
// 	int	start_grid_y;
// 	int	end_grid_y;

// 	int offset_x;
// 	int	offset_y;


// }	t_minimap;

// void	get_dimantion(t_game *game, t_minimap *mini)
// {
// 	int player_grid_x;
// 	int player_grid_y;

// 	player_grid_x = (int)(game->player.x / TILE_SIZE);
// 	player_grid_y = (int)(game->player.y / TILE_SIZE);

// 	mini->start_grid_x = player_grid_x
// 	- MINIMAP_VIEW_RADIUS_IN_TILES;
// 	if (mini->start_grid_x < 0)
// 		mini->start_grid_x = 0;

// 	mini->end_grid_x = player_grid_x 
// 	+ MINIMAP_VIEW_RADIUS_IN_TILES;
// 	if (mini->end_grid_x > game->map.width)
// 		mini->end_grid_x = game->map.width;

// 	mini->start_grid_y = player_grid_y 
// 	- MINIMAP_VIEW_RADIUS_IN_TILES;
// 	if (mini->start_grid_y < 0)
// 		mini->start_grid_y = 0;

// 	mini->end_grid_y = player_grid_y 
// 	+ MINIMAP_VIEW_RADIUS_IN_TILES;
// 	if (mini->end_grid_y > game->map.height)
// 		mini->end_grid_y = game->map.height;

// }

// void	minimap(t_game *game)
// {
// 	t_minimap mini;
// 	int	x;
// 	int	y;

// 	int minigrid_x;
// 	int minigrid_y;

	
// 	get_dimantion(game, &mini);

// 	y = mini.start_grid_y;
// 	while (y < mini.end_grid_y)
// 	{
// 		x = mini.start_grid_x;
// 		while (x < mini.end_grid_x)
// 		{
// 			minigrid_x = x - mini.start_grid_x;
// 			minigrid_y = y - mini.start_grid_y;
// 			if (minigrid_y >= 0 && minigrid_y < 10 && minigrid_x >= 0 && minigrid_x < 10)
// 			{
// 				if (y >= 0 && y < game->map.height
// 					&& x >= 0 && x < game->map.width)
// 				{
// 					game->map.minigrid[minigrid_y][minigrid_x] = game->map.grid[y][x];
// 				}
// 				else
// 					game->map.minigrid[minigrid_y][minigrid_x] = ' ';
// 			}
// 			x++;
// 		}
// 		y++;	
// 	}

// 	int color;
// 	y = 0;
// 	while (y < 10 && game->map.minigrid[y])
// 	{
// 		x = 0;
// 		while (x < 10 && game->map.minigrid[y][x])
// 		{
// 			if (game->map.minigrid[y][x] == '1')
// 				color = 0x37CACEFF;
// 			else if (game->map.minigrid[y][x] == '0')
// 				color = 0xFFFFFFFF;
// 			else if (game->map.minigrid[y][x] == ' ')
// 				color = 0x710000;
// 			int minimap_x = (x * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
// 			int minimap_y = (y * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
// 			draw_square(game, minimap_x, minimap_y, color);
// 			x++;
// 		}
// 		y++;
		
// 	}
		
// }

