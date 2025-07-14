/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize_ray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 13:06:27 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/14 15:11:40 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

bool	intialize_ray(t_game *game)
{
	game->player.rotation_angle = 0;
    game->player.turn_direction = 0;
    game->player.walk_direction = 0;
	game->player.strafe_direction = 0;
    game->player.move_speed = 0.4;
    game->player.rotation_speed = 0.2 * (PI / 180);
	return (true);
}