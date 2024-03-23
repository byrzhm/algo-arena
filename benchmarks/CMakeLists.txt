message(STATUS "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp")
message(STATUS "Benchmarks: ${SRC_FILES}")

foreach(SRC_FILE ${SRC_FILES})
    get_filename_component(NAME ${SRC_FILE} NAME_WE)
    add_executable(${NAME} ${SRC_FILE})
    target_link_libraries(
        ${NAME}
        PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
    )
endforeach()
