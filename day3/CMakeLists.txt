configure_file(sample_input.txt sample_input.txt COPYONLY)
configure_file(puzzle_input.txt puzzle_input.txt COPYONLY)

add_executable(day3 main.cpp)