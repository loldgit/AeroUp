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
 *       Filename:  gloseq.hpp
 *
 *    Description:  
 *
 *        Version:  0.3.2
 *        Created:  27/12/2013 10:40:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  gloseq_INC
#define  gloseq_INC

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "global.hpp"
#include "buffer.hpp"
#include "buffermanager.hpp"
#include "rules.hpp"
#include "serialprop.hpp"
#include "config.h"

#if HAVE_LIBBOOST_REGEX
  #include "regboost.hpp"
#else
  #include "reglinux.hpp"
#endif


/*
 *        Class:  GloSeq
 *  Description:  Contains all the processing related to the glo file.
 */
class GloSeq
{
  public:
    void verify();
    void upload(SerialProp & ser);

    GloSeq (std::string fileName);  /* constructor      */



  private:
    void cleanLine(std::string& rline);

    const char SP  = 0x20;
    const char TAB = 0x09;
    const char CR  = 0x0d;
    const char LF  = 0x0a;
    const int NOT_VALID = -1;

    std::string file_name;
    std::ifstream glofile;

    struct command
    {
      std::string line;
      int cmd_type;
      int nb_line;
    };
    std::vector <command> cmdTab;


    Buffer buff;
    Rules rules;
    BufferManager buffManager;
    

}; /* -----  end of class GloSeq  ----- */


#endif   /* ----- #ifndef gloseq_INC  ----- */
