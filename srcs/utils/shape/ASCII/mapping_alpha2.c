/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_alpha2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:12:04 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:12:04 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_alpha7(t_game *game);

int	get_alpha6(t_game *game)
{
	const int	al_u[5][5] = {{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	const int	al_v[5][5] = {{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1},
	{0, 1, 0, 1, 0}, {0, 0, 1, 0, 0}};
	const int	al_w[5][5] = {{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1},
	{1, 1, 0, 1, 1}, {1, 0, 0, 0, 1}};
	const int	al_x[5][5] = {{1, 0, 0, 0, 1}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0}, {1, 0, 0, 0, 1}};

	game->tab_num['u'] = ft_1d_to_2d_int(game->gc_head, &al_u[0][0], 5, 5);
	if (!game->tab_num['u'])
		return (0);
	game->tab_num['v'] = ft_1d_to_2d_int(game->gc_head, &al_v[0][0], 5, 5);
	if (!game->tab_num['v'])
		return (0);
	game->tab_num['w'] = ft_1d_to_2d_int(game->gc_head, &al_w[0][0], 5, 5);
	if (!game->tab_num['w'])
		return (0);
	game->tab_num['x'] = ft_1d_to_2d_int(game->gc_head, &al_x[0][0], 5, 5);
	if (!game->tab_num['x'])
		return (0);
	return (get_alpha7(game));
}

static int	get_alpha7(t_game *game)
{
	const int	al_y[5][5] = {{1, 0, 0, 0, 1}, {0, 1, 0, 1, 0}, {0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}};
	const int	al_z[5][5] = {{1, 1, 1, 1, 1}, {0, 0, 0, 1, 0}, {0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0}, {1, 1, 1, 1, 1}};

	game->tab_num['y'] = ft_1d_to_2d_int(game->gc_head, &al_y[0][0], 5, 5);
	if (!game->tab_num['y'])
		return (0);
	game->tab_num['z'] = ft_1d_to_2d_int(game->gc_head, &al_z[0][0], 5, 5);
	if (!game->tab_num['z'])
		return (0);
	return (get_special(game));
}
