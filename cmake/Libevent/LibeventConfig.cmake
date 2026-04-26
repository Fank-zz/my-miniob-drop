# Libevent CMake configuration file
set(Libevent_VERSION 2.1.12)

set(LIBEVENT_LIB_DIR /usr/lib/x86_64-linux-gnu)
set(LIBEVENT_INCLUDE_DIR /usr/include)

add_library(libevent::core SHARED IMPORTED)
set_target_properties(libevent::core PROPERTIES
    IMPORTED_LOCATION "${LIBEVENT_LIB_DIR}/libevent_core.so"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBEVENT_INCLUDE_DIR}"
)

add_library(libevent::pthreads SHARED IMPORTED)
set_target_properties(libevent::pthreads PROPERTIES
    IMPORTED_LOCATION "${LIBEVENT_LIB_DIR}/libevent_pthreads.so"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBEVENT_INCLUDE_DIR}"
)

add_library(libevent SHARED IMPORTED)
set_target_properties(libevent PROPERTIES
    IMPORTED_LOCATION "${LIBEVENT_LIB_DIR}/libevent.so"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBEVENT_INCLUDE_DIR}"
)