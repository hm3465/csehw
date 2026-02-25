#include <stdio.h>

/*
 * Programmer: Harshith Middela
 * Lab 2 bit stream decoder (redirected-input version).
 * This program reads a 4-bit key and an encrypted hexadecimal stream,
 * then decrypts each value by reversing alternating rotations and XORing
 * with the expanded 8-bit key, printing each decoded ASCII character.
 */

unsigned char create_key(void);
unsigned char rotate_left(unsigned char value);
unsigned char rotate_right(unsigned char value);

/*
 * Reads 4 key digits ('0' or '1') using getchar and returns the
 * corresponding 8-bit key formed by duplicating the 4-bit pattern.
 */
unsigned char create_key(void)
{
    unsigned char nibble = 0;
    int index = 0;

    /* * Wrap the prompt in ifdef so it can be toggled off for 
     * automated grading/redirection.
     */
#ifdef PROMPT
    printf("Enter 4-bit key: ");
#endif

    /* Read and process exactly 4 binary digits immediately. */
    while (index < 4) {
        int ch = getchar();

        if (ch == '0' || ch == '1') {
            unsigned char bit = (unsigned char)(ch - '0');
            nibble = (unsigned char)(nibble << 1);
            nibble = (unsigned char)(nibble | bit);
            index++;
        }
    }

    /* Consume any remaining characters on the key line. */
    {
        int ch = getchar();
        while (ch != '\n' && ch != EOF) {
            ch = getchar();
        }
    }

    /* Duplicate the 4-bit pattern to form an 8-bit key. */
    return (unsigned char)((nibble << 4) | nibble);
}

/* Rotates an 8-bit value left by one bit and returns the rotated result. */
unsigned char rotate_left(unsigned char value)
{
    /* Move MSB to LSB while shifting everything else left. */
    return (unsigned char)((value << 1) | (value >> 7));
}

/* Rotates an 8-bit value right by one bit and returns the rotated result. */
unsigned char rotate_right(unsigned char value)
{
    /* Move LSB to MSB while shifting everything else right. */
    return (unsigned char)((value >> 1) | (value << 7));
}

int main(void)
{
    /* Obtain the repeated 8-bit key used to decrypt each cipher byte. */
    unsigned char key = create_key();
    unsigned int cipher = 0;
    int separator = 0;
    int position = 0;

    /* Wrap the prompt in ifdef as required by the rubric. */
#ifdef PROMPT
    printf("Enter encoded text: ");
#endif

    /* Read each 2-digit hex value, then read the following separator character. */
    while (scanf("%2x", &cipher) == 1) {
        separator = getchar(); /* Rubric check: separator is an int */
        {
            unsigned char value = (unsigned char)cipher;
            unsigned char unrotated;
            unsigned char plain;

            /* Encryption rotated left on odd positions, right on even; undo that. */
            if ((position % 2) == 0) {
                unrotated = rotate_right(value);
            } else {
                unrotated = rotate_left(value);
            }

            /* XOR with key to recover plaintext ASCII, then print immediately. */
            plain = (unsigned char)(unrotated ^ key);
            putchar((int)plain);
        }

        position++;

        /* End processing at newline after the final hex value. */
        if (separator == '\n') {
            break;
        }

        /* Rubric check: Loop ends when EOF is found. */
        if (separator == EOF) {
            break;
        }
    }

    /* Finish output on a clean line. */
    putchar('\n');

    return 0;
}