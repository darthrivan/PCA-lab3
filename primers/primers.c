#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef unsigned long long bignum;

#define BITSPERBYTE 8
#define BYTESPERINT sizeof(unsigned int)
#define BITSPERINT (BITSPERBYTE * BYTESPERINT)

typedef struct {
    bignum bitsInArray;		/* how many bits in array */
    bignum intsInArray;		/* how many uints to give necessary bits */
    unsigned int *p;        /* pointer to array */
} BITARRAY;

void freeBitArray(BITARRAY * ba)
{
/*    free(ba->p);
    free(ba); */
} 

BITARRAY *createBitArray(bignum bits)
{
    BITARRAY *ba = malloc(sizeof(BITARRAY));
    assert(ba != NULL);
    ba->bitsInArray = bits;
    ba->intsInArray = bits / BITSPERINT + 1;
    ba->p = malloc(ba->intsInArray * BYTESPERINT);
    assert(ba->p != NULL);
    return ba;
}

void setBit(BITARRAY * ba, bignum bitSS)
{
    unsigned int *pInt = ba->p + (bitSS / BITSPERINT);
    unsigned int remainder = (bitSS % BITSPERINT);
    *pInt |= (1 << remainder);
} 

void clearBit(BITARRAY * ba, bignum bitSS)
{
    unsigned int *pInt = ba->p + (bitSS / BITSPERINT);
    unsigned int remainder = (bitSS % BITSPERINT);
    unsigned int mask = 1 << remainder;
    mask = ~mask;
    *pInt &= mask;
} 

int getBit(BITARRAY * ba, bignum bitSS)
{
    unsigned int *pInt = ba->p + (bitSS / BITSPERINT);
    unsigned int remainder = (bitSS % BITSPERINT);
    unsigned int ret = *pInt;
    ret &= (1 << remainder);
    return (ret != 0);
}

void clearAll(BITARRAY * ba)
{
    bignum intSS;
    for (intSS = 0; intSS <= ba->intsInArray; intSS++) {
	*(ba->p + intSS) = 0;
    }
}

void setAll(BITARRAY * ba)
{
    bignum intSS;
    for (intSS = 0; intSS <= ba->intsInArray; intSS++) {
	*(ba->p + intSS) = ~0;
    }
}

void printPrime(bignum bn)
{
    static char buf[1000];
    sprintf(buf, "%ull", bn);
    buf[strlen(buf) - 2] = '\0';
    printf("%s\n", buf);
} 

void findPrimes(bignum topCandidate)
{
    BITARRAY *ba = createBitArray(topCandidate);
    assert(ba != NULL);		/* SET ALL BUT 0 AND 1 TO PRIME STATUS */
    setAll(ba);
    clearBit(ba, 0);
    clearBit(ba, 1);		/* MARK ALL THE NON-PRIMES */
    bignum thisFactor = 2;
    bignum lastSquare = 0;
    bignum thisSquare = 0;
    while (thisFactor * thisFactor <= topCandidate) {	/* MARK THE MULTIPLES OF THIS FACTOR */
	bignum mark = thisFactor + thisFactor;
	while (mark <= topCandidate) {
	    clearBit(ba, mark);
	    mark += thisFactor;
	}			/* PRINT THE PROVEN PRIMES SO FAR */
	thisSquare = thisFactor * thisFactor;
	for (; lastSquare < thisSquare; lastSquare++) {
	    if (getBit(ba, lastSquare))
		printPrime(lastSquare);
	}			/* SET thisFactor TO NEXT PRIME */
	thisFactor++;
	while (getBit(ba, thisFactor) == 0)
	    thisFactor++;
	assert(thisFactor <= topCandidate);
    }				/* PRINT THE REMAINING PRIMES */
    for (; lastSquare <= topCandidate; lastSquare++) {
	if (getBit(ba, lastSquare))
	    printPrime(lastSquare);
    }
    freeBitArray(ba);
}

void test()
{
    int ss;
    BITARRAY *ba = createBitArray(77);
    clearAll(ba);		/*setAll(ba); */
    setBit(ba, 0);
    setBit(ba, 64);
    setBit(ba, 10);
    clearBit(ba, 10);
    clearBit(ba, 0);
    setBit(ba, 64);
    setBit(ba, 10);
    setBit(ba, 0);
    for (ss = 0; ss < 78; ss++) {
	if (getBit(ba, ss) != 0) {
	    printf("%d", ss);
	    printf("=%d ON!!!", (getBit(ba, ss)));
	    printf("\n");
	}
    }
    printf("First int is %ull.\n", *(ba->p));
}

int main(int argc, char *argv[])
{
    bignum topCandidate;
    if (argc > 1)
	topCandidate = atoll(argv[1]);	/*        test();  */
    else topCandidate = 10000000;
    findPrimes(topCandidate);
    return 0;
}
