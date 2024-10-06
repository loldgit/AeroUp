#!/bin/bash - 
#  Copyright (C) 2014 BARRATERO Laurent                                   
#
#  AeroUp is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by 
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  Aeroup is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License along
#  with this program; if not, write to the Free Software Foundation, Inc.,
#  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. 

#===============================================================================
#
#          FILE: createMan.sh
# 
#         USAGE: ./createMan.sh 
# 
#   DESCRIPTION: Create the man files 
# 
#       OPTIONS: ---
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: ---
#        AUTHOR: BARATTERO Laurent, laurentBa<at>larueluberlu.net
#  ORGANIZATION: La rue Luberlu
#       CREATED: 27/01/2014 09:32:46 CET
#      REVISION:  ---
#===============================================================================

set -o nounset                              # Treat unset variables as an error

rm ../man/aeroup.man.txt
rm ../man/aeroup.man.html

man ../man/aeroup.man > ../man/aeroup.man.txt 
man ../man/aeroup.man | man2html  -noheads  -title "AeroUp Man Page" -compress > ../man/aeroup.man.html

