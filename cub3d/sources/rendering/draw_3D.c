/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:19:07 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/24 11:01:04 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

// static void	render_3d(t_game *game, int wall_top_pixel, int wall_bottom_pixel, int i, int color)
// {
// 	int	y;

// 	y = 0;
// 	while (y < wall_top_pixel)
// 		my_mlx_pixel_put(game, i, y++, 0x0087CEEB);
// 	y = wall_top_pixel;
// 	while (y < wall_bottom_pixel)
// 		my_mlx_pixel_put(game, i, y++, color);
// 	y = wall_bottom_pixel;
// 	while (y < WINDOW_HEIGHT)
// 		my_mlx_pixel_put(game, i, y++, 0xc29b3e);
// }

/**
  	X  = ? (Projection wall height)
	1- Using Triangle Similarity:
		A/B = D/C
		D = X
		A = actuial wall height = TILE_SIZE
		B = distance to wall = ray distance (from raycasting)
		C = distance from player to proj.plane = (WINDOW_WIDTH / 2) / tan(FOV / 2)
		D = A/B * C   
*/

// static int	get_wall_color(t_ray *ray)
// {
// 	if (ray->was_hit_vertical)
// 	{
// 		if (ray->is_ray_facing_right)
// 			return (0xFF0000); // West Wall - Red
// 		else
// 			return (0x00FF00); // East Wall - Green
// 	}
// 	else
// 	{
// 		if (ray->is_ray_facing_down)
// 			return (0x0000FF); // North Wall - Blue
// 		else
// 			return (0xFFFF00); // South Wall - Yellow
// 	}
// }

// In draw_3D.c

// A helper to get a pointer to the correct texture based on the ray
static t_texture	*get_wall_texture(t_game *game, int i)
{
	t_ray	*ray;

	ray = &game->rays[i];
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_right) // Ray facing right hits a WEST wall
			return (&game->asset_data.textures[2]);
		else // Ray facing left hits an EAST wall
			return (&game->asset_data.textures[3]);
	}
	else
	{
		if (ray->is_ray_facing_down) // Ray facing down hits a NORTH wall
			return (&game->asset_data.textures[0]);
		else // Ray facing up hits a SOUTH wall
			return (&game->asset_data.textures[1]);
	}
}

// This function draws one textured vertical stripe
// static void	draw_wall_stripe(t_game *game, t_3d *t, int i)
// {
// 	t_texture	*tex;
// 	int			tex_x;
// 	int			tex_y;
// 	int			color;
// 	float		y_step;
// 	float		tex_pos;
	
// 	tex = get_wall_texture(game, i);
// 	if (game->rays[i].was_hit_vertical)
// 		tex_x = (int)game->rays[i].wall_hit_y % tex->width;
// 	else
// 		tex_x = (int)game->rays[i].wall_hit_x % tex->width;

// 	y_step = (float)tex->height / t->projected_wall_height;
// 	tex_pos = (t->wall_top_pixel - (WINDOW_HEIGHT / 2)
// 			+ (t->projected_wall_height / 2)) * y_step;
	
// 	for (int y = t->wall_top_pixel; y < t->wall_bottom_pixel; y++)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y >= tex->height)
// 			tex_y = tex->height - 1;
		
// 		color = *(unsigned int *)(tex->addr + (tex_y * tex->line_len
// 					+ tex_x * (tex->bpp / 8)));
// 		my_mlx_pixel_put(game, i, y, color);
// 		tex_pos += y_step;
// 	}
// }

// in draw_3D.c

