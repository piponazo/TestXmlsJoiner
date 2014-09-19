/*!
 *      @file  XmlJoiner.h
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  07/08/2014
 */

#include "Types.h"

#include <QStringList>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QMap>

#include <vector>

namespace TestsXml
{

/*!
 * \brief This class let you join the several XML test reports obtained with different framework.
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
   void processTestFailureAttrs(const QXmlStreamAttributes attrs);
   void processTestCDataAttrs(const QStringRef text);

   void outputXmlHeader(QXmlStreamWriter &writer);
   void outputXmlElements(QXmlStreamWriter &writer);
   void outputXmlFooter(QXmlStreamWriter &writer);

   QStringList _files;

   QMap<QString, QString>           _totalProperties; // tests, failures, errors
   std::vector<TestSuite *>         _suites;
}; // -----  end of class XmlJoiner  -----

}
