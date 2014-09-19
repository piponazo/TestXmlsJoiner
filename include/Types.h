/*!
 *      @file  Types.h
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  05/09/2014
 */

#include <QString>
#include <vector>

namespace TestsXml
{

struct TestCase
{
   TestCase(const QString name, const QString valid) : _name(name), _valid(valid) {}

   QString  _name;
   QString  _valid;
   QString  _failureMsg;
   QString  _cDATA;
};

struct TestSuite
{
   TestSuite(const QString name, const int tests, const int failures, const int errors) :
       _name(name)
      ,_tests(tests)
      ,_failures(failures)
      ,_errors(errors)
   {}

   ~TestSuite();

   QString _name;
   quint32 _tests = 0;
   quint32 _failures = 0;
   quint32 _errors = 0;
   std::vector<TestCase *> _cases;
};

}
