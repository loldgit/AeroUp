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
 *       Filename:  Symlink.hpp
 *
 *    Description:  Return a beautiful Symlink for udev
 *
 *        Version:  0.3.2
 *        Created:  19/01/2014 14:51:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  Symlink_INC
#define  Symlink_INC

#include <stdlib.h>
#include <string>
#include <exception>
#include <sstream> 
#include <unistd.h>
#include <iostream>

/* 
 *         Name:  Symlink
 *  Description:  Symlink declaration
 */
namespace Symlink
{
//  extern uint16_t BALL;
//  extern uint16_t STAFF;
//  extern uint16_t CLUB;
//  extern uint16_t POI;



//  const uint32_t PROB_MASK;
//  const uint32_t NUM_MASK;

  std::string getSym(std::string serial_str);
  std::string whatProp(uint8_t id);
  void badSerNum();

  class Bad_Symlink{};
}

#endif   /* ----- #ifndef symlink_INC  ----- */
