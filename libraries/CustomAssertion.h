#ifndef CUSTOMASSERTION_H
#define CUSTOMASSERTION_H

#ifndef UT
    #include <assert.h>
#else
    # define assert(EX) (void)((EX) || (_assert(#EX, __FILE__, __LINE__),0))
    void _assert(const char *msg, const char *file, int line);
#endif

#endif // CUSTOMASSERTION_H
