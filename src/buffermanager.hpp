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
 *       Filename:  buffermanager.hpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  30/12/2013 12:07:43
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  commandfactory_INC
#define  commandfactory_INC

#include <string>
#include <vector>

#include "buffer.hpp"
#include "global.hpp"
#include "rules.hpp"
#include "define_ultimate_fct.h"

/* -- commands byte values -- */
const uint8_t C_CMD         =   1;
const uint8_t D_LOW_CMD     =   2;
const uint8_t L_CMD         =   3;
const uint8_t D_HIGH_CMD    =   4;
const uint8_t E_CMD         =   5;
const uint8_t R_CMD         =   7;
const uint8_t G_CMD         =   8;
const uint8_t B_CMD         =   9;
const uint8_t RAMP_LOW_CMD  =  12;
const uint8_t RAMP_HIGH_CMD =  13;
const uint8_t SUB_CMD       =  10;
const uint8_t ENDSUB_CMD    =  11;
const uint8_t END_CMD       = 255;

/*
 *        Class:  BufferManager
 *  Description:  
 */
class BufferManager
{
  public:
    BufferManager (Buffer* theBuff, Rules* theRules);    /* constructor */

    void createCommand ( std::vector <std::string> tokens,
                                               int cmd_type,
                                               int nb_line );
    void completesCreateCommand (); 

  private:
    /*  ...FillBuff function   */
    void delayFillBuff(std::vector<std::string> tokens);
    void oneByteFillBuff(int fct);
    void oneColorFillBuff(std::vector <std::string> tokens, int col);
    void colorsFillBuff(std::vector<std::string> tokens);
    void rampFillBuff(std::vector<std::string> tokens);
    void loopFillBuff(std::vector<std::string> tokens);
    void subFillBuff(std::vector<std::string> tokens);
    void defsubFillBuff(std::vector<std::string> tokens, int nb_line);

    /* Second pass to buff, Completes createCommand work */
    void addDefsubToBuff();
    void verifyEndFileError();

    /* Byte verification */
    int verifyByteOverflow(int Value);
    int verify2BytesOverflow(int Value);

    /* Colors utility */
    void buffAddTriColors(std::vector<std::string>& tokens);
    void buffAddOneColor(std::string& tok);

    /* aggregation */
    Buffer* buff;
    Rules* rules;

    /* data  */
    std::string fileName;

};

#endif   /* ----- #ifndef command_factory_INC  ----- */
