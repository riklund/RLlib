#ifndef RLLIB_MACROS
#define RLLIB_MACROS 1

#include <cfloat>
#include <complex>


typedef std::complex<double> ComplexDouble;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long long ullong;


#ifndef MAX
#define MAX(x,y) (((x) > (y)) ? (x) : (y))
#endif

#define EPS 1E-9
#define DBL_EQUAL(d1, d2) (abs((d1)-(d2)) < EPS)

#define HPREC_EPSILON 10*DBL_EPSILON

#define DBL_EQUAL_HPREC(d1, d2) (abs((d1)-(d2)) < HPREC_EPSILON * MAX(abs(d1), abs(d2)) || MAX(abs(d1), abs(d2) ) < HPREC_EPSILON )


#define foru(var, to)		\
  for(int var = 0; var < to; ++var)

#define foruu(var1, var2, to) \
  for(int var1 = 0; var1 < to; ++var1) \
	for(int var2 = 0; var2 < to; ++var2) \

#define SGN(x) ( (x > 0) - (x < 0) )

#define foric(type, object, it)											\
  for(type::const_iterator it = object.begin(); it!=object.end(); ++it)

#define PI 3.141592653589793238462643



#endif
