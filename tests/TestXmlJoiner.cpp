/*!
 *      @file  TestXmlJoiner.cpp
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  08/08/2014
 */

#include "XmlJoiner.h"

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

TEST_F(TestXmlJoiner, shouldWriteOutputFile)
{
   ASSERT_NO_THROW(_joiner->processFolder(argPath->sval[0]));
   ASSERT_NO_THROW(_joiner->writeOutput("prueba"));
}
