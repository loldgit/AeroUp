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
 *       Filename:  gloInterface.hpp
 *
 *    Description:  
 *
 *        Version:  0.3.0  
 *        Created:  11/01/2014 14:03:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  gloInterface_INC
#define  gloInterface_INC



#include "global.hpp"
#include "gloseq.hpp"


/*
 *        Class: GloInterface
 *  Description:  
 */
class GloInterface
{
  public:
    GloInterface(){;}    /* constructor */

    int verifyFile( std::string fileName)
    {
      GloSeq file(fileName);
      file.verify();
      return (1); // tempory implementaion return 
    }


  private:

}; /* -----  end of class Editor  ----- */

#endif
