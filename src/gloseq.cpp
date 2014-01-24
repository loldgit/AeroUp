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
 *       Filename:  gloseq.cpp
 *
 *    Description:  
 *
 *        Version:  0.3.0
 *        Created:  27/12/2013 10:38:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu 
 */

#include <sstream>
#include "gloseq.hpp"

using namespace std;


/*
 *       Class:  GloSeq
 *      Method:  GloSeq :: GloSeq
 * Description:  Constructor, open glo file in read mode 
 */
GloSeq::GloSeq (string fileName):
             file_name(fileName),
                          buff(),
                rules(file_name),
      buffManager(&buff, &rules)
{
  try
  {
    glofile.open(fileName);
    if (!glofile)
    {
      throw "Error : can't opening glo file : ";
    }
  }
  catch(const char* cstr)
  {
    cerr << cstr << fileName << endl;
    throw;
  }
}		/* -----  end of constructor  ----- */

/*
 *       Class:  GloSeq
 *      Method:  GloSeq :: verify
 * Description:  Verify that the glo file is valid.
 *               At the end of process, if no error happened the buffer is filled
 *               and ready to be upload.
 */
  void
GloSeq::verify ()
{
  /* step 1 */
  #ifdef DEBUG
  cout << endl
       << "1) Clean lines and keep what is needed :" << endl
       << "========================================" << endl;
  int j = 0;
  #endif

  string line;
  for(int nb_line = 1; getline(glofile, line) != 0; nb_line++)
  {
    // cleaning each line
    cleanLine(line);
    if (line.length() != 0)
    {
      // put it in a vector
      cmdTab.push_back({line, -1, nb_line});
#ifdef DEBUG
      cout << cmdTab[j].nb_line <<"| "<< cmdTab[j].line << endl;
      ++j;
#endif
    }
  }

  /* step 2 */
  #ifdef DEBUG
  cout << endl
       << "2) Regex validation :" << endl
       << "=====================" << endl;
  #endif
  
#if HAVE_LIBBOOST_REGEX
    RegBoost* reg = new RegBoost;
#else
    RegLinux* reg = new RegLinux;
#endif
  auto iterlist = cmdTab.begin();
  int cmd;
  int nb_error = 0;

  while (iterlist != cmdTab.end())
  {
    cmd = reg->isValidSyntax( (*iterlist).line );
    if (cmd == NOT_VALID)
    {
      if (!nb_error)
        cout << "Syntax error in file " << file_name << " :" << endl; 

      cout << "Error line " << (*iterlist).nb_line
           << ", " << (*iterlist).line << endl;
      ++nb_error;
    }
    else
      (*iterlist).cmd_type = cmd;
    ++iterlist;
  }
  delete reg;

  try
  {
    if (nb_error != 0)
      throw(nb_error);
  }
  catch (int nb_error )
  {
    if (nb_error == 1)
      cerr << "Error : "<< nb_error <<" syntax error in " << file_name << endl;
    else
      cerr << "Error : "<< nb_error <<" syntax errors in " << file_name << endl;
      throw;
  }

  /* step 3  */
  #ifdef DEBUG
  cout << endl
       << "3) Tokenize and send to buffManager:" << endl
       << "========================================" << endl;
  #endif
  iterlist = cmdTab.begin();  
  vector <string> tokens;
  //vector<string>::iterator it_string;
  
  while (iterlist != cmdTab.end())
  {
    istringstream iss((*iterlist).line);
    tokens.clear();
    for (string each; (getline(iss, each, ',')); tokens.push_back(each));
    try
    {
      buffManager.createCommand(tokens, (*iterlist).cmd_type, (*iterlist).nb_line);
    }
    catch( const std::exception & e )
    {
      cerr << e.what() << "\n";
      throw;
    }

    ++iterlist;
  }

  #ifdef DEBUG
  buff.printBuff();
  buff.printSubPos();
  buff.printDefsubPos();
  #endif

  try
  {
  /* 
   * createCommand second pass:
   * makes some works haven't been at the first pass
   * 1) error detection, we can't see during the createCommand function 
   * 2) fill buffer with the adress of beginning of defsub 
   **/
    buffManager.completesCreateCommand();
  }
  catch( const std::exception & e )
  {
    cerr << e.what() << "\n";
    throw;
  }

  #ifdef DEBUG
  cout << "(debug) print buff second pass :" << endl
       << "================================" << endl;
  buff.printBuff();
  #endif
}		/* -----  end of method GloSeq::verify  ----- */

/*
 *       Class:  GloSeq
 *      Method:  GloSeq :: cleanLine
 * Description:  
 */
  void
GloSeq::cleanLine ( string &rline )
{
  size_t i;
  // parsing a line
  for (i = 0 ; i < rline.length(); ++ i )
  {
    if (rline[i] == ';')
      rline.erase(i, rline.length());

    else if (rline[i] == SP || rline[i] == TAB || rline[i] == CR || rline[i] == LF)
      rline.erase(rline.begin() + i--);
  }
}		/* -----  end of method GloSeq::cleanLine  ----- */


/*
 *       Class:  GloSeq
 *      Method:  GloSeq :: upload
 * Description:  
 */
  void
GloSeq::upload(SerialProp & ser)
{
  ser.sendString(buff.getSizeUpCmd(), 3);
  ser.sendString(buff.pointToBuff(), buff.getSize());

}		/* -----  end of method GloSeq::upload ----- */


