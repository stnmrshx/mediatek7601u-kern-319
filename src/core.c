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

int mt7601u_wait_asic_ready(struct mt7601u_dev *dev)
{
	int i = 100;
	u32 val;

	do {
		if (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			return -EIO;

		val = mt7601u_rr(dev, MT_MAC_CSR0);
		if (val && ~val)
			return 0;

		udelay(10);
	} while (i--);
	return -EIO;
}

bool mt76_poll(struct mt7601u_dev *dev, u32 offset, u32 mask, u32 val, int timeout)
{
	u32 cur;
	timeout /= 10;
	do {
		if (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			return false;

		cur = mt7601u_rr(dev, offset) & mask;
		if (cur == val)
			return true;

		udelay(10);
	} while (timeout-- > 0);

	dev_err(dev->dev, "Error: Time out with reg %08x\n", offset);
	return false;
}

bool mt76_poll_msec(struct mt7601u_dev *dev, u32 offset, u32 mask, u32 val, int timeout)
{
	u32 cur;
	timeout /= 10;
	do {
		if (test_bit(MT7601U_STATE_REMOVED, &dev->state))
			return false;

		cur = mt7601u_rr(dev, offset) & mask;
		if (cur == val)
			return true;

		msleep(10);
	} while (timeout-- > 0);

	dev_err(dev->dev, "Error: Time out with reg %08x\n", offset);
	return false;
}