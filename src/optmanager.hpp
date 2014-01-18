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
 *       Filename:  optmanager.hpp
 *
 *    Description:  
 *
 *        Version:  0.2
 *        Created:  23/12/2013 22:59:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  optmanager_INC
#define  optmanager_INC

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <vector>
#include "global.hpp"
#include "ultimate.hpp"
#include "gloInterface.hpp"

#define MAX_LEN_OPT 2

#define FLAG_SET_SER  0x1
#define FLAG_UP_GLO   0x2
#define FLAG_UP_GLOC  0x4
#define FLAG_COLOR    0x8
#define FLAG_VERIFY   0x10

/*
 *        Class:  OptManager
 *  Description:  Manages command line options & sub options
 */
class OptManager
{
  public:
    OptManager (){;}    /* constructor */

    void start();

    void addItemStart(std::string port_name)
                {startList.push_back(port_name);}

    void addItemTest(std::string port_name)
                {testList.push_back(port_name);}

    void addItemGetSerial(std::string port_name)
                {getSerialList.push_back(port_name);}

    void addItemVerify(std::string glo_file)
                {verifyList.push_back(glo_file);}

    void subRoutine(const short int FLAG);

  private:
    // Send functions
    void sendTest(std::string port_name);
    void sendStart(std::string port_name);
    void sendColor(uint8_t red, uint8_t green, uint8_t blue, std::string port_name);
    void sendGetSerial(std::string port_name); 
    void sendSetSerial(uint32_t i_serialNumber, std::string port);
    void sendVerify(std::string fileName);
    void sendUpGlo(std::string fileName, std::string port);
    // void sendUpGloC(std::string fileName, std::string port);
    
    // Sub functions
    void subRoutineColor();
    void subRoutineUp(const short FLAG);
    void subRoutineSetSerial();

    // Tool functions
    uint32_t isValidSerialNumber(std::string strNb);
    int isValid0xFF(char* value);
    bool isHexNotation(std::string const& s);
    bool isDecNotation(std::string const& s);

    // GetSubOpt data 
    char * token[MAX_LEN_OPT]={0};
    char *subopts;
    char *value;
    enum { RED = 0, GREEN, BLUE, PORT_NAME };


    // Structures and variables for opts containers
    // struct
    struct optCol 
    {
      unsigned char rgb[3];
      std::string port;
    };

    struct optUp
    {
      std::string fileName;
      std::string port;
    };

    struct optSerial
    {
      uint32_t i_serialNumber;
      std::string serialNumber;
      std::string port;
    };
    // Var
    std::vector<std::string> startList; 
    std::vector<std::string> testList; 
    std::vector<optCol> colorList; 
    std::vector<optUp> upGloList; 
    std::vector<optUp> upGloCList; 
    std::vector<std::string> verifyList; 
    std::vector<optSerial> setSerialList; 
    std::vector<std::string> getSerialList;
    // end of Structures and variables for opts containers 

}; /* -----  end of class OptManager  ----- */

#endif   /* ----- #ifndef optmanager_INC  ----- */
