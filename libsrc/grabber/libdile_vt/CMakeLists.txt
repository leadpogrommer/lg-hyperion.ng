SET(CURRENT_HEADER_DIR ${CMAKE_SOURCE_DIR}/include/grabber)
SET(CURRENT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libsrc/grabber/libdile_vt)

find_package(PkgConfig REQUIRED)

# ---
# find required packages
include(FindPkgConfig)

pkg_check_modules(PMLOG REQUIRED PmLogLib)
include_directories(${PMLOG_INCLUDE_DIRS})

add_subdirectory(libyuv)
add_subdirectory(tv-native-apis)

FILE ( GLOB LGGrabberSOURCES "${CURRENT_HEADER_DIR}/LG*.h"  "${CURRENT_SOURCE_DIR}/*.h"  "${CURRENT_SOURCE_DIR}/*.cpp" "${CURRENT_SOURCE_DIR}/*.c")

add_library(lg-grabber STATIC ${LGGrabberSOURCES} )
set_target_properties(lg-grabber PROPERTIES LINK_FLAGS "-lPmLogLib")

target_link_libraries(lg-grabber
        ${PMLOG_LDFLAGS}
        hyperion
        dile_vt yuv
        ${QT_LIBRARIES})
