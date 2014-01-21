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
 *       Filename:  regboost.hpp
 *
 *    Description:  
 *
 *        Version:  0.3.0.1
 *        Created:  19/12/2013 05:23:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */


#ifndef  regboost_INC
#define  regboost_INC


#include <boost/regex.hpp>
#include <iostream>
#include "define_ultimate_fct.h"
#include "global.hpp"

// BOOST REGEX TAB
static const boost::regex reg_tab[] = {
  boost::regex("^C,[[:digit:]]{1,3},[[:digit:]]{1,3},[[:digit:]]{1,3}$"),                         // C_FCT      
     boost::regex("^D,[[:digit:]]{1,5}$"),                                                        // D_FCT   
     boost::regex("^RAMP,[[:digit:]]{1,3},[[:digit:]]{1,3},[[:digit:]]{1,3},[[:digit:]]{1,5}$"),  // RAMP_FCT
     boost::regex("^L,[[:digit:]]{1,3}$"),                                                        // L_FCT    
     boost::regex("^E$"),                                                                         // E_FCT    
     boost::regex("^R,[[:digit:]]{1,3}$"),                                                        // R_FCT    
     boost::regex("^G,[[:digit:]]{1,3}$"),                                                        // G_FCT    
     boost::regex("^B,[[:digit:]]{1,3}$"),                                                        // B_FCT    
     boost::regex("^SUB,[-_[:alnum:]]+$"),                                                        // SUB_FCT  
     boost::regex("^DEFSUB,[-_[:alnum:]]+$"),                                                     // DEFSUB_FCT    
     boost::regex("^ENDSUB$"),                                                                    // ENDSUB_FCT    
     boost::regex("^END$")};                                                                      // END_FCT  


/*
 *        Class:  RegBoost
 *  Description:    
 */
class RegBoost
{
  public:
    RegBoost ();    /* constructor */
    
    int isValidSyntax( std::string &rline);

}; /* -----  end of class RegBoost  ----- */

#endif   /* ----- #ifndef regboost_INC  ----- */
