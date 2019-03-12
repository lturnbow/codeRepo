/* 
Lauren Turnbow
10/2/2016
CS225
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cipher.h"

void print_bit( char v, int pos ) 
{
    char one = 1;
    if ( v & one<<pos ) { printf( "1" ); } else { printf( "0" ); }
}

void print_bits( char* buffer, int start_pos, int how_many )
{
    int i,j;
    printf( "Bits: " );
    for ( i=0; i<how_many ;  ) { /* for each char */
        char *ch = buffer + (start_pos+i)/8;
        for ( j=0; j<8 && i<how_many; ++j, ++i ) { /* from more significant to less */
            print_bit( *ch, j );
        }
    }
    printf ( "\n" );
}

int read_bit( char const* buffer, int i ) 
{
    char const * ch = buffer + i/8;
    int pos  = i%8;
    return ( *ch & 1<<pos ) ? 1:0;
}

/* decode num_chars characters from ciphertext */
/* function assumes output C-style string is allocated by someone else and big enough */
void decode( char const* ciphertext, int num_chars, char* plaintext ) 
{
    int i,j;
    int pos = 0;
    for(i = 0; i < num_chars; ++i) 
    {
        /* read 2 bits for group (00,01,10,11) */
        int group_index = read_bit(ciphertext, pos) + 2 * read_bit(ciphertext, pos + 1);
        int index = 0; /* index inside group */
        pos += 2;
        for(j = 0; j < group_index + 1; ++j) 
        {
            index += (read_bit(ciphertext, pos) << j);
            ++pos;
        }
        plaintext[i] = 'a' + ((1 << (group_index+ 1 )) - 2) + index;
    }
    plaintext[num_chars] = 0; /* null terminate final result */
}

/* assume all lower case input a-z (no spaces) */
void encode( char const * plaintext, char* encryptedtext, int *num_bits_used ) 
{
  int i = 0;                     /* Loop counter */
  int j = 0;
  int counter = 0;               /* Counter for number of letters in plaintext array */
  int group1234 = 0;             /* Group number, either 00, 01, 10, or 11 */
  int characterCode = 0;         /* Number for each specifie letter */
  int bitsHeld = 0;              /* Buffer that will hold the encoded bits */
  int num_bits_written = 0;      /* Total bits written to the buffer */
  int groupNumber = 0;           /* Group number that will be in decimal, not binary after being shifted */
  int groupBits = 2;             /* Bits for a group */
  *num_bits_used = 0;            /* Initializing num_bits_used just in case */
  
  while (plaintext[i] >= 'a' && plaintext[i] <= 'z')      /* Check for letters in the array. Only read in text to encode */
  {
    counter++;                                            /* Increment counter of letters in the array */
    i++;
  }
  
  for (i = 0; i < counter; i++)                           /* Going through each letter in the plaintext array */
  {
    if (plaintext[i] >= 'a' && plaintext[i] <= 'b')       /* If letter is in first group */ 
    {
      group1234 = 0;                                      /* Assign group number */
      groupNumber = group1234;                            /* Assign group number that will be used in decimal */
      characterCode = plaintext[i] - 'a';                 /* Get number for each specific letter */
    }
    
    if (plaintext[i] >= 'c' && plaintext[i] <= 'f')       /* Second group */
    {
      group1234 = 1;
      groupNumber = group1234;
      characterCode = plaintext[i] - 'c';
    }
    
    if (plaintext[i] >= 'g' && plaintext[i] <= 'n')       /* Third group */
    {
      group1234 = 2;
      groupNumber = group1234;
      characterCode = plaintext[i] - 'g';
    }
    
    if (plaintext[i] >= 'o' && plaintext[i] <= 'z')       /* Fourth group */
    {
      group1234 = 3;
      groupNumber = group1234;
      characterCode = plaintext[i] - 'o';
    }
                                                         /* Example with encoding d */
    bitsHeld |= group1234 << num_bits_written;           /* 00000000 | (01 << 0) = 00000001*/ 
    num_bits_written += groupBits;                       /* Add two for the number of bits that make up the group specification to the total number of bits written */
    
    bitsHeld |= characterCode << num_bits_written;       /* 00000001 | (001 << 2) = 00001001*/
    num_bits_written += groupNumber + 1;                 /* Add bits of character code, which is the group number + 1 */
      
    if (num_bits_written >= 8)                           /* If buffer array is over 8 bits, write to encrypted text as a byte */
    {
      *(encryptedtext + j) = bitsHeld;                   /* Write 8 bits to encryptedtext array */
      j++;
      bitsHeld = bitsHeld >> 8;                          /* Shift 8 bits to clear bitsHeld */
      num_bits_written -= 8;                             /* Subtract 8 because 8 bits were taken out of bitsHeld and added to encryptedtext */
      
      *num_bits_used += 8;                               /* Increment by 8 total number of bits added to encryptedtext */
    }
  }
  
  *(encryptedtext + j) = bitsHeld;                           /* if number of bits is not greater than 8, still write the bits to the encryptedtext array after encoding a letter */
}
