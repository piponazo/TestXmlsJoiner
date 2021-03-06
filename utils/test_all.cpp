/*!
 *      @file  test_all.cpp
 *    @author  Luis Díaz Más (LDM), ldiaz@catec.aero
 *
 *  @internal
 *    Created  05/08/2014
 *   Compiler  gcc/g++
 *    Company  FADA-CATEC
 *  Copyright  Copyright (c) 2014, FADA-CATEC
 */

#include "XmlJoiner.h"
#include "dataModel/DataModel/types.h"
#include "dataModel/DataModel/AircraftStates/InertialState.h"
#include "dataModel/DataModel/AircraftStates/CustomState.h"
#include "dataModel/DataModel/sys_status.h"
#include "unitTests/plugins/HmiARCAS/testHmiARCAS.h"
#include "unitTests/plugins/AutoWaypoint/testAutoWaypoint.h"
#include "business/CController.h"

#include "gtest/gtest.h"
#include <QApplication>
#include <QtTest>
#include <argtable2.h>

using namespace gcs;

// #####   PROTOTYPES  -  LOCAL TO THIS SOURCE FILE   ##################
static void readArguments(int argc, char **argv);

// #####   VARIABLES  -  LOCAL TO THIS SOURCE FILE   ###################
struct arg_str *plugsPath  = arg_str1("p", "path", "STR", "Path with plugins");
struct arg_str *argXml     = arg_str0("x", "xml", "STR", "Generate XML files reporting results");
struct arg_lit *argHelp    = arg_lit0("h", "help", "Show this help");
struct arg_end *argErr     = arg_end(3);
void *argtable[] = {
   plugsPath,
   argXml,
   argHelp,
   argErr
};

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   QApplication app(argc, argv);
   readArguments(argc, argv);

   QCoreApplication::setOrganizationName("FADA-CATEC");
   QCoreApplication::setApplicationName("GCS");

   qRegisterMetaType<UavInertialDTO>("UavInertialDTO");
   qRegisterMetaType<UavCustomDTO>  ("UavCustomDTO");
   qRegisterMetaType<SysStatusDTO>  ("SysStatusDTO");
   qRegisterMetaType<AlarmSeverity> ("AlarmSeverity");
   qRegisterMetaType<AlarmSource>   ("AlarmSource");

   int ret = 0;
   XmlJoiner * xmlJoiner = nullptr;
   QStringList qTestCmds;
   if (argXml->count)
   {
      xmlJoiner = new XmlJoiner();
      qTestCmds << " " << "-xunitxml" << "-o" << "qtests.xml";
   }

   // Run tests implemented with Google test framework
   ret += RUN_ALL_TESTS();
   if (argXml->count) { xmlJoiner->processFile("test_detail.xml"); }

   // Run tests implemented with Qt test framework
   HmiARCASTest      testHmi;
   ret += QTest::qExec(&testHmi, qTestCmds);
   if (argXml->count) { xmlJoiner->processFile("qtests.xml"); }

   AutoWaypointTest  testAutoWp;
   ret += QTest::qExec(&testAutoWp, qTestCmds);
   if (argXml->count) { xmlJoiner->processFile("qtests.xml"); }

   Q_UNUSED(ret);
   ControllerSingleton::destroySingleton();
   if (argXml->count) { xmlJoiner->writeOutput(argXml->sval[0]); }

   arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
   delete xmlJoiner;

   return EXIT_SUCCESS; // Because of CI
}  // ----------  end of function main  ----------

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
