#include "../../includes/cub3D.h"

void my_mlx_pixel_put_minimap(t_game *game, int x, int y, int color)
{
	if (x >= 0 && x < MINIMAP_WIDTH_IN_PIXELS &&
		y >= 0 && y < MINIMAP_HEIGHT_IN_PIXELS)
	{
		my_mlx_pixel_put(game, x, y, color);
	}
}

// void	my_mlx_pixel_put_minimap(t_game *game, int x, int y, int color)
// {
// 	int		dx;
// 	int		dy;
// 	float	distance_from_center;
// 	int		radius;

// 	// This is the radius of our circular minimap.
// 	radius = MINIMAP_WIDTH_IN_PIXELS / 2;

// 	// Calculate the distance of the pixel (x, y) from the center.
// 	dx = x - MINIMAP_CENTER_X;
// 	dy = y - MINIMAP_CENTER_Y;
	
// 	// We use distance squared to avoid a slow sqrt() call.
// 	// This is a very common optimization.
// 	distance_from_center = (dx * dx) + (dy * dy);

// 	// --- THIS IS THE NEW CIRCLE LOGIC ---
// 	// Only draw the pixel if it's inside the square boundary AND inside the circle.
// 	if (x >= 0 && x < MINIMAP_WIDTH_IN_PIXELS &&
// 		y >= 0 && y < MINIMAP_HEIGHT_IN_PIXELS &&
// 		distance_from_center <= (radius * radius))
// 	{
// 		my_mlx_pixel_put(game, x, y, color);
// 	}
// }