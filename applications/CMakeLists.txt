file(GLOB app_list CONFIGURE_DEPENDS "*.cpp")

foreach(app ${app_list})
    get_filename_component(app_name "${app}" NAME_WE)
    add_executable(${app_name} ${app_name}.cpp)
    target_link_libraries(${app_name} PRIVATE ${OpenCV_LIBS})
endforeach()
