/*!
 *      @file  xml_join.cpp
 *     @brief  Application that joins several XML files into a simple one (CI purpose)
 *    @author  Luis Díaz Más (LDM), ldiaz@catec.aero
 *
 *  @internal
 *    Created  08/07/2014
 *   Compiler  gcc/g++
 *    Company  FADA-CATEC
 *  Copyright  Copyright (c) 2014, FADA-CATEC
 */

#include "XmlJoiner.h"

#include <argtable2.h>
#include <iostream>

// #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ##################
static void readArguments(int argc, char **argv);

// #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ###################
struct arg_str *argFolder  = arg_str1("i", "path", "STR", "Input path with XML files to join");
struct arg_str *argOutput  = arg_str1("o", "output", "STR", "Output xml file");
struct arg_lit *argHelp    = arg_lit0("h", "help", "Show this help");
struct arg_end *argErr     = arg_end(4);

void *argtable[] = {
   argFolder,
   argOutput,
   argHelp,
   argErr
};

int main(int argc, char **argv)
{
   readArguments(argc, argv);

   XmlJoiner joiner;
   joiner.processFolder(argFolder->sval[0]);
   joiner.writeOutput(argOutput->sval[0]);
}

static void readArguments(int argc, char **argv)
{
   int nerrors = arg_parse(argc, argv, argtable);
   if(argHelp->count)
   {
      arg_print_syntax(stdout, argtable, "\n");
      arg_print_glossary(stdout, argtable, "%-25s %s\n");
      exit(EXIT_SUCCESS);
   }
   else if(nerrors != 0)
   {
      std::cerr << "There was " << nerrors << " errors in the command line parsing\n";
      arg_print_syntax(stdout, argtable, "\n");
      arg_print_glossary(stdout, argtable, "%-25s %s\n");
      exit(EXIT_FAILURE);
   }
}
