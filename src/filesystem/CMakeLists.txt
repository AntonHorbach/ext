set(
        INCLUDES
        ${INCLUDE_DIR}/
        ${INCLUDE_DIR}/filesystem/
)

set(
        SOURCES
        EntryInfo.cpp
        EntryType.cpp
        filesystem_utils.cpp
)

add_library(ext-filesystem ${SOURCES})
target_include_directories(ext-filesystem PUBLIC ${INCLUDES})