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
 *       Filename:  reglinux.cpp
 *
 *    Description:  Regex lib (linux version) 
 *
 *        Version:  0.3.0.1
 *        Created:  18/01/2014 01:16:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */
#include <stdlib.h>
#include "reglinux.hpp"

/*
 *       Class:  RegLinux
 *      Method:  RegLinux :: RegLinux
 * Description:  Constructor
 */
RegLinux::RegLinux()
{
    comp();
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RegLinux
 *      Method:  RegLinux :: comp
 * Description:  Compile Regex
 *--------------------------------------------------------------------------------------
 */
    void
RegLinux::comp(void)
{
    int err = regcomp (reg, str_regex[0], REG_NOSUB | REG_EXTENDED);
    if (err != 0)
    {
       printf("ERROR");
       exit (EXIT_FAILURE);
    }

    for (int i = 0; i < REG_TAB_LEN  ; i++, preg++)
    {

       err = regcomp (preg, str_regex[i], REG_NOSUB | REG_EXTENDED);
       if (err != 0)
       {
           printf("ERROR");
           exit (EXIT_FAILURE);
       }
    }
}


/*
 *--------------------------------------------------------------------------------------
 *       Class:  RegLinux
 *      Method:  RegLinux :: isValidSyntax
 * Description:  Compile Regex
 *--------------------------------------------------------------------------------------
 */
  int
RegLinux::isValidSyntax ( std::string &rline )
{
  preg = &reg[0];
  int match;
  for (int i = 0; i < REG_TAB_LEN; i++, preg++)
  {
    match = regexec (preg, rline.c_str(), 0, NULL, 0);
    if (match == 0)
      return i;
  }
  return -1;
}		/* -----  end of method RegLinux::isValidSyntax  ----- */


