
FILE(GLOB SOURCES *.h *.cpp)

add_executable(osZonePreCU ${SOURCES})
target_link_libraries(osZonePreCU 
    gsApplication
    gsCore
    gsNetwork
    gsObjects
    gsServer
    osSOEProtocol
    Sockets
)
