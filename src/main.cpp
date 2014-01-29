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
 *       Filename:  main.cpp
 *
 *    Description:  command line entry point.
 *                  lib getopt needed this is for unix users
 *
 *
 *        Version:  0.3.0
 *        Created:  20/12/2013 00:57:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  BARATTERO Laurent, laurentba<at>larueluberlu.net
 *   Organization:  La rue Luberlu
 */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector> 
#include <string> 

#include <getopt.h>
#include "global.hpp"
#include	"main.hpp"
#include	"optmanager.hpp"
#include	"config.h"



using namespace std;


bool VERBOSE_AERO;

/* 
 *         Name:  main
 *  Description:  get cmd args... gives the job to OptManager.
 *                and finally said to OptManager to start launch
 *                of what is expected.
 */
  int
main ( int argc, char *argv[] )
{

  int version = 0;
  int help = 0;
  VERBOSE_AERO = false;
  int c;
  OptManager manager;

  while (1)
  {
    static struct option long_options[] =
    {
      {"start", required_argument,     NULL, 'o'},
      {"test",  required_argument,     NULL, 't'},
      {"color", required_argument,     NULL, 'c'},
      {"getSerial", required_argument, NULL, 'G'},
      {"setSerial", required_argument, NULL, 'S'},
      {"verify", required_argument,    NULL, 'i'},
      {"uploadGlo", required_argument, NULL, 'u'},
      {"uploadGloc", no_argument,      NULL, 'U'},
      {"symlink", no_argument,         NULL, 'k'},
      {"verbose", no_argument,         NULL, 'v'},
      {"thread", no_argument,          NULL,  1 },
      {"version", no_argument,     &version,  1 },
      {"help", no_argument,            NULL, 'h'},
      {0, 0, 0, 0}
    };
    /* getopt_long stores the option index here. */
    int option_index = 0;
    c = getopt_long (argc, argv, "o:t:c:G:S:u:U:k:i:vh",
                     long_options, &option_index);

    /* Detect the end of the options. */
    if (c == -1)
      break;

    switch (c)
    {
      case 0:
        /* If this option set a flag, do nothing else now. */
        if (long_options[option_index].flag != 0)
        break;

      case 'o':
        manager.addItemStart(optarg);
        break;

      case 't':
        manager.addItemTest(optarg);
        break;

      case 'c':
        try
        {
          manager.subRoutine(FLAG_COLOR);
        }
        catch ( const string & Msg )
        {
          cerr << "Error : " << Msg << endl;
          return(EXIT_FAILURE);
        }
        break;

      case 'G':
        manager.addItemGetSerial(optarg);
        break;

      case 'S':
        try
        {
          manager.subRoutine(FLAG_SET_SER);
        }
        catch ( const string & Msg )
        {
          cerr << "Error : " << Msg << endl;
          return(EXIT_FAILURE);
        }
        break;
      
      case 'i':
        manager.addItemVerify(optarg);
        break;

      case 'u':
        manager.subRoutine(FLAG_UP_GLO);
        break;

      case 'U':
        manager.subRoutine(FLAG_UP_GLOC);
        break;

      case 'k':
        manager.addItemSymlink(optarg);
        break;

      case 'v':
        VERBOSE_AERO = true;
        break;

      case 'h':
        help = 1;
        break;

      case '?':
        /* getopt_long already printed an error message. */
        puts("To get help : 'aeroup --help' or 'man aeroup'");
        return EXIT_FAILURE;
        break;

      default:
        abort ();
    }
 }
     
  /* Print any remaining command line arguments (not options). */
  if (optind < argc)
  {
    printf ("non-option ARGV-elements: ");
    while (optind < argc)
      printf ("%s ", argv[optind++]);
    putchar ('\n');
    puts("To get help : 'aeroup --help' or 'man aeroup'");
    return(EXIT_FAILURE);
  }


  if(version)
  {
    aeroVersion();
    return(EXIT_SUCCESS);
  }

  if(help || argc == 1)
  {
    aeroHelp();
    return(EXIT_SUCCESS);
  }
  
  try
  {
  manager.start();
  }
  catch( const exception & e )
  {
    return(EXIT_FAILURE);
  }
  catch( Symlink::Bad_Symlink )
  {
    cerr << "Error : Bad Symlink input\n"
         << "'$man aeroup' section 'Improved management driver' may be help you\n";
    return(EXIT_FAILURE);
  }
  catch(...)
  {
    //return(EXIT_FAILURE);
    puts("UNKNOWN ERROR, CATCHED IN MAIN");
    return(EXIT_FAILURE);
  }

  return(EXIT_SUCCESS);
}


