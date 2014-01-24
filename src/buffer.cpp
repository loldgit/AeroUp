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
 *       Filename:  buffer.cpp
 *
 *    Description:  
 *
 *        Version:  0.3.0  
 *        Created:  28/12/2013 07:06:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu 
 *
 */

#include <buffer.hpp>

using namespace std;

Buffer::Buffer():
    size(0)
{
   //memset(buff, 0, sizeof(buff));
}

int Buffer::addChr(unsigned char val)
{
  verify_size();
  //buff[size++] = val;
  //strcpy((char*)buff[size],(const char *)val);
  buff[size] = val;
  size++;
  return 1;
     
}

  string
Buffer::addDefsubToBuff()
{
  for(auto itr = sub_position.begin(); itr != sub_position.end(); ++itr)
  {
    while(((*itr).second.empty()) == false )
    {
      auto it = defsub_position.find((*itr).first);
      if(it != defsub_position.end())
      {
      buff[(*itr).second.back()] = defsub_position[(*itr).first][0];
      buff[(*itr).second.back() + 1] = defsub_position[(*itr).first][1];
      (*itr).second.pop_back();
      }
      else
      {
        return (*itr).first ;
      }
    }
  }
  return "";
}

  int 
Buffer::addDefsubPos(string defsubName)
{
  auto it = defsub_position.find(defsubName);
  if(it == defsub_position.end())
  {
    defsub_position[defsubName][0] = (uint8_t)(size & 0xff);
    defsub_position[defsubName][1] = (uint8_t)(size >> 8);
    return 0;
  }
  else
  {
    return 1;
  }
}

  void 
Buffer::addSubPos(string subName)
{
  sub_position[subName].push_back(size);
}

  void 
Buffer::printDefsubPos()
{
  cout << endl
       << "(Debug function) print map defsub_position :" << endl
       << "============================================" << endl;
  for(auto itr = defsub_position.begin(); itr != defsub_position.end(); ++itr)
  {
    cout << "Key : " << (*itr).first << endl
         << "Lsb : " << dec << (int)(*itr).second[0] << endl
         << "Msb : " << dec << (int)(*itr).second[1] << endl ;
  }
}

  void 
Buffer::printSubPos()
{
  cout << endl
       << "(Debug function) print map sub_position :" << endl
       << "=========================================" << endl;
  for(auto itr = sub_position.begin(); itr != sub_position.end(); ++itr)
  {
    cout << "Key : " << (*itr).first << endl
         << "Value : " ;
    for (auto itr_vect = (*itr).second.begin();
         itr_vect != (*itr).second.end();
         ++itr_vect)
    {
      cout << (*itr_vect) << " ";
    }

    cout << endl;
  }
}

  void
Buffer::printBuff(void) const
{
    for (unsigned int i = 0; i < size ; i++)
    {
        printf("buff[%d] : %d\n", i, buff[i]);
        
    }

}

  void 
Buffer::verify_size(void)
{
    if (size > BUFF_SIZE_MAX)
    {
        printf ("Error glow file too big !");
        exit (EXIT_FAILURE);
    }
}


/* 
 * where is sub map string vector int subnamekey, (byte,...)
 * defsub defsubname, localisation subfunction
 *
 * if sub define 2 times error
 *
 * */
  unsigned char*
Buffer::getSizeUpCmd()
{
  lsb_msb[0]= 100;
  lsb_msb[1]= (uint8_t)(size & 0xff);
  lsb_msb[2]= (uint8_t)(size >> 8);
  return lsb_msb;


}
