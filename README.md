README for AeroUp 0.2
=====================


AeroUp is an open source and multiplatform tool to control Ultimate (programmable light sequencing juggling props) from Aerotech Projects.

There is not yet support for microsoft Window, because as i working on the core part who'll become a shared lib,
and there is no support for getoptlong for Window, as a Qt gui is scheduled soon, i don't bother me.  


Features 
========
* Start command 
* Test command
* Color command
* Get Serial Number command
* Set Serial Number command
* Upload glo sequences command
* checks syntax of .glo files  

multithread, multiplatform gui,  and some others original features coming soon...


Installation
============
```
 cd AeroUp
 ./configure
 sudo make install
```

if you have boost library it will use it.
but it should not be a problem if you don't have it.

Documentation
=============
man aeroup 
or look at the man folder.

Links
=====
* Github page : https://github.com/LaurentBa/AeroUp
* http://www.aerotechprojects.com/index.htm

note : there will be no support for microsoft Window before version 1  

