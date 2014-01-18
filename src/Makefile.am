bin_PROGRAMS =   aeroup 

ext_src =
if BOOST 
ext_src += serialboost.cpp
ext_src += regboost.cpp 
#echo have boost
else
ext_src += reglinux.cpp 
ext_src += seriallinux.cpp
#echo have not boost
endif

aeroup_SOURCES = \
								 main.cpp \
								 ultimate.cpp \
								 serialprop.cpp \
								 optmanager.cpp \
								 gloseq.cpp \
								 buffer.cpp \
								 buffermanager.cpp \
								 rules.cpp \
								 ${ext_src}

aeroup_CPPFLAGS = -W -Wall -std=c++11 
aeroup_LDFLAGS =  
#LIBS += 
#-DSERIAL_BOOST_LIB
