#include <stdio.h>

/*
 * Programmer: Harshith Middela
 * Lab 2 bit stream decoder.
 * This program reads a 4-bit key and an encrypted hexadecimal stream,
 * then decrypts each value by reversing alternating rotations and XORing
 * with the expanded 8-bit key, printing each decoded ASCII character.
 * When compiled with -DPROMPT it runs interactively (bit_decode1).
 * Without that flag it reads silently from redirected input (bit_decode2).
 */

unsigned char create_key(void);
unsigned char rotate_left(unsigned char value);
unsigned char rotate_right(unsigned char value);

/*
 * Reads 4 key digits using getchar and returns the
 * corresponding 8-bit key formed by duplicating the 4-bit pattern.
 */
unsigned char create_key(void)
{
    unsigned char nibble = 0;
    int index = 0;

    /* Prompt the user for the 4-bit binary key. */
#ifdef PROMPT
    printf("Enter 4-bit key: ");
#endif

    /* Read and process exactly 4 binary digits. */
    while (index < 4) {
        int ch = getchar();

        if (ch == '0' || ch == '1') {
            /* Convert ASCII digit to a single 1 or 0 value. */
            unsigned char bit = (unsigned char)(ch - '0');
            /* Shift the nibble left to make room for the new bit. */
            nibble = (unsigned char)(nibble << 1);
            /* Push the new bit into the least-significant position. */
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

    /* Duplicate the 4-bit pattern to form an 8-bit key using shift and OR. */
    return (unsigned char)((nibble << 4) | nibble);
}

/* Rotates an 8-bit value left by one bit, wrapping the MSB to the LSB. */
unsigned char rotate_left(unsigned char value)
{
    /* Move MSB to LSB while shifting everything else left. */
    return (unsigned char)((value << 1) | (value >> 7));
}

/* Rotates an 8-bit value right by one bit, wrapping the LSB to the MSB. */
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
    /* Separator is int so it can hold EOF from redirected input. */
    int separator = 0;
    int position = 0;

    /* Prompt user for the encrypted hex stream. */
#ifdef PROMPT
    printf("Enter encoded text: ");
#endif

    /* Read each 2-digit hex value; loop ends when scanf cannot read or EOF. */
    while (scanf("%2x", &cipher) == 1) {
        /* Read the character that follows the hex value (space, newline, or EOF). */
        separator = getchar();
        {
            unsigned char value = (unsigned char)cipher;
            unsigned char unrotated;
            unsigned char plain;

            /* Reverse the rotation: right on even positions, left on odd. */
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

        /* End processing when EOF is found (redirected-input case). */
        if (separator == EOF) {
            break;
        }
    }

    /* Finish output on a clean line. */
    putchar('\n');

    return 0;
}
