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
 *       Filename:  buffermanager.cpp
 *
 *    Description:  take the parsed, tokenized lines and manage them.
 *                  send also some rules test
 *
 *        Version:  0.3.0
 *        Created:  30/12/2013 12:12:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#include "buffermanager.hpp"

using namespace std;


/*
 *       Class:  BufferManager
 *      Method:  BufferManager
 * Description:  constructor
 */

BufferManager::BufferManager (Buffer* theBuff, Rules* theRules):
                    buff(theBuff),
                    rules(theRules)
{
} 

/*
 *       Class:  BufferManager
 *      Method:  completesCreateCommand
 * Description:  Second pass to buff, Completes createCommand work
 */
  void
BufferManager::completesCreateCommand()
{
  verifyEndFileError();
  addDefsubToBuff();
}

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: verifyEndFileError
 * Description:  Verification which require that EOF is reached
 *               executed after the multiple call
 *               to the createCommand function by GloSeq instance.
 */
  void
BufferManager::verifyEndFileError()
{
  /* verify there is no DEFSUB without ENDSUB before EOF */
  rules->endTestDefsub();

}

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: addDefsubToBuff
 * Description:  adds the defsub adress to every sub of the buffer 
 */
  void
BufferManager::addDefsubToBuff()
{
  string sub_name = buff->addDefsubToBuff();
  /* If a sub is not defined, we throw an error */
  if(!sub_name.empty())
  {
    rules->noDefsubError(sub_name);
  }
}

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: createCommand
 * Description:  fills the buffer with a token line 
 */

  void
BufferManager::createCommand (vector <string> tokens, int cmd_type, int nb_line)
{

  switch (cmd_type) {

    case C_FCT:	
      rules->isStandardCmdPossible(nb_line, C_FCT);
      colorsFillBuff(tokens);
      break;

    case D_FCT:	
      rules->isStandardCmdPossible(nb_line, D_FCT);
      delayFillBuff(tokens);
      break;

    case RAMP_FCT:	
      rules->isStandardCmdPossible(nb_line, RAMP_FCT);
      rampFillBuff(tokens);
      break;

    case L_FCT:	
      rules->setloop(nb_line);
      loopFillBuff(tokens);
      break;

    case E_FCT:	
      rules->unsetloop(nb_line);
      oneByteFillBuff(E_CMD);
      break;

    case R_FCT:	
      rules->isStandardCmdPossible(nb_line, R_FCT);
      oneColorFillBuff(tokens, R_CMD);
      break;

    case G_FCT:	
      rules->isStandardCmdPossible(nb_line, G_FCT);
      oneColorFillBuff(tokens, G_CMD);
      break;

    case B_FCT:	
      rules->isStandardCmdPossible(nb_line, B_FCT);
      oneColorFillBuff(tokens, B_CMD);
      break;

    case SUB_FCT:	
      rules->isStandardCmdPossible(nb_line, SUB_FCT);
      subFillBuff(tokens);
      break;

    case DEFSUB_FCT:	
      rules->setDefsub(nb_line);
      defsubFillBuff(tokens, nb_line);
      break;

    case ENDSUB_FCT:	
      rules->unsetDefsub(nb_line);
      oneByteFillBuff(ENDSUB_CMD);
      break;

    case END_FCT:	
      rules->setEnd(nb_line);
      oneByteFillBuff(END_CMD);
      break;
  }				/* -----  end switch  ----- */
  return ;
}		/* -----  end of method BufferManager::createCommand  ----- */



/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: oneColorFillBuff
 * Description:  ( *FillBuff function ) generic method for R, G, B commands 
 */

  void
BufferManager::oneColorFillBuff(vector <string> tokens, int col)
{
  buff->addChr(col);
  buffAddOneColor(tokens[1]);
}


/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: ColorFillBuff
 * Description:  ( *FillBuff function ) Color C
 */
  void
BufferManager::colorsFillBuff (vector <string> tokens)
{
  buff->addChr(C_CMD);
  buffAddTriColors(tokens);
}


/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: delayFillBuff
 * Description:  ( *FillBuff function ) Delay D
 */

  void
