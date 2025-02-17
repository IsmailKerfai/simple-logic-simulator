cmake_minimum_required(VERSION 3.5.0)
project(asciimap VERSION 0.1.0)

# Compiler settings
set(CMAKE_CXX_STANDARD 20)
set(GCC_DEBUG_WARNINGS "-Wall;-Wextra;-Wpedantic;-Winit-self;-Wold-style-cast;-Wcast-qual;-Wundef;-Wsign-compare;-Woverloaded-virtual;-Wconversion;-Wzero-as-null-pointer-constant")
set(GCC_DEBUG_SANITIZE "-fsanitize=address;-fsanitize=undefined;-fsanitize=leak;-fsanitize=float-cast-overflow;-fno-omit-frame-pointer")
set(GCC_LIKE "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
add_compile_options("$<$<CONFIG:DEBUG>:$<${GCC_LIKE}:${GCC_DEBUG_WARNINGS}>>")
add_compile_options("$<$<CONFIG:DEBUG>:$<${GCC_LIKE}:${GCC_DEBUG_SANITIZE}>>")
add_link_options("$<$<CONFIG:DEBUG>:$<${GCC_LIKE}:${GCC_DEBUG_SANITIZE}>>")

# Main program
set(SRC_DIR ${PROJECT_SOURCE_DIR}/implementation)
set(ANALYSIS_DIR ${SRC_DIR}/Analysis-EDA)
set(SRC_FILES 
  ${ANALYSIS_DIR}/AnalysisEDA.cpp
)
link_directories(${PROJECT_SOURCE_DIR}/api/lib64)
add_executable(eda-lab ${SRC_FILES} ${SRC_DIR}/main.cpp)
target_link_libraries(eda-lab Circuit Library Parser)
target_include_directories(eda-lab PRIVATE ${PROJECT_SOURCE_DIR}/api/include ${SRC_DIR})
