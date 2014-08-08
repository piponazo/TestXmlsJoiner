/*!
 *      @file  TestXmlJoiner.cpp
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  08/08/2014
 */

#include "XmlJoiner.h"
#include <gtest/gtest.h>

class TestXmlJoiner : public ::testing::Test
{
protected:
   XmlJoiner *_joiner = nullptr;

   virtual void SetUp()
   {
      /// \todo add unique_ptr
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
