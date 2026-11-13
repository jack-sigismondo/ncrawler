cmake_minimum_required(VERSION 3.8)
project(ncrawler LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Verbatim from https://cmake.org/cmake/help/latest/module/FindCurses.html
find_package(Curses)
if(Curses_FOUND AND NOT TARGET Curses::Curses)
  add_library(Curses::Curses INTERFACE IMPORTED)
  set_target_properties(
    Curses::Curses
    PROPERTIES
      INTERFACE_LINK_LIBRARIES "${CURSES_LIBRARIES}"
      INTERFACE_INCLUDE_DIRECTORIES "${CURSES_INCLUDE_DIRS}"
  )
endif()

add_executable(ncrawler
		main.c
		graphics.c
		logic.c
		map.c

		minigames/arrow.c
		minigames/fight.c)

file(COPY
	"${CMAKE_SOURCE_DIR}/maps"
	"${CMAKE_SOURCE_DIR}/graphics"
	DESTINATION "${CMAKE_BINARY_DIR}")

target_include_directories(ncrawler PRIVATE
				        ${CMAKE_CURRENT_SOURCE_DIR}
					${CMAKE_CURRENT_SOURCE_DIR}/minigames)
				    
target_link_libraries(ncrawler PRIVATE Curses::Curses)