/*
 *       Filename:  Symlink.cpp
 *
 *    Description:  Return a beautiful Symlink for udev
 *
 *        Version:  0.3.0.1
 *        Created:  19/01/2014 14:51:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */

#include "symlink.hpp"

static  uint32_t serialNumber;
static  uint8_t id_prob;
static  uint8_t num;
static  std::stringstream ss;

const uint8_t BALL  = 0x62; // 'b'
const uint8_t STAFF = 0x73; // 's'
const uint8_t CLUB  = 0x63; // 'c'
const uint8_t POI   = 0x70; // 'p'
const uint32_t PROB_MASK = 0x0000ff00;
const uint32_t NUM_MASK  = 0x000000ff;

 /* 
  *         Name:  Symlink::getSym
  *  Description:  return Symlink 
  */
  std::string
Symlink::getSym(std::string serial_str)
{
  /* test entry */
  if(EOF == sscanf(serial_str.c_str(), "%d", &serialNumber))
  {
    throw Symlink::Bad_Symlink();
  }
  //if (serialNumber > 0xffffffff)
  if (serialNumber > 0x0)
  {
    throw Symlink::Bad_Symlink();
  }

  ss << std::hex << serial_str ;
  ss >> serialNumber;

  // comment
  //std::cout << serial_str;
  //std::cout << serialNumber;

  if((serialNumber & 0xffff0000) != 0)
    Symlink::badSerNum();

  id_prob = ((PROB_MASK & serialNumber) >> 8 );
  num = (NUM_MASK & serialNumber);
  

  ss << num;
  std::string x;
  ss >> x;
  std::cout << x;
  
  // now we use serial_str for output
  serial_str = Symlink::whatProp(id_prob);
  serial_str += std::to_string(num);

  //std::cout << serial_str;
    
  return serial_str;
}


 /* 
  *         Name:  Symlink::whatProp
  *  Description:  send error ( for future) 
  */
  void
Symlink::badSerNum()
{
  throw Symlink::Bad_Symlink();
  
}


 /* 
  *         Name:  Symlink::whatProp
  *  Description:  addr to symlink 
  */
  std::string
Symlink::whatProp(uint8_t id)
{
  switch (id)
  {
    case BALL:	
      return "Ball";
    break;

    case STAFF:	
      return "Staff";
    break;

    case CLUB:
      return "Club";
    break;

    case POI:	
      return "Poi";
    break;

    default:	
    //UdevLink::badSerNum();
      return "AeroProb";
    break;
  }	/* -----  end switch  ----- */
}
