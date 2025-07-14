/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-garo <eel-garo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 16:12:23 by eel-garo          #+#    #+#             */
/*   Updated: 2025/07/14 16:16:11 by eel-garo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

float	normalize_angle(float angle)
{
	// fmod is the floating-point version of the modulo operator (%)
	angle = fmod(angle, 2 * PI);
	// mode(%) will set it to 360 if it pass 360 if not it wil keep it one it angle
	if (angle < 0)
	{
		angle = angle + (2 * PI);
		// add 360 to correct it (exp: -10 --> -10 + 360 = 350)
	}
	return (angle);
}
