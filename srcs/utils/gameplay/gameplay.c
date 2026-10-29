/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 05:29:11 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/12 07:31:38 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	back_to_home(t_game *game)
{
	game->data_desc->score_checked = FALSE;
	game->data_desc->prev_best_time = game->data_desc->last_best_time;
	game->player->angle = game->player->backup_angle;
	game->player->x = (game->data_desc->player_x * BLOCK) + (BLOCK / 2);
	game->player->y = (game->data_desc->player_y * BLOCK) + (BLOCK / 2);
}

/**
 * @brief  Set the player’s facing angle from numeric keypad input.
 *
 * Updates the player’s orientation depending on the keycode received:
 * - PAD_2 → face downward (π/2).
 * - PAD_4 → face left (π).
 * - PAD_8 → face upward (-π/2).
 * - PAD_6 → face right (0).
 *
 * @param  game     Global game context containing the player state.
 * @param  keycode  Key symbol from input (expected: PAD_2, PAD_4, PAD_8, PAD_6).
 * @return None.
 *
 * @note   Angles are expressed in radians, consistent with trigonometric funcs.
 * @warning Do nothing if keycode is not one of the expected keypad values.
 * @pre    game->player must be valid and accessible.
 * @post   Player’s angle reflects the chosen cardinal orientation.
 */
void	set_angle(t_game *game, int keycode)
{
	if (keycode == PAD_2)
		game->player->angle = 0.5f * PI;
	else if (keycode == PAD_4)
		game->player->angle = PI;
	else if (keycode == PAD_8)
			game->player->angle = -0.5f * PI;
	else if (keycode == PAD_6)
		game->player->angle = 0.0f;
}

void	reset_game(t_game *game)
{
	stop_thread(game);
	game->start = 0;
	back_to_home(game);
	start_time(game);
}
