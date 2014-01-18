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
 *       Filename:  buffer.hpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  28/12/2013 07:01:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  buffer_INC
#define  buffer_INC

#define BUFF_SIZE_MAX 8959
//#define SIZE_MAX_OVER 20000 


#include "global.hpp"
#include <map>
#include <vector>

class Buffer
{
public:
    Buffer();
    int addChr(unsigned char val);
    void addSubPos(std::string subName);
    int addDefsubPos(std::string defsubName);
    std::string addDefsubToBuff();
    void printSubPos();
    void printDefsubPos();
    void printBuff(void) const;
    // SIZE
    unsigned short int getSize(void) const { return size;}
    unsigned char * pointToBuff(){return buff;}
    unsigned char* getSizeUpCmd();
    

private:
    void setSize(unsigned short int val) {size = val ;}
    void verify_size(void);
    unsigned short int size;
    uint8_t lsb_msb[3];

    // metre une variable pour 80
    uint8_t buff[BUFF_SIZE_MAX];
    std::map <std::string, std::vector<int> > sub_position; 
    std::map <std::string, uint8_t[2]> defsub_position;
};


#endif   /* ----- #ifndef buffer_INC  ----- */
