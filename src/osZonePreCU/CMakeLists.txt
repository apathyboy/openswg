
FILE(GLOB SOURCES *.h *.cpp)

add_executable(osZonePreCU ${SOURCES})
target_link_libraries(osZonePreCU 
    gsApplication
    gsCore
    gsNetwork
    gsServer
    osSOEProtocol
    Sockets
	debug ${GLOG_LIBRARY_DEBUG}
	optimized ${GLOG_LIBRARY_RELEASE}
	debug ${MYSQLPP_LIBRARY_DEBUG}
	optimized ${MYSQLPP_LIBRARY_RELEASE}
	debug ${ZLIB_LIBRARY_DEBUG}
	optimized ${ZLIB_LIBRARY_RELEASE}
)
