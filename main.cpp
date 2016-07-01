#include "soft_number.h"

I32 error_count;

void Error(U32 expected, SU32 result, U32 linenumber)
{
    U32 r = SU32ToUint32(result);
    if (expected != r)
    {
        error_count++;
        printf("Test failed at line %d! expected: %d, result: %d", linenumber, expected, r);
    }
}

void TestSoftUintAddition(U32 a, U32 b, U32 linenumber)
{
    U32 a0 = a;
    U32 b0 = b;
    SU32 a1 = a;
    SU32 b1 = b;
    
    U32 rb = a0 + b0;
    SU32 ra = a1 + b1;
    
    Error(rb, ra, linenumber);
}

#define TEST_SOFT_UINT_ADDITION(a, b) TestSoftUintAddition((a), (b), __LINE__)

void TestSoftUintSubtraction(U32 a, U32 b, U32 linenumber)
{
    U32 a0 = a;
    U32 b0 = b;
    SU32 a1 = a;
    SU32 b1 = b;
    
    U32 rb = a0 - b0;
    SU32 ra = a1 - b1;
    
    Error(rb, ra, linenumber);
}

#define TEST_SOFT_UINT_SUBTRACTION(a, b) TestSoftUintSubtraction((a), (b), __LINE__)

int main (int argc, char **argv)
{
    printf("Testing soft number ...\n");
    
    error_count = 0;
    
    TEST_SOFT_UINT_ADDITION(0, 0);
    TEST_SOFT_UINT_ADDITION(0, 1);
    TEST_SOFT_UINT_ADDITION(0, 2);
    TEST_SOFT_UINT_ADDITION(1, 1);
    TEST_SOFT_UINT_ADDITION(1, 2);
    TEST_SOFT_UINT_ADDITION(2, 2);
    TEST_SOFT_UINT_ADDITION(3322, 4552);
    TEST_SOFT_UINT_ADDITION(0xffffffff, 0);
    TEST_SOFT_UINT_ADDITION(0xffffffff, 1);
    TEST_SOFT_UINT_ADDITION(0xffffffff, 3);
    TEST_SOFT_UINT_ADDITION(0x1fffffff, 1);
    
    TEST_SOFT_UINT_SUBTRACTION(0, 0);
    TEST_SOFT_UINT_SUBTRACTION(1, 0);
    TEST_SOFT_UINT_SUBTRACTION(1, 1);
    TEST_SOFT_UINT_SUBTRACTION(2, 1);
    TEST_SOFT_UINT_SUBTRACTION(5, 4);
    TEST_SOFT_UINT_SUBTRACTION(3322, 2335);
    TEST_SOFT_UINT_SUBTRACTION(0xffffffff, 0xffffffff);
    TEST_SOFT_UINT_SUBTRACTION(0xffffffff, 0x0000ffff);
    TEST_SOFT_UINT_SUBTRACTION(0xffffffff, 0xffff0000);
    TEST_SOFT_UINT_SUBTRACTION(0, 1);
    TEST_SOFT_UINT_SUBTRACTION(1, 3);
    TEST_SOFT_UINT_SUBTRACTION(5, 11);
    TEST_SOFT_UINT_SUBTRACTION(435676, 9432678);
    TEST_SOFT_UINT_SUBTRACTION(0, 0xffffffff);
    TEST_SOFT_UINT_SUBTRACTION(1, 0xffffffff);
    
    if (error_count == 0)
    {
        printf("\nAll tests passed!\n");
    }
    
    printf("\nTesting ended.\n");
    return 0;
}

