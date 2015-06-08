/*
  module to read cfg file

  cfg file should be organized by module:
  moduleName (
             moduleParam1 val1
             moduleParam2 val2
             )

             
	YMeng 2014-03-15
	Add new functions to process the cfg files

 */

#ifndef CfgReader_H
#define CfgReader_H

#include <map>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class CfgReader{

public:
  CfgReader();

  map< string, map< string, string> > contents;
  string fName;  
  bool cfgIsInit;

  // populate contents from file
  int readCfgFile(string fName);

  // get value of string parameter in a module
  string getParam(string moduleName,
                  string paramName,
                  string defValue) const; //,
//                  bool useDefValue) const;
  
  // get value of parameter in a module
  template <typename Type>
  Type getParam(string moduleName,
                string paramName,
                Type defValue) const; //,
//                bool useDefValue) const;

  
private:

  // convert string to whatever specified type
  template <typename ValueType>
  ValueType string_to_Type(string name) const;


};


// templated functions must be defined in header

template <typename ValueType> inline
ValueType CfgReader::string_to_Type(string name) const
{
  istringstream input(name);
  ValueType returnVal;
  input >> returnVal;
  return returnVal;
}


inline string CfgReader::getParam(string moduleName,
                                  string paramName,
                                  string defValue) const //,
//                                bool useDefValue) const
{
  if (!cfgIsInit) {
    cout << "ERROR: CfgReader not initialized!!!" << endl;
    return defValue;
  }
  
  else if (contents.find(moduleName) == contents.end()) {
    cout << "ERROR: module \"" << moduleName
         << "\" doesn't exist!!!" << endl;
    return defValue;
  }
  
  //else if (useDefValue) {
  //  return defValue;
  //}
  
  else if (contents.at(moduleName).find(paramName) ==
           contents.at(moduleName).end()) {
    cout << "WARNING: CfgReader: "
         << moduleName << ": parameter \"" << paramName
         << "\" not found in cfg file. Setting to default: "
         << defValue << endl;
    return defValue;
  }
  
  cout << "CfgReader: " << moduleName
       << ": read parameter \"" << paramName << "\": "
       << contents.at(moduleName).at(paramName)
       << endl;

  return contents.at(moduleName).at(paramName);
}

template <typename Type> inline
Type CfgReader::getParam(string moduleName,
                         string paramName,
                         Type defValue) const //,
//                         bool useDefValue=false) const
{
  if (!cfgIsInit) {
    cout << "ERROR: CfgReader not initialized!!!" << endl;
    return defValue;
  }
  
  else if (contents.find(moduleName) == contents.end()) {
    cout << "ERROR: module \"" << moduleName
         << "\" doesn't exist!!!" << endl;
    return defValue;
  }
  
  //else if (useDefValue) {
  //  return defValue;
  //}
  
  else if (contents.at(moduleName).find(paramName) ==
           contents.at(moduleName).end()) {
    cout << "WARNING: CfgReader: "
         << moduleName << ": parameter \"" << paramName
         << "\" not found in cfg file. Setting to default: "
         << defValue << endl;
    return defValue;
  }
  
  cout << "CfgReader: " << moduleName
       << ": read parameter \"" << paramName << "\": "
       << string_to_Type<Type>(contents.at(moduleName).at(paramName))
       << endl;
  
  return string_to_Type<Type>(contents.at(moduleName).at(paramName));
}

  
#endif
