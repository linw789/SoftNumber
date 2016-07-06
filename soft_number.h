#include <stdint.h>
#include <stdio.h>

typedef int32_t  I32;
typedef uint32_t U32;
typedef uint8_t  U8;

// 32-bit unsigned integer
struct SU32
{
    SU32()
    :v(0)
    {}
    
    SU32(U32 value)
    :v(value)
    {}
    
    void operator=(U32 value)
    {
        v = value;
    }
    
    U32 v;
};

// 32-bit signed integer
struct SI32
{
    void operator=(I32 value)
    {
        v = value;
    }
    
    U32 v;
};

// 32-bit floating point
struct SR32
{
    void operator=(float value)
    {
        v = value;
    }
    
    U32 v;
};

U32 SU32ToUint32(SU32 x)
{
    return x.v;
}

I32 SI32ToInt32(SI32 x)
{
    // regardless of the Endianness.
    I32 result = 0;
    
    return result;
}

/*
 Radix Complement, r: radix, n: number of digits, x: positive number
 dc(x) = (r^n) - x
 
 Diminished Radix Complement 
 drc(x) = dc(x) - 1 
        = (r ^ n) - 1 - x
 
 (r ^ n) - 1 = ... 
             = (r - 1) * (r ^ (n-1)) + (r - 1) * (r ^ (n-2)) + ... + (r - 1) * (r ^ 0)
 
 x = d_(n-1) * (r ^ (n-1)) + d_(n-2) * (r ^ (n-2)) + ... + d_0 * (r ^ 0)
 
 d_n is the number on the n-th digit
 d_n is guaranteed to be smaller than or equal to (r - 1)
 
 drc(x) = ((r ^ n) - 1) - x 
        = ((r - 1) - d_(n-1)) * (r ^ (n-1)) + ((r - 1) - d_(n-2)) * (r ^ (n-2)) + ... + ((r - 1) - d_0) * (r ^ 0)
 
 Binary case:
 drc(x) = [11...1] - x = negate every bit of x
*/
SU32 DiminishedTwoComplement(SU32 x)
{
    U32 result = x.v ^ 0xffffffff;
    return SU32(result);
}

SU32 operator+(SU32 x, SU32 y)
{
    U32 bit_x = 0, bit_y = 0;
    U32 sum = 0;
    U32 carry = 0;
    U32 mask = 1;
    
    for (;;)
    {
        // unroll the loop a bit
        
        // 1
        bit_x = x.v & mask;
        bit_y = y.v & mask;
        sum |= (bit_x ^ bit_y) ^ carry;
        
        mask = mask << 1;
        if (!mask) break;
        
        carry = (bit_x & bit_y) | ((bit_x ^ bit_y) & carry);
        carry = carry << 1;
        
        // 2
        bit_x = x.v & mask;
        bit_y = y.v & mask;
        sum |= (bit_x ^ bit_y) ^ carry;
        
        mask = mask << 1;
        if (!mask) break;
        
        carry = (bit_x & bit_y) | ((bit_x ^ bit_y) & carry);
        carry = carry << 1;
        
        // 3
        bit_x = x.v & mask;
        bit_y = y.v & mask;
        sum |= (bit_x ^ bit_y) ^ carry;
        
        mask = mask << 1;
        if (!mask) break;
        
        carry = (bit_x & bit_y) | ((bit_x ^ bit_y) & carry);
        carry = carry << 1;
        
        // 4
        bit_x = x.v & mask;
        bit_y = y.v & mask;
        sum |= (bit_x ^ bit_y) ^ carry;
        
        mask = mask << 1;
        if (!mask) break;
        
        carry = (bit_x & bit_y) | ((bit_x ^ bit_y) & carry);
        carry = carry << 1;
    }
    
    return SU32(sum);
}

/*
 To calculate x - y,
 method 1: drc(drc(x) + y)
 method 2: (x + drc(y)) - (r ^ n) + 1
*/
SU32 operator-(SU32 x, SU32 y)
{
    // use method 2
    
    SU32 dtc_y = DiminishedTwoComplement(y);
    
    // automatically subtract (r ^ n) by overflowing
    SU32 st = x + SU32(dtc_y);
    
    SU32 result = st + 1;
    
    return result;
}

/*

 naive method:
 
         101011
    *      1101
    -----------
         101011
    +        0
    +  101011
    + 101011
    -----------
     1000101111
 
 */
SU32 operator*(SU32 x, SU32 y)
{
    SU32 sum = 0;
    SU32 counter = 0;
    U32 mask = 1;
    U32 bit_y = 0;
    
    do
    {
        bit_y = y.v & mask;
        
        // TODO lw: eliminate this branch
        if (bit_y)
        {
            U32 mx = x.v << counter.v;
            sum = sum + SU32(mx);
        }

        counter = counter + 1;
        mask = mask << 1;
    } while (mask);

    return sum;
}
