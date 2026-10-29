/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 08:14:11 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:46:49 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_c_pixel(t_game *game, int big_pixel, int small_pixel)
{
	int	bpp;
	int	k;

	bpp = game->minimap->mmap_img->bpp / 8;
	if (small_pixel < 0 || small_pixel
		>= game->minimap->mmap_img->ll * game->data_desc->nb_line * BLOCK2
		|| ft_pixel_get2(&game->minimap->mmap_img->addr[small_pixel])
		== MLX_BLACK)
		return ;
	k = -1;
	while (++k < bpp)
		game->data_img->addr[big_pixel + k] = game->minimap->mmap_img->addr[
			small_pixel + k];
}

static void	draw_ray(t_game *game, float angle, int safety_counter)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;

	ray_x = game->minimap->minimap.x
		+ (game->minimap->minimap.w / 2) + BLOCK2 / 2;
	ray_y = game->minimap->minimap.y
		+ (game->minimap->minimap.h / 2) + BLOCK2 / 2;
	step_x = cosf(angle);
	step_y = sinf(angle);
	while (safety_counter > 0)
	{
		ft_pixel_put(game->data_img, (int)ray_x, (int)ray_y, MLX_YELLOW);
		ray_x += step_x;
		ray_y += step_y;
		safety_counter--;
	}
}

void	draw_minimap(t_game *game)
{
	if (game->minimap->mmap_img->img)
		mlx_destroy_image(game->mlx, game->minimap->mmap_img->img);
	init_map(game);
	get_map(game, game->minimap->mmap_img);
	draw_trect(game->data_img, game->minimap->minimap, MLX_GREY);
	draw_ray(game, game->player->angle, BLOCK2 * 1.5f);
	draw_frect(game->data_img,
		get_rect(
			game->minimap->minimap.x + (game->minimap->minimap.w / 2),
			game->minimap->minimap.y + (game->minimap->minimap.h / 2),
			BLOCK2, BLOCK2),
		MLX_PURPLE);
	copy_map(game);
	draw_rect(game->data_img, game->minimap->minimap, game->timer->color);
}

void	init_map(t_game *game)
{
	t_data_img	*img;

	game->minimap->minimap.x = BLOCK2;
	game->minimap->minimap.y = W_HEIGHT - (W_HEIGHT / 4);
	game->minimap->minimap.w = 32 * BLOCK2;
	game->minimap->minimap.h = 26 * BLOCK2;
	img = game->minimap->mmap_img;
	img->img = mlx_new_image(game->mlx,
			game->data_desc->line_length * BLOCK2,
			game->data_desc->nb_line * BLOCK2);
	img->addr = mlx_get_data_addr(img->img,
			&img->bpp, &img->ll, &img->endian);
	get_map(game, img);
}