/* 
 *         Name:  aeroHelp
 *  Description:  --help
 */
  void
aeroHelp()
{
  cout << "Usage : " << PACKAGE <<" [OPTION [SUB_OPTION]]...\n"
       << "AeroUp is an open source command line tool to control Ultimate juggling props sold by Aerotech Projects.\n\n"
       << "  -t, --test=serialPort                     Send a test command on dev serialPort.\n"
       << "  -o, --start=serialPort                    Send a start sequence command on dev serialPort.\n"
       << "  -c, --color=R,G,B,serialPort              Send a color command on dev serialPort.\n"
       << "                                            R,G,B can be hex (0x#), dec (#) value,\n"
       << "                                            in range of [0-255] (8bit).\n"
       << "  -G, --getSerial=serialPort                Get serial number on dev serialPort, and print it to standard output.\n"
       << "  -S, --setSerial=serialNumber,serialPort   Set serialNumber on dev serialPort. the 32 bits serialNumber value\n"
       << "                                            can be writen in hex (0x#) or dec (#).\n"
       << "  -i, --verify=gloFile                      Verify that syntax glo file is valid.\n"
       << "  -k --symlink                              Return the serial name used as symlink of kernel name by udev.\n" 
       << "                                            More info in the AeroUp man.\n"
       << "  -u, --uploadGloc=gloFile,serialPort       Verify that syntax glo file is valid, and if this is the case,\n"
       << "                                            upload it on dev serialPort.\n"
       << "  -P, --thread                              Multithread mode, not implemented yet...\n"
       << "  -U, --uploadGloc=glocFile,serialPort      Not implemented yet...\n"
       << "  -v                                        Verbose mode.\n"
       << "  -h, --help                                Print help.\n"
       << "      --version                             Print version.\n\n"
       << "Each sub options have to be separate with a comma without blank.\n"
       << "you 'll find more info in the man of aeroup.\n\n"
       << "Examples\n"
       << "  aeroup -t /dev/ttyACM0\n"
       << "  aeroup -o /dev/ttyACM0 -o /dev/ttyACM1 -t /dev/ttyACM3\n"
       << "  aeroup -c 255,69,255,/dev/ttyACM0 27,3,7,/dev/ttyACM1\n"
       << "  aeroup -S 0x0b01/dev/ttyACM0\n"
       << "  aeroup -G /dev/ttyACM0\n\n"
       << "AeroUp project page : " PACKAGE_URL << "\n"
       << "You can also take a look at the AeroWrite project page https://github.com/LaurentBa/AeroWrite\n"
       << "Report bugs to " << PACKAGE_BUGREPORT << "\n"
       << endl;

}


/* 
 *         Name:  aeroVersion
 *  Description:  --version
 */
  void
aeroVersion()
{
  cout << PACKAGE_STRING << "\n"
          "Copyright © 2014 BARATTERO Laurent\n"
          "License GPLv3+: GNU GPL version 3 or later\n"
          "<http://gnu.org/licenses/gpl.html>\n"
          "This is free software: you are free to change and redistribute it.\n"
          "There is NO WARRANTY, to the extent permitted by law\n";
}





