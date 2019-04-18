project(ExecutionPolicyThreadCountTest)

add_executable(${PROJECT_NAME} main.cpp)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED on)
target_compile_options(${PROJECT_NAME}
                       PRIVATE /W4
                               /WX
                               /permissive-
                               /Zc:twoPhase-)
target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN NOMINMAX)
