file(GLOB headers CONFIGURE_DEPENDS *.h)

add_executable(de_casteljau bezier/de_casteljau.cpp ${headers})
target_link_libraries(de_casteljau Eigen3::Eigen)

add_executable(degree_elevation bezier/degree_elevation.cpp ${headers})
target_link_libraries(degree_elevation Eigen3::Eigen)

add_executable(catmull_clark subdivision/catmull_clark_subdivision.cpp)
target_include_directories(catmull_clark PRIVATE ${OPENMESH_INCLUDE_DIRS})
target_link_libraries(catmull_clark PRIVATE ${OPENMESH_LIBRARIES})

add_executable(nurbs B-Spline/nurbs.cpp ${headers})
target_link_libraries(nurbs Eigen3::Eigen)