static void	draw_wall_stripe(t_game *game, t_3d *t, int i)
{
	t_texture	*tex;
	int			tex_x;
	int			tex_y;
	int			color;
	float		y_step;
	float		tex_pos;

	tex = get_wall_texture(game, i);
	
	// --- FIX #1: Calculate tex_x safely ---
	if (game->rays[i].was_hit_vertical)
		tex_x = fmod(game->rays[i].wall_hit_y, TILE_SIZE);
	else
		tex_x = fmod(game->rays[i].wall_hit_x, TILE_SIZE);
	// Scale tex_x to the texture's actual width (if not 64x64)
	tex_x = tex_x * ((float)tex->width / TILE_SIZE);

	// --- FIX #2: Calculate starting tex_pos safely ---
	y_step = (float)tex->height / t->projected_wall_height;
	tex_pos = 0; // Start at the top of the texture
	if (t->projected_wall_height > WINDOW_HEIGHT)
	{
		// If the wall is taller than the screen, we need to find the correct
		// starting position inside the texture.
		tex_pos = ((t->projected_wall_height - WINDOW_HEIGHT) / 2.0) * y_step;
	}

	for (int y = t->wall_top_pixel; y < t->wall_bottom_pixel; y++)
	{
		tex_y = (int)tex_pos;

		// --- FIX #3: Add boundary checks as a final safety net ---
		if (tex_x < 0) tex_x = 0;
		if (tex_x >= tex->width) tex_x = tex->width - 1;
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex->height) tex_y = tex->height - 1;
		
		color = *(unsigned int *)(tex->addr + (tex_y * tex->line_len
					+ tex_x * (tex->bpp / 8)));
		my_mlx_pixel_put(game, i, y, color);
		tex_pos += y_step;
	}
}

// void	render_3d_projaction(t_game *game)
// {
// 	t_3d	t;
// 	int		i;

// 	t.dist_to_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
// 	i = 0;
// 	while (i < WINDOW_WIDTH)
// 	{
// 		t.corrected_dist = game->rays[i].distance
// 			* cos(game->rays[i].ray_angle - game->player.rotation_angle);
				
// 		t.projected_wall_height = (TILE_SIZE / t.corrected_dist) * t.dist_to_proj_plane;
		
// 		t.wall_top_pixel = (WINDOW_HEIGHT / 2) - (t.projected_wall_height / 2);
// 		if (t.wall_top_pixel < 0)
// 			t.wall_top_pixel = 0;
// 		t.wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (t.projected_wall_height / 2);
// 		if (t.wall_bottom_pixel > WINDOW_HEIGHT)
// 			t.wall_bottom_pixel = WINDOW_HEIGHT;
// 		int wall_color;

// 		wall_color = get_wall_color(&game->rays[i]);
// 		render_3d(game, t.wall_top_pixel, t.wall_bottom_pixel, i, wall_color);
// 		i++;
// 	}	
// }

// in draw_3D.c

void	render_3d_projaction(t_game *game)
{
	t_3d	t;
	int		i;

	t.dist_to_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		// This part is the same
		t.corrected_dist = game->rays[i].distance
			* cos(game->rays[i].ray_angle - game->player.rotation_angle);
		t.projected_wall_height = (TILE_SIZE / t.corrected_dist)
			* t.dist_to_proj_plane;
		t.wall_top_pixel = (WINDOW_HEIGHT / 2)
			- (t.projected_wall_height / 2);
		if (t.wall_top_pixel < 0)
			t.wall_top_pixel = 0;
		t.wall_bottom_pixel = (WINDOW_HEIGHT / 2)
			+ (t.projected_wall_height / 2);
		if (t.wall_bottom_pixel > WINDOW_HEIGHT)
			t.wall_bottom_pixel = WINDOW_HEIGHT;

		// --- NEW DRAWING LOGIC ---
		// 1. Draw Ceiling
		for (int y = 0; y < t.wall_top_pixel; y++)
			my_mlx_pixel_put(game, i, y, 0x0087CEEB); // Or your ceiling color

		// 2. Draw Textured Wall
		draw_wall_stripe(game, &t, i);

		// 3. Draw Floor
		for (int y = t.wall_bottom_pixel; y < WINDOW_HEIGHT; y++)
			my_mlx_pixel_put(game, i, y, 0xc29b3e); // Or your floor color
		i++;
	}
}

