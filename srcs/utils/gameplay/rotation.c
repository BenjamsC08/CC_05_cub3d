/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 06:44:18 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/12 05:03:50 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	apply_mouse_rotate(t_game *game)
{
	int		x;
	int		y;
	int		delta_x;
	float	step;

	if (game->lock_mouse)
	{
		mlx_mouse_get_pos(game->mlx, game->win, &x, &y);
		delta_x = x - (W_WIDTH / 2);
		if (x > W_WIDTH)
			delta_x = 1;
		if (delta_x != 0)
		{
			step = DEGREE * (SENSI * MOUSE_SENSI_SCALE);
			game->player->angle += (float)delta_x * step;
			if (game->player->angle >= 2.0f * PI)
				game->player->angle -= 2.0f * PI;
			if (game->player->angle < 0.0f)
				game->player->angle += 2.0f * PI;
			mlx_mouse_move(game->mlx, game->win, (W_WIDTH / 2), (W_HEIGHT / 2));
		}
	}
}

/**
 * @brief  Apply player rotation based on input keys.
 *
 * Adjusts the player’s facing angle according to rotation inputs (left/right).
 * Rotation speed is scaled by SENSI (sensitivity). The angle is then wrapped
 * to remain within the range [0, 2π).
 *
 * @param  game  Global game context containing player state and input flags.
 * @return None.
 *
 * @note   Angle is stored in radians; DEGREE is expected to be π/180.
 * @warning Excessive sensitivity may cause large, abrupt rotations.
 * @pre    game->player must be initialized and accessible.
 * @post   game->player->angle is updated and normalized.
 */
void	apply_rotate(t_game *game)
{
	if (game->player->rot_left == TRUE)
		game->player->angle -= DEGREE * SENSI;
	if (game->player->rot_right == TRUE)
		game->player->angle += DEGREE * SENSI;
	if (game->player->angle > 2.0f * PI)
		game->player->angle -= 2.0f * PI;
	if (game->player->angle < 0.0f)
		game->player->angle += 2.0f * PI;
}
