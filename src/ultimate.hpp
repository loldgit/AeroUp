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
 *       Filename:  ultimatecmd.hpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  19/12/2013 20:28:34
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  ultimate_INC
#define  ultimate_INC

#include <string>
#include "global.hpp"
#include "serialprop.hpp"
#include "gloseq.hpp"


/*
 *        Class:  Ultimate
 *  Description:  Ultimate interface, access to all commands used by your props
 */
class Ultimate
{
  public:
    Ultimate (std::string serial_name);    /* constructor */

    void start();
    void test();
    void color(unsigned char red,
               unsigned char green,
               unsigned char blue);
    std::string getSerial();
    int uploadGlo(std::string file_name);
    int uploadGloc(std::string file_name);
    uint32_t setSerialUlt(uint32_t serialNumber);

  private:
    SerialProp ser;

}; /* -----  end of class UltimateCmd  ----- */

#endif   /* ----- #ifndef ultimatecmd_INC  ----- */
