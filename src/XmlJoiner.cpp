/*!
 *      @file  XmlJoiner.cpp
 *    @author  Luis Díaz Más (LDM), piponazo@gmail.com
 *
 *  @internal
 *    Created  08/07/2014
 */

#include "XmlJoiner.h"

#include <QDir>
#include <QDebug>
#include <stdexcept>

XmlJoiner::~XmlJoiner()
{
   foreach(auto testSuite, _suites)
   {
      delete testSuite;
   }
}

void XmlJoiner::processFolder(const QString folder)
{
   QDir xmlDir(folder);
   QStringList extensions("*.xml");
   foreach(const QString &file, xmlDir.entryList(extensions,
           QDir::Files | QDir::NoDotAndDotDot, QDir::Name))
   {
      processFile(xmlDir.absoluteFilePath(file));
   }
}

void XmlJoiner::processFile(const QString absolutePath)
{
   QFile file(absolutePath);

   if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
      throw std::runtime_error("Error opening file " + absolutePath.toStdString());
   }

   QXmlStreamReader xml(&file);

   while(!xml.atEnd() && !xml.hasError())
   {
      QXmlStreamReader::TokenType token = xml.readNext();

      if(token == QXmlStreamReader::StartElement)
      {
         if(xml.name() == "testsuite")
         {
            processTestSuiteAttrs(xml.attributes());
         }
         else if(xml.name() == "testcase")
         {
            processTestCaseAttrs(xml.attributes());
         }
      }
   }

   if(xml.hasError())
   {
      throw std::runtime_error("Error parsing the xml file " + absolutePath.toStdString());
   }
   file.close();
}

void XmlJoiner::processTestSuiteAttrs(const QXmlStreamAttributes attrs)
{
   TestSuite * suite = new TestSuite(attrs.value("name").toString(),
                                     attrs.value("tests").toString().toInt(),
                                     attrs.value("failures").toString().toInt(),
                                     attrs.value("errors").toString().toInt());
   _suites.push_back(suite);
}

void XmlJoiner::processTestCaseAttrs(const QXmlStreamAttributes attrs)
{
   QString valid("run");

   if(attrs.hasAttribute("status"))  // google tests case
   {
      if(attrs.value("status") != "run")
      {
         valid = attrs.value("status").toString();
      }
   }
   else if(attrs.hasAttribute("result"))  // qt tests case
   {
      if(attrs.value("result") != "pass")
      {
         valid = attrs.value("result").toString();
      }
   }

   TestSuite *suite = _suites.back();
   TestCase *testCase = new TestCase(attrs.value("name").toString(), valid);
   suite->_cases.push_back(testCase);
}

void XmlJoiner::writeOutput(const QString pathFile)
{
   QFile outFile(pathFile);

   if(!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
   {
      qDebug() << "Error opening output file for writing";
      /// \todo throw exception and delete debug message
      exit(-1);
   }

   QXmlStreamWriter xmlOut(&outFile);
   outputXmlHeader(xmlOut);
   outputXmlElements(xmlOut);
   outputXmlFooter(xmlOut);
}

void XmlJoiner::outputXmlHeader(QXmlStreamWriter &writer)
{
   writer.setAutoFormatting(true);
   writer.writeStartDocument();
   writer.writeStartElement("testsuites");

   // Gather information about all the tests
   int tests=0, failures=0, errors=0;
   foreach(const auto testSuite, _suites)
   {
      tests += testSuite->_tests;
      failures += testSuite->_failures;
      errors += testSuite->_errors;
   }

   writer.writeAttribute("name", "AllTests");
   writer.writeAttribute("tests", QString::number(tests));
   writer.writeAttribute("failures", QString::number(failures));
   writer.writeAttribute("errors", QString::number(errors));
}

void XmlJoiner::outputXmlElements(QXmlStreamWriter &writer)
{
   foreach(const auto testSuite, _suites)
   {
      writer.writeStartElement("testsuite");
      writer.writeAttribute("name", testSuite->_name);
      writer.writeAttribute("tests", QString::number(testSuite->_tests));
      writer.writeAttribute("failures", QString::number(testSuite->_failures));
      writer.writeAttribute("errors", QString::number(testSuite->_errors));

      foreach(const auto testCase, testSuite->_cases)
      {
         writer.writeStartElement("testcase");
         writer.writeAttribute("name", testCase->_name);
         writer.writeAttribute("status", testCase->_valid);
         writer.writeAttribute("classname", testSuite->_name);
         writer.writeEndElement();
      }

      writer.writeEndElement();
   }
}

void XmlJoiner::outputXmlFooter(QXmlStreamWriter &writer)
{
   writer.writeEndElement(); // testsuites
   writer.writeEndDocument();
}


TestSuite::~TestSuite()
{
   foreach(auto testCase, _cases)
   {
      delete testCase;
   }
}
