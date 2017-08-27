foreach (class ${PRIVATE_CLASSES})
    LIST (APPEND SOURCES ${class}.cpp)
    LIST (APPEND HEADERS ${class}.hpp)
endforeach ()

foreach (class ${HEADERS_ONLY})
    LIST (APPEND HEADERS ${class}.hpp)
endforeach ()

foreach (class ${PUBLIC_HEADERS})
    LIST (APPEND HEADERS ../include/${class}.hpp)
endforeach ()

foreach (class ${PUBLIC_CLASSES})
    LIST (APPEND SOURCES ${class}.cpp)
    LIST (APPEND HEADERS ../include/${PROJECT}/${class}.h)
    LIST (APPEND PUBLIC_HEADERS ../include/${class}.h)
endforeach ()

foreach (class ${GRAPH_LIB_CLASSES})
    LIST (APPEND SOURCES ../../../bstroustrup_code/${class}.cpp)
    LIST (APPEND HEADERS ../../../bstroustrup_code/${class}.h)
endforeach ()

foreach (class ${GRAPH_LIB_ONLY_HEADERS})
    LIST (APPEND HEADERS ../../../bstroustrup_code/${class}.h)
endforeach ()
