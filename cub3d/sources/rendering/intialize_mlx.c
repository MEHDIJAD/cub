/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize_mlx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 09:31:10 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/14 16:23:04 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"


void update_player(t_game *game)
{
    float   move_step;
    float   strafe_step;
    float   new_x;
    float   new_y;
    float   strafe_angle;

	game->player.rotation_angle += game->player.turn_direction * game->player.rotation_speed;
    // Normalize angle to keep it between 0 and 2*PI
    // (This is a good practice to add)
    game->player.rotation_angle = normalize_angle(game->player.rotation_angle);

    // 2. Calculate forward/backward movement
    move_step = game->player.walk_direction * game->player.move_speed;
    float move_x = cos(game->player.rotation_angle) * move_step;
    float move_y = sin(game->player.rotation_angle) * move_step;

    strafe_angle = game->player.rotation_angle + (PI / 2);
    strafe_step = game->player.strafe_direction * game->player.move_speed;
    float strafe_x = cos(strafe_angle) * strafe_step;
    float strafe_y = sin(strafe_angle) * strafe_step;

    // 4. Combine movements to get the final new position
    new_x = game->player.x + move_x + strafe_x;
    new_y = game->player.y + move_y + strafe_y;
    // 5. Perform collision check and update position
    if (!hit_wall(game, new_x, new_y))
    {
        game->player.x = new_x;
        game->player.y = new_y;
    }
}

int key_press_hook(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        ft_exit(game);
    // W and S for forward/backward movement
    if (keycode == KEY_UP)
        game->player.walk_direction = +1;
    if (keycode == KEY_DOWN)
        game->player.walk_direction = -1;
    // A and D for left/right strafing
    if (keycode == KEY_D)
        game->player.strafe_direction = +1;
    if (keycode == KEY_A)
        game->player.strafe_direction = -1;
    // Arrow keys for turning
    if (keycode == KEY_RIGHT)
        game->player.turn_direction = +1; // Right turn is positive
    if (keycode == KEY_LEFT)
        game->player.turn_direction = -1; // Left turn is negative
    return (0);
}

int key_release_hook(int keycode, t_game *game)
{
    if (keycode == KEY_UP || keycode == KEY_DOWN)
        game->player.walk_direction = 0;
    if (keycode == KEY_A || keycode == KEY_D)
        game->player.strafe_direction = 0;
    if (keycode == KEY_RIGHT || keycode == KEY_LEFT)
        game->player.turn_direction = 0;
    return (0);
}

int	game_loop(t_game *game)
{
	update_player(game);
	render(game);
	
	return (0);
}

bool	intialize_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->img.img_ptr = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img_ptr, &game->img.bpp,
		&game->img.line_len, &game->img.endian);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (false);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_hook(game->win, 2, 1L<<0, key_press_hook, game);
    mlx_hook(game->win, 3, 1L<<1, key_release_hook, game);
	mlx_loop(game->mlx);
	return (true);		
}
