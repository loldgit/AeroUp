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
 *       Filename:  serialprop.cpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  21/12/2013 01:39:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#include "serialprop.hpp"

using namespace std;


  void 
SerialProp::start()
{
  sendChar('o');
}

  void 
SerialProp::test()
{
  sendChar('t');
}

  void 
SerialProp::color(unsigned char red, unsigned char green, unsigned char blue )
{
  unsigned char rgb[5] = { 'c', red, green, blue, '\0'};
  sendString(rgb, 4);
}

  void 
SerialProp::serialNumber(uint8_t * five)
{
  sendString(five, 5);
}

  string
SerialProp::getSerial()
{
  string line;
  sendChar('G');
  line = readLine();
  return line.erase(0,13);
}
