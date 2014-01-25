#!/bin/bash - 
# 
# Copyright (C) 2014 BARRATERO Laurent
# 
# AeroUp is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
# 
# Aeroup is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
# 
 
#===============================================================================
#
#          FILE: updateVersion.sh
# 
#         USAGE: ./updateVersion.sh 
# 
#   DESCRIPTION: Retrieves the version number in configure.ac 
#                and updates all files with this number  
# 
#       OPTIONS: -u --update    does the job
#                -y --yes       say me yes every time
#                -h --help
#                -v --version
#
#  REQUIREMENTS: ---
#          BUGS: ---
#         NOTES: 
#        AUTHOR: BARATTERO Laurent, laurentBa<at>larueluberlu.net
#  ORGANIZATION: La rue Luberlu
#       CREATED: 22/01/2014 03:14:03 CET
#      REVISION:  0.2
#===============================================================================
set -o nounset                              # Treat unset variables as an error

# INIT
######
SCRIPT_NAME="update_aero"
SCRIPT_VERSION="0.2"

Bold=`tput bold`
EndBold=`tput sgr0`

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT_PATH=${DIR}/../
SRC_PATH=${ROOT_PATH}/src/
README="${ROOT_PATH}README.md"
CONFIGURE_AC="${ROOT_PATH}/configure.ac"

opt_help=0
opt_update=0
opt_yes=0

# options
#########
while getopts ":hvuy-:" opt ; do
  if [ "$opt" = "-" ] ; then
    case $OPTARG in
      update) opt=u ;;
      yes) opt=y ;;
      help ) opt=h ;;
      version ) opt=v ;;
      * ) echo "Unknow $OPTARG option" ;;
    esac
  fi
  case $opt in
    u ) opt_update=1 ;;
    y ) opt_yes=1 ;;
    h ) opt_help=1 ;;
    v ) echo "$SCRIPT_NAME Version $SCRIPT_VERSION";;
  esac
done

# functions
###########
yesOrNot()
{
  if [ $opt_yes == 0 ]; then
    answer=""
  else
    answer="y"
  fi
  stty_bak=$(stty -g)
  stty -icanon time 1 min 0 -echo
  #while [ -z $answer ] ; do
  while [ "$answer" != "y"  -a "$answer" != "n" ]; do
    read answer
  done
  stty $stty_bak
}	# ----------  end of function setStty  ----------

# opt_update
############
if [ $opt_update = 1 ]; then
  # Get version #.#.# in configure
  NEW_VERSION=$(sed -n -re "s/(^AC_INIT\(\[[[:alpha:]]+\][[:blank:]]*\,[[:blank:]]*\[)([[:digit:]]{1,2}\.[[:digit:]]{1,2}(\.[[:digit:]]{1,2})?)(\].*)/\2/p" $CONFIGURE_AC)
  echo "New version     : $NEW_VERSION" 

  # Test if syntax is ok for security 
  echo "$NEW_VERSION" | grep -E "[[:digit:]]+\.[[:digit:]]+(\.[[:digit:]]+)?$" > /dev/null
  if [ $? -eq 1 ] ; then
    echo "Error: bad string version in configure.ac" 
    exit 1;
  fi

  # Test version in file
  # README.md File
  VERSION=$(sed -n -re "s/(README[[:blank:]]+for[[:blank:]]+[[:alpha:]]+[[:blank:]]+)([[:digit:]]+\.[[:digit:]]+(\.[[:digit:]])?)(.*)/\2/p" < $README)
  echo "Current version : $VERSION"
  if [ "$NEW_VERSION" != "$VERSION"  ] ; then
    echo "Update $README ? y/n"
    yesOrNot
    if [ $answer == "y" ] ; then
      sed -i -re "s/^README for [[:alpha:]]+[[:blank:]+[[:digit:]]+.[[:digit:]]+.*/README for AeroUp $NEW_VERSION/"  $README
      echo -e "Update... ok"
    else
      echo "pass..."
    fi
  else
    echo "No think do to"
  fi

  # Src Files
  for file in $(find $DIR/../src/ -name "*.cpp" -o -name "*.h*"); do

    VERSION=(sed -n  -e 's/\(^[[:blank:]]\*[[:blank:]]\+Version:[[:blank:]]\+\)\([[:digit:]]\+\.[[:digit:]]\+\(\.[[:digit:]]\+\)*\)\([[:blank:]]\+\)/\2/p' $file)
    if [ "$NEW_VERSION" != "$VERSION"  ] ; then
      echo "Update "${file##*/../.}" ? y/n"
      yesOrNot
      if [ $answer == "y" ] ; then
        sed -i -re "/[[:blank:]]+\*[[:blank:]]+Version\:[[:blank:]]+/ s/[[:digit:]]+\.[[:digit:]]+(\.[[:digit:]])*/$NEW_VERSION/" $file
        echo -e "Update... ok"
      else
        echo "pass..."
      fi
  else
    echo "No think do to"
  fi
  done

fi	# ----------  end of opt_update  ----------

if [ $opt_help = 1 ]; then
  echo "$SCRIPT_NAME Usage :
    -u --update  Update version in project
    -y --yes     Always says yes
    -h --help    Print help
    -v --version Print version"
fi


