cmake_minimum_required(VERSION 2.8.2)

project(openswg CXX)

# current version
set(OPENSWG_VERSION_MAJOR 1)
set(OPENSWG_VERSION_MINOR 0)
set(OPENSWG_VERSION_PATCH 4)
set(OPENSWG_VERSION 
	${OPENSWG_VERSION_MAJOR}.${OPENSWG_VERSION_MINOR}.${OPENSWG_VERSION_PATCH})
	
# set the path for custom cmake scripts
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build-aux/cmake")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

if(DEFINED VENDOR_PREFIX)
    set(BOOST_ROOT ${VENDOR_PREFIX}/boost)
    set(GLM_ROOT ${VENDOR_PREFIX}/glm)
    set(GLOG_ROOT ${VENDOR_PREFIX}/glog)
    set(GTEST_ROOT ${VENDOR_PREFIX}/gtest)
    set(GMOCK_ROOT ${VENDOR_PREFIX}/gmock)
    set(LUA_ROOT ${VENDOR_PREFIX}/lua)
    set(ENV{MYSQL_DIR} ${VENDOR_PREFIX}/mysql-connector-c)
    set(MysqlConnectorCpp_ROOT ${VENDOR_PREFIX}/mysql-connector-cpp)
    set(MYSQLPP_ROOT ${VENDOR_PREFIX}/mysql++)
    set(NOISE_ROOT ${VENDOR_PREFIX}/noise)
    set(PYTHON_ROOT ${VENDOR_PREFIX}/python)
    
    if(WIN32)
        set(ENV{TBB_ARCH_PLATFORM} "ia32\\vc10")
    endif()
    
    set(TBB_INSTALL_DIR ${VENDOR_PREFIX}/tbb)
    set(TOLUAPP_ROOT ${VENDOR_PREFIX}/tolua++)
    set(ZLIB_ROOT ${VENDOR_PREFIX}/zlib)
endif()

find_package(Boost 1.45.0 COMPONENTS date_time regex thread system program_options filesystem serialization REQUIRED)
find_package(Glm REQUIRED)
find_package(GLog REQUIRED)
find_package(GTest REQUIRED)
find_package(GMock REQUIRED)
find_package(MysqlConnectorC REQUIRED)
find_package(MYSQLPP REQUIRED)
find_package(TBB REQUIRED)
find_package(ZLib REQUIRED)

# make sure the source directory and the binary directory (where any generated
# files will be found) are automatically searched for includes
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_BINARY_DIR}/src     
    ${Boost_INCLUDE_DIR}
    ${GLOG_INCLUDE_DIR}
    ${MYSQLPP_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
)
 
link_directories(
	${Boost_LIBRARY_DIRS}
)

if(MSVC)
	get_filename_component(GLOG_DEBUG_DLL_PATH ${GLOG_LIBRARY_DEBUG} PATH)
	get_filename_component(GLOG_RELEASE_DLL_PATH ${GLOG_LIBRARY_RELEASE} PATH)
	get_filename_component(MYSQL_DLL_PATH ${MYSQL_LIB} PATH)
	get_filename_component(MYSQLPP_DEBUG_DLL_PATH ${MYSQLPP_LIBRARY_DEBUG} PATH)
	get_filename_component(MYSQLPP_RELEASE_DLL_PATH ${MYSQLPP_LIBRARY_RELEASE} PATH)
	get_filename_component(ZLIB_DEBUG_DLL_PATH ${ZLIB_LIBRARY_DEBUG} PATH)
	get_filename_component(ZLIB_RELEASE_DLL_PATH ${ZLIB_LIBRARY_RELEASE} PATH)

	add_definitions(/D HAVE_OPENSSL=0)
	add_definitions(/D WIN32_LEAN_AND_MEAN /D NOGDI)
	add_definitions(/D _CRT_SECURE_NO_WARNINGS)

	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4244")
	
	file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/logs)
	
	set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
	    
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/config DESTINATION bin)
	
	install(
	    DIRECTORY 
	          ${GLOG_DEBUG_DLL_PATH}/
	          ${MYSQL_DLL_PATH}/
	          ${MYSQLPP_DEBUG_DLL_PATH}/
	          ${ZLIB_DEBUG_DLL_PATH}/
	    DESTINATION bin
	    CONFIGURATIONS Debug
	    FILES_MATCHING PATTERN "*.dll"
	)
	
	install(
	    DIRECTORY 
	          ${GLOG_RELEASE_DLL_PATH}/
	          ${MYSQL_DLL_PATH}/
	          ${MYSQLPP_RELEASE_DLL_PATH}/
	          ${ZLIB_RELEASE_DLL_PATH}/
	    DESTINATION bin
	    CONFIGURATIONS Release
	    FILES_MATCHING PATTERN "*.dll"
	)
	
	install(
	    DIRECTORY 
	    DESTINATION bin/logs
	)
endif()

add_subdirectory(src/gsApplication)
add_subdirectory(src/gsCore)
add_subdirectory(src/gsNetwork)
add_subdirectory(src/gsServer)
add_subdirectory(src/Sockets)

add_subdirectory(src/osLogin)
add_subdirectory(src/osSOEProtocol)
add_subdirectory(src/osZonePreCU)
