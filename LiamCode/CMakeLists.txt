#This is one of my first CMake files so do not trust it.
cmake_minimum_required(VERSION 2.6)

#The name of this project is (tentatively) VG_1
project(VG_1)

#Displays all warnings
set(CMAKE_CPP_FLAGS -Wall)

#These include the directories with the various GL files
#WARNING, MAY NOT WORK FOR SYSTEMS OTHER THAN LINUX!
include_directories(/usr/X11R6/include /usr/local/include)
link_directories(/usr/X11R6/lib /usr/local/lib)

#creates the executables and links the various cpp files together
add_executable(main main.cpp level.cpp Character.cpp)

#links the various openGL libraries to main.
SET(EXTRA_LIBS GL X11 GLU glut)
target_link_libraries(main ${EXTRA_LIBS})


#g++ -Wall -I/usr/X11R6/include -I/opt/local/include -L/opt/local/lib -L/usr/X11R6/lib -lglut -lglu -lgl -o main main.cpp
