/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping_alpha1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:12:01 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 11:14:46 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_alpha2(t_game *game);
static int	get_alpha3(t_game *game);
static int	get_alpha4(t_game *game);
static int	get_alpha5(t_game *game);

int	get_alpha1(t_game *game)
{
	const int	al_a[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}};
	const int	al_b[5][5] = {{1, 1, 1, 1, 0}, {1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 0}};
	const int	al_c[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}};
	const int	al_d[5][5] = {{1, 1, 1, 1, 0}, {1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 0}};

	game->tab_num['a'] = ft_1d_to_2d_int(game->gc_head, &al_a[0][0], 5, 5);
	if (!game->tab_num['a'])
		return (0);
	game->tab_num['b'] = ft_1d_to_2d_int(game->gc_head, &al_b[0][0],
			5, 5);
	if (!game->tab_num['b'])
		return (0);
	game->tab_num['c'] = ft_1d_to_2d_int(game->gc_head, &al_c[0][0], 5, 5);
	if (!game->tab_num['c'])
		return (0);
	game->tab_num['d'] = ft_1d_to_2d_int(game->gc_head, &al_d[0][0], 5, 5);
	if (!game->tab_num['d'])
		return (0);
	return (get_alpha2(game));
}

static int	get_alpha2(t_game *game)
{
	const int	al_e[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}};
	const int	al_f[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0}, {1, 0, 0, 0, 0}};
	const int	al_g[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 0, 0, 1, 1},
	{1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	const int	al_h[5][5] = {{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}};

	game->tab_num['e'] = ft_1d_to_2d_int(game->gc_head, &al_e[0][0], 5, 5);
	if (!game->tab_num['e'])
		return (0);
	game->tab_num['f'] = ft_1d_to_2d_int(game->gc_head, &al_f[0][0], 5, 5);
	if (!game->tab_num['f'])
		return (0);
	game->tab_num['g'] = ft_1d_to_2d_int(game->gc_head, &al_g[0][0], 5, 5);
	if (!game->tab_num['g'])
		return (0);
	game->tab_num['h'] = ft_1d_to_2d_int(game->gc_head, &al_h[0][0], 5, 5);
	if (!game->tab_num['h'])
		return (0);
	return (get_alpha3(game));
}

static int	get_alpha3(t_game *game)
{
	const int	al_i[5][5] = {{1, 1, 1, 1, 1}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0}, {1, 1, 1, 1, 1}};
	const int	al_j[5][5] = {{0, 0, 0, 1, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	const int	al_k[5][5] = {{1, 0, 0, 0, 1}, {1, 0, 0, 1, 0}, {1, 1, 1, 0, 0},
	{1, 0, 0, 1, 0}, {1, 0, 0, 0, 1}};
	const int	al_l[5][5] = {{1, 0, 0, 0, 0}, {1, 0, 0, 0, 0}, {1, 0, 0, 0, 0},
	{1, 0, 0, 0, 0}, {1, 1, 1, 1, 1}};

	game->tab_num['i'] = ft_1d_to_2d_int(game->gc_head, &al_i[0][0], 5, 5);
	if (!game->tab_num['i'])
		return (0);
	game->tab_num['j'] = ft_1d_to_2d_int(game->gc_head, &al_j[0][0], 5, 5);
	if (!game->tab_num['j'])
		return (0);
	game->tab_num['k'] = ft_1d_to_2d_int(game->gc_head, &al_k[0][0], 5, 5);
	if (!game->tab_num['k'])
		return (0);
	game->tab_num['l'] = ft_1d_to_2d_int(game->gc_head, &al_l[0][0], 5, 5);
	if (!game->tab_num['l'])
		return (0);
	return (get_alpha4(game));
}

static int	get_alpha4(t_game *game)
{
	const int	al_m[5][5] = {{1, 0, 0, 0, 1}, {1, 1, 0, 1, 1}, {1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}};
	const int	al_n[5][5] = {{1, 0, 0, 0, 1}, {1, 1, 0, 0, 1}, {1, 0, 1, 0, 1},
	{1, 0, 0, 1, 1}, {1, 0, 0, 0, 1}};
	const int	al_o[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	const int	al_p[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0}, {1, 0, 0, 0, 0}};

	game->tab_num['m'] = ft_1d_to_2d_int(game->gc_head, &al_m[0][0], 5, 5);
	if (!game->tab_num['m'])
		return (0);
	game->tab_num['n'] = ft_1d_to_2d_int(game->gc_head, &al_n[0][0], 5, 5);
	if (!game->tab_num['n'])
		return (0);
	game->tab_num['o'] = ft_1d_to_2d_int(game->gc_head, &al_o[0][0], 5, 5);
	if (!game->tab_num['o'])
		return (0);
	game->tab_num['p'] = ft_1d_to_2d_int(game->gc_head, &al_p[0][0], 5, 5);
	if (!game->tab_num['p'])
		return (0);
	return (get_alpha5(game));
}

static int	get_alpha5(t_game *game)
{
	const int	al_q[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1},
	{1, 0, 0, 1, 1}, {1, 1, 1, 1, 1}};
	const int	al_r[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0}, {1, 0, 0, 0, 1}};
	const int	al_s[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 0}, {1, 1, 1, 1, 1},
	{0, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	const int	al_t[5][5] = {{1, 1, 1, 1, 1}, {0, 0, 1, 0, 0}, {0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0}, {0, 0, 1, 0, 0}};

	game->tab_num['q'] = ft_1d_to_2d_int(game->gc_head, &al_q[0][0], 5, 5);
	if (!game->tab_num['q'])
		return (0);
	game->tab_num['r'] = ft_1d_to_2d_int(game->gc_head, &al_r[0][0], 5, 5);
	if (!game->tab_num['r'])
		return (0);
	game->tab_num['s'] = ft_1d_to_2d_int(game->gc_head, &al_s[0][0], 5, 5);
	if (!game->tab_num['s'])
		return (0);
	game->tab_num['t'] = ft_1d_to_2d_int(game->gc_head, &al_t[0][0], 5, 5);
	if (!game->tab_num['t'])
		return (0);
	return (get_alpha6(game));
}
