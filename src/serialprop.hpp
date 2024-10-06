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
 *       Filename:  serialprop.hpp
 *
 *    Description:  
 *
 *        Version:  0.3.2
 *        Created:  19/12/2013 23:25:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */


#ifndef  serialprop_INC
#define  serialprop_INC
#include "global.hpp"
#include "config.h"

#if HAVE_TERMIOS_H==1
#include "seriallinux.hpp"
/*
 *        Class:  SerialProp
 *  Description:   
 */
class SerialProp : public SerialLinux
{
  public:
    SerialProp (std::string port_name) : SerialLinux(port_name){};    /* constructor */

    void test();
    void start();
    void color(unsigned char red, unsigned char green, unsigned char blue);
    void serialNumber(uint8_t * five);
    std::string getSerial();
}; /* -----  end of class SerialAbs  ----- */


#else      /* -----  not HAVE_TERMIOS_H  ----- */
 #include "serialboost.hpp"
/*
 *        Class:  SerialProp
 *  Description:   
 */
class SerialProp : public SerialBoost
{
  public:
    SerialProp (std::string port_name) : SerialBoost(port_name){};    /* constructor */

    void test();
    void start();
    void color(unsigned char red, unsigned char green, unsigned char blue);
    void serialNumber(uint8_t * five);
    std::string getSerial();
}; /* -----  end of class SerialAbs  ----- */
#endif     /* -----  not HAVE_TERMIOS_H  ----- */

#endif   /* ----- #ifndef serialabs_INC  ----- */
