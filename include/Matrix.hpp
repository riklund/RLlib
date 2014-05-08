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
  Matrix(ulong _rows, ///Number of rows for the matrix to use.
		 ulong _columns ///Number of columns.
		 ); ///Constructor.

  ~Matrix(); ///Destructor.

  void InitializeAll(T value); ///Set all elements to

  T & Element(ulong row, ///Row number. Zero indexed. 
				 ulong column ///Column number. Zero indexed.
				 ); ///Returns the element in row row and column column. Throws exception if one or both of these parameters are out of bound.

  T Element(ulong row, ///Row number. Zero indexed. 
				 ulong column ///Column number. Zero indexed.
				 ) const; ///Returns the element in row row and column column. Throws exception if one or both of these parameters are out of bound.

  T * GetArray() const; ///Returns the underlying array itself. Use this to send it to LAPACK. Ownership is NOT TRANSFERRED, although the array may (will) be modified (by LAPACK). Do NOT use delete on this, or you will have a segfault on your hands. Instead use DeleteArray() if you need to destroy the array for freeing memory, but not deleting the object.

  ulong Rows() const; ///Returns the number of rows in the matrix.

  ulong Columns() const; ///Returns the number of columns in the matrix.

  bool IsSquare() const; ///Returns true if the number of rows and the number of columns is equal.

  inline bool IsSymmetric(bool verbose = false ///If set to true, this will print info on the first found cells where symmetricity is violated, if any.
				   ) const; ///Checks if the matrix is symmetric, or not. Returns true if symmetric.

  inline bool IsHermitian(bool verbose = false ///If set to true, this will print info on the first found cells where hermiticity is violated, if any.
						  ) const; ///Checks if the matrix is Hermitian or not. Returns true if Hermitian.


  inline string ToString() const;

  void DeleteArray(); ///Call this to delete array and free memory.

  void MultiplyBy(T value); ///Multiply each cell in the matrix by this number.

  void MultMv(const T * input, ///Input vector.
			  T * output ///Output vector.
			  ) const; ///Computes the product Matrix * input = output. For ARPACK compatibility.
  
private:
  inline static bool TEquality(T x1, T x2);
  T * ElementArray; ///The underlying data structure (array) containing the data.
  ulong rows; ///Number of rows in the array.
  ulong columns; ///Number of columns.
};


template<class T>
void Matrix<T>::DeleteArray()
{
  rows = 0;
  columns = 0;
  if(ElementArray)
	{
	  delete [] ElementArray;
	  ElementArray = NULL;
	}
}

template<class T>
inline bool Matrix<T>::TEquality(T x1, T x2)
{
  //printf("%f + %fi %f + %fi\n",real(x1), imag(x1),real(x2),imag(x2));
  return abs(x1+x2) < T_EPS || (abs(x1-x2)/(abs(x1)+abs(x2))) < T_EPS;
}

template<class T>
void Matrix<T>::MultiplyBy(T value)
{
  for(ulong n = 0; n<rows; ++n)
	{
	  for(ulong m = 0; m<columns; ++m)
		{
		  Element(n, m) *= value;
		}
	}
}

template<class T>
void Matrix<T>::MultMv(const T * input, T * output) const
{
  for(ulong n = 0; n<rows; ++n)
	{
	  output[n] = 0;
	  for(ulong m = 0; m<columns; ++m)
		{
		  output[n] += Element(n, m) * input[m];
		}
	}  
}

template<class T>
ulong Matrix<T>::Rows() const
{
  return rows;
}

template<class T>
ulong Matrix<T>::Columns() const
{
  return columns;
}

template<class T>
bool Matrix<T>::IsSquare() const
{
  return rows == columns;
}

template<class T>
Matrix<T>::Matrix(ulong _rows, ulong _columns)
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
  for(ulong i = 0; i<rows*columns; ++i)
	{
	  ElementArray[i]=value;
	}
}

template<class T>
Matrix<T>::~Matrix()
{
  if(ElementArray)
	delete [] ElementArray;
}

template<class T>
string Matrix<T>::ToString() const
{
  stringstream ss;
  for(ulong n = 0; n<rows; ++n)
	{
	  for(ulong m = 0; m < columns; ++m)
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
  for(ulong n = 0; n<rows; ++n)
	{
	  for(ulong m = 0; m<n; ++m)
		{
		  if(! TEquality(Element(n, m), Element(m, n)) )
			{
			  if(verbose)
 				printf("Symmetricity invalidity detected: (%ld, %ld) = %5.12f , (%ld, %ld) = %5.12f .\n",n,m,Element(n,m),m,n,Element(m, n));
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
  for(ulong n = 0; n<rows; ++n)
	{
	  for(ulong m = 0; m<n; ++m)
		{
		  if(! TEquality(Element(n, m), Element(m, n)) )
			{
			  if(verbose)
 				printf("Symmetricity invalidity detected: (%ld, %ld) = %10.12f%+10.12fi, (%ld, %ld) = %10.12f%+10.12fi.\n",n,m,real(Element(n,m)),imag(Element(n,m)),m,n,real(Element(m, n)), imag(Element(m, n)));
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
  for(ulong n = 0; n<rows; ++n)
	{
	  for(ulong m = 0; m<=n; ++m)
		{
		  if(! TEquality(Element(n, m),conj(Element(m, n))) )
			{
			  if(verbose)
				printf("Hermiticity invalidity detected: (%ld, %ld) = %f + %fi, (%ld, %ld) = %f + %fi.\n",n,m,real(Element(n,m)),imag(Element(n,m)),m,n,real(Element(m, n)), imag(Element(m, n)));
			  return false;
			}
		}
	}
  return true;
}

template<class T>
T & Matrix<T>::Element(ulong row, ulong column)
{
  if(row >= rows)
	{
	  throw RLException("Matrix: Row out of bounds: asked for %ld, but there are %ld rows.", row, rows);
	}
  if( column >= columns )
	{
	  throw RLException("Matrix Column out of bounds: asked for %ld, but there are %ld columns.", column, columns);
	}
  return ElementArray[row*columns+column];
}

template<class T>
T Matrix<T>::Element(ulong row, ulong column) const
{
  if(row >= rows)
	{
	  throw RLException("Matrix: Row out of bounds: asked for %ld, but there are %ld rows.", row, rows);
	}
  if( column >= columns )
	{
	  throw RLException("Matrix Column out of bounds: asked for %ld, but there are %ld columns.", column, columns);
	}
  return ElementArray[row*columns+column];
}

template<class T>
T * Matrix<T>::GetArray() const
{
  return ElementArray;
}

#endif
