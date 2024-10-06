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
 *       Filename:  rules.cpp
 *
 *    Description:  
 *
 *        Version:  0.3.2
 *        Created:  31/12/2013 18:33:14
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 *
 */
#include "rules.hpp"

using namespace std;

/*
 *       Class:  Rules
 *      Method:  Rules
 * Description:  constructor
 */
Rules::Rules (string gloFileName):
  fileName(gloFileName)
{
}  /* -----  end of method Rules::Rules  (constructor)  ----- */

  bool 
Rules::isStandardCmdPossible(int nb_line, int fct)
{
  if(!end || defsub_cout )
    return true;
  else
  {
    string error = "invalid " + FctVectStr[fct] + " not in main sequence or sub-sequence"; 
    throw RulesError( error.c_str() , fileName, nb_line );
    return false;
  }
}
  bool
Rules::isDefsubCmdPossible()
{

  return true;
}
  bool
Rules::isEndPossible()
{

  return true;
}

  bool
Rules::isSeqOk()
{
  return true;

}


  void
Rules::setEnd(int nb_line)
{
  if(!end && !loop_count)
    end = true;
  else
  {
    if(end)
    {
      string error = "Attempt to define more than one 'END command'"; 
      throw RulesError(error.c_str(), fileName, nb_line );
    }
    else
    {
      string error = "Reached end of main sequence with unterminated loop"; 
      throw RulesError(error.c_str(), fileName, nb_line );
    }
  }
}

  void
Rules::setDefsub(int nb_line)
{
  if(!defsub_cout && end)
  {
    defsub_cout = nb_line;
  }
  else
  { 
    if(!end)
    {
      string error = "Attempt to define subsequence before the main sequence is complete "; 
      throw RulesError(error.c_str(), fileName, nb_line );
    }
    else
    {
      string error = "Attempting to define a subroutine inside another subroutine' "; 
      throw RulesError(error.c_str(), fileName, nb_line );
    }
  }
}

  void
Rules::unsetDefsub(int nb_line)
{
  if(defsub_cout && !loop_count)
  {
    defsub_cout = 0;
  }
  else 
  {
    if (!defsub_cout)
    {
      string error = "ENDSUB without corresponding DEFSUB command"; 
      throw RulesError(error.c_str(), fileName, nb_line );
    }
    else
    {
      string error = "'ENDSUB command' found with unterminated 'Loop command'"; 
      throw RulesError(error.c_str(), fileName, nb_line );
    }
  }
}

  void
Rules::endTestDefsub()
{
  if (defsub_cout)
  {
    string error = "Reached EOF with unterminated 'DEFSUB command'";
    throw RulesError(error.c_str(), fileName, defsub_cout);
  }
}



  void
Rules::setloop(int nb_line)
{
  isStandardCmdPossible(nb_line, L_FCT);
  loop_count +=1;
}

  void
Rules::unsetloop(int nb_line)
{
  isStandardCmdPossible(nb_line, E_FCT);
  if (loop_count > 0)
    loop_count -=1;
  else
  {
    string error = "End Loop command with no Loop Command"; 
    throw RulesError(error.c_str(), fileName, nb_line );
  }
}



/*
 *       Class:  Rules
 *      Method:  Rules :: twiceDefsubError
 * Description:  
 */
  void
Rules::twiceDefsubError(int nb_line)
{
    // to do : add class warning
    throw RulesError("Error, more than one definition for a sub function !", fileName, nb_line );

}		/* -----  end of method Rules::twiceDefsubError  ----- */

  void
Rules::noDefsubError(string sub_name)
{
    string error = "No definition for SUB," + sub_name ; 
    throw RulesError(error.c_str(), fileName);

}

