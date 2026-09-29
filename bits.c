/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x&y)&~(~x&~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!(x&&y))
        return(!x&&!y);
    else return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result = 0;
    int shift = ((v>>16)>0)<<4;
    v = v >> shift;
    result = result | shift;
    shift = ((v>>8)>0)<<3;
    v = v >> shift;
    result = result | shift;
    shift = ((v>>4)>0)<<2;
    v = v >> shift;
    result = result | shift;
    shift = ((v>>2)>0)<<1;
    v = v >> shift;
    result = result | shift;
    shift = ((v>>1)>0)<<0;
    v = v >> shift;
    result = result | shift;
    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int zm = m << 3;
    int zn = n << 3;
    int bytem = x >> (zm);
    int byten = x >> (zn);
    byten = byten << (zm);
    bytem = bytem << (zn);
    int yn = 0xFF << (zm);
    int ym = 0xFF << (zn);
    byten = byten & yn;
    bytem = bytem & ym;
    x = x & ~(yn | ym);
    x = x | byten | bytem;
    return x;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    int i = 31;
    unsigned v4 = 0;
    while(i+1){
        unsigned v1 = v >> i;
        unsigned v2 = v1 & 0x1;
        unsigned v3 = v2 << (31 - i);
        v4 = v4 | v3;
        i--;
    }
    return v4;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int y = n + (~0) + !n;
    int z = (1 << 31)>>y;
    int h = (~z)|(!n << 31);
    int p = (x >> n) & h;
    return p;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int a;
    int count = 0;
    int all = !(~x);
    a = !(~(x >> 16));
    count = count + (a << 4);
    x = x << (a << 4);

    a = !(~(x >> 24));
    count = count + (a << 3);
    x = x << (a << 3);

    a = !(~(x >> 28));
    count = count + (a << 2);
    x = x << (a << 2);

    a = !(~(x >> 30));
    count = count + (a << 1);
    x = x << (a << 1);

    count = count + !!(x >> 31);
    return (count + all);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign;
    unsigned ux;
    unsigned tmp;
    unsigned frac;
    unsigned rest;
    unsigned result;
    int E;
    int shift;
    if (!x)
        return 0;
    sign = x & 0x80000000;
    ux = x;
    if (x < 0)
        ux = -ux;
    E = 0;
    tmp = ux;
    while ((tmp = tmp >> 1))
        E = E + 1;
    if (E <= 23)
        return sign | ((E + 127) << 23)
                    | ((ux << (23 - E)) & 0x7FFFFF);
    shift = E - 23;
    frac = ux >> shift;
    rest = ux & ((1 << shift) - 1);
    result = sign | ((E + 127) << 23)
                  | (frac & 0x7FFFFF);
    return result +
           ((rest + (frac & 1)) > (1 << (shift - 1)));
}
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    if (exp == 0xFF)
        return uf;

    if (exp == 0)
        return sign | (frac << 1);

    exp = exp + 1;

    if (exp == 0xFF)
        frac = 0;

    return sign | (exp << 23) | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign;
    unsigned exp;
    unsigned frac_hi;
    unsigned mant;
    int E;
    int result;
    sign = uf2 >> 31;//取出符号位
    exp = (uf2 >> 20) & 0x7FF;//取出11位阶码
    E = exp - 1023;//得到真实指数E
    if(E < 0)
        return 0;//小于一的小数直接取0
    if(E > 31)
        return 0x80000000;//溢出
    if((!sign)&(!(E-31)))//!sign表示正数，!(E - 31)表示31位,这里&与&&效果一致
        return 0x80000000;//正数溢出
    frac_hi = uf2 & 0xFFFFF;//取出uf2尾数的二十位
    mant = frac_hi | 0x100000;//恢复隐藏的1
    if (E <= 20){
        result = mant >> (20 - E);//将第二十位移到第E位
    }else{//位数不够，uf1的高位取
        result = mant << (E - 20);//提前扩充需要的位数
        result = result | (uf1 >> (32 - (E - 20)));//不上不足的尾数
    }
    if(sign){
        return (-result);
    }else return result;

}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149)
        return 0;

    if (x < -126)
        return 1 << (x + 149);

    if (x <= 127)
        return (x + 127) << 23;

    return 0xFF << 23;
}






