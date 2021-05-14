#include <iostream>

#include <clang/StaticAnalyzer/Core/Checker.h>
#include <clang/StaticAnalyzer/Core/CheckerManager.h>
#include <clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h>
#include <clang/StaticAnalyzer/Frontend/CheckerRegistry.h>

using namespace clang;
using namespace ento;

namespace {

class ParserPlugin : public Checker<check::ASTCodeBody, check::EndOfTranslationUnit> {
public:
	void checkEndOfTranslationUnit(const TranslationUnitDecl *TU,
				       AnalysisManager &,
				       BugReporter &) const {
		llvm::errs() << __func__ << ":\n";
		TU->dump();
	}

	void checkASTCodeBody(const Decl *D, AnalysisManager& mgr,
			BugReporter &) const {
		llvm::errs() << __func__ << ":\n";

		if (auto ND = dynamic_cast<const NamedDecl *>(D)) {
			llvm::errs() << "decl is NAMED as '" << ND->getName() << "'\n";
		}

		if (CFG *cfg = mgr.getCFG(D)) {
			llvm::errs() << "dumping a CFG:\n";
			cfg->dump(mgr.getLangOpts(), true);
		} else {
			llvm::errs() << "NOT a CFG:\n";
			D->dump();
		}
	}
};

}

void registerParserPlugin(CheckerManager &mgr) {
	mgr.registerChecker<ParserPlugin>();
}

bool shouldRegisterParserPlugin(const CheckerManager &) {
	return true;
}

extern "C" void clang_registerCheckers(CheckerRegistry &registry) {
  registry.addChecker(registerParserPlugin, shouldRegisterParserPlugin,
		      "stanseCL.MyChecker", "Example Description",
		      "stanseCL.mychecker.documentation.nonexistent.html",
		      false);
#if 0
  registry.addCheckerOption(/*OptionType*/ "bool",
			    /*CheckerFullName*/ "stanseCL.MyChecker",
			    /*OptionName*/ "ExampleOption",
			    /*DefaultValStr*/ "false",
			    /*Description*/ "This is an example checker opt.",
			    /*DevelopmentStage*/ "released");
#endif
}

extern "C" const char clang_analyzerAPIVersionString[] =
    CLANG_ANALYZER_API_VERSION_STRING;

#if 0
class Consumer : public ASTConsumer {
	void HandleTranslationUnit(ASTContext &Ctx) override {
		auto TU = Ctx.getTranslationUnitDecl();
		for (auto D: TU->decls())
			if (auto FD = dyn_cast<FunctionDecl>(D)) {
				FD->getASTContext().get;
				clang::AnalysisDeclContext A;
			}
	}
};


class ParserPlugin : public clang::PluginASTAction {

	std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance &,
			StringRef) override {
		return std::make_unique<Consumer>();
	}

	bool ParseArgs(const CompilerInstance &,
			const std::vector<std::string> &) override {
		return true;
	}

};

static FrontendPluginRegistry::Add<ParserPlugin> X("stanseCL", "my plugin description");
#endif
