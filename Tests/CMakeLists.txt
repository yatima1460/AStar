include(FetchContent)

# Pin GoogleTest v1.16.0 to an exact commit; library-only builds do not fetch it.
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG 6910c9d9165801d8827d628cb72eb7ea9dd538c5
)

# Keep the parent project's MSVC runtime choice.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(Pathfinder Main.cpp Test.cpp)
target_compile_features(Pathfinder PRIVATE cxx_std_17)
set_target_properties(Pathfinder PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(Pathfinder PRIVATE Pathfinding GTest::gtest)

include(GoogleTest)
# The StaticAnalyzer tests in Test.cpp contain hard-coded /home/... paths.
# Run only behavioral tests through CTest until those sources are made portable.
gtest_discover_tests(Pathfinder TEST_FILTER "Pathfinding.*")
