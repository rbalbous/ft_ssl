/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 20:12:07 by rbalbous          #+#    #+#             */
/*   Updated: 2019/06/13 01:01:42 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned int g_r[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7,
	12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5,
	9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4,
	11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6,
	10, 15, 21
};

unsigned int g_x[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void		init_hash(t_hash *hash)
{
	hash->a = 0x67452301;
	hash->b = 0xefcdab89;
	hash->c = 0x98badcfe;
	hash->d = 0x10325476;
	hash->aa = hash->a;
	hash->bb = hash->b;
	hash->cc = hash->c;
	hash->dd = hash->d;
}

unsigned int	rotate_left(unsigned int x, unsigned int c)
{
	x = (((x) << (c)) | ((x) >> (32 - (c))));
	return (x);
}

void			md5_encrypt(t_hash *hash, unsigned int *w)
{
	unsigned int fghi;
	unsigned int g;
	unsigned int i;
	unsigned int tmp;

	g = 0;
	i = 0;
	tmp = 0;
	fghi = 0;
	while (i < 64)
	{
		if (i < 16)
		{
			fghi = (hash->bb & hash->cc) | ((~hash->bb) & hash->dd);
			g = i;
		}
		else if (i < 32)
		{
			fghi = (hash->dd & hash->bb) | ((hash->cc) & (~hash->dd));
			g = (5 * i + 1) % 16;
		}
		else if (i < 48)
		{
			fghi = hash->bb ^ hash->cc ^ hash->dd;
			g = (3 * i + 5) % 16;
		}
		else if (i < 64)
		{
			fghi = hash->cc ^ (hash->bb | (~hash->dd));
			g = (7 * i) % 16;
		}
		tmp = hash->dd;
		hash->dd = hash->cc;
		hash->cc = hash->bb;
        printf("rotateLeft(%x + %x + %x + %x, %d)\n", hash->aa, fghi, g_x[i], w[g], g_r[i]);
		hash->bb = hash->bb + rotate_left(hash->aa + fghi + g_x[i] + w[g], g_r[i]);
		hash->aa = tmp;
		i++;
	}
}

void		md5(char *str, int len, t_hash *hash)
{
	int				new_len;
	unsigned char	*msg;
	unsigned int	bit_len;
	int		offset;
	unsigned int *w;

	msg = NULL;
	w = 0;
	bit_len = len * 8;
	new_len = bit_len + 1;
	offset = 0;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	msg = ft_memalloc(new_len + 64);
	ft_memcpy(msg, str, len);
	msg[len] = 128;
 	ft_memcpy(msg + new_len, &bit_len, 4);
	while (offset < new_len)
	{
		w = (unsigned int *)(msg + offset);
		md5_encrypt(hash, w);
		offset += 64;
	}
	free(msg);
}

void		algo_md5(t_args *args, char *str)
{
	size_t		len;
	t_hash		hash;
	unsigned char *p;

	(void)args;
	hash = (t_hash){0, 0, 0, 0, 0, 0, 0, 0};
	len = ft_strlen(str);
	init_hash(&hash);
	md5(str, len, &hash);
	hash.a += hash.aa;
	hash.b += hash.bb;
	hash.c += hash.cc;
	hash.d += hash.dd;
	if (args->arg_s && !args->arg_q)
		ft_printf("MD5 (\"%s\") = ", str);
	p=(unsigned char *)&hash.a;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(unsigned char *)&hash.b;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(unsigned char *)&hash.c;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
    p=(unsigned char *)&hash.d;
    ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	ft_printf("\n");
}
