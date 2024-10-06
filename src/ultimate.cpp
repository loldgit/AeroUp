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
 *       Filename:  ultimatecmd.cpp
 *
 *    Description:  Interface for Ultimate props
 *
 *        Version:  0.3.2
 *        Created:  19/12/2013 20:28:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */
#include <stdlib.h>
#include "ultimate.hpp"

extern bool VERBOSE_AERO;

using namespace std;   

Ultimate::Ultimate ( string serial_name ):
          ser(serial_name)
{
}		/* -----  end of constructor  ----- */


/*
 *       Class:  Ultimate
 *      Method:  Ultimate :: test
 * Description:  
 */
void Ultimate::test ()
{
  ser.test();
}

/*
 *       Class:  Ultimate
 *      Method:  Ultimate :: start
 * Description:  
 */
  void
Ultimate::start ()
{
  ser.start();
}

/*
 *       Class:  Ultimate
 *      Method:  Ultimate :: color
 * Description:  
 */
  void
Ultimate::color (unsigned char red, unsigned char green, unsigned char blue)
{
  ser.color(red, green, blue);
}

/*
 *       Class:  Ultimate
 *      Method:  Ultimate :: getSerial
 * Description:  
 */
  string
Ultimate::getSerial ()
{
  string nb = ser.getSerial();
  return nb;
}

/*
 *       Class:  Ultimate
 *      Method:  Ultimate :: uploadGloc
 * Description:  
 */
  int
Ultimate::uploadGloc ( string filename)
{
  return sizeof(filename);
}	

/*
 *       Class:  Ultimate
 *      Method:  Ultimate :: uploadGlo
 * Description:  
 */
  int
Ultimate::uploadGlo ( string fileName)
{
  GloSeq file(fileName);
  file.verify();
  // to do add security
  file.upload(ser);
  return sizeof(fileName);
}

/*
 *       Class:  Ultimate
 *      Method:  Ultimate :: setSerialUlt
 * Description:  
 */
  uint32_t
Ultimate::setSerialUlt(uint32_t serialNumber)
{
  uint8_t ser_nb[6] = {83,0,0,0,0,0};
  
  ser_nb[4] = (uint8_t)((serialNumber & 0xff000000UL) >> 24);
  ser_nb[3] = (uint8_t)((serialNumber & 0x00ff0000UL) >> 16);
  ser_nb[2] = (uint8_t)((serialNumber & 0x0000ff00UL) >>  8);
  ser_nb[1] = (uint8_t)((serialNumber & 0x000000ffUL)      );

  ser.serialNumber(ser_nb) ;

  return serialNumber;

  //exit (EXIT_FAILURE);

}
