/*
  based mostly on genroot.

  
  This file contains directives for all classes/functions that need to have
  a dictionary generated for ROOT. This is necessary to store
  instances of classes in a tree.

  Note that any class which will be be stored in an stl container needs to have
  that container specifically defined as well.

 */

#include <vector>

using namespace std;

#ifdef __MAKECINT__
#pragma link C++ class EventData+;
#endif
