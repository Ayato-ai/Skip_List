set(target ${SKIP_LIST_CUSTOM})

file(GLOB hdrs "*.h*")

add_custom_target(${target} SOURCES ${hdrs})