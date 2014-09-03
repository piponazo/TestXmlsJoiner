/*!
 *      @file  tests_main.cpp
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  08/08/2014
 */

#include <gtest/gtest.h>
#include <argtable2.h>

using namespace std;

#define UNUSED(x) (void)(x)

// #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ##################
static void readArguments(int argc, char **argv);

// #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ###################
struct arg_str *argPath = arg_str1("p", "path", "PATH", "Path with xml files");
struct arg_lit *argHelp = arg_lit0("h", "help", "Show this help");
struct arg_end *argErr  = arg_end(3);
void *argtable[] = {
   argPath,
   argHelp,
   argErr
};

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   readArguments(argc, argv);

   int ret = RUN_ALL_TESTS();
   UNUSED(ret);

   arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
   return EXIT_SUCCESS;
}

static void readArguments(int argc, char **argv)
{
   int nerrors = arg_parse(argc, argv, argtable);

   if(argHelp->count)
   {
      arg_print_syntax(stdout, argtable, "\n");
      arg_print_glossary(stdout, argtable, "%-25s %s\n");
      arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
      exit(EXIT_SUCCESS);
   }
   else if(nerrors != 0)
   {
      cerr << "There was " << nerrors << " errors in the command line parsing\n";
      arg_print_syntax(stdout, argtable, "\n");
      arg_print_glossary(stdout, argtable, "%-25s %s\n");
      arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
      exit(EXIT_FAILURE);
   }
}
