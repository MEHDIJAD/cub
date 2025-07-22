#include "../../includes/cub3D.h"

void my_mlx_pixel_put_minimap(t_game *game, int x, int y, int color)
{
	// --- THIS IS THE CLIPPING LOGIC ---
	// Only draw the pixel if it's inside the minimap's square area.
	if (x >= 0 && x < MINIMAP_WIDTH_IN_PIXELS &&
		y >= 0 && y < MINIMAP_HEIGHT_IN_PIXELS)
	{
		// If it's safe, call the original function to draw it.
		my_mlx_pixel_put(game, x, y, color);
	}
}