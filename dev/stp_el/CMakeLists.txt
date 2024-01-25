cmake_minimum_required(VERSION 3.15.0)
project(stp-el VERSION 1.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(stp_el stp.c stp_el.c ../../event_loop.c ../../timerlib.c network_utils.c rt.c)
target_link_libraries(stp_el PUBLIC pthread)
