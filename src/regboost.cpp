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
 *       Filename:  regboost.cpp
 *
 *    Description:  
 *
 *        Version:  0.3.2
 *        Created:  19/12/2013 05:22:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 *
 */
#include "regboost.hpp"


using namespace std;
//using namespace boost;

RegBoost::RegBoost (  )
{
}		/* -----  end of method RegBoost::RegBoost  ----- */



  int
RegBoost::isValidSyntax ( string &rline )
{
  for (int i = 0; i < REG_TAB_LEN; i++)
  {
    if ( boost::regex_match(rline.begin(), rline.end(), reg_tab[i]) ) 
    {
      #ifdef DEBUG
      cout << rline << " -> ok" << endl;
      #endif
      return i;
    }
  }
  return -1;

}		/* -----  end of method RegBoost::isValidSyntax  ----- */