BufferManager::delayFillBuff (vector <string> tokens)
{
  int tmp_byte;
  tmp_byte = stoi(tokens[1]);
  if (verifyByteOverflow(tmp_byte) != -1)
  {
    buff->addChr(D_LOW_CMD);
    buff->addChr((uint8_t)tmp_byte);
    return;
  }
  else if(verify2BytesOverflow(tmp_byte) != -1)
  {
    buff->addChr(D_HIGH_CMD);
    buff->addChr((uint8_t)(tmp_byte & 0xff));
    buff->addChr((uint8_t)(tmp_byte >> 8));
    return;
  }
  else
    exit(EXIT_FAILURE);
}		/* -----  end of method BufferManager::delayFillBuff  ----- */

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: loopFillBuff
 * Description:  ( *FillBuff function ) Loop L
 */
  void
BufferManager::loopFillBuff (vector <string> tokens)
{
  buff->addChr(L_CMD);
  int tmp_byte;
    tmp_byte = stoi(tokens[1]);
    if(verifyByteOverflow(tmp_byte)!= -1)
    {
      buff->addChr((uint8_t)tmp_byte);
    }
    else 
    {
      exit(EXIT_FAILURE);
    }
}		/* -----  end of method BufferManager::loopFillBuff  ----- */

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: oneByteFillBuff
 * Description:  ( *FillBuff function ) Generic for E, END, ENDSUB
 */
  void
BufferManager::oneByteFillBuff(int cmd)
{
  buff->addChr(cmd);
}		/* -----  end of method BufferManager::endLoopFillBuff  ----- */
  
/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: rampFillBuff
 * Description:  ( *FillBuff function ) RAMP
 */
  void 
BufferManager::rampFillBuff(std::vector<std::string> tokens)
{
  int tmp_byte;
  tmp_byte = stoi(tokens[4]);
  if (verifyByteOverflow(tmp_byte) != -1)
  {
    buff->addChr(RAMP_LOW_CMD);
    buffAddTriColors(tokens);
    buff->addChr(tmp_byte);
  }
  else if(verify2BytesOverflow(tmp_byte) != -1)
  {
    buff->addChr(RAMP_HIGH_CMD);
    buffAddTriColors(tokens);
    buff->addChr((uint8_t)(tmp_byte & 0xff));
    buff->addChr((uint8_t)(tmp_byte >> 8));
    return;
  }
  else
    exit(EXIT_FAILURE);
}		/* -----  end of method BufferManager::rampFillBuff  ----- */


/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: subFillBuff
 * Description:  ( *FillBuff function ) SUB
 *               - Add SUB_CMD to buff
 *               - Stores the buffer position of the SUB LSB value in a map
 *               - And add two tempory '\0' value to buff for LSB & MSB  
 */
  void
BufferManager::subFillBuff(std::vector<std::string> tokens)
{
  buff->addChr(SUB_CMD);
  buff->addSubPos(tokens[1]);
  buff->addChr(0);
  buff->addChr(0);
} /* -----  end of method BufferManager::subFillBuff ----- */

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: defsubFillBuff
 * Description:  ( *FillBuff function ) DEFSUB
 *               - Add the beginning position of the DEFSUB 
 *                  function in the buffer to a map.
 *               - throws an error if the same function is defined twice
 */
  void
BufferManager::defsubFillBuff(std::vector<std::string> tokens, int nb_line)
{
  if(buff->addDefsubPos(tokens[1]))
  {
    rules->twiceDefsubError(nb_line);
  }

} /* ----- end of method BufferManager::defsubFillBuff function ----- */



/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: verifyByteOverflow
 */
  int
BufferManager::verifyByteOverflow(int value)
{
  if (value < 256 && value > -1)
  {
    return value;
  }
  else
    return -1;
} /* ----- end of method BufferManager::verifyByteOverflow function ----- */

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: verify2BytesOverflow
 */
  int
BufferManager::verify2BytesOverflow(int value)
{
  if (value < 65536 && value > 255)
  {
    return value;
  }
  else
    return -1;
} /* ----- end of method BufferManager::verify2BytesOverflow function ----- */

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: buffAddTriColors
 */
  void
BufferManager::buffAddTriColors(vector<string>& tokens)
{
  for(int i = 1; i < 4; i++)
  {
    buffAddOneColor(tokens[i]);
  }
} /* ----- end of method BufferManager::buffAddTriColors function ----- */

/*
 *       Class:  BufferManager
 *      Method:  BufferManager :: buffAddOneColor
 */
  void
BufferManager::buffAddOneColor(string& tok)
{
    int tmp_byte;
    tmp_byte = stoi(tok);
    if(verifyByteOverflow(tmp_byte)!= -1)
    {
      buff->addChr((uint8_t)tmp_byte);
    }
    else {
      exit(EXIT_FAILURE);
    }
} /* ----- end of method BufferManager::buffAddOneColor function ----- */

