/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:09:23 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 10:09:23 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	stop_thread(t_game *game)
{
	pthread_mutex_lock(game->timer->mtx_run);
	game->timer->run = FALSE;
	pthread_mutex_unlock(game->timer->mtx_run);
	pthread_join(game->timer->thread, NULL);
}

int	close_all(t_game *game, int exit_code)
{
	if (game->timer)
		stop_thread(game);
	if (game->data_img->img)
		mlx_destroy_image(game->mlx, game->data_img->img);
	if (game->minimap && game->minimap->mmap_img)
		mlx_destroy_image(game->mlx, game->minimap->mmap_img->img);
	if (game->data_desc && game->data_desc->map)
		free_strs(game->data_desc->map);
	if (game->data_desc && game->data_desc->backup_map)
		free_strs(game->data_desc->backup_map);
	assets_destroy_all(game);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	ft_clear_gc(game->gc_head);
	exit (exit_code);
}
