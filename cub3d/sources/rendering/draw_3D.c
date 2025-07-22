/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3D.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:19:07 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/17 11:20:03 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	render_3d(t_game *game, int wall_top_pixel, int wall_bottom_pixel, int i, int color)
{
	int	y;

	y = 0;
	while (y < wall_top_pixel)
		my_mlx_pixel_put(game, i, y++, 0x0087CEEB);
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
		my_mlx_pixel_put(game, i, y++, color);
	y = wall_bottom_pixel;
	while (y < WINDOW_HEIGHT)
		my_mlx_pixel_put(game, i, y++, 0xc29b3e);
}

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

static int	get_wall_color(t_ray *ray)
{
	if (ray->was_hit_vertical)
	{
		if (ray->is_ray_facing_right)
			return (0xFF0000); // West Wall - Red
		else
			return (0x00FF00); // East Wall - Green
	}
	else
	{
		if (ray->is_ray_facing_down)
			return (0x0000FF); // North Wall - Blue
		else
			return (0xFFFF00); // South Wall - Yellow
	}
}

void	render_3d_projaction(t_game *game)
{
	t_3d	t;
	int		i;

	t.dist_to_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV / 2);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		t.corrected_dist = game->rays[i].distance
			* cos(game->rays[i].ray_angle - game->player.rotation_angle);
				
		t.projected_wall_height = (TILE_SIZE / t.corrected_dist) * t.dist_to_proj_plane;
		
		t.wall_top_pixel = (WINDOW_HEIGHT / 2) - (t.projected_wall_height / 2);
		if (t.wall_top_pixel < 0)
			t.wall_top_pixel = 0;
		t.wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (t.projected_wall_height / 2);
		if (t.wall_bottom_pixel > WINDOW_HEIGHT)
			t.wall_bottom_pixel = WINDOW_HEIGHT;
		int wall_color;

		wall_color = get_wall_color(&game->rays[i]);
		render_3d(game, t.wall_top_pixel, t.wall_bottom_pixel, i, wall_color);
		i++;
	}	
}
