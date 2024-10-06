README for AeroUp 0.3.2
=======================


AeroUp is an open source tool to control the "old" but brave Ultimate (programmable light sequencing juggling props) from Aerotech Projects on GNU/Linux.


Features 
========
* Start command 
* Test command
* Color command
* Get Serial Number command
* Set Serial Number command
* Upload glo sequences command
* Improved driver (udev linux)
* Checks syntax of .glo files  
* And more...


Installation
============
```
 git clone https://github.com/LaurentBa/AeroUp.git
 cd AeroUp
 ./configure
 make
 sudo make install
```

If you have boost library it will use it.
But it should not be a problem if you don't have it.


Documentation
=============
```
man aeroup 
```
A text version is available in the sources :
https://git.larueluberlu.net/AeroUp/tree/man/aeroup.man.txt


Exemple
=======
```
# Test prop on /dev/ttyACM0
aeroup -t /dev/ttyACM0

# Start props on /dev/ttyACM0 et /dev/tty/ACM1 and test /dev/tty/ACM3
aeroup -o /dev/ttyACM0 -o /dev/ttyACM1 -t /dev/ttyACM3

# Set color to blue and red
aeroup -c O,O,255,/dev/ttyACM0 255,0,0,/dev/ttyACM1

# Upload file.glo to /devttyACMO
aeroup -u /path/to/file.glo,/dev/ttyACM0

# Set serial number 0x7002 to have a prop named Poi2
aeroup -S 0x7002,/dev/ttyACM0

# Verify your serial number is now : 0x7002
aeroup -G /dev/ttyACM0

# Verify your serial name is Poi2
aeroup -k /dev/ttyACM0
```


Links
=====
* Git page : https://git.larueluberlu.net/AeroUp
* Cie La rue Luberlu : https://larueluberlu.net

