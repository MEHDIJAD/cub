/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:42:51 by ymazini           #+#    #+#             */
/*   Updated: 2025/07/14 16:14:52 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char *dest;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dest = game->img.addr + (y * game->img.line_len + x * (game->img.bpp / 8));
		*(unsigned int *)dest = color;
	}
} 

float distance(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void draw_line(t_game *game, float x1, float y1, float x2, float y2)
{
    float   dx = x2 - x1;
    float   dy = y2 - y1;
    int     steps;
    float   x_inc, y_inc;
    float   x, y;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);
	 if (steps == 0)
	{
        my_mlx_pixel_put(game, round(x1), round(y1), 0x00FF0000);
        return;
    }

    x_inc = dx / (float)steps;
    y_inc = dy / (float)steps;

    x = x1;
    y = y1;
    for (int i = 0; i <= steps; i++)
    {
        if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
        	my_mlx_pixel_put(game, round(x), round(y), 0x00FF0000);
		x += x_inc;
		y += y_inc;
    }
}


void draw_minimap_tile(t_game *game, int map_x, int map_y, int color)
{
	int i = 0;
	int j;
    int screen_x = map_x * MINIMAP_TILE_SIZE;
    int screen_y = map_y * MINIMAP_TILE_SIZE;

	while (i < MINIMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_TILE_SIZE)
		{
			my_mlx_pixel_put(game, screen_x + j, screen_y + i, color);
			j++;
		}
		i++;
	}	
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	
	while (y < game->map.height && game->map.grid[y])
	{
		x = 0;
		while (x < game->map.width && game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1'){
				draw_minimap_tile(game, x , y, 0x006272A4);
			}
			else{
				draw_minimap_tile(game, x, y, 0xFFFFFFFF);
			}
			x++;
		}
		y++;	
	}
}

void draw_miniplayer(t_game *game)
{
	int i;
	int j;
    int player_pixel_x;
    int player_pixel_y;
    int player_dot_size = 2;

    player_pixel_x = (int)(game->map.map_player_x * MINIMAP_TILE_SIZE);
    player_pixel_y = (int)(game->map.map_player_y * MINIMAP_TILE_SIZE);

    i = -player_dot_size / 2;
	while (i < player_dot_size / 2)
	{
		j = -player_dot_size / 2;
		while (j < player_dot_size / 2)
		{
			my_mlx_pixel_put(game, player_pixel_x + j, player_pixel_y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}



void	initdir(t_game *game, float ray_angle)
{
	game->ray.is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	game->ray.is_ray_facing_up = !game->ray.is_ray_facing_down;
	game->ray.is_ray_facing_left = ray_angle > PI / 2 && ray_angle < 1.5 * PI;
	game->ray.is_ray_facing_right = !game->ray.is_ray_facing_left;
}

bool	find_nexthorz_hit(t_game *game, float x_intecept, float y_intecept,
	float x_step, float y_step)
{
	float	next_x;
	float	next_y;
	float y_to_check;
	
	next_x = x_intecept;
	next_y = y_intecept;
	while (next_x >= 0 && next_x <= WINDOW_WIDTH && next_y >= 0 && next_y <= WINDOW_HEIGHT)
	{
		y_to_check = next_y;
		if (game->ray.is_ray_facing_up)
			y_to_check -= 1;
		if (hit_wall(game, next_x, y_to_check))
		{
			game->ray.horz_wallhitx = next_x;
			game->ray.horz_wallhity = next_y;
			return (true);
		}
		next_x += x_step;
		next_y += y_step;
	}
	return (false);
}
bool	find_horizontal_intersection(t_game *game, float ray_angle)
{
	float	y_intecept;
	float	x_intecept;
	float	x_step;
	float	y_step;
	float	player_pixel_x;
	float	player_pixel_y;
	
	player_pixel_x = game->player.x * TILE_SIZE;
	player_pixel_y = game->player.y * TILE_SIZE;
	initdir(game, ray_angle);
	y_intecept = floor(player_pixel_y / TILE_SIZE) * TILE_SIZE;
	if (game->ray.is_ray_facing_down)
		y_intecept += TILE_SIZE;
	x_intecept = player_pixel_x + (y_intecept - player_pixel_y) / tan(ray_angle);
	y_step = TILE_SIZE;
	if (game->ray.is_ray_facing_up)
		y_step *= -1;
	x_step = TILE_SIZE / tan(ray_angle);
	if (game->ray.is_ray_facing_left && x_step > 0)
		x_step *= -1;
	if (game->ray.is_ray_facing_right && x_step < 0)
		x_step *= -1;
	return (find_nexthorz_hit(game, x_intecept, y_intecept, x_step, y_step));
}

bool	find_nextvert_hit(t_game *game, float x_intecept, float y_intecept,
	float x_step, float y_step)
{
	float	next_x;
	float	next_y;
	float	x_to_check;
	
	next_x = x_intecept;
	next_y = y_intecept;
	while (next_x >= 0 && next_x <= WINDOW_WIDTH && next_y >= 0 && next_y <= WINDOW_HEIGHT)
	{
		x_to_check = next_x;
        if (game->ray.is_ray_facing_left)
            x_to_check -= 1;
		if (hit_wall(game, x_to_check, next_y))
		{
			game->ray.vert_wallhitx = next_x;
			game->ray.vert_wallhity = next_y;
			return (true);
		}
		next_x += x_step;
		next_y += y_step;
	}
	return (false);
}

bool	find_vertical_intersection(t_game *game, float ray_angle)
{
	float	y_intecept;
	float	x_intecept;
	float	x_step;
	float	y_step;
	float	player_pixel_x;
	float	player_pixel_y;
	
	player_pixel_x = game->player.x * TILE_SIZE;
	player_pixel_y = game->player.y * TILE_SIZE;
	initdir(game, ray_angle);
	x_intecept = floor(player_pixel_x / TILE_SIZE) * TILE_SIZE;
	if (game->ray.is_ray_facing_right)
		x_intecept += TILE_SIZE;
	y_intecept = player_pixel_y + (x_intecept - player_pixel_x) * tan(ray_angle);
	x_step = TILE_SIZE;
	if (game->ray.is_ray_facing_left)
		x_step *= -1;
	y_step = TILE_SIZE * tan(ray_angle);
	if (game->ray.is_ray_facing_up && y_step > 0)
		y_step *= -1;
	if (game->ray.is_ray_facing_down && y_step < 0)
		y_step *= -1;
	return (find_nextvert_hit(game, x_intecept, y_intecept, x_step, y_step));
}

void	cast_one_ray(t_game *game, float ray_angle)
{

	float horz_hit_distance;
	float vert_hit_distance;
	float player_pixel_x = game->player.x * TILE_SIZE;
    float player_pixel_y = game->player.y * TILE_SIZE;
	
	ray_angle = normalize_angle(ray_angle);

	horz_hit_distance = 1e30;
	vert_hit_distance = 1e30;
	
	if (find_horizontal_intersection(game, ray_angle))
	{
		horz_hit_distance = distance(player_pixel_x, player_pixel_y,
			game->ray.horz_wallhitx, game->ray.horz_wallhity);	
	}
	if (find_vertical_intersection(game, ray_angle))
	{
		vert_hit_distance = distance(player_pixel_x, player_pixel_y,
			game->ray.vert_wallhitx, game->ray.horz_wallhity);
	}
	if (vert_hit_distance < horz_hit_distance)
	{
		game->ray.distance = vert_hit_distance;
		game->ray.wall_hit_x = game->ray.vert_wallhitx;
		game->ray.wall_hit_y = game->ray.vert_wallhity;
	}
	else
	{
		game->ray.distance = horz_hit_distance;
		game->ray.wall_hit_x = game->ray.horz_wallhitx;
		game->ray.wall_hit_y = game->ray.horz_wallhity;
	}
	draw_line(
        game,
        game->player.x * MINIMAP_TILE_SIZE,
        game->player.y * MINIMAP_TILE_SIZE,
        game->ray.wall_hit_x / TILE_SIZE * MINIMAP_TILE_SIZE,
        game->ray.wall_hit_y / TILE_SIZE * MINIMAP_TILE_SIZE);
}



void	cast_rays(t_game *game)
{
	float	ray_angle;
	int		num_rays;
	int		i;

	ray_angle = game->player.rotation_angle - (FOV_ANGLE /2);
	num_rays = WINDOW_WIDTH;
	i = 0;
	while (i < num_rays)
	{
		cast_one_ray(game, ray_angle);
		ray_angle += FOV_ANGLE / num_rays;
		i++;
	}
}

void	render(t_game *game)
{
	draw_minimap(game);
	draw_miniplayer(game);
	cast_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img_ptr, 0, 0);
}