/*!
 *      @file  TestXmlJoiner.cpp
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  08/08/2014
 */

#include "XmlJoiner.h"

#include <QDir>
#include <gtest/gtest.h>
#include <argtable2.h>

using namespace TestsXml;

extern struct arg_str *argPath;

class TestXmlJoiner : public ::testing::Test
{
protected:
   XmlJoiner *_joiner = nullptr;

   virtual void SetUp()
   {
      _joiner = new XmlJoiner();
   }

   virtual void TearDown()
   {
      delete _joiner;
   }
};

TEST_F(TestXmlJoiner, shouldCreateAndDestroyObjectInstance)
{
}

TEST_F(TestXmlJoiner, shouldProcessExistingFolderWithXmls)
{
   ASSERT_NO_THROW(_joiner->processFolder(argPath->sval[0]));
}

TEST_F(TestXmlJoiner, shouldNotProcessNonExistingFolder)
{
   ASSERT_THROW(_joiner->processFolder("nonExistingFolder"), std::logic_error);
}

TEST_F(TestXmlJoiner, shouldNotProcessExistingFolderWithoutXmlFiles)
{
   ASSERT_THROW(_joiner->processFolder("CMakeFiles"), std::logic_error);
}

TEST_F(TestXmlJoiner, shouldProcessExistingXmlFile)
{
   QDir xmlDir(argPath->sval[0]);
   QStringList extensions("*.xml");
   QStringList xmlFiles = xmlDir.entryList(extensions,
                                           QDir::Files | QDir::NoDotAndDotDot,
                                           QDir::Name);
   if (xmlFiles.empty() == false)
      ASSERT_THROW(_joiner->processFile(xmlFiles[0]), std::logic_error);
}

TEST_F(TestXmlJoiner, shouldNotProcessNonExistingFile)
{
   ASSERT_THROW(_joiner->processFile("nonExistingFile"), std::logic_error);
}

TEST_F(TestXmlJoiner, shouldNotProcessNonXmlFile)
{
   ASSERT_THROW(_joiner->processFile("CMakeCache.txt"), std::logic_error);
}

TEST_F(TestXmlJoiner, shouldWriteOutputFile)
{
   ASSERT_NO_THROW(_joiner->processFolder(argPath->sval[0]));
   ASSERT_NO_THROW(_joiner->writeOutput("prueba"));
}

TEST_F(TestXmlJoiner, shouldNotWriteOutputFile)
{
   ASSERT_NO_THROW(_joiner->processFolder(argPath->sval[0]));
   ASSERT_THROW(_joiner->writeOutput("/root/prueba"), std::logic_error);
}
