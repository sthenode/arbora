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
# Os QtCreator .pri file for arbora
########################################################################
UNAME = $$system(uname)

contains(UNAME,Darwin) {
ARBORA_OS = macosx
} else {
ARBORA_OS = linux
}

#CONFIG += c++11
#CONFIG += c++0x

########################################################################
# rostra
ROSTRA_THIRDPARTY_PKG_MAKE_BLD = $${ROSTRA_THIRDPARTY_PKG}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
ROSTRA_THIRDPARTY_PRJ_MAKE_BLD = $${ROSTRA_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
ROSTRA_THIRDPARTY_PKG_BLD = $${ROSTRA_THIRDPARTY_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
ROSTRA_THIRDPARTY_PRJ_BLD = $${ROSTRA_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
ROSTRA_PKG_BLD = $${OTHER_BLD}/$${ROSTRA_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
ROSTRA_PRJ_BLD = $${OTHER_BLD}/$${ROSTRA_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
#ROSTRA_LIB = $${ROSTRA_THIRDPARTY_PKG_MAKE_BLD}/lib
#ROSTRA_LIB = $${ROSTRA_THIRDPARTY_PRJ_MAKE_BLD}/lib
#ROSTRA_LIB = $${ROSTRA_THIRDPARTY_PKG_BLD}/lib
#ROSTRA_LIB = $${ROSTRA_THIRDPARTY_PRJ_BLD}/lib
#ROSTRA_LIB = $${ROSTRA_PKG_BLD}/lib
ROSTRA_LIB = $${ROSTRA_PRJ_BLD}/lib
#ROSTRA_LIB = $${ARBORA_LIB}

# rostra LIBS
#
rostra_LIBS += \
-L$${ROSTRA_LIB}/lib$${ROSTRA_NAME} \
-l$${ROSTRA_NAME} \

########################################################################
# nadir
NADIR_THIRDPARTY_PKG_MAKE_BLD = $${NADIR_THIRDPARTY_PKG}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
NADIR_THIRDPARTY_PRJ_MAKE_BLD = $${NADIR_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
NADIR_THIRDPARTY_PKG_BLD = $${NADIR_THIRDPARTY_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
NADIR_THIRDPARTY_PRJ_BLD = $${NADIR_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
NADIR_PKG_BLD = $${OTHER_BLD}/$${NADIR_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
NADIR_PRJ_BLD = $${OTHER_BLD}/$${NADIR_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
#NADIR_LIB = $${NADIR_THIRDPARTY_PKG_MAKE_BLD}/lib
#NADIR_LIB = $${NADIR_THIRDPARTY_PRJ_MAKE_BLD}/lib
#NADIR_LIB = $${NADIR_THIRDPARTY_PKG_BLD}/lib
#NADIR_LIB = $${NADIR_THIRDPARTY_PRJ_BLD}/lib
#NADIR_LIB = $${NADIR_PKG_BLD}/lib
NADIR_LIB = $${NADIR_PRJ_BLD}/lib
#NADIR_LIB = $${ARBORA_LIB}

# nadir LIBS
#
nadir_LIBS += \
-L$${NADIR_LIB}/lib$${NADIR_NAME} \
-l$${NADIR_NAME} \

########################################################################
# crono
CRONO_THIRDPARTY_PKG_MAKE_BLD = $${CRONO_THIRDPARTY_PKG}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
CRONO_THIRDPARTY_PRJ_MAKE_BLD = $${CRONO_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
CRONO_THIRDPARTY_PKG_BLD = $${CRONO_THIRDPARTY_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
CRONO_THIRDPARTY_PRJ_BLD = $${CRONO_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
CRONO_PKG_BLD = $${OTHER_BLD}/$${CRONO_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
CRONO_PRJ_BLD = $${OTHER_BLD}/$${CRONO_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
#CRONO_LIB = $${CRONO_THIRDPARTY_PKG_MAKE_BLD}/lib
#CRONO_LIB = $${CRONO_THIRDPARTY_PRJ_MAKE_BLD}/lib
#CRONO_LIB = $${CRONO_THIRDPARTY_PKG_BLD}/lib
#CRONO_LIB = $${CRONO_THIRDPARTY_PRJ_BLD}/lib
#CRONO_LIB = $${CRONO_PKG_BLD}/lib
CRONO_LIB = $${CRONO_PRJ_BLD}/lib
#CRONO_LIB = $${ARBORA_LIB}

# crono LIBS
#
crono_LIBS += \
-L$${CRONO_LIB}/lib$${CRONO_NAME} \
-l$${CRONO_NAME} \

########################################################################
# fila
FILA_THIRDPARTY_PKG_MAKE_BLD = $${FILA_THIRDPARTY_PKG}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
FILA_THIRDPARTY_PRJ_MAKE_BLD = $${FILA_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
FILA_THIRDPARTY_PKG_BLD = $${FILA_THIRDPARTY_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
FILA_THIRDPARTY_PRJ_BLD = $${FILA_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
FILA_PKG_BLD = $${OTHER_BLD}/$${FILA_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
FILA_PRJ_BLD = $${OTHER_BLD}/$${FILA_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
#FILA_LIB = $${FILA_THIRDPARTY_PKG_MAKE_BLD}/lib
#FILA_LIB = $${FILA_THIRDPARTY_PRJ_MAKE_BLD}/lib
#FILA_LIB = $${FILA_THIRDPARTY_PKG_BLD}/lib
#FILA_LIB = $${FILA_THIRDPARTY_PRJ_BLD}/lib
#FILA_LIB = $${FILA_PKG_BLD}/lib
FILA_LIB = $${FILA_PRJ_BLD}/lib
#FILA_LIB = $${ARBORA_LIB}

# fila LIBS
#
fila_LIBS += \
-L$${FILA_LIB}/lib$${FILA_NAME} \
-l$${FILA_NAME} \

########################################################################
# archa
ARCHA_THIRDPARTY_PKG_MAKE_BLD = $${ARCHA_THIRDPARTY_PKG}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
ARCHA_THIRDPARTY_PRJ_MAKE_BLD = $${ARCHA_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/$${BUILD_CONFIG}
ARCHA_THIRDPARTY_PKG_BLD = $${ARCHA_THIRDPARTY_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
ARCHA_THIRDPARTY_PRJ_BLD = $${ARCHA_THIRDPARTY_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
ARCHA_PKG_BLD = $${OTHER_BLD}/$${ARCHA_PKG}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
ARCHA_PRJ_BLD = $${OTHER_BLD}/$${ARCHA_PRJ}/build/$${ARBORA_OS}/QtCreator/$${BUILD_CONFIG}
#ARCHA_LIB = $${ARCHA_THIRDPARTY_PKG_MAKE_BLD}/lib
#ARCHA_LIB = $${ARCHA_THIRDPARTY_PRJ_MAKE_BLD}/lib
#ARCHA_LIB = $${ARCHA_THIRDPARTY_PKG_BLD}/lib
#ARCHA_LIB = $${ARCHA_THIRDPARTY_PRJ_BLD}/lib
#ARCHA_LIB = $${ARCHA_PKG_BLD}/lib
ARCHA_LIB = $${ARCHA_PRJ_BLD}/lib
#ARCHA_LIB = $${ARBORA_LIB}

# archa LIBS
#
archa_LIBS += \
-L$${ARCHA_LIB}/lib$${ARCHA_NAME} \
-l$${ARCHA_NAME} \

########################################################################
# arbora

# arbora INCLUDEPATH
#
arbora_INCLUDEPATH += \

# arbora DEFINES
#
arbora_DEFINES += \

# arbora LIBS
#
arbora_LIBS += \
$${archa_LIBS} \
$${fila_LIBS} \
$${crono_LIBS} \
$${nadir_LIBS} \
$${rostra_LIBS} \
$${build_arbora_LIBS} \
-lpthread \
-ldl \

contains(ARBORA_OS,linux) {
arbora_LIBS += \
-lrt
} else {
}

