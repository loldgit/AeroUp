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
 *       Filename:  optmanager.cpp
 *
 *    Description:  Manages command line options & sub options
 *                  To do : make space possible on command line 
 *                  for sub option would be cool more cool
 *
 *          ToDo :  Verify that the value for setSerial is not out of range
 *                  for the time being, the value is set to max.
 *                  we could test string before conversion.
 *
 *        Version:  0.2
 *        Created:  23/12/2013 23:31:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#include "optmanager.hpp"

extern bool VERBOSE_AERO;

using namespace std;


/*
 *       Class:  OptManager
 *      Method:  OptManager :: start
 * Description:  Order Processing
 */
  void 
OptManager::start()
{
  // Start command
  for (vector<string>::iterator iter = startList.begin();
                      iter != startList.end(); ++iter)
  {
    sendStart(*iter);
    if (VERBOSE_AERO)
      cout << "Start command sent on : " << *iter << endl;
  }

  // Color Command
  for (vector<optCol>::iterator iter = colorList.begin();
                      iter != colorList.end(); ++iter)
  {
    if ( (*iter).port != "\0")
    {
      sendColor( (*iter).rgb[RED],
                 (*iter).rgb[GREEN],
                 (*iter).rgb[BLUE],
                 (*iter).port);
    }
    else
    {
      cout << "missing port name argument in color command" << endl;
      exit (EXIT_FAILURE);
    }

    if(VERBOSE_AERO)
    {
      cout << "Color command (c" << dec 
           << "," << static_cast<int>((*iter).rgb[RED])   
           << "," << static_cast<int>((*iter).rgb[GREEN])
           << "," << static_cast<int>((*iter).rgb[BLUE])
           << ") sent on port \"" << (*iter).port << "\"" 
           << endl;

    }
  }

  // Test command
  for ( vector<string>::iterator iter = testList.begin();
                      iter != testList.end(); ++iter)
  {
    sendTest(*iter);
    if (VERBOSE_AERO)
      cout << "Test command sent on : " << *iter << endl;
  }

  // Upload Glo file
  for (vector<optUp>::iterator iter = upGloList.begin();
                      iter != upGloList.end(); ++iter)
  {
    sendUpGlo((*iter).fileName, (*iter).port);
  }

  // Get serial number
  for (vector<string>::iterator iter = getSerialList.begin();
                      iter != getSerialList.end(); ++iter)
  {
    sendGetSerial(*iter);
  }

  // Set serial number
  for (vector<optSerial>::iterator iter = setSerialList.begin();
                      iter != setSerialList.end(); ++iter)
  {
    sendSetSerial((*iter).i_serialNumber,(*iter).port);
  }

  // Verify Glo file
  for ( vector<string>::iterator iter = verifyList.begin();
                      iter != verifyList.end(); ++iter)
  {
    sendVerify(*iter);
    if (VERBOSE_AERO)
      cout << "Process verification on file " << *iter << endl;
  }

}	/* -----  end of method OptManager::start  ----- */


/*
 *                           .::SEND COMMAND::.
 * all the functionalities functionality proposed by the command line interface  
 */

/*
 *      Method:  OptManager :: sendTest
 */
  void
OptManager::sendTest( std::string  port_name )
{
  Ultimate prop( port_name );
  prop.test();

}

/*
 *      Method:  OptManager :: sendStart
 */
  void 
OptManager::sendStart(string port_name)
{
          Ultimate prop(port_name);
          prop.start();
}

/*
 *      Method:  OptManager :: sendColor
 */
  void 
OptManager::sendColor( uint8_t red, uint8_t green, uint8_t blue, string port_name)
{
          Ultimate prop(port_name);
          prop.color(red, green, blue);
}

/*
 *      Method:  OptManager :: sendGetSerial
 */
  void 
OptManager::sendGetSerial( std::string port_name)
{
  Ultimate prop(port_name);
  cout << "Serial number is : 0x" << prop.getSerial() << endl;
          
}

/*
 *      Method:  OptManager :: sendSetSerial
 */
  void
OptManager::sendSetSerial(uint32_t i_serialNumber, string port)
{
  Ultimate prop(port);
  prop.setSerialUlt( i_serialNumber);
}

/*
 *      Method:  OptManager :: sendVerify
 */
  void
OptManager::sendVerify(string fileName)
{
  GloInterface gloInt;
  gloInt.verifyFile(fileName);
}
/*
 *      Method:  OptManager :: sendUpGlo
 */
  void 
OptManager::sendUpGlo(string fileName, string port_name)
{
  Ultimate prop(port_name);
  if( prop.uploadGlo(fileName))
  {
    cout << "Upload " << fileName << " OK" << endl;
  }
}

/* ---- End of SEND COMMAND ---- */ 


/*
 *        .::SUB COMMAND::.
 */
 
/*
 *       Class:  OptManager
 *      Method:  OptManager :: subRoutine
 * Description:  Getopt sub routine switch
 */
  void
