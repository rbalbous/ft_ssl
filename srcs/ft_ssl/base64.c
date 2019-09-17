/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:52:42 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/17 15:27:00 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint8_t g_base_64[64] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
	'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd',
	'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
	't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7',
	'8', '9', '+', '/'
};

void	init_base(t_base *base, t_infos *infos, char *str, uint32_t i)
{
	uint32_t	h;

	h = ((uint32_t)str[i]) << 16;
	if (i + 1 < infos->len)
		h += ((uint32_t)str[i + 1]) << 8;
	if (i + 2 < infos->len)
		h += ((uint32_t)str[i + 2]);
	base->h0 = (uint8_t)(h >> 18) & 63;
	base->h1 = (uint8_t)(h >> 12) & 63;
	base->h2 = (uint8_t)(h >> 6) & 63;
	base->h3 = (uint8_t)h & 63;
}

void	base64(t_args *args, t_infos *infos, char *str, char *file)
{
	(void)args;
	(void)file;
	uint32_t	index_input;
	uint32_t	result_index;
	t_base		base;
	char		*result;
	uint32_t	tot_len;
	uint32_t	add_padding;

	index_input = 0;
	result_index = 0;
	add_padding = infos->len % 3;
	tot_len = (infos->len * 4) / 3 + infos->len % 3;
	if (!(result = (char*)malloc(sizeof(result) * (tot_len + 1))))
		ft_dprintf(2, "malloc error\n");
	base = (t_base){0, 0, 0, 0};
	while (index_input < infos->len)
	{
		init_base(&base, infos, str, index_input);
		result[result_index++] = g_base_64[base.h0];
		result[result_index++] = g_base_64[base.h1];
		if (index_input + 1 < infos->len)
			result[result_index++] = g_base_64[base.h2];
		if (index_input + 2 < infos->len)
		result[result_index++] = g_base_64[base.h3];
		index_input += 3;
	}
	if (add_padding > 0)
	{
		while (add_padding < 3)
		{
			result[result_index++] = '=';
			add_padding++;
		}
	}
	result[result_index] = 0;
	ft_printf("%s\n", result);
}

int		parse_base64(t_args *args, t_infos *infos, char **str, int argc)
{
	(void)str;

	if (argc < 3)
	{
		treat_file(args, infos, NULL, 0);
		return (1);
	}
	else

	return (0);
}
