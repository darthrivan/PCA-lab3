#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

int N, N4;
char a[10240], b[10240], c[10240];
char string[100];
unsigned short memo239_q[239][10];
unsigned short memo239_r[239][10];
unsigned short memo25_q[25][10];
unsigned short memo25_r[25][10];
unsigned short memo5_q[5][10];
unsigned short memo5_r[5][10];

char memo_s[10][10][2][2];

void DIVIDE25( char *x)                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;                                       
    for( k = 0; k <= N4; k++ )                  
    {                                            
        q = memo25_q[r][x[k]];
        r = memo25_r[r][x[k]];
        x[k] = q;
    }                                           
}

void precompute() {
    // precomputing DIVIDE239
    char d, d2, d3;
    unsigned q, r, u;
    for (r = 0; r < 239; ++r) {
        for (d = 0; d <= 9; ++d) {
            u = (r*10 + d);
            q = u / 239;
            memo239_q[r][d] = q;
            memo239_r[r][d] = u - q*239;
        }
    }

    // precomputing DIVIDE25
    for (r = 0; r < 25; ++r) {
        for (d = 0; d <= 9; ++d) {
            u = (r*10 + d);
            q = u / 25;
            memo25_q[r][d] = q;
            memo25_r[r][d] = u - q*25;
        }
    }

    // precomputing DIVIDE5
    for (r = 0; r < 5; ++r) {
        for (d = 0; d <= 9; ++d) {
            u = (r*10 + d);
            q = u / 5;
            memo5_q[r][d] = q;
            memo5_r[r][d] = u - q*5;
        }
    }
    
    // subtract memoization
    for (d = 0; d <= 9; ++d) {
        for (d2 = 0; d2 <= 9; ++d2) {
            d3 = d - d2;
            memo_s[d][d2][0][0] = d3 >= 0?d3:d3+10;
            memo_s[d][d2][0][1] = d3 < 0;
            d3--;
            memo_s[d][d2][1][0] = d3 >= 0?d3:d3+10;
            memo_s[d][d2][1][1] = d3 < 0;

        }
    }
}

void DIVIDE239( char *x)                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;
    for( k = 0; k <= N4; k++ )
    {
        q = memo239_q[r][x[k]];
        r = memo239_r[r][x[k]];
        x[k] = q;
    }
}

void DIVIDE5( char *x)                           
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    r = 0;
    for( k = 0; k <= N4; k++ )
    {
        q = memo5_q[r][x[k]];
        r = memo5_r[r][x[k]];
        x[k] = q;
    }
}

void LONGDIV( char *x, int n )                          
{                                                
    int j, k;
    unsigned q, r, u;
    long v;

    // if( n < 6553 )                               
    // {                                            
        r = 0;                                   
        for( k = 0; k <= N4; k++ )               
        {                                        
            u = r * 10 + x[k];                   
            q = u / n;                           
            r = u - q * n;                       
            x[k] = q;                            
        }                                       
    // }                                            
    // else                                         
    // {                                            
    //     r = 0;                                   
    //     for( k = 0; k <= N4; k++ )              
    //     {                                       
    //         if( r < 6553 )                      
    //         {                                   
    //             u = r * 10 + x[k];              
    //             q = u / n;                      
    //             r = u - q * n;                  
    //         }                                   
    //         else                                
    //         {                                   
    //             v = (long) r * 10 + x[k];       
    //             q = v / n;                      
    //             r = v - q * n;                  
    //         }                                   
    //         x[k] = q;                           
    //     }                                       
    // }                                           
}

void MULTIPLY( char *x, int n )                        
{                                            
    int j, k;
    unsigned q, r, u;
    long v;
    r = 0;                                   
    for( k = N4; k >= 0; k-- )               
    {                                        
        q = n * x[k] + r;                    
        r = q / 10;                          
        x[k] = q - r * 10;                   
    }                                        
}

void SET( char *x, int n )                              
{                                                
    memset( x, 0, N4 + 1 );                      
    x[0] = n;                                    
}


void SUBTRACT( char *x, char *y, char *z )                      
{                                                
    int j, k;
    unsigned q, r, u;
    long v;
    r = 0;
    for( k = N4; k >= 0; k-- )                   
    {                                            
        char *p = memo_s[y[k]][z[k]][r];
        x[k] = p[0];
        r = p[1];
    }                                            
}


void calculate( void );
void progress( void );
void epilog( void );


int main( int argc, char *argv[] )
{
    N = 10000;

    setbuf(stdout, NULL);

    precompute();

    calculate();

    epilog();

    return 0;
}

void calculate( void )
{
    int j;

    N4 = N + 4;

    SET( a, 0 );
    SET( b, 0 );

    for( j = 2 * N4 + 1; j >= 3; j -= 2 )
    {
        SET( c, 1 );
        LONGDIV( c, j );

        SUBTRACT( a, c, a );
        DIVIDE25( a );

        SUBTRACT( b, c, b );
        DIVIDE239( b );
        DIVIDE239( b );

        progress();
    }

    SET( c, 1 );

    SUBTRACT( a, c, a );
    DIVIDE5( a );

    SUBTRACT( b, c, b );
    DIVIDE239( b );

    MULTIPLY( a, 4 );
    SUBTRACT( a, a, b );
    MULTIPLY( a, 4 );

    progress();
}

/*

 N = 10000                      
 A = 0                          
 B = 0                          
 J = 2 * (N + 4) + 1            
 FOR J = J TO 3 STEP -2         
     A = (1 / J - A) / 5 ^ 2    
     B = (1 / J - B) / 239 ^ 2  
 NEXT J                         
 A = (1 - A) / 5                
 B = (1 - B) / 239              
 PI = (A * 4 - B) * 4           

*/

void progress( void )
{
    printf(".");
}

void epilog( void )
{
    int j;

    {
        fprintf( stdout, " \n3.");
        for( j = 1; j <= N; j++ )
        {
            fprintf( stdout, "%d", a[j]);
            if( j % 5  == 0 )
                if( j % 50 == 0 )
                    if( j % 250  == 0 )
                        fprintf( stdout, "    <%d>\n\n   ", j );
                    else
                        fprintf( stdout, "\n   " );
                else
                    fprintf( stdout, " " );
        }
    }
}

