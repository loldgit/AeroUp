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
 *       Filename:  serialboost.hpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  20/12/2013 00:06:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  serialboost_INC
#define  serialboost_INC

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/ref.hpp>
#include "global.hpp"

/*
 *        Class:  SerialBoost
 *  Description:  
 */
class SerialBoost
{
  public:
    SerialBoost (std::string port_name);    /* constructor */
    ~SerialBoost ();    /* destructor */

    void sendChar(char c);
    void sendChar(unsigned char c);
    void sendString(unsigned char* s, int nb_char);
    void sendString(char* s, int nb_char);
    void sendString(const char* s, int nb_char);
    void sendString(std::string s);
    void getString();
    void getString(char* s, int nb_char);
    std::string readLine();

  protected:
    boost::asio::io_service port_io;
    boost::asio::serial_port port;

}; /* -----  end of class SerialBoost  ----- */

#endif   /* ----- #ifndef serialboost_INC  ----- */
