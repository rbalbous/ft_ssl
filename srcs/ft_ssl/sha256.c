/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 18:06:56 by rbalbous          #+#    #+#             */
/*   Updated: 2019/09/11 22:56:32 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

uint32_t g_k[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

uint32_t	rotate_right(uint32_t x, uint32_t c)
{
	return ((x >> c) | (x << (32 - c)));
}


void		init_sha(t_sha *sha)
{
	sha->h0 = 0x6a09e667;
	sha->h1 = 0xbb67ae85;
	sha->h2 = 0x3c6ef372;
	sha->h3 = 0xa54ff53a;
	sha->h4 = 0x510e527f;
	sha->h5 = 0x9b05688c;
	sha->h6 = 0x1f83d9ab;
	sha->h7 = 0x5be0cd19;
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
}

void		update_sha_pre(t_sha *sha)
{
	sha->a = sha->h0;
	sha->b = sha->h1;
	sha->c = sha->h2;
	sha->d = sha->h3;
	sha->e = sha->h4;
	sha->f = sha->h5;
	sha->g = sha->h6;
	sha->h = sha->h7;
}

void		update_sha_post(t_sha *sha)
{
	sha->h0 += sha->a;
	sha->h1 += sha->b;
	sha->h2 += sha->c;
	sha->h3 += sha->d;
	sha->h4 += sha->e;
	sha->h5 += sha->f;
	sha->h6 += sha->g;
	sha->h7 += sha->h;
}

uint32_t		*init_msg(uint32_t *bit_len, uint32_t *new_len, uint32_t *len)
{
	uint32_t *msg;

	*bit_len = *len * 8;
	if (*bit_len)
		*bit_len += 64;
	*new_len = 1 + *bit_len / 512;
	if (!(msg = (uint32_t*)ft_memalloc(sizeof(msg) * *new_len * 16)))
	{
		exit(ft_dprintf(2, "malloc error in sha256 initiation"));
	}
	return (msg);
}

void		add_padding(uint32_t len, uint32_t *msg)
{
	uint32_t	pad;
	size_t		last_bytes;
	size_t		index;

	last_bytes = len % 4;
	index = len / 4;
	pad = 0x00000080;
	if (last_bytes == 1)
		pad = 0x00008000;
	else if (last_bytes == 2)
		pad = 0x00800000;
	else if (last_bytes == 3)
		pad = 0x80000000;
	else if (last_bytes == 4)
	{
		index++;
	}
	msg[index] = msg[index] | pad;
}

uint32_t	swap_bytes_32bit(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

void		add_size(uint32_t *msg, uint32_t bit_len, uint32_t new_len)
{
	size_t		size;
	size_t		index;

	size = 0;
	if (bit_len)
	{
		size = bit_len - 64;
	}
	index = new_len * 16 - 2;
	msg[index] = (size >> 32) & 0xffffffff;
	msg[index + 1] = size & 0xffffffff;
}

void			sha256_encrypt(t_sha *sha, uint32_t *w)
{
	uint32_t i;

	i = 0;
	while (i < 64)
	{
		sha->s1 = rotate_right(sha->e, 6) ^ rotate_right(sha->e, 11)
			^ rotate_right(sha->e, 25);
		sha->ch = (sha->e & sha->f) ^ (~sha->e & sha->g);
		sha->tmp1 = sha->h + sha->s1 + sha->ch + g_k[i] + w[i];
		sha->s0 = rotate_right(sha->a, 2) ^ rotate_right(sha->a, 13)
			^ rotate_right(sha->a, 22);
		sha->maj = (sha->a & sha->b) ^ (sha->a & sha->c)
		^ (sha->b & sha->c);
		sha->tmp2 = sha->s0 + sha->maj;
		sha->h = sha->g;
		sha->g = sha->f;
		sha->f = sha->e;
		sha->e = sha->d + sha->tmp1;
		sha->d = sha->c;
		sha->c = sha->b;
		sha->b = sha->a;
		sha->a = sha->tmp1 + sha->tmp2;
		i++;
	}
	update_sha_post(sha);
}

static void		schedule_array(uint32_t *w, uint32_t *msg, int offset)
{
	uint32_t	s0;
	uint32_t	s1;
	int			i;

	ft_memcpy(w, &msg[offset * 16], 16 * sizeof(uint32_t));
	i = 16;
	while (i < 64)
	{
		s0 = rotate_right(w[i - 15], 7) ^ rotate_right(w[i - 15], 18)
			^ (w[i - 15] >> 3);
		s1 = rotate_right(w[i - 2], 17) ^ rotate_right(w[i - 2], 19)
			^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		i++;
	}
}

void		algo_sha(char *str, uint32_t len, t_sha *sha)
{
	uint32_t	new_len;
	uint32_t	*msg;
	uint32_t	bit_len;
	uint32_t 	w[64];
	uint32_t	i;
	
	i = 0;
	msg = init_msg(&bit_len, &new_len, &len);
	ft_memcpy(msg, str, len);
	add_padding(len, msg);
	while (i < new_len * 16)
	{
		msg[i] = swap_bytes_32bit(msg[i]);
		i++;
	}
	add_size(msg, bit_len, new_len);
	len = 0;
	while (len < new_len)
	{
		schedule_array(w, msg, len);
		update_sha_pre(sha);
		sha256_encrypt(sha, w);
		len++;
	}
	free(msg);
}

void		sha256(t_args *args, t_infos *infos, char *str, char *file)
{
	size_t		len;
	t_sha		sha;

	if (infos->len == 0 && str != NULL)
		len = ft_strlen(str);
	else
		len = infos->len;
	init_sha(&sha);
	algo_sha(str, len, &sha);
	(void)file;
	if (args->arg_r)
		args->arg_r = 2;
	if (args->arg_p && !args->arg_q && !args->arg_r)
	{
		args->arg_p = 0;
		ft_printf("%s", str);
	}
	if (args->arg_s && !args->arg_q && !args->arg_r)
	{
		args->arg_s = 0;
		ft_printf("SHA256 (\"%s\") = ", str);
	}
	ft_printf("%.8x%.8x%.8x%.8x%.8x%.8x%.8x%.8x", sha.h0, sha.h1, sha.h2, sha.h3,
	sha.h4, sha.h5, sha.h6, sha.h7);
	if (args->arg_r && args->arg_s && !args->arg_q)
		ft_printf(" \"%s\"", str);
	if (args->arg_r && file != NULL && !args->arg_q)
		ft_printf(" %s", file);
	ft_printf("\n");
}
