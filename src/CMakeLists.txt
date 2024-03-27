find_package(Boost REQUIRED COMPONENTS
                              filesystem
                              program_options
                              system
                              thread
                              unit_test_framework
                              )

FIND_PACKAGE(Wt REQUIRED Wt HTTP)
ADD_DEFINITIONS(-DHPDF_DLL)
include(CTest)
# enable_testing()

add_executable(calculus main.cc paintinginteractivewidget.cc paintingwidget.cc)
target_link_libraries(${PROJECT_NAME_STR}
                      # ${Boost_LIBRARIES}
                      ssl
                      # crypto
                      # stdc++fs
                      Wt::Wt
                      Wt::HTTP
                      # debug libhpdfd
                      )

# add_executable(BoostTest src/boostTester.cpp)
# target_link_libraries(
#   BoostTest
#   ${Boost_FILESYSTEM_LIBRARY}
#   ${Boost_SYSTEM_LIBRARY}
#   ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
# )
# add_test(boostTest BoostTest)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
