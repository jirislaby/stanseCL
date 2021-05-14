#include <clang/Frontend/CompilerInstance.h>

int main()
{
	clang::CompilerInstance CI;

	CI.createFileManager();
	CI.createSourceManager(CI.getFileManager());
	CI.createPreprocessor(clang::TU_Prefix);

	CI.createASTContext();

	return 0;
}
