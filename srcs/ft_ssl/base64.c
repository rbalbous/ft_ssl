/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 16:52:42 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/20 01:37:01 by rbalbous         ###   ########.fr       */
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

uint8_t		get_base_index(char i)
{
	uint8_t	index;

	index = 0;
	while (g_base_64[index] != i)
	{
		index++;
	}
	return (index);
}

void	init_decrypt_base(t_base *base, char *str, uint32_t i)
{
	if (!(str[i]))
		exit(1);
	base->h0 = get_base_index(str[i]);
	if (!(str[i + 1]))
		exit(1);
	base->h1 = get_base_index(str[i + 1]);
	if (!(str[i + 2]))
		exit(1);
	base->h2 = get_base_index(str[i + 2]);
	if (!(str[i + 3]))
		exit(1);
	base->h3 = get_base_index(str[i + 3]);
	base->r0 = (base->h0 << 2);
	base->r0 = base->r0 ^ (base->h1 >> 4);
	base->r1 = (base->h1 << 4);
	base->r1 = base->r1 ^ (base->h2 >> 2);
	base->r2 = base->h2 << 6;
	base->r2 = base->r2 ^ base->h3;
}

uint32_t	add_elem(char *result, uint32_t result_index, uint8_t base)
{
	static int count = 0;

	result[result_index] = g_base_64[base];
	count++;
	result_index++;
	if (count == 64)
	{
		result[result_index] = '\n';
		result_index++;
		count = 0;
	}
	return (result_index);
}

int		padding(char *str, int len)
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (!(str[len - i] >= 'A' &&  str[len - i] <= 'Z') && !(str[len - i] >= 'a' && str[len - i] <= 'z') && !(str[len - i] >= '0' && str[len - i] <= '9') && str[len - i] != '+' && str[len - i] != '/')
	{
		count++;
		i++;
	}
	return (count);
}
  
void	base_decrypt(t_args *args, t_infos *infos, char *str, char *file)
{
	(void)args;
	(void)file;
	(void)str;
	uint32_t	index_input;
	uint32_t	result_index;
	char		*result;
	uint32_t	tot_len;
	t_base		base;
	uint32_t	sub_padding;
	

	index_input = 0;
	result_index = 0;
	sub_padding = padding(str, infos->len);
	infos->len -= sub_padding;
	str[infos->len] = 0;
	tot_len = infos->len;
	tot_len -= tot_len / 64;
	tot_len = (tot_len * 3) / 4;
	if (!(result = (char*)malloc(sizeof(result) * (tot_len + 1))))
		exit(ft_dprintf(2, "malloc error\n"));
	while (str[index_input] && index_input < infos->len - sub_padding)
	{
		init_decrypt_base(&base, str, index_input);
		result[result_index++] = base.r0;
		result[result_index++] = base.r1;
		result[result_index++] = base.r2;
		index_input += 4;
	}
	result[result_index] = 0;
	ft_printf("%s", result);
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

	if (args->arg_d == 1)
		return (base_decrypt(args, infos, str, file));
	index_input = 0;
	result_index = 0;
	add_padding = infos->len % 3;
	tot_len = (infos->len * 4) / 3 + infos->len % 3;
	tot_len += tot_len / 64;
	if (!(result = (char*)malloc(sizeof(result) * (tot_len + 1))))
		exit(ft_dprintf(2, "malloc error\n"));
	base = (t_base){0, 0, 0, 0, 0, 0, 0};
	while (index_input < infos->len)
	{
		init_base(&base, infos, str, index_input);
		result_index = add_elem(result, result_index, base.h0);
		result_index = add_elem(result, result_index, base.h1);
		if (index_input + 1 < infos->len)
			result_index = add_elem(result, result_index, base.h2);
		if (index_input + 2 < infos->len)
			result_index = add_elem(result, result_index, base.h3);
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

int		get_file_base(t_args *args, t_infos *infos, char **str, int index)
{
	int		i;
	char	*file;

	i = 0;
	index++;
	if (!str[index])
		exit(ft_dprintf(2, "file error :\nusage: -i <file>"));
	file = ft_strdup(str[index]);
	parse_file(args, infos, file, 0);
	return (1);
}

int		parse_base_flags(t_args *args, t_infos *infos, char **str, int argc)
{
	(void)str;
	(void)infos;
	(void)args;
	int32_t	index;
	uint32_t	i;

	index = 2;
	i = 0;
	while (index < argc)
	{
		i = 0;
		while (str[index][i] && str[index][i] != '-')
			i++;
		if (!(str[index][i]))
		{
			treat_file(args, infos, NULL, 0);
			return (1);
		}
		while (str[index][i] && str[index][i] != '-')
			i++;
		while (str[index][i])
		{
			if (str[index][i] == 'i')
			{
				return (get_file_base(args, infos, str, index));
			}
			if (str[index][i] == 'o')
			{
				args->arg_o = 1;
			}
			if (str[index][i] == 'e')
			{
				args->arg_e = 1;
				args->arg_d = 0;
			}
			if (str[index][i] == 'd')
			{
				args->arg_e = 0;
				args->arg_d = 1;
			}
			i++;
		}
		index++;
	}
	return (0);
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
	{
		if (!(parse_base_flags(args, infos, str, argc)))
			treat_file(args, infos, NULL, 0);
	}
	return (0);
}

// h0 0010 1110
// h1 0001 0111
// h2 0000 0010
// h3 0001 1111

// r0 10 111001
// r1 0111 0000
// r2 1001 1111

// r0 = (h0 << 2);
// r0 = r0 & (h1 >> 4);
// r1 = (h1 << 4);
// r1 = r1 & (h2 >> 2);
// r2 = h2 << 6;
// r2 = r2 & h3;