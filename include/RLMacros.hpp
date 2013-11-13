#ifndef RLLIB_MACROS
#define RLLIB_MACROS 1


#define EPS (1E-9)
#define DBL_EQUAL(d1, d2) (abs((d1)-(d2)) < EPS)


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
