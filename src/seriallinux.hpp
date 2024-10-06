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
 *       Filename:  seriallinux.hpp
 *
 *    Description:  Serial lib linux (termios version)
 *                  used if haven't boost
 *
 *        Version:  0.3.2
 *        Created:  17/01/2014 03:31:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */


#ifndef  seriallinux_INC
#define  seriallinux_INC

#ifndef DEF_SERIAL
#define DEF_SERIAL

#include <termios.h>
#include <unistd.h>
#include "global.hpp"


class SerialLinux
{
  public:
    SerialLinux(std::string dev);
    ~SerialLinux();
    void sendChar(char c);
    void sendString(uint8_t *c, int n);
    std::string readLine();
    void fclose();
  
  private:
    void setspeed(speed_t vitesse);
    int nb_read;
    struct termios tio, old_tio;
    int fd;

};
#endif


#endif   /* ----- #ifndef seriallinux_INC  ----- */
