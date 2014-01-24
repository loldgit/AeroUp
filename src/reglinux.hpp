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
 *       Filename:  reglinux.hpp
 *
 *    Description:  Regex lib (linux version)
 *
 *        Version:  0.3.0
 *        Created:  18/01/2014 01:16:31
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  reglinux_INC
#define  reglinux_INC


#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <string.h>
#include "define_ultimate_fct.h"
#include "global.hpp"


/*
 *        Class:  RegLinux
 *  Description:  Linux regex lib version 
 */

class RegLinux
{
public:
    RegLinux();
    int isValidSyntax(std::string &rline);


private:
    void comp(void);

    regex_t reg[REG_TAB_LEN];
    regex_t *preg = &reg[0];

    const char *str_regex[REG_TAB_LEN] ={
     "^C,[[:digit:]]{1,3},[[:digit:]]{1,3},[[:digit:]]{1,3}$",                      // C_FCT      
     "^D,[[:digit:]]{1,5}$",                                                        // D_FCT   
     "^RAMP,[[:digit:]]{1,3},[[:digit:]]{1,3},[[:digit:]]{1,3},[[:digit:]]{1,5}$",  // RAMP_FCT
     "^L,[[:digit:]]{1,3}$",                                                        // L_FCT    
     "^E$",                                                                         // E_FCT    
     "^R,[[:digit:]]{1,3}$",                                                        // R_FCT    
     "^G,[[:digit:]]{1,3}$",                                                        // G_FCT    
     "^B,[[:digit:]]{1,3}$",                                                        // B_FCT    
     "^SUB,[-_[:alnum:]]+$",                                                        // SUB_FCT  
     "^DEFSUB,[-_[:alnum:]]+$",                                                     // DEFSUB_FCT    
     "^ENDSUB$",                                                                    // ENDSUB_FCT    
     "^END$"};                                                                      // END_FCT  
};



#endif   /* ----- #ifndef reglinux_INC  ----- */
