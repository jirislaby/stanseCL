#include "Parser.h"

int main(int argc, const char **argv)
{
	runParser("void f() {\n"
		"int a; a = 5;\n"
		"}");
}
