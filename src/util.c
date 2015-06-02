/*
** Copyright (c) 2015 StnMrshx <stnmrshx@gmail.com>.
** 
** This program is free software; you can redistribute it and/or
** modify it under the terms of the GNU General Public License
** as published by the Free Software Foundation; either version 2
** of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**/
#include "../include/mt7601u.h"

void mt76_remove_hdr_pad(struct sk_buff *skb)
{
	int len = ieee80211_get_hdrlen_from_skb(skb);
	memmove(skb->data + 2, skb->data, len);
	skb_pull(skb, 2);
}

int mt76_insert_hdr_pad(struct sk_buff *skb)
{
	int len = ieee80211_get_hdrlen_from_skb(skb);
	int ret;

	if (len % 4 == 0)
		return 0;

	ret = skb_cow(skb, 2);
	if (ret)
		return ret;

	skb_push(skb, 2);
	memmove(skb->data, skb->data + 2, len);
	skb->data[len] = 0;
	skb->data[len + 1] = 0;
	return 0;
}