# mediatek7601u-kern-319
Driver Mediatek 7601u usb wifi

A.K.A

USB WIFI TPLINK TL-WN727N

Iniiiih penampakannyaaaah
<img src="http://www.tp-link.com/resources/images/products/gallery/TL-WN727N-01.jpg" style="text-align:left;"/>

$ git clone https://github.com/stnmrshx/mediatek7601u-kern-319.git <br />
$ cd mediatek7601u-kern-319<br />
$ sudo cp firmware/MT7601.bin /lib/firmware/mt7601u.bin<br />
$ make<br />
$ sudo modprobe mac80211<br />
$ sudo insmod ./mt7601u.ko<br />