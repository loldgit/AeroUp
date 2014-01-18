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
 *       Filename:  rules.hpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  31/12/2013 18:32:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  rules_INC
#define  rules_INC
#include "ruleserror.hpp"
#include "define_ultimate_fct.h"
#include <vector>
#include "global.hpp"
/*
 *        Class:  Rules
 *  Description:  
 */
class Rules
{
  public:
    Rules (std::string gloFileName);    /* constructor */
    void twiceDefsubError(int nb_line);
    void noDefsubError(std::string sub_name);

    bool isStandardCmdPossible(int nb_line, int fct=0);
    bool isDefsubCmdPossible();
    bool isEndPossible();
    bool isSeqOk();

    /* END */
    void setEnd(int nb_line);

    /* DEFSUB */
    void setDefsub(int nb_line);
    void unsetDefsub(int nb_line);
    void endTestDefsub();

    /* LOOP */
    void setloop(int nb_line);
    void unsetloop(int nb_line);

  private:
    struct defsub
    {
      bool on = false;
      int line = 0;
    } ;

    int defsub_cout = 0;
    int loop_count = 0;
    bool end = false;
    std::string fileName;
    std::vector<std::string> FctVectStr = {
          "'C command'",
          "'D command'",
          "'RAMP command'",
          "'L command'",
          "'E command'",
          "'R command'",
          "'G command'",
          "'B command'",
          "'SUB command'",
          "'DEFSUB command'",
          "'ENDSUB command'",
          "'END command'"
    };
}; /* -----  end of class Rules  ----- */

#endif   /* ----- #ifndef rules_INC  ----- */
