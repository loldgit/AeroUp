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
 *       Filename:  Symlink.cpp
 *
 *    Description:  Return a beautiful Symlink for udev
 *
 *        Version:  0.3.2
 *        Created:  19/01/2014 14:51:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#include "symlink.hpp"

static  uint32_t serialNumber;
static  uint8_t id_prob;
static  uint8_t num;
static  std::stringstream ss;

const uint8_t BALL  = 0x62; // 'b'
const uint8_t STAFF = 0x73; // 's'
const uint8_t CLUB  = 0x63; // 'c'
const uint8_t POI   = 0x70; // 'p'
const uint32_t PROB_MASK = 0x0000ff00;
const uint32_t NUM_MASK  = 0x000000ff;

 /* 
  *         Name:  Symlink::getSym
  *  Description:  return Symlink 
  */
  std::string
Symlink::getSym(std::string serial_str)
{
  /* test entry */
  if(EOF == sscanf(serial_str.c_str(), "%d", &serialNumber))
  {
    throw Symlink::Bad_Symlink();
  }
  //if (serialNumber > 0xffffffff)
  if (serialNumber > 0xffffffff)
  {
    throw Symlink::Bad_Symlink();
  }

  ss << std::hex << serial_str ;
  ss >> serialNumber;

  if((serialNumber & 0xffff0000) != 0)
    Symlink::badSerNum();

  id_prob = ((PROB_MASK & serialNumber) >> 8 );
  num = (NUM_MASK & serialNumber);

  ss << num;
  std::string x;
  ss >> x;
  std::cout << x;
  
  // now we use serial_str for output
  serial_str = Symlink::whatProp(id_prob);
  serial_str += std::to_string(num);
    
  return serial_str;
}


 /* 
  *         Name:  Symlink::whatProp
  *  Description:  send error ( for future) 
  */
  void
Symlink::badSerNum()
{
  throw Symlink::Bad_Symlink();
  
}


 /* 
  *         Name:  Symlink::whatProp
  *  Description:  addr to symlink 
  */
  std::string
Symlink::whatProp(uint8_t id)
{
  switch (id)
  {
    case BALL:	
      return "Ball";
    break;

    case STAFF:	
      return "Staff";
    break;

    case CLUB:
      return "Club";
    break;

    case POI:	
      return "Poi";
    break;

    default:	
    //UdevLink::badSerNum();
      return "AeroProb";
    break;
  }	/* -----  end switch  ----- */
}
