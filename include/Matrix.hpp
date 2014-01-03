#ifndef Matrix_hpp
#define Matrix_hpp

#include "RLException.hh"
#include "RLMacros.hpp"
#include <stdio.h>
#include <sstream>
#include <iomanip>
#include <string>

#define T_EPS 1E-5

using namespace std;

///This class should be a wrapper for a matrix stored as a 1D array. In that way, we can extract the array directly to use it with LAPACK (for example).

template<class T>
class Matrix
{
public:
  Matrix(unsigned int _rows, ///Number of rows for the matrix to use.
		 unsigned int _columns ///Number of columns.
		 ); ///Constructor.

  ~Matrix(); ///Destructor.

  void InitializeAll(T value); ///Set all elements to

  T & Element(unsigned int row, ///Row number. Zero indexed. 
				 unsigned int column ///Column number. Zero indexed.
				 ); ///Returns the element in row row and column column. Throws exception if one or both of these parameters are out of bound.

  T Element(unsigned int row, ///Row number. Zero indexed. 
				 unsigned int column ///Column number. Zero indexed.
				 ) const; ///Returns the element in row row and column column. Throws exception if one or both of these parameters are out of bound.

  T * GetArray() const; ///Returns the underlying array itself. Use this to send it to LAPACK. Ownership is NOT TRANSFERRED, although the array may (will) be modified (by LAPACK). Do NOT use delete on this, or you will have a segfault on your hands.

  unsigned int Rows() const; ///Returns the number of rows in the matrix.

  unsigned int Columns() const; ///Returns the number of columns in the matrix.

  bool IsSquare() const; ///Returns true if the number of rows and the number of columns is equal.

  inline bool IsSymmetric(bool verbose = false ///If set to true, this will print info on the first found cells where symmetricity is violated, if any.
				   ) const; ///Checks if the matrix is symmetric, or not. Returns true if symmetric.

  inline bool IsHermitian(bool verbose = false ///If set to true, this will print info on the first found cells where hermiticity is violated, if any.
						  ) const; ///Checks if the matrix is Hermitian or not. Returns true if Hermitian.


  inline string ToString() const;

  void MultiplyBy(T value); ///Multiply each cell in the matrix by this number.
  
private:
  inline static bool TEquality(T x1, T x2);
  T * ElementArray; ///The underlying data structure (array) containing the data.
  unsigned int rows; ///Number of rows in the array.
  unsigned int columns; ///Number of columns.
};

template<class T>
inline bool Matrix<T>::TEquality(T x1, T x2)
{
  //printf("%lf + %lfi %lf + %lfi\n",real(x1), imag(x1),real(x2),imag(x2));
  return abs(x1+x2) < T_EPS || (abs(x1-x2)/(abs(x1)+abs(x2))) < T_EPS;
}

template<class T>
void Matrix<T>::MultiplyBy(T value)
{
  for(unsigned int n = 0; n<rows; ++n)
	{
	  for(unsigned int m = 0; m<columns; ++m)
		{
		  Element(n, m) *= value;
		}
	}
}

template<class T>
unsigned int Matrix<T>::Rows() const
{
  return rows;
}

template<class T>
unsigned int Matrix<T>::Columns() const
{
  return columns;
}

template<class T>
bool Matrix<T>::IsSquare() const
{
  return rows == columns;
}

template<class T>
Matrix<T>::Matrix(unsigned int _rows, unsigned int _columns)
  :rows(_rows),columns(_columns)
{
  if( rows < 1 || columns < 1 )
	{
	  throw RLException("Matrix: Must have # rows > 0 and # columns > 0");
	}
  ElementArray = new T[rows*columns];
}

template<class T>
void Matrix<T>::InitializeAll(T value)
{
  for(unsigned int i = 0; i<rows*columns; ++i)
	{
	  ElementArray[i]=value;
	}
}

template<class T>
Matrix<T>::~Matrix()
{
  delete [] ElementArray;
}

template<class T>
string Matrix<T>::ToString() const
{
  stringstream ss;
  for(unsigned int n = 0; n<rows; ++n)
	{
	  for(unsigned int m = 0; m < columns; ++m)
		{
		  ss << setw(23) << Element(n, m);
		  if(m < columns - 1)
			ss << " ";
		  else
			ss << endl;
		}
	}
  return ss.str();
}

template<class T>
bool Matrix<T>::IsSymmetric( bool verbose ) const
{
  if( !IsSquare() )
	{
	  return false; ///A matrix must be square in order to be symmetric.
	}
  for(unsigned int n = 0; n<rows; ++n)
	{
	  for(unsigned int m = 0; m<n; ++m)
		{
		  if(! TEquality(Element(n, m), Element(m, n)) )
			{
			  if(verbose)
 				printf("Symmetricity invalidity detected: (%d, %d) = %5.12lf , (%d, %d) = %5.12lf .\n",n,m,Element(n,m),m,n,Element(m, n));
			  return false;
			}
		}
	}
  return true;
}

template<>
inline bool Matrix<ComplexDouble>::IsSymmetric( bool verbose ) const
{
  if( !IsSquare() )
	{
	  if(verbose)
		printf("Non-square matrix cannot be symmetric.\n");
	  return false; ///A matrix must be square in order to be symmetric.
	}
  for(unsigned int n = 0; n<rows; ++n)
	{
	  for(unsigned int m = 0; m<n; ++m)
		{
		  if(! TEquality(Element(n, m), Element(m, n)) )
			{
			  if(verbose)
 				printf("Symmetricity invalidity detected: (%d, %d) = %10.12lf%+10.12lfi, (%d, %d) = %10.12lf%+10.12lfi.\n",n,m,real(Element(n,m)),imag(Element(n,m)),m,n,real(Element(m, n)), imag(Element(m, n)));
			  return false;
			}
		}
	}
  return true;
}


template <>
inline bool Matrix<ComplexDouble>::IsHermitian(bool verbose) const
{
  if ( !IsSquare() )
	{
	  return false;
	}
  for(unsigned int n = 0; n<rows; ++n)
	{
	  for(unsigned int m = 0; m<=n; ++m)
		{
		  if(! TEquality(Element(n, m),conj(Element(m, n))) )
			{
			  if(verbose)
				printf("Hermiticity invalidity detected: (%d, %d) = %lf + %lfi, (%d, %d) = %lf + %lfi.\n",n,m,real(Element(n,m)),imag(Element(n,m)),m,n,real(Element(m, n)), imag(Element(m, n)));
			  return false;
			}
		}
	}
  return true;
}

template<class T>
T & Matrix<T>::Element(unsigned int row, unsigned int column)
{
  if(row >= rows)
	{
	  throw RLException("Matrix: Row out of bounds: asked for %d, but there are %d rows.", row, rows);
	}
  if( column >= columns )
	{
	  throw RLException("Matrix Column out of bounds: asked for %d, but there are %d columns.", column, columns);
	}
  return ElementArray[row*columns+column];
}

template<class T>
T Matrix<T>::Element(unsigned int row, unsigned int column) const
{
  if(row >= rows)
	{
	  throw RLException("Matrix: Row out of bounds: asked for %d, but there are %d rows.", row, rows);
	}
  if( column >= columns )
	{
	  throw RLException("Matrix Column out of bounds: asked for %d, but there are %d columns.", column, columns);
	}
  return ElementArray[row*columns+column];
}

template<class T>
T * Matrix<T>::GetArray() const
{
  return ElementArray;
}

#endif
