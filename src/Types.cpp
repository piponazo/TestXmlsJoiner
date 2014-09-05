/*!
 *      @file  Types.cpp
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  05/09/2014
 */

#include "Types.h"

namespace TestsXml
{

TestSuite::~TestSuite()
{
   for(auto &testCase: _cases)
   {
      delete testCase;
   }
}

}
