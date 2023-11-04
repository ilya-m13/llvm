#include <libllvmgraph/graph.hpp>

#include <llvm/IR/InstIterator.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_os_ostream.h>

#include <string_view>
#include <unordered_set>

namespace llvmgraph {

void call_graph(const llvm::Module *module, std::ostream &os) {
    os << "digraph graphname {\n";
    for (const auto &func : module->functions()) {
        std::unordered_set<std::string_view> checked_funcs;
        for (auto i = llvm::inst_begin(func), e = llvm::inst_end(func); i != e;
             i++) {
            const auto *callinst = llvm::dyn_cast<llvm::CallInst>(&*i);
            if (callinst == nullptr) {
                continue;
            }
            const auto callee = callinst->getCalledFunction()->getName();
            if (checked_funcs.contains(std::string_view(callee.data()))) {
                continue;
            }
            checked_funcs.emplace(callee.data());
            os << "\t" << func.getName().data() << " -> " << callee.data()
               << "\n";
        }
    }
    os << "}";
}

void def_use_graph(const llvm::Module *module, std::ostream &os) {
    llvm::raw_os_ostream raw_os(os);
    raw_os << "digraph graphname {\n";
    for (const auto &func : module->functions()) {
        for (auto i = llvm::inst_begin(func), e = llvm::inst_end(func); i != e;
             i++) {
            for (const auto &operand : i->operands()) {
                if (const auto *const instruction =
                        llvm::dyn_cast<llvm::Instruction>(operand.get())) {
                    raw_os << "\t\"" << *i << "\" -> \"" << *instruction
                           << "\"\n";
                }
            }
        }
    }
    raw_os << "}";
}

} // namespace llvmgraph
