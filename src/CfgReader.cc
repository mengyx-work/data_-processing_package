/*

  source code for cfgReader.hh


 */


#include "CfgReader.hh"

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm> //std::find_if

using namespace std;


CfgReader::CfgReader()
{
  
  cfgIsInit = false;

}


int CfgReader::readCfgFile(string fName)
{
  fstream inStream;
  inStream.open(fName.c_str(), ios::in);
  if (!inStream.is_open())
    return 0;
  string line;
  string tmpModuleName;
  while (getline(inStream, line)) {

    // trim white space from beginning of string
    line.erase(line.begin(), std::find_if(line.begin(), line.end(), not1(ptr_fun<int, int>(isspace))));
    
    // ignore line if is comment or is empty
    if (line[0] == '#' || line.empty()) continue;
    
    // read first two elements of line, ignore rest of line
    string elem1 = line.substr(0, line.find(' '));
    line.erase(0, line.find(' ')+1);
    string elem2 = line.substr(0, line.find(' '));


    // if first element is ), this is end of module parameters. move on to next line
    if (elem1[0] == ')')
      continue;


    // if second element is (, then first element is module name
    if (elem2[0] == '(') {
      tmpModuleName = elem1;
      // check if module is in contents yet
      if (contents.find(elem1) == contents.end()) {
        map< string, string> moduleContents;
        contents.insert( pair<string, map<string, string> >(elem1, moduleContents));
      }
    }

    // if got here then elem1 and elem2 are paramName and paramValue. insert into map
    contents.at(tmpModuleName).insert( pair<string, string>(elem1, elem2));
  }


  cfgIsInit = true;

  return 1;
}








