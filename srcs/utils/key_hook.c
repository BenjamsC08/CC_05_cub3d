/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 05:17:55 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/15 12:42:09 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	enable_mouse_capture(t_game *game)
{
	if (MOUSE_HIDE)
		mlx_mouse_hide(game->mlx, game->win);
	mlx_mouse_move(game->mlx, game->win, (W_WIDTH / 2), (W_HEIGHT / 2));
}

void	game_management(t_game *game)
{
	if (game->start >= 2)
	{
		pthread_detach(game->timer->thread);
		game->start = 0;
		free_strs(game->data_desc->map);
		game->data_desc->map = ft_strsdup(game->data_desc->backup_map);
		if (!game->data_desc->map)
		{
			game->start = 2;
			return ;
		}
		back_to_home(game);
		start_time(game);
	}
	else
	{
		game->start = TRUE;
		set_start_time(game);
	}
}

static int	key_pressed2(int keycode, t_game *game)
{
	int	door_x;
	int	door_y;

	if ((keycode == PAD_2 || keycode == PAD_4
			|| keycode == PAD_6 || keycode == PAD_8)
		&& game->start == 1)
		set_angle(game, keycode);
	else if (keycode == BACKSPACE && game->start == 1)
		back_to_home(game);
	else if (keycode == SPACE && game->start != 1)
		game_management(game);
	else if (keycode == E_KEY && game->start == 1)
	{
		if (door_find_in_front(game, &door_x, &door_y))
			door_try_open(game, door_x, door_y);
	}
	else if (keycode == L_ALT || keycode == R_ALT)
		game->lock_mouse = !game->lock_mouse;
	else if (keycode == DEL)
		reset_game(game);
	else
		ft_printf("key unknown press code :%d\n", keycode);
	return (0);
}

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_all(game, 0);
	else if (keycode == W_KEY && game->start == 1)
		game->player->key_up = TRUE;
	else if (keycode == A_KEY && game->start == 1)
		game->player->key_left = TRUE;
	else if (keycode == S_KEY && game->start == 1)
		game->player->key_down = TRUE;
	else if (keycode == D_KEY && game->start == 1)
		game->player->key_right = TRUE;
	else if (keycode == M_KEY)
		game->minimap->disp_map = TRUE;
	else if (keycode == CAPS && game->minimap->disp_map == TRUE)
		game->minimap->disp_map = FALSE;
	else if (keycode == CAPS && game->minimap->disp_map == FALSE)
		game->minimap->disp_map = TRUE;
	else if (keycode == SHIFT && game->start == 1)
			game->player->run = TRUE;
	else if (keycode == L_ARROW && game->start == 1)
			game->player->rot_left = TRUE;
	else if (keycode == R_ARROW && game->start == 1)
			game->player->rot_right = TRUE;
	else
		return (key_pressed2(keycode, game));
	return (0);
}

int	key_released(int keycode, t_game *game)
{
	if (keycode == W_KEY)
		game->player->key_up = FALSE;
	if (keycode == A_KEY)
		game->player->key_left = FALSE;
	if (keycode == S_KEY)
		game->player->key_down = FALSE;
	if (keycode == D_KEY)
		game->player->key_right = FALSE;
	if (keycode == M_KEY)
		game->minimap->disp_map = FALSE;
	else if (keycode == SHIFT)
			game->player->run = FALSE;
	if (keycode == L_ARROW)
			game->player->rot_left = FALSE;
	if (keycode == R_ARROW)
			game->player->rot_right = FALSE;
	return (0);
}
