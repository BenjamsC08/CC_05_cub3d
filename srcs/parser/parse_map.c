/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: benjamsc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 07:03:15 by benjamsc          #+#    #+#             */
/*   Updated: 2025/09/12 10:54:00 by benjamsc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	extract_loop(char ***ptr_map, char *line, int *max)
{
	char	**map;
	int		l;

	map = *ptr_map;
	if (!ft_strcmp(line, "\n"))
		return (free_strs(map), free(line), 0);
	l = ft_strlen(line);
	if (l > *max)
		*max = l - 1;
	if (!*map)
	{
		*map = ft_strdup(line);
		if (!*map)
			return (free(map), 0);
	}
	else
		map = ft_strsfadd(map, line);
	if (!map)
		return (free(line), 0);
	*ptr_map = map;
	return (1);
}

static int	skip_newline(char **line, int fd)
{
	if (!*line)
		return (0);
	while (*line && !ft_strcmp(*line, "\n"))
	{
		free(*line);
		*line = get_next_line(fd);
	}
	if (!*line)
		return (0);
	return (1);
}

int	extract_map(t_game *game, int fd)
{
	char	*line;
	char	**map;
	int		length;
	int		i;

	length = 0;
	i = 0;
	line = get_next_line(fd);
	if (!skip_newline(&line, fd))
		return (0);
	map = ft_calloc(2, sizeof(char *));
	if (!map)
		return (0);
	while (line)
	{
		if (!extract_loop(&map, line, &length))
			return (0);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->data_desc->map = map;
	game->data_desc->line_length = length;
	game->data_desc->nb_line = i;
	return (check_map(game));
}
