/*!
 *      @file  tests_main.cpp
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  08/08/2014
 */

#include <gtest/gtest.h>
#define UNUSED(x) (void)(x)

int main(int argc, char **argv)
{
   ::testing::InitGoogleTest(&argc, argv);
   int ret = RUN_ALL_TESTS();
   UNUSED(ret);

   return EXIT_SUCCESS;
}
