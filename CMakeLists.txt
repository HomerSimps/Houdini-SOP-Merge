cmake_minimum_required( VERSION 3.6 )

project( HDK_Project )

list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )

find_package( Houdini REQUIRED )

set( library_name SOP_Merge )


houdini_generate_proto_headers( FILES SOP_MergeS.C )

add_library( ${library_name} SHARED
    SOP_MergeS.C
    SOP_MergeS.h
)

target_link_libraries( ${library_name} Houdini )

target_include_directories( ${library_name} PRIVATE
    ${CMAKE_CURRENT_BINARY_DIR}
)

houdini_configure_target( ${library_name} )
