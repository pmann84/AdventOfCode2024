configure_file(sample_input.txt sample_input.txt COPYONLY)
configure_file(puzzle_input.txt puzzle_input.txt COPYONLY)

add_executable(day1 main.cpp)
target_link_libraries(day1 sage)