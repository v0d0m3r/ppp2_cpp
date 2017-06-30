set("${PROJECT}_VERSION_MAJ" 0)
set("${PROJECT}_VERSION_MIN" 1)
set("${PROJECT}_VERSION_A" 1)
set("${PROJECT}_VERSION_B" 1)
set("${PROJECT}_VERSION" ${${PROJECT}_VERSION_MAJ}0${${PROJECT}_VERSION_MIN}0${${PROJECT}_VERSION_A}0${${PROJECT}_VERSION_B})

message(STATUS ${${PROJECT}_VERSION})

# основной файл программы
set(MAIN_SOURCES
    main.cpp
)

# непубличные пары исходников
set(PRIVATE_CLASSES
    "Link"
    ""
)

# файлы только заголовочные, у которых нет пары-исходника
set(HEADERS_ONLY
    ""
    ""
)

# публичные исходники
set(PUBLIC_CLASSES)

# используемые в программе библиотеки
set(ADDITIONAL_LIBRARIES
    stdc++   
)

set(PUBLIC_HEADERS
    ""
)

set(SOURCES)

# исходники графической библиотеки
set(GRAPH_LIB_CLASSES

)

# файлы только заголовочные, у которых нет пары-исходника
set(GRAPH_LIB_ONLY_HEADERS   
    "std_lib_facilities"
)

include(add_src_hdr.cmake)

add_executable(${PROJECT} ${MAIN_SOURCES} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT} ${ADDITIONAL_LIBRARIES})

set_target_properties(${PROJECT} PROPERTIES VERSION "${${PROJECT}_VERSION}" SOVERSION "0")

INSTALL(
    TARGETS
    ${PROJECT}
    DESTINATION
    lib${LIB_SUFFIX}
)

INSTALL(
    FILES
    ${PUBLIC_HEADERS}
    DESTINATION
    include/${PROJECT}
)
