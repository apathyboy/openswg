find_path(MYSQLPP_INCLUDE_DIR mysql++.h
    PATH_SUFFIXES include lib
    HINTS
        $ENV{MYSQLPP_ROOT}
        ${MYSQLPP_ROOT}
        ${MYSQLPP_INCLUDEDIR}
)

find_library(MYSQLPP_LIBRARY_DEBUG
    NAMES mysqlpp_d libmysqplpp_d
    PATH_SUFFIXES lib lib/Debug Debug vc2008/Debug
    HINTS
        $ENV{MYSQLPP_ROOT}
        ${MYSQLPP_ROOT}
        ${MYSQLPP_LIBRARYDIR}
)

find_library(MYSQLPP_LIBRARY_RELEASE
    NAMES mysqlpp libmysqplpp
    PATH_SUFFIXES lib lib/Release Release vc2008/Release
    HINTS
        $ENV{MYSQLPP_ROOT}
        ${MYSQLPP_ROOT}
        ${MYSQLPP_LIBRARYDIR}
)

# handle the QUIETLY and REQUIRED arguments and set OPENAL_FOUND to TRUE if
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MYSQLPP DEFAULT_MSG MYSQLPP_LIBRARY_DEBUG MYSQLPP_LIBRARY_RELEASE MYSQLPP_INCLUDE_DIR)

mark_as_advanced(MYSQLPP_LIBRARY_DEBUG MYSQLPP_LIBRARY_RELEASE MYSQLPP_INCLUDE_DIR)
