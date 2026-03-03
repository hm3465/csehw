//Question 2: Implementing string functions
char *my_strncpy(char *dest, const char *src, unsigned int n) {
    char *start = dest; //Save the original starting address
    //Copy characters until we hit 'n'
    while (n > 0 && *src != '\0') {
        *dest = *src; 
        dest++;       
        src++;        
        n--;          
    }
    //If we haven't reached 'n', the rest should be null characters
    while (n > 0) {
        *dest = '\0';
        dest++;
        n--;
    }
    return start;
}

int my_strncmp(const char *s1, const char *s2, unsigned int n) {
    //Traverse as long as characters match
    while (n > 0 && *s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
        n--;
    }
    //If we checked all 'n' characters without breaking, the strings should equal 'n'
    if (n == 0) {
        return 0;
    }
    //Cast to unsigned char before subtracting
    return (unsigned char)(*s1) - (unsigned char)(*s2);
}
char *my_strncat(char *dest, const char *src, unsigned int n) {
    char *start = dest; 
    //Walk the 'dest' pointer to the end of the current string
    while (*dest != '\0') {
        dest++;
    }
    //Copy characters from 'src' to the end of 'dest'
    while (n > 0 && *src != '\0') {
        *dest = *src;
        dest++;
        src++;
        n--;
    }
    //Ensure the new string is null-terminated
    *dest = '\0';
    return start;
}