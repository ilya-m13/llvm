#pragma once

#include <llvm/IR/Module.h>

#include <ostream>

namespace llvmgraph {

void call_graph(const llvm::Module *module, std::ostream &os);
void def_use_graph(const llvm::Module *module, std::ostream &os);

} // namespace llvmgraph
