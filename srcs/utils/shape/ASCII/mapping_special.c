/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_special.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:12:08 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:12:08 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_special1(t_game *game);
static int	get_special2(t_game *game);

int	get_special(t_game *game)
{
	const int	colon[5][5] = {{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}};
	const int	semi_colon[5][5] = {{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0},
	{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 0, 0, 0}};
	const int	dot[5][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}};
	const int	comma[5][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 1, 0, 0, 0}};

	game->tab_num[':'] = ft_1d_to_2d_int(game->gc_head, &colon[0][0], 5, 5);
	if (!game->tab_num[':'])
		return (0);
	game->tab_num[';'] = ft_1d_to_2d_int(game->gc_head, &semi_colon[0][0],
			5, 5);
	if (!game->tab_num[';'])
		return (0);
	game->tab_num['.'] = ft_1d_to_2d_int(game->gc_head, &dot[0][0], 5, 5);
	if (!game->tab_num['.'])
		return (0);
	game->tab_num[','] = ft_1d_to_2d_int(game->gc_head, &comma[0][0], 5, 5);
	if (!game->tab_num[','])
		return (0);
	return (get_special1(game));
}

static int	get_special1(t_game *game)
{
	const int	space[5][5] = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};
	const int	ex_m[5][5] = {{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}};
	const int	arrow_l[5][5] = {{1, 0, 0, 0, 0}, {1, 1, 0, 0, 0},
	{1, 1, 1, 0, 0}, {1, 1, 0, 0, 0}, {1, 0, 0, 0, 0}};
	const int	arrow_r[5][5] = {{0, 0, 0, 0, 1}, {0, 0, 0, 1, 1},
	{0, 0, 1, 1, 1}, {0, 0, 0, 1, 1}, {0, 0, 0, 0, 1}};

	game->tab_num[' '] = ft_1d_to_2d_int(game->gc_head, &space[0][0], 5, 5);
	if (!game->tab_num[' '])
		return (0);
	game->tab_num['!'] = ft_1d_to_2d_int(game->gc_head, &ex_m[0][0],
			5, 5);
	if (!game->tab_num['!'])
		return (0);
	game->tab_num['>'] = ft_1d_to_2d_int(game->gc_head, &arrow_l[0][0],
			5, 5);
	if (!game->tab_num['>'])
		return (0);
	game->tab_num['<'] = ft_1d_to_2d_int(game->gc_head, &arrow_r[0][0],
			5, 5);
	if (!game->tab_num['<'])
		return (0);
	return (get_special2(game));
}

static int	get_special2(t_game *game)
{
	const int	brack_o[5][5] = {{0, 0, 0, 1, 1}, {0, 0, 1, 1, 0},
	{0, 0, 1, 0, 0}, {0, 0, 1, 1, 0}, {0, 0, 0, 1, 1}};
	const int	brack_c[5][5] = {{1, 1, 0, 0, 0}, {0, 1, 1, 0, 0},
	{0, 0, 1, 0, 0}, {0, 1, 1, 0, 0}, {1, 1, 0, 0, 0}};
	const int	sbrack_o[5][5] = {{0, 0, 1, 1, 1}, {0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 1, 1}};
	const int	sbrack_c[5][5] = {{1, 1, 1, 0, 0}, {0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}, {1, 1, 1, 0, 0}};

	game->tab_num['('] = ft_1d_to_2d_int(game->gc_head, &brack_o[0][0], 5, 5);
	if (!game->tab_num['('])
		return (0);
	game->tab_num[')'] = ft_1d_to_2d_int(game->gc_head, &brack_c[0][0],
			5, 5);
	if (!game->tab_num[')'])
		return (0);
	game->tab_num['['] = ft_1d_to_2d_int(game->gc_head, &sbrack_o[0][0], 5, 5);
	if (!game->tab_num['['])
		return (0);
	game->tab_num[']'] = ft_1d_to_2d_int(game->gc_head, &sbrack_c[0][0],
			5, 5);
	if (!game->tab_num[']'])
		return (0);
	return (1);
}
