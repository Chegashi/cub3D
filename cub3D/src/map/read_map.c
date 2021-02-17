/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mochegri <mochegri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 04:57:35 by mochegri          #+#    #+#             */
/*   Updated: 2021/02/17 14:42:52 by mochegri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_cub	*ft_read_cub(char *s)
{
	t_cub	*cub;

	cub = ft_init_cub();
	cub->fd = open(s, O_RDONLY);
	while (get_next_line(cub->fd, &(cub->line)) > 0)
		ft_fill(cub->line, cub);
	check_map(cub);
	return (cub);
}

void	ft_destroy_cub(t_cub *cub)
{
	free(cub->line);
	free(cub->floor_color);
	free(cub->ceilling_color);
	free(cub->resolution);
	free(cub->player_position);
	free(cub->textures);
	free(cub->map_str);
	free(cub->map);
	free(cub);
}

void	ft_fill(char *line, t_cub *cub)
{
	if (*line == '\0')
		return ;
	else if (*line == 'R' && cub->resolution[0] == -1)
		ft_resolution(line, cub);
	else if (*line == 'N' && !(cub->textures[0].is_defined))
		ft_read_texture(line, &(cub->textures[0]));
	else if (*line == 'E' && !(cub->textures[1].is_defined))
		ft_read_texture(line, &(cub->textures[1]));
	else if (*line == 'W' && !(cub->textures[3].is_defined))
		ft_read_texture(line, &(cub->textures[3]));
	else if (*line == 'S' && line[1] == 'O' && !(cub->textures[2].is_defined))
		ft_read_texture(line, &(cub->textures[2]));
	else if (*line == 'S' && line[1] == ' ' && !(cub->textures[4].is_defined))
		ft_read_texture(line, &(cub->textures[4]));
	else if (*line == 'F' && (cub->floor_color[0] == -1))
		ft_read_color(line, &(cub->floor_color));
	else if (*line == 'C' && cub->ceilling_color[0] == -1)
		ft_read_color(line, &(cub->ceilling_color));
	else if ((*line == ' ' || *line == '1') && !(cub->map))
		ft_read_map(cub);
	else
		get_err("error in cub file\t start of a line\n");
}

void	ft_tomap(t_cub *cub)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = -1;
	cub->map = (char**)malloc(sizeof(char*) * cub->nbr_ligne);
	while (++i < cub->nbr_ligne)
	{
		cub->map[i] = (char*)malloc(sizeof(char) * cub->nbr_column);
		j = -1;
		k++;
		while (++j < cub->nbr_column)
			if (cub->map_str[k] != '\n' && cub->map_str[k])
			{
				if (ft_isin("EWNS", cub->map_str[k]))
					ft_set_player(cub->map_str[k], i, j, cub);
				else
					cub->map[i][j] = cub->map_str[k];
				k++;
			}
			else
				(cub->map)[i][j] = ' ';
	}
}

void	ft_set_player(char direct, int x, int y, t_cub *cub)
{
	if (!cub->direction)
	{
		cub->direction = direct;
		cub->map[x][y] = '0';
		cub->player_position[0] = x;
		cub->player_position[1] = y;
	}
	else
	{
		cub->valide = 0;
		get_err("Multiplayer or missing player\n");
	}
}
