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
#   File: arbora.pri
#
# Author: $author$
#   Date: 4/26/2018
#
# QtCreator .pri file for arbora executable arbora
########################################################################

########################################################################
# arbora

# arbora_exe TARGET
#
arbora_exe_TARGET = arbora

# arbora_exe INCLUDEPATH
#
arbora_exe_INCLUDEPATH += \
$${arbora_INCLUDEPATH} \

# arbora_exe DEFINES
#
arbora_exe_DEFINES += \
$${arbora_DEFINES} \

########################################################################
# arbora_exe OBJECTIVE_HEADERS
#
#arbora_exe_OBJECTIVE_HEADERS += \
#$${ARBORA_SRC}/arbora/base/Base.hh \

# arbora_exe OBJECTIVE_SOURCES
#
#arbora_exe_OBJECTIVE_SOURCES += \
#$${ARBORA_SRC}/arbora/base/Base.mm \

########################################################################
# arbora_exe HEADERS
#
arbora_exe_HEADERS += \
$${ARBORA_SRC}/xos/base/std/tree/branch.hpp \
$${ARBORA_SRC}/xos/base/std/tree/search.hpp \
$${ARBORA_SRC}/xos/app/console/arbora/main.hpp \
$${FILA_SRC}/xos/console/main_main.hpp \

# arbora_exe SOURCES
#
arbora_exe_SOURCES += \
$${ARBORA_SRC}/xos/base/std/tree/branch.cpp \
$${ARBORA_SRC}/xos/base/std/tree/search.cpp \
$${ARBORA_SRC}/xos/app/console/arbora/main.cpp \
$${FILA_SRC}/xos/console/main_main.cpp \

########################################################################
# arbora_exe FRAMEWORKS
#
arbora_exe_FRAMEWORKS += \
$${arbora_FRAMEWORKS} \

# arbora_exe LIBS
#
arbora_exe_LIBS += \
$${arbora_LIBS} \


