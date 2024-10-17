#include "34.12.hpp"
#include "34.13.hpp"
#include "Test.h"
#include <iostream>

int main()
{
  GOST_34_13::Kuzn kuzn({"7766554433221100FFEEDDCCBBAA9988"}, {"EFCDAB89674523011032547698BADCFE"});
  Test test({ "7766554433221100FFEEDDCCBBAA9988" }, { "EFCDAB89674523011032547698BADCFE" });
  
  test.setTestData("Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world!!!");
  test.runAllTests();
  
  kuzn.execute();
}
