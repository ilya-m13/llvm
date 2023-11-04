llvm_map_components_to_libnames(llvm_libs support core irreader)

set(appname ir-graph)

add_executable(${appname} ir-graph/main.cpp)

set_compile_options(${appname})
target_link_libraries(
    ${appname}
        ${llvm_libs}
        llvmgraph    
)