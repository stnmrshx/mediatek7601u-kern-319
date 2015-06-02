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
#ifndef __MT7601U_DMA_H
#define __MT7601U_DMA_H

#include <asm/unaligned.h>
#include <linux/skbuff.h>

#include "util.h"

#define MT_DMA_HDR_LEN			4
#define MT_RX_INFO_LEN			4
#define MT_FCE_INFO_LEN			4
#define MT_DMA_HDRS			(MT_DMA_HDR_LEN + MT_RX_INFO_LEN)

#define MT_TXD_INFO_LEN			GENMASK(15, 0)
#define MT_TXD_INFO_D_PORT		GENMASK(29, 27)
#define MT_TXD_INFO_TYPE		GENMASK(31, 30)

enum mt76_msg_port {
	WLAN_PORT,
	CPU_RX_PORT,
	CPU_TX_PORT,
	HOST_PORT,
	VIRTUAL_CPU_RX_PORT,
	VIRTUAL_CPU_TX_PORT,
	DISCARD,
};

enum mt76_info_type {
	DMA_PACKET,
	DMA_COMMAND,
};

#define MT_TXD_PKT_INFO_NEXT_VLD	BIT(16)
#define MT_TXD_PKT_INFO_TX_BURST	BIT(17)
#define MT_TXD_PKT_INFO_80211		BIT(19)
#define MT_TXD_PKT_INFO_TSO		BIT(20)
#define MT_TXD_PKT_INFO_CSO		BIT(21)
#define MT_TXD_PKT_INFO_WIV		BIT(24)
#define MT_TXD_PKT_INFO_QSEL		GENMASK(26, 25)

enum mt76_qsel {
	MT_QSEL_MGMT,
	MT_QSEL_HCCA,
	MT_QSEL_EDCA,
	MT_QSEL_EDCA_2,
};

#define MT_TXD_CMD_INFO_SEQ		GENMASK(19, 16)
#define MT_TXD_CMD_INFO_TYPE		GENMASK(26, 20)

static inline int mt7601u_dma_skb_wrap(struct sk_buff *skb, enum mt76_msg_port d_port, enum mt76_info_type type, u32 flags)
{
	u32 info;

	info = flags | 
		MT76_SET(MT_TXD_INFO_LEN, round_up(skb->len, 4)) | 
		MT76_SET(MT_TXD_INFO_D_PORT, d_port) | 
		MT76_SET(MT_TXD_INFO_TYPE, type);
	put_unaligned_le32(info, skb_push(skb, sizeof(info)));
	return skb_put_padto(skb, round_up(skb->len, 4) + 4);
}

static inline int mt7601u_dma_skb_wrap_pkt(struct sk_buff *skb, enum mt76_qsel qsel, u32 flags)
{
	flags |= MT76_SET(MT_TXD_PKT_INFO_QSEL, qsel);
	return mt7601u_dma_skb_wrap(skb, WLAN_PORT, DMA_PACKET, flags);
}

#define MT_RXD_INFO_LEN			GENMASK(13, 0)
#define MT_RXD_INFO_PCIE_INTR		BIT(24)
#define MT_RXD_INFO_QSEL		GENMASK(26, 25)
#define MT_RXD_INFO_PORT		GENMASK(29, 27)
#define MT_RXD_INFO_TYPE		GENMASK(31, 30)
#define MT_RXD_PKT_INFO_UDP_ERR		BIT(16)
#define MT_RXD_PKT_INFO_TCP_ERR		BIT(17)
#define MT_RXD_PKT_INFO_IP_ERR		BIT(18)
#define MT_RXD_PKT_INFO_PKT_80211	BIT(19)
#define MT_RXD_PKT_INFO_L3L4_DONE	BIT(20)
#define MT_RXD_PKT_INFO_MAC_LEN		GENMASK(23, 21)
#define MT_RXD_CMD_INFO_SELF_GEN	BIT(15)
#define MT_RXD_CMD_INFO_CMD_SEQ		GENMASK(19, 16)
#define MT_RXD_CMD_INFO_EVT_TYPE	GENMASK(23, 20)

enum mt76_evt_type {
	CMD_DONE,
	CMD_ERROR,
	CMD_RETRY,
	EVENT_PWR_RSP,
	EVENT_WOW_RSP,
	EVENT_CARRIER_DETECT_RSP,
	EVENT_DFS_DETECT_RSP,
};

#endif