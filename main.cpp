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

void TestSoftUintAddition(U32 x, U32 y, U32 linenumber)
{
    U32 x0 = x;
    U32 y0 = y;
    SU32 x1 = x;
    SU32 y1 = y;
    
    U32 r0 = x0 + y0;
    SU32 r1 = x1 + y1;
    
    Error(r0, r1, linenumber);
}

#define TEST_SOFT_UINT_ADDITION(x, y) TestSoftUintAddition((x), (y), __LINE__)

void TestSoftUintSubtraction(U32 x, U32 y, U32 linenumber)
{
    U32 x0 = x;
    U32 y0 = y;
    SU32 x1 = x;
    SU32 y1 = y;
    
    U32 r0 = x0 - y0;
    SU32 r1 = x1 - y1;
    
    Error(r0, r1, linenumber);
}

#define TEST_SOFT_UINT_SUBTRACTION(x, y) TestSoftUintSubtraction((x), (y), __LINE__)

void TestSoftUintMultiplication(U32 x, U32 y, U32 linenumber)
{
    U32 x0 = x;
    U32 y0 = y;
    SU32 x1 = x;
    SU32 y1 = y;
    
    U32 r0 = x0 * y0;
    SU32 r1 = x1 * y1;
    
    Error(r0, r1, linenumber);
}

#define TEST_SOFT_UINT_MULTIPLICATION(x, y) TestSoftUintMultiplication((x), (y), __LINE__)

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
    
    TEST_SOFT_UINT_MULTIPLICATION(0, 0);
    TEST_SOFT_UINT_MULTIPLICATION(1, 0);
    TEST_SOFT_UINT_MULTIPLICATION(1, 2);
    TEST_SOFT_UINT_MULTIPLICATION(8, 7);
    TEST_SOFT_UINT_MULTIPLICATION(2343, 47320);
    TEST_SOFT_UINT_MULTIPLICATION(0xffffffff, 1);
    TEST_SOFT_UINT_MULTIPLICATION(0xffffffff, 5);
    TEST_SOFT_UINT_MULTIPLICATION(0xffffffff, 0xffffffff);

    if (error_count == 0)
    {
        printf("\nAll tests passed!\n");
    }
    
    printf("\nTesting ended.\n");
    return 0;
}

