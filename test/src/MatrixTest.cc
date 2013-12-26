#include "MatrixTest.hh"

int MatrixTest::TestCase1() const
{
  ///Test so that the matrix is initializing the correct dimensions, so on and so forth.

  for(unsigned int j = 0; j<20; ++j)
	{
	  for(unsigned int i = 0; i<20; ++i)
		{
		  bool threwn = true;
		  try
			{
			  ///Throw exception for invalid i, j.
			  Matrix<double> myMatrix(i, j);
			  threwn = false;

			  ///Check if matrix dimensions are correct.
			  if(myMatrix.Rows() != i || myMatrix.Columns() != j)
				return 1;

			  ///Check if matrix is square for i=j.
			  if( i == j && !myMatrix.IsSquare())
				return 2;

			  ///Check if matrix initializes correctly.
			  myMatrix.InitializeAll(i);
			  for(unsigned int a = 0; a<j; ++a)
				{
				  for(unsigned int b = 0; b<i; ++b)
					{
					  if(myMatrix.Element(b, a) != i )
						return 3;
					}
				}

			  ///Check if we can set the elements in the matrix correctly.
			  for(unsigned int a = 0; a<j; ++a)
				{
				  for(unsigned int b = 0; b<i; ++b)
					{
					  myMatrix.Element(b, a) = 1329;
					  if(myMatrix.Element(b, a) != 1329 )
						return 4;
					  myMatrix.Element(b, a) = a*b;
					}
				}
			  
			  ///Check if matrix is symmetric (should be).
			  if(i==j)
				{
				  if(!myMatrix.IsSymmetric())
					return 7;
				}
			  ///Verify that an assymmetry changes the return value of IsSymmetric.
			  if(i > 3 && j > 6)
				{
				  myMatrix.Element(3, 6) = 2;
				  if(myMatrix.IsSymmetric())
					return 8;
				}
			  

			}
		  catch(RLException & ex)
			{
			  ///Check if exception is threwn if one or both of i, j is less than 1.
			  if(i >= 1 && j>=1)
				return 5;
			}
		  ///If no exception was threwn, that's also a problem.
		  if(( i < 1 || j < 1 ) && !threwn)
			return 6;
		}
	}
  
  return 0;
}

int MatrixTest::TestCase2() const
{
  ///Same as case 1, but with a complex double matrix instead.

  for(unsigned int j = 0; j<20; ++j)
	{
	  for(unsigned int i = 0; i<20; ++i)
		{
		  bool threwn = true;
		  try
			{
			  ///Throw exception for invalid i, j.
			  Matrix<ComplexDouble> myMatrix(i, j);
			  threwn = false;

			  ///Check if matrix dimensions are correct.
			  if(myMatrix.Rows() != i || myMatrix.Columns() != j)
				return 1;

			  ///Check if matrix is square for i=j.
			  if( i == j && !myMatrix.IsSquare())
				return 2;

			  ///Check if matrix initializes correctly.
			  myMatrix.InitializeAll(i);
			  for(unsigned int a = 0; a<j; ++a)
				{
				  for(unsigned int b = 0; b<i; ++b)
					{
					  if(myMatrix.Element(b, a) != ComplexDouble(i,0) )
						return 3;
					}
				}

			  ///Check if we can set the elements in the matrix correctly.
			  for(unsigned int a = 0; a<j; ++a)
				{
				  for(unsigned int b = 0; b<i; ++b)
					{
					  myMatrix.Element(b, a) = ComplexDouble(1329,0);
					  if(myMatrix.Element(b, a) != ComplexDouble(1329, 0) )
						return 4;
					  myMatrix.Element(b, a) = a*b;
					}
				}
			  
			  ///Check if matrix is symmetric (should be).
			  if(i==j)
				{
				  if(!myMatrix.IsSymmetric())
					return 7;
				}
			  ///Verify that an assymmetry changes the return value of IsSymmetric.
			  if(i > 3 && j > 6)
				{
				  myMatrix.Element(3, 6) = ComplexDouble(2,0);
				  if(myMatrix.IsSymmetric())
					return 8;
				}
			  

			}
		  catch(RLException & ex)
			{
			  ///Check if exception is threwn if one or both of i, j is less than 1.
			  if(i >= 1 && j>=1)
				return 5;
			}
		  ///If no exception was threwn, that's also a problem.
		  if(( i < 1 || j < 1 ) && !threwn)
			return 6;
		}
	}
  
  return 0;
}

int MatrixTest::TestCase3() const
{
  Matrix<double> myMatrix(3, 4);
  myMatrix.InitializeAll(0);
  for(int i = 0; i<12; ++i)
	myMatrix.Element(i/4,i%4) = i;
  for(int j = 0; j<12; ++j)
	if(myMatrix.GetArray()[j] != j)
	  return j;
  return 0;
}


int MatrixTest::RunTests() const
{
  cout << "Running unit tests on Matrix...";
  cout << flush;
  int code1 = TestCase1();
  if(code1)
    return code1;
  code1 = TestCase2();
  if(code1)
    return 100+code1;
  code1 = TestCase3();
  if(code1)
    return 200+code1;

  cout << "done" << endl;
  return 0;
}


string MatrixTest::ToString() const
{
  return "MatrixTest"; 
}
