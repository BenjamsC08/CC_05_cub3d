/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:09:32 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 10:09:32 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_mlx(t_game *game)
{
	game->mlx = ft_gc_addnode(game->gc_head, mlx_init());
	if (!game->mlx)
		return (ft_clear_gc(game->gc_head), 0);
	game->win = mlx_new_window(game->mlx, W_WIDTH, W_HEIGHT,
			"CUB3D");
	if (!game->win)
		return (ft_clear_gc(game->gc_head), 0);
	game->data_img = ft_gcalloc(game->gc_head, sizeof(t_data_img));
	if (!game->data_img)
		return (ft_clear_gc(game->gc_head), 0);
	game->data_img->img = mlx_new_image(game->mlx, W_WIDTH, W_HEIGHT);
	game->data_img->addr = mlx_get_data_addr(game->data_img->img,
			&game->data_img->bpp,
			&game->data_img->ll, &game->data_img->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->data_img->img, 0, 0);
	return (1);
}

int	init_player(t_game *game)
{
	game->player = ft_gcalloc(game->gc_head, sizeof(t_player));
	if (!game->player)
		return (0);
	game->player->x = game->data_desc->player_x * BLOCK + BLOCK / 2.0;
	game->player->y = game->data_desc->player_y * BLOCK + BLOCK / 2.0;
	if (game->data_desc->player == 'N')
		game->player->backup_angle = -PI / 2.0f;
	else if (game->data_desc->player == 'S')
		game->player->backup_angle = PI / 2.0f;
	else if (game->data_desc->player == 'E')
		game->player->backup_angle = 0.0f;
	else if (game->data_desc->player == 'W')
		game->player->backup_angle = PI;
	game->player->angle = game->player->backup_angle;
	return (1);
}

int	init_maps(t_game *game)
{
	game->minimap = ft_gcalloc(game->gc_head, sizeof(t_minimap));
	if (!game->minimap)
		return (0);
	game->minimap->mmap_img = ft_gcalloc(game->gc_head, sizeof(t_data_img));
	if (!game->minimap->mmap_img)
		return (0);
	init_map(game);
	init_minimap(game);
	game->minimap->disp_map = FALSE;
	return (1);
}

int	init_base(t_game *game)
{
	game->gc = init_gc();
	if (!game->gc)
		return (0);
	game->gc_head = &(game->gc);
	game->start = 0;
	game->lock_mouse = TRUE;
	assets_zero(game);
	if (!init_mlx(game))
		return (ft_clear_gc(game->gc_head), 0);
	return (1);
}