OptManager::subRoutine(const short int FLAG )
{
  switch(FLAG)
  {
    case FLAG_COLOR:
      subRoutineColor();
      break;

    case FLAG_UP_GLOC:
    case FLAG_UP_GLO:  
      subRoutineUp(FLAG);
      break;

    case FLAG_SET_SER:
      subRoutineSetSerial();
      break;
  }
}

/*
 *       Class:  OptManager
 *      Method:  OptManager :: subRoutineSetSerial
 * Description:  Getopt sub routine for Set Serial
 */
  void
OptManager::subRoutineSetSerial()
{
  optSerial  tmpSerialNb; 
  subopts = optarg;
  tmpSerialNb.i_serialNumber = 0;
  uint32_t tmp_int;
  for (int i = 0; *subopts !='\0'; i++)
  {
    getsubopt(&subopts, token, &value);
    switch (i)
    {
      case 0:
        tmp_int =isValidSerialNumber(value);
        if (tmp_int != 1)
          tmpSerialNb.i_serialNumber = tmp_int; 
        else
          cerr << "error without throw" << endl;
        break;

      case 1:
        tmpSerialNb.port = value; 
        break;

      default:
        cout << "too many args in set serial command" << endl;
        break;
    }
  }
  setSerialList.push_back(tmpSerialNb); 
}


/*
 *       Class:  OptManager
 *      Method:  OptManager :: subRoutineUp
 * Description:  Getopt sub routine for Upload Glo & GloC
 */
  void
OptManager::subRoutineUp(const short int FLAG )
{
  optUp  tmpOpt; 

  subopts = optarg;
  for (int i = 0; *subopts !='\0'; i++)
  {
    getsubopt(&subopts, token, &value);
    switch (i)
    {
      case 0:
        tmpOpt.fileName = value;
        break;

      case 1:
        tmpOpt.port = value;
        break;

      default:
        cout << "too many args in upload command" << endl;
        break;
    }
  }

  switch (FLAG)
  {
    case FLAG_UP_GLO:
      upGloList.push_back(tmpOpt);
    case FLAG_UP_GLOC:
      upGloCList.push_back(tmpOpt); 
      break;
  }
}

/*
 *       Class:  OptManager
 *      Method:  OptManager :: subRoutineColor
 * Description:  Getopt sub routine for color command
 */
  void
OptManager::subRoutineColor()
{
  optCol tmpcol;
  uint8_t intensity[3] = {0}  ;
  int tmp_int;
  subopts = optarg;
  for (int i = 0; *subopts !='\0'; i++)
  {
    getsubopt(&subopts, token, &value);
    switch (i)
    {
      
      // for all color verify the validity of values
      case RED: case GREEN: case BLUE:
        tmp_int = isValid0xFF(value);
        if (tmp_int == -1)
        {
          cerr << "ERROR : non valid color for color command c " 
               << value << endl;
          exit (EXIT_FAILURE);
        }
        intensity[i] = ( char)tmp_int;
        break;

      case PORT_NAME:
        for (int index = 0 ; index<3; index++)
          tmpcol.rgb[index] = intensity[index];
        tmpcol.port = value;
        colorList.push_back(tmpcol);
        break;

      default:
        cerr << "Error, too many args for -c" << endl;
        exit (EXIT_FAILURE);
        break;
    }
  }
}		/* -----  end of method OptManager::subRoutineColor  ----- */


/*
 *       Class:  OptManager
 *      Method:  OptManager :: isValid0xFF
 * Description:  verify if value can become 1 byte(0-255) 
 */
  int 
OptManager::isValid0xFF(char * value)
{
  int hexval = strtol(value,(char**)NULL,0); 
  if (hexval < 256 && hexval > -1)
    return hexval;
  return -1;
}

/*
 *       Class:  OptManager
 *      Method:  OptManager :: isValidSerialNumber
 * Description:  test with dec, hex & bin notation 
 */
  uint32_t 
OptManager::isValidSerialNumber(string strNb)
{
  uint32_t i_ser_nb; 

  if (isDecNotation( strNb)) 
  {
    std::stringstream ss( strNb);
    ss >> dec >> i_ser_nb;
    cout << i_ser_nb << endl;
  }
  else if(isHexNotation( strNb))
  {
    std::stringstream ss( strNb.substr(2));
    ss >> hex >> i_ser_nb;
    cout << i_ser_nb << endl;
  }
  else
  {
    throw std::string( "Bad serial number" );
  }

  return i_ser_nb;
}

/*
 *       Class:  OptManager
 *      Method:  OptManager :: isHexNotation
 * Description:  is hex notation
 */
  bool
OptManager::isHexNotation(std::string const& s)
{
  return s.compare(0, 2, "0x") == 0
      && s.size() > 2
      && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}


/*
 *       Class:  OptManager
 *      Method:  OptManager :: isDecNotation
 * Description:  is dec notation
 */
  bool
OptManager::isDecNotation(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
