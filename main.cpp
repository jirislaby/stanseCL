#include <string>

int main(int argc, const char **argv)
{
	void runParser(const std::string &);

	runParser("void f() {\n"
		"int a; a = 5;\n"
		"}");
}

#if 0
#include <clang/Serialization/PCHContainerOperations.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <clang/StaticAnalyzer/Frontend/FrontendActions.h>
#include <llvm/Support/Signals.h>
#include <llvm/Support/TargetSelect.h>

using namespace clang::tooling;
using namespace llvm;

static cl::OptionCategory StanseCLCategory("StanseCL");

int main(int argc, const char **argv)
{
	llvm::sys::PrintStackTraceOnErrorSignal(argv[0]);
	llvm::IntrusiveRefCntPtr<llvm::vfs::InMemoryFileSystem> VFS(
				new llvm::vfs::InMemoryFileSystem);
	VFS->addFile("/a.c", 0,
		    llvm::MemoryBuffer::getMemBuffer("void fun() {\n"
						     "\tint x;\n"
						     "}\n"));

	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmPrinters();
	llvm::InitializeAllAsmParsers();

	const char *my_argv[] = {
		argv[0],
		"/a.c",
		NULL
	};
	argc = 2;
	CommonOptionsParser OptionsParser(argc, my_argv, StanseCLCategory);
	ClangTool Tool(OptionsParser.getCompilations(),
		       OptionsParser.getSourcePathList(),
		       std::make_shared<clang::PCHContainerOperations>(),
		       VFS);

	// Clear adjusters because -fsyntax-only is inserted by the default chain.
	Tool.clearArgumentsAdjusters();
	Tool.appendArgumentsAdjuster(getClangStripOutputAdjuster());
	Tool.appendArgumentsAdjuster(getClangStripDependencyFileAdjuster());
	Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster(
					     "--analyze", ArgumentInsertPosition::BEGIN));

	std::unique_ptr<FrontendActionFactory> FrontendFactory;

	FrontendFactory = newFrontendActionFactory<clang::ento::AnalysisAction>();

	llvm::errs() << "ahoj\n";
	return Tool.run(FrontendFactory.get());
}

#endif
