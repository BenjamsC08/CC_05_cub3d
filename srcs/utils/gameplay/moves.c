/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 05:28:33 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/12 05:50:15 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief  Attempt horizontal movement with collision check.
 *
 * Computes the next X position and applies it only if the circle
 * collision check confirms no wall intersection.
 *
 * @param  game     Global game context with player state.
 * @param  test_x   Proposed movement offset along X axis.
 * @return None.
 *
 * @note   Y remains unchanged in this function.
 * @warning Prevents player from passing through walls on X axis.
 * @pre    Player coordinates and collide_circle() are valid.
 * @post   Player’s x may be updated if no collision occurs.
 */
static void	try_move_x(t_game *game, float test_x)
{
	float	next_x;
	float	y;

	next_x = game->player->x + test_x;
	y = game->player->y;
	if (!collide_circle(game, next_x, y))
		game->player->x = next_x;
}

/**
 * @brief  Attempt vertical movement with collision check.
 *
 * Computes the next Y position and applies it only if the circle
 * collision check confirms no wall intersection.
 *
 * @param  game     Global game context with player state.
 * @param  test_y   Proposed movement offset along Y axis.
 * @return None.
 *
 * @note   X remains unchanged in this function.
 * @warning Prevents player from passing through walls on Y axis.
 * @pre    Player coordinates and collide_circle() are valid.
 * @post   Player’s y may be updated if no collision occurs.
 */
static void	try_move_y(t_game *game, float test_y)
{
	float	x;
	float	next_y;

	x = game->player->x;
	next_y = game->player->y + test_y;
	if (!collide_circle(game, x, next_y))
		game->player->y = next_y;
}

/**
 * @brief  Accumulate movement intent into a test vector.
 *
 * Updates the test displacement vector based on pressed keys (up, down,
 * left strafe, right strafe). Forward/backward use the facing direction;
 * strafing uses perpendicular direction with half speed.
 *
 * @param  game        Global game context with input flags.
 * @param  test        Displacement vector to update.
 * @param  dir         Normalized facing direction vector.
 * @param  move_speed  Movement speed in world units.
 * @return None.
 *
 * @note   Strafing offsets are scaled down to avoid diagonal overspeed.
 * @warning Collision is not checked here; test displacement may be invalid.
 * @pre    test is initialized to (0,0) before calling.
 * @post   test contains combined displacement for this frame.
 */
static void	travelling(t_game *game, t_vec *test, t_vec dir, float move_speed)
{
	if (game->player->key_up == TRUE)
	{
		test->x += dir.x * move_speed;
		test->y += dir.y * move_speed;
	}
	if (game->player->key_down == TRUE)
	{
		test->x -= dir.x * (move_speed / 2);
		test->y -= dir.y * (move_speed / 2);
	}
	if (game->player->key_left == TRUE)
	{
		test->x -= -dir.y * (move_speed / 2);
		test->y -= dir.x * (move_speed / 2);
	}
	if (game->player->key_right == TRUE)
	{
		test->x -= dir.y * (move_speed / 2);
		test->y -= -dir.x * (move_speed / 2);
	}
}

/**
 * @brief  Apply computed displacement with collision handling.
 *
 * Uses the test displacement vector from travelling(), then applies
 * movement along X and Y independently while checking for collisions.
 *
 * @param  game        Global game context with player state.
 * @param  dir         Normalized facing direction vector.
 * @param  move_speed  Movement speed in world units.
 * @return None.
 *
 * @note   Processes X and Y separately to allow sliding along walls.
 * @warning Without circle collision checks, the player could clip into walls.
 * @pre    dir must be derived from current player angle.
 * @post   Player’s position is updated if movement is unobstructed.
 */
static void	travel_management(t_game *game, t_vec dir, float move_speed)
{
	t_vec	test;

	test.x = 0.0f;
	test.y = 0.0f;
	travelling(game, &test, dir, move_speed);
	try_move_x(game, test.x);
	try_move_y(game, test.y);
}

/**
 * @brief  Handle per-frame player input: rotation and movement.
 *
 * Applies rotation, determines movement speed (walk/run/diagonal),
 * computes facing direction, and calls travel_management() to move
 * the player with collision handling.
 *
 * @param  game  Global game context with player state and input flags.
 * @return None.
 *
 * @note   Diagonal, lateral, or backward movements reduce speed by half.
 * @warning If input states are inconsistent, displacement may be unexpected.
 * @pre    Input flags (keys, run, rotate) are up-to-date.
 * @post   Player’s position and angle reflect this frame’s inputs.
 */
void	moves(t_game *game)
{
	float	move_speed;
	t_vec	dir;

	apply_mouse_rotate(game);
	apply_rotate(game);
	move_speed = WALK_SPD;
	if (game->player->run == TRUE)
		move_speed = RUN_SPD;
	if ((game->player->key_up || game->player->key_down)
		&& (game->player->key_left || game->player->key_right))
		move_speed /= 2.0f;
	dir.x = cosf(game->player->angle);
	dir.y = sinf(game->player->angle);
	travel_management(game, dir, move_speed);
	is_win(game);
}
