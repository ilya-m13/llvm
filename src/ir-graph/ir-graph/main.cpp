#include <libllvmgraph/graph.hpp>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/CommandLine.h>

#include <fstream>
#include <iostream>

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
llvm::cl::opt<std::string> c_inputfile(
    "input",
    llvm::cl::desc("input filename"),
    llvm::cl::value_desc("filename"),
    llvm::cl::Required);
llvm::cl::alias c_inputfile_short(
    "i", llvm::cl::desc("alias for --input"), llvm::cl::aliasopt(c_inputfile));
llvm::cl::opt<std::string> c_outputfile(
    "output",
    llvm::cl::desc("output filename"),
    llvm::cl::value_desc("filename"),
    llvm::cl::init(""));
llvm::cl::alias c_outputfile_short(
    "o",
    llvm::cl::desc("alias for --output"),
    llvm::cl::aliasopt(c_outputfile));
llvm::cl::opt<bool>
    c_dot_call_graph("dot-callgraph", llvm::cl::desc("output callgraph"));
llvm::cl::opt<bool>
    c_dot_def_use("dot-def-use", llvm::cl::desc("output def-use"));
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

int main(int argc, char **argv) {
    llvm::cl::ParseCommandLineOptions(argc, argv);

    if (!(c_dot_call_graph || c_dot_def_use)) {
        std::cerr << "The option to dot a graph is not selected\n";
        return 0;
    }

    llvm::SMDiagnostic err;
    llvm::LLVMContext context;
    const auto m = llvm::parseIRFile(c_inputfile, err, context);
    if (m == nullptr) {
        err.print("ir-graph", llvm::errs());
        return 1;
    }

    std::ofstream ofs;
    std::ostream os(std::cout.rdbuf());
    if (!c_outputfile.empty()) {
        ofs.open(c_outputfile);
        os.rdbuf(ofs.rdbuf());
    }

    if (c_dot_call_graph) {
        llvmgraph::call_graph(m.get(), os);
    }
    if (c_dot_def_use) {
        llvmgraph::def_use_graph(m.get(), os);
    }
}