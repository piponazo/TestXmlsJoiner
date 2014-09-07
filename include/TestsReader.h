/*!
 *      @file  TestsReader.h
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  05/09/2014
 */

#include <QString>

namespace TestsXml
{

/*!
 * \brief Collect stats about a xml test report.
 */
class FileReader
{
public:
   /// @brief Constructor.
   /// @param path[in] File path of the xml file.
   FileReader(const QString path);

private:
   void processTestSuiteAttrs(const QXmlStreamAttributes attrs);
   void processTestCaseAttrs(const QXmlStreamAttributes attrs);
   void processTestFailureAttrs(const QXmlStreamAttributes attrs);
};

}
