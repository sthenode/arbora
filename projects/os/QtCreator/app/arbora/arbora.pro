########################################################################
# Copyright (c) 1988-2018 $organization$
#
# This software is provided by the author and contributors ``as is''
# and any express or implied warranties, including, but not limited to,
# the implied warranties of merchantability and fitness for a particular
# purpose are disclaimed. In no event shall the author or contributors
# be liable for any direct, indirect, incidental, special, exemplary,
# or consequential damages (including, but not limited to, procurement
# of substitute goods or services; loss of use, data, or profits; or
# business interruption) however caused and on any theory of liability,
# whether in contract, strict liability, or tort (including negligence
# or otherwise) arising in any way out of the use of this software,
# even if advised of the possibility of such damage.
#
#   File: arbora.pro
#
# Author: $author$
#   Date: 4/26/2018
#
# QtCreator .pro file for arbora executable arbora
########################################################################
include(../../../../../build/QtCreator/arbora.pri)
include(../../../../QtCreator/arbora.pri)
include(../../arbora.pri)
include(../../../../QtCreator/app/arbora/arbora.pri)

TARGET = $${arbora_exe_TARGET}

########################################################################
# INCLUDEPATH
#
INCLUDEPATH += \
$${arbora_exe_INCLUDEPATH} \

# DEFINES
# 
DEFINES += \
$${arbora_exe_DEFINES} \

########################################################################
# OBJECTIVE_HEADERS
#
OBJECTIVE_HEADERS += \
$${arbora_exe_OBJECTIVE_HEADERS} \

# OBJECTIVE_SOURCES
#
SOURCES += \
$${arbora_exe_OBJECTIVE_SOURCES} \

########################################################################
# HEADERS
#
HEADERS += \
$${arbora_exe_HEADERS} \

# SOURCES
#
SOURCES += \
$${arbora_exe_SOURCES} \
$${OBJECTIVE_SOURCES} \

########################################################################
# FRAMEWORKS
#
FRAMEWORKS += \
$${arbora_exe_FRAMEWORKS} \

# LIBS
#
LIBS += \
$${arbora_exe_LIBS} \
$${FRAMEWORKS} \


