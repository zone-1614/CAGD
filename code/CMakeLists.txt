file(GLOB headers CONFIGURE_DEPENDS *.h)

add_executable(de_casteljau bezier/de_casteljau.cpp ${headers})
target_link_libraries(de_casteljau Eigen3::Eigen)

add_executable(degree_elevation bezier/degree_elevation.cpp ${headers})
target_link_libraries(degree_elevation Eigen3::Eigen)