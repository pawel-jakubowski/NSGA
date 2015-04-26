#include <CustomAssertion.h>

#ifdef UT
#pragma message("UT defined")
#include <unittest++/UnitTest++.h>

void _assert(const char *msg, const char *file, int line)
{
    throw UnitTest::AssertException(msg,file,line);
}
#endif
