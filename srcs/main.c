/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 09:10:58 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/15 12:48:04 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	disp_management(t_game *game)
{
	if (game->minimap->disp_map == TRUE)
	{
		draw_trect(game->data_img, get_rect(0, 0, W_WIDTH, W_HEIGHT), MLX_GREY);
		draw_map(game);
	}
	else
	{
		draw_minimap(game);
	}
	if (!game->start)
	{
		draw_trect(game->data_img, get_rect(0, 0, W_WIDTH, W_HEIGHT),
			MLX_BLACK);
		str_put(game, get_text("press [space]!", 10, MLX_GREEN,
				get_rect(W_WIDTH / 2 - 300, W_HEIGHT / 2 - 50, 600, 100)));
	}
	else if (game->start == 2)
		defeat_screen(game);
	else if (game->start == 3)
		victory_screen(game);
}

int	looping_hook(t_game *game)
{
	moves(game);
	draw_frect(game->data_img, get_rect(0, 0, W_WIDTH, W_HEIGHT / 2),
		game->data_desc->ceiling_color);
	draw_frect(game->data_img, get_rect(0, W_HEIGHT / 2, W_WIDTH, W_HEIGHT / 2),
		game->data_desc->floor_color);
	door_anim_update(game);
	render_frame(game);
	put_timer(game, 10, get_rect(2 * BLOCK2, W_HEIGHT - (W_HEIGHT / 4) - 80,
			300, 70));
	disp_management(game);
	mlx_put_image_to_window(game->mlx, game->win, game->data_img->img, 0, 0);
	return (0);
}

int	game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, key_released, game);
	mlx_hook(game->win, 17, 1L << 0, close_all, game);
	mlx_loop_hook(game->mlx, looping_hook, game);
	mlx_loop(game->mlx);
	return (0);
}

static int	game_condition(t_game *game, char **argv)
{
	if (!init_base(game))
		return (1);
	if (!good_file_ext(argv[1], "cub"))
		return (close_all(game, 1), 0);
	if (!init_parser(game))
		return (close_all(game, 1), 0);
	if (!load_cub_file(game, argv[1]))
		return (close_all(game, 1), 0);
	if (!load_score_history(game, argv[1]))
		return (close_all(game, 1), 0);
	if (!assets_paths_ready(game))
		return (not_a_good_file(BAD_IMAGE), close_all(game, 1), 0);
	if (!assets_load_all(game, (const char **)game->assets.path))
		return (not_a_good_file(BAD_IMAGE), close_all(game, 1), 0);
	if (!init_maps(game))
		return (close_all(game, 1), 0);
	if (!init_player(game))
		return (close_all(game, 1), 0);
	if (!create_num(game))
		return (close_all(game, 1), 0);
	if (!start_time(game))
		return (close_all(game, 1), 0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_game	game;

	if (!envp || !*envp)
		return (1);
	ft_bzero(&game, sizeof(t_game));
	if (argc != 2)
		return (not_a_good_file(0), 1);
	if (!game_condition(&game, argv))
		return (1);
	enable_mouse_capture(&game);
	game_loop(&game);
	return (0);
}
