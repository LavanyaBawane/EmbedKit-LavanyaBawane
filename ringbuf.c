
#include <stdio.h>
#include <stdint.h>

#define SIZE 8

uint8_t b[SIZE], h = 0, t = 0, c = 0;

int buffer_write(uint8_t x)
{
    if (c == SIZE) return 0;
    b[h] = x;
    h = (h + 1) % SIZE;
    c++;
    return 1;
}

int buffer_read(uint8_t *x)
{
    if (c == 0) return 0;
    *x = b[t];
    t = (t + 1) % SIZE;
    c--;
    return 1;
}

int main(void)
{
    uint8_t x;

    for (int i = 0; i < SIZE; i++)
        printf("Write %X: %s\n", 0x41+i,
               buffer_write(0x41+i) ? "OK" : "FAIL");

    printf("Full: %s\n", c == SIZE ? "YES" : "NO");
    printf("Write 99: %s\n", buffer_write(0x99) ? "OK" : "FAIL");

    for (int i = 0; i < 3; i++) {
        buffer_read(&x);
        printf("Read: %X\n", x);
    }

    for (int i = 0; i < 3; i++)
        buffer_write(0x49+i);

    while (buffer_read(&x))
        printf("Read: %X\n", x);

    printf("Empty read: %s\n",
           buffer_read(&x) ? "OK" : "FAIL");

    return 0;
}
