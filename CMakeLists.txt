cmake_minimum_required(VERSION 3.0)	  #Указываем версию сmake
project(ssl_server VERSION 1 LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
add_executable("${PROJECT_NAME}.a" main.cpp src/server.cpp src/session.cpp src/parsing.cpp)  #Указываем результат работы и все исходники
#add_subdirectory(asio_server asio_server/build) #Добавить подпроект со своим файлов "CMakeList.txt"
#add_library(mylib STATIC test1.cpp test2.cpp test3.cpp) Генерирует библиотеку указаного вида из указанных исходников
#target_link_libraries(asio_server boost_date_time pthread) #Линкую указанные библиотеки

set_target_properties("${PROJECT_NAME}.a" 
	PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/debug"
) #Устанавливаю директорию с исполняемым файлом

add_definitions(-DDEBUG)	

find_package(Boost 1.75.0 REQUIRED COMPONENTS system thread) #Подключение boost asio
find_package(OpenSSL)
#if (Boost_FOUND)
#	target_INCLUDE_DIRECTORIES(asio_server ${Boost_INCLUDE_DIRS})
#	target_LINK_DIRECTORIES(asio_server ${Boost_LIBRARY_DIRS})
#endif(Boost_FOUND)

set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${OPENSSL_LIBRARIES})

target_link_libraries("${PROJECT_NAME}.a" ${USED_LIBS})


