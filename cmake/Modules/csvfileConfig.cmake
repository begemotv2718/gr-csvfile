INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_CSVFILE csvfile)

FIND_PATH(
    CSVFILE_INCLUDE_DIRS
    NAMES csvfile/api.h
    HINTS $ENV{CSVFILE_DIR}/include
        ${PC_CSVFILE_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    CSVFILE_LIBRARIES
    NAMES gnuradio-csvfile
    HINTS $ENV{CSVFILE_DIR}/lib
        ${PC_CSVFILE_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(CSVFILE DEFAULT_MSG CSVFILE_LIBRARIES CSVFILE_INCLUDE_DIRS)
MARK_AS_ADVANCED(CSVFILE_LIBRARIES CSVFILE_INCLUDE_DIRS)

