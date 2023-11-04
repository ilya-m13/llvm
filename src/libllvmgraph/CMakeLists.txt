llvm_map_components_to_libnames(llvm_libs support core)

set(libname llvmgraph)

add_library(
  ${libname}
  STATIC
    libllvmgraph/graph.cpp  
)

set_compile_options(${libname})
target_compile_definitions(
  ${libname}
  PUBLIC
    ${LLVM_DEFINITIONS_LIST}
)
target_include_directories(
  ${libname}
    SYSTEM PUBLIC ${LLVM_INCLUDE_DIRS}
    PUBLIC .
)
target_link_libraries(
  ${libname}
    ${llvm_libs}
)