#include "RLExceptionTest.hh"

bool RLExceptionTest::Test_ConstructsAndReturnsCorrectly_Case1() const
{
  try
	{
	  throw RLException();
	}
  catch (RLException& e)
  {
    return strcmp(e.what(),"Exception!")==0;
  }
}

bool RLExceptionTest::Test_ConstructsAndReturnsCorrectly_Case2() const
{
  try
	{
	  throw RLException("QWERTYasdf123");
	}
  catch (RLException& e)
  {
    return strcmp(e.what(),"QWERTYasdf123")==0;
  }
}

bool RLExceptionTest::Test_ConstructsAndReturnsCorrectly_VA1() const
{
  try
	{
	  throw RLException("Adding variable arguments: int %d and string %s.",1337,"test");
	}
  catch (RLException& e)
  {
    return strcmp(e.what(),"Adding variable arguments: int 1337 and string test.")==0;
  }
}


int RLExceptionTest::RunTests() const
{
  if(!Test_ConstructsAndReturnsCorrectly_Case1())
    return 1;
  if(!Test_ConstructsAndReturnsCorrectly_Case2())
    return 2;
  if(!Test_ConstructsAndReturnsCorrectly_VA1())
    return 2;
  return 0;
}

string RLExceptionTest::ToString() const
{
  return "RLException";
}
