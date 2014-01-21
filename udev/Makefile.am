#IS_UDEV_DIR=$(call test uname -e /etc/udev/rules.d)
echo 'print: ; @echo "$(VAR)"' | make -f Makefile -f - print

if UDEV
udevdir=/etc/udev/rules.d
udev_DATA=60-aeroup.rules
endif

