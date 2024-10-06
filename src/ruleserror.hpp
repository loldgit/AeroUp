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
 *       Filename:  rulesError.hpp
 *
 *    Description:  
 *
 *        Version:  0.3.2
 *        Created:  06/01/2014 10:04:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */


#ifndef  ruleserror_INC
#define  ruleserror_INC

#include <iostream>
#include <sstream>
#include <exception>


/*
 *        Class:  RulesError
 *  Description:  
 */
class RulesError : public std::exception
{
  public:
    RulesError (const char * Msg, std::string fileName, int line)
    {
        std::ostringstream oss;
        oss << "In File \"" << fileName << "\"" 
            << ", Error line " << line << " : "
            << Msg;
        this->msg = oss.str();
    } /* constructor 1 */

    RulesError (const char * Msg, std::string fileName)
    {
        std::ostringstream oss;
        oss << "In File \"" << fileName << "\"" 
            << ", Error" << " : "
            << Msg;
        this->msg = oss.str();
    } /* constructor 2 */

    virtual ~RulesError() throw()
    {
    }

    virtual const char* what() const throw()
    {
      return this->msg.c_str();
    }

  private:
    std::string msg;

}; /* -----  end of class RulesError  ----- */

#endif   /* ----- #ifndef ruleserror_INC  ----- */
