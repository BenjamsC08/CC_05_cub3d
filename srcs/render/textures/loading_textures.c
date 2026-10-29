/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 10:52:31 by mkerrien          #+#    #+#             */
/*   Updated: 2025/09/11 07:19:33 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assets_zero(t_game *game)
{
	int	i;

	i = -1;
	while (++i < TEX_COUNT)
	{
		game->assets.path[i] = NULL;
		game->assets.tex[i].img = NULL;
		game->assets.tex[i].addr = NULL;
		game->assets.tex[i].w = 0;
		game->assets.tex[i].h = 0;
		game->assets.tex[i].bpp = 0;
		game->assets.tex[i].ll = 0;
		game->assets.tex[i].endian = 0;
	}
}

int	assets_paths_ready(t_game *game)
{
	if (!game->assets.path[TEX_NORTH])
		return (0);
	if (!game->assets.path[TEX_SOUTH])
		return (0);
	if (!game->assets.path[TEX_WEST])
		return (0);
	if (!game->assets.path[TEX_EAST])
		return (0);
	return (1);
}

void	assets_destroy_all(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		if (game->assets.tex[i].img)
			mlx_destroy_image(game->mlx, game->assets.tex[i].img);
		i++;
	}
}

int	load_one_texture(t_game *game, t_tex *dst, const char *xpm_path)
{
	if (!xpm_path || !*xpm_path)
		return (FALSE);
	dst->img = mlx_xpm_file_to_image(game->mlx, (char *)xpm_path,
			&dst->w, &dst->h);
	if (!dst->img)
		return (FALSE);
	dst->addr = mlx_get_data_addr(dst->img, &dst->bpp, &dst->ll, &dst->endian);
	if (!dst->addr)
		return (FALSE);
	return (TRUE);
}

int	assets_load_all(t_game *game, const char **paths)
{
	int			i;
	const int	nb_tex_bonus = TEX_COUNT - 4;

	if (!load_one_texture(game, &game->assets.tex[TEX_NORTH], paths[TEX_NORTH]))
		return (FALSE);
	if (!load_one_texture(game, &game->assets.tex[TEX_SOUTH], paths[TEX_SOUTH]))
		return (FALSE);
	if (!load_one_texture(game, &game->assets.tex[TEX_EAST], paths[TEX_EAST]))
		return (FALSE);
	if (!load_one_texture(game, &game->assets.tex[TEX_WEST], paths[TEX_WEST]))
		return (FALSE);
	define_hard_tex_paths(game);
	i = -1;
	while (++i < nb_tex_bonus)
	{
		if (!load_one_texture(game, &game->assets.tex[i + 4],
				game->bonus_paths[i]))
			return (FALSE);
	}
	return (TRUE);
}
