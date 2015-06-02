# mediatek7601u-kern-319
Driver Mediatek 7601u usb wifi

A.K.A

USB WIFI TPLINK TL-WN727N

$ git clone https://github.com/stnmrshx/mediatek7601u-kern-319.git
$ cd mediatek7601u-kern-319
$ sudo cp firmware/MT7601.bin /lib/firmware/mt7601u.bin
$ make
$ sudo modprobe mac80211
$ sudo insmod ./mt7601u.ko