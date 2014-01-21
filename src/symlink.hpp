/*
 *       Filename:  Symlink.hpp
 *
 *    Description:  Return a beautiful Symlink for udev
 *
 *        Version:  0.3.0.1
 *        Created:  19/01/2014 14:51:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#ifndef  Symlink_INC
#define  Symlink_INC

#include <stdlib.h>
#include <string>
#include <exception>
#include <sstream> 
#include <unistd.h>
#include <iostream>

/* 
 *         Name:  Symlink
 *  Description:  Symlink declaration
 */
namespace Symlink
{
//  extern uint16_t BALL;
//  extern uint16_t STAFF;
//  extern uint16_t CLUB;
//  extern uint16_t POI;



//  const uint32_t PROB_MASK;
//  const uint32_t NUM_MASK;

  std::string getSym(std::string serial_str);
  std::string whatProp(uint8_t id);
  void badSerNum();

  class Bad_Symlink{};
}

#endif   /* ----- #ifndef symlink_INC  ----- */
