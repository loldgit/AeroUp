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
 *       Filename:  serialboost.cpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  20/12/2013 00:06:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */
#include <serialboost.hpp>

using namespace std;
using namespace boost;


/*
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: SerialBoost
 * Description:  Constructor
 */
SerialBoost::SerialBoost ( std::string port_name ):
                port(port_io)
{
  try
  {
  port.open( port_name );
  }
  catch(boost::system::system_error& e)
  {
        cout<<"Serial Error ("<<e.what()<< ")" << endl;
        throw;
  }

  typedef asio::serial_port_base asio_serial;
  port.set_option(asio_serial::baud_rate(19200));
  port.set_option(asio_serial::flow_control(asio_serial::flow_control::none));
  port.set_option(asio_serial::parity( asio_serial::parity::none));
  port.set_option(asio_serial::stop_bits( asio_serial::stop_bits::one));
  port.set_option(asio_serial::character_size(8));

}		/* -----  end of Constructor  ----- */


/*
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: ~SerialBoost
 * Description:  Destructor
 */
SerialBoost::~SerialBoost (  )
{
  port.close();

}		/* -----  end of Destructor  ----- */


/**
 * SEND A CHAR METHODS... 
 **/

/*              
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: sendChar
 * Description:  Write on serial port
 *               char version
 */
  void
SerialBoost::sendChar(char c)
{
    port.write_some(asio::buffer(&c, 1));
}

/*
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: sendChar
 * Description:  Write on serial port
 *               unsigned Char version
 */
  void
SerialBoost::sendChar(unsigned char c)
{
    port.write_some(asio::buffer(&c, 1));

}

/**
 * SEND A STRING METHODS...
 **/

/*
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: sendString
 * Description:  Write on serial port
 *               (char* + nb) version
 */
  void
SerialBoost::sendString(char* s, int nb_char)
{
  port.write_some(asio::buffer(s, nb_char));
}

/*
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: sendString 
 * Description:  Write on serial port
 *               (unsigned char* + nb) version
 */
  void
SerialBoost::sendString(unsigned char* s, int nb_char)
{
  port.write_some(asio::buffer(s, nb_char));
}
  
/*               
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: sendString
 * Description:  Write on serial port
 *               (const char* + nb) version
 */
  void
SerialBoost::sendString(const char* s, int nb_char)
{
  port.write_some(asio::buffer(s, nb_char));
}

/*               
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: sendString
 * Description:  Write on serial port
 *               String version
 */
  void 
SerialBoost::sendString(string s)
{
  port.write_some(asio::buffer(s.c_str(),s.size()));
}

/** 
 * READ METHODS... 
 **/

/*               
 *       Class:  SerialBoost
 *      Method:  SerialBoost ::readLine
 * Description:  Read on serial port
 *               Readline version
 */
  string
SerialBoost::readLine()
{
  char c;
  string result;
    for(;;)
    {
      asio::read(port, asio::buffer(&c,1));
      switch(c)
      {
        case '\r':
          break;
        case '\n':
          return result;
        default:
          result+=c;
       }
    }
}

/*               
 *       Class:  SerialBoost
 *      Method:  SerialBoost :: getString
 * Description:  Read on serial port
 *               (char* + nb-read) version
 */
void SerialBoost::getString(char* s, int nb_char)
{
  asio::read(port, asio::buffer(s, nb_char));
}


