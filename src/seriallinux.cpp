/*
    Copyright (C) 2014 BARRATERO Laurent                                   

    AeroUp is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by 
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    Aeroup is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. 
*/

/*
 *       Filename:  seriallinux.cpp
 *
 *    Description:  Serial lib linux (termios version)
 *                  used if haven't boost
 *
 *        Version:  0.3.0
 *        Created:  17/01/2014 03:31:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <iostream>
#include <pthread.h>

#include "seriallinux.hpp"


using namespace std;

/*
 *        Class:  SerialLinux
 *  Description:  open/write to serial port
 */
SerialLinux::SerialLinux(std::string dev)
    {
      memset(&tio,0,sizeof(tio));
      tio.c_iflag= IGNPAR ;
      tio.c_oflag=0;
      tio.c_cflag= CS8|CREAD|CLOCAL ;
      tio.c_lflag=0;
      tio.c_cc[VMIN]=1;
      tio.c_cc[VTIME]=0;
      
      fd = open( dev.c_str(), O_RDWR  | O_NOCTTY);      
      if(fd < 0)
      {
        perror("open");
        printf("file => %s\n", dev.c_str());
        exit(EXIT_FAILURE);
      }

      tcgetattr(fd,&old_tio);
      tcflush(fd, TCIFLUSH);
      cfsetospeed(&tio, B19200);            
      cfsetispeed(&tio, B19200);
      tcsetattr(fd,TCSANOW,&tio);

    }

SerialLinux::~SerialLinux()
{
  tcsetattr(fd,TCSANOW,&old_tio);
  fclose();
}

  void
SerialLinux::sendChar(char c)
{
  write(fd,&c,1);
}

  void
SerialLinux::sendString(uint8_t *c, int n)
{
      write(fd, c, n);
}

  string
SerialLinux::readLine()
{
  char c[] = {0,0};
  string result;
    for(;;)
    {
      nb_read = read(fd, c, 1);
      switch(c[0])
      {
        case '\r':
          break;
        case '\n':
          return result;
        default:
          result+=c[0];
       }
    }
}

  void
SerialLinux::fclose()
{
  if (close(fd)<0)
  {
    perror("close");
    exit(EXIT_FAILURE);
  }
} 


  void 
SerialLinux::setspeed(speed_t vitesse)
{
  cfsetospeed(&tio, vitesse);            
  cfsetispeed(&tio, vitesse);
  tcsetattr(fd,TCSANOW,&tio);
}




