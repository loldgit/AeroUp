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
 *       Filename:  main.hpp
 *
 *    Description:  
 *
 *        Version:  0.3.0
 *        Created:  21/12/2013 03:56:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  main_INC
#define  main_INC

#define TEST_FLAG          0x1
#define START_FLAG         0x2
#define GET_SERIAL_FLAG    0x4
#define SET_SERIAL_FLAG    0x8
#define UPLOAD_GLO_FLAG   0x10
#define UPLOAD_GLOC_FLAG  0x20
#define VERBOSSE_FLAG     0x40
#define VERIFY_FLAG       0x80
#define MAKE_GLOC_FLAG   0x100
#define FLAG1 0x100

void aeroHelp();
void aeroVersion();

#endif   /* ----- #ifndef main_INC  ----- */
