/*!
 *      @file  XmlJoiner.h
 *    @author  Luis Díaz Más (LDM), ldiaz@catec.aero
 *
 *  @internal
 *    Created  08/07/2014
 *   Compiler  gcc/g++
 *    Company  FADA-CATEC
 *  Copyright  Copyright (c) 2014, FADA-CATEC
 */

#include <QStringList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QList>
#include <QMap>

struct TestCase
{
   TestCase(const QString name, const QString valid) : _name(name), _valid(valid) {}

   QString  _name;
   QString  _valid;
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
   QList<TestCase *> _cases;
};

/*!
 * \brief This class let you join the xml output of GTests and QTests and a unique file.
 *
 * There are some differencies between the two formats. In gtest we have and additional element
 * called testsuites that gather statistics of all the gtest. We can reject this data and extract
 * all the information from the common tags : testsuite & testcase.
 *
 * All the information from input XML are read and keeped in memory before writing the output file.
 *
 * \todo add more safety conditions
 * \todo use unique_ptr
 */
class XmlJoiner
{
public:
   ~XmlJoiner ();

   void processFolder(const QString folder);
   void processFile(const QString absolutePath);
   void writeOutput(const QString pathFile);

private:
   void processTestSuiteAttrs(const QXmlStreamAttributes attrs);
   void processTestCaseAttrs(const QXmlStreamAttributes attrs);

   void outputXmlHeader(QXmlStreamWriter &writer);
   void outputXmlElements(QXmlStreamWriter &writer);
   void outputXmlFooter(QXmlStreamWriter &writer);

   QStringList _files;

   QMap<QString, QString>           _totalProperties; // tests, failures, errors
   QList<TestSuite *>               _suites;
}; // -----  end of class XmlJoiner  -----

