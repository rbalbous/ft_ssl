/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 15:09:07 by rbalbous          #+#    #+#             */
/*   Updated: 2020/10/10 15:13:46 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		update_hash_md5_pre(t_hash *hash)
{
	hash->aa = hash->a;
	hash->bb = hash->b;
	hash->cc = hash->c;
	hash->dd = hash->d;
}

void		update_hash_md5_post(t_hash *hash)
{
	hash->a += hash->aa;
	hash->b += hash->bb;
	hash->c += hash->cc;
	hash->d += hash->dd;
}

void		init_hash_md5(t_hash *hash)
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

uint32_t	rotate_left(uint32_t x, uint32_t c)
{
	x = (((x) << (c)) | ((x) >> (32 - (c))));
	return (x);
}

void		md5_ops(int i, uint32_t *fghi, uint32_t *g, t_hash *hash)
{
	if (i < 16)
	{
		*fghi = (hash->bb & hash->cc) | ((~hash->bb) & hash->dd);
		*g = i;
	}
	else if (i < 32)
	{
		*fghi = (hash->dd & hash->bb) | ((hash->cc) & (~hash->dd));
		*g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		*fghi = hash->bb ^ hash->cc ^ hash->dd;
		*g = (3 * i + 5) % 16;
	}
	else if (i < 64)
	{
		*fghi = hash->cc ^ (hash->bb | (~hash->dd));
		*g = (7 * i) % 16;
	}
}
