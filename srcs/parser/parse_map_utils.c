/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:36:48 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 10:39:02 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	prealable_check(t_game *game, char c, int y, int x)
{
	if (!ft_ischarset(c, "NSWE0123X \t"))
		return (0);
	if (ft_ischarset(c, "NSWE") && !game->data_desc->player)
	{
		game->data_desc->player = c;
		game->data_desc->player_x = x;
		game->data_desc->player_y = y;
	}
	else if (ft_ischarset(c, "NSWE") && game->data_desc->player)
		return (0);
	return (1);
}

static int	char_check(char **map, int i, int j)
{
	if (!map[j][i - 1] || ft_iswhitespace(map[j][i - 1]))
		return (0);
	if (!map[j][i + 1] || ft_iswhitespace(map[j][i + 1]))
		return (0);
	if (!map[j - 1][i] || ft_iswhitespace(map[j - 1][i]))
		return (0);
	if (!map[j + 1][i] || ft_iswhitespace(map[j + 1][i]))
		return (0);
	return (1);
}

static int	check_char(t_game *game, char **map, int j, int i)
{
	if (!prealable_check(game, map[j][i], j, i))
		return (0);
	if (j == 0 || i == 0 || j == game->data_desc->nb_line - 1
		|| (t_uint)i == ft_strlen(map[j]))
	{
		if (map[j][i] != '1' && !ft_iswhitespace(map[j][i]))
			return (0);
		else
			return (1);
	}
	else if (ft_iswhitespace(map[j][i]))
	{
		if (map[j][i - 1] && !ft_ischarset(map[j][i - 1], " 1\n"))
			return (0);
		if (map[j][i + 1] && !ft_ischarset(map[j][i + 1], "1 \n"))
			return (0);
		if (map[j - 1][i] && !ft_ischarset(map[j - 1][i], "1 \n"))
			return (0);
		if ((t_uint)i < ft_strlen(map[j + 1]) && (map[j + 1][i]
			&& !ft_ischarset(map[j + 1][i], "1 \n0")))
			return (0);
	}
	else if (ft_ischarset(map[j][i], "023NSWEX"))
		return (char_check(map, i, j));
	return (1);
}

int	check_map(t_game *game)
{
	int		i;
	int		j;
	char	**map;

	j = 0;
	if (!game->data_desc->map || !*game->data_desc->map)
		return (0);
	map = ft_strsdup(game->data_desc->map);
	while (map[j] && j < game->data_desc->nb_line)
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n' )
		{
			if (!check_char(game, map, j, i))
				return (error_map(map, j, i));
			i++;
		}
		j++;
	}
	free_strs(map);
	if (!game->data_desc->player)
		return (not_a_good_file(MAP));
	return (1);
}
