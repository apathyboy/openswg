
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

if(WIN32)
    configure_file(${CMAKE_SOURCE_DIR}/build-aux/windows/user_project.vcxproj.in
        ${CMAKE_CURRENT_BINARY_DIR}/osZonePreCU.vcxproj.user @ONLY
    )
        
    if (NOT EXISTS ${CMAKE_BINARY_DIR}/config/login.ini)
        file(COPY ${CMAKE_SOURCE_DIR}/data/config/login.ini
            DESTINATION ${CMAKE_BINARY_DIR}/config)
    endif()
endif()

install(TARGETS osZonePreCU DESTINATION bin)