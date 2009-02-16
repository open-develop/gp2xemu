#ifndef ASSERT_ARM_H_INCLUDED
#define ASSERT_ARM_H_INCLUDED

#ifdef DEBUG
#include <assert.h>
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif

#endif

