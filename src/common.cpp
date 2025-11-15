#include "common.h"
#include "kernel.h"

static unsigned long long divmod_u64(unsigned long long value, unsigned base, unsigned *remainder)
{
    unsigned long long quotient = 0;
    unsigned long long rem = 0;
    for (int bit = 63; bit >= 0; bit--)
    {
        rem = (rem << 1) | ((value >> bit) & 1ull);
        if (rem >= base)
        {
            rem -= base;
            quotient |= 1ull << bit;
        }
    }
    *remainder = (unsigned)rem;
    return quotient;
}

static void print_unsigned(unsigned long long value, unsigned base)
{
    char digits[] = "0123456789abcdef";
    char buf[65];
    int i = 0;

    if (base < 2)
        base = 10;

    do
    {
        unsigned rem = 0;
        value = divmod_u64(value, base, &rem);
        buf[i++] = digits[rem];
    } while (value);

    while (i--)
        putchar(buf[i]);
}

static void print_signed(long long value)
{
    unsigned long long magnitude = (unsigned long long)value;
    if (value < 0)
    {
        putchar('-');
        magnitude = (unsigned long long)(-(value + 1)) + 1;
    }

    print_unsigned(magnitude, 10);
}

void printf(const char *fmt, ...)
{
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt)
    {
        if (*fmt == '%')
        {
            fmt++;
            int long_mod = 0;
            while (*fmt == 'l')
            {
                long_mod++;
                fmt++;
            }

            if (*fmt == '\0')
            {
                putchar('%');
                goto end;
            }

            switch (*fmt)
            {
            case '\0':
                putchar('%');
                goto end;
            case '%':
                putchar('%');
                break;
            case 's':
            {
                const char *s = va_arg(vargs, const char *);
                while (*s)
                {
                    putchar(*s);
                    s++;
                }
                break;
            }
            case 'd':
            { // Print a signed integer in decimal.
                long long value;
                if (long_mod >= 2)
                    value = va_arg(vargs, long long);
                else if (long_mod == 1)
                    value = va_arg(vargs, long);
                else
                    value = va_arg(vargs, int);
                print_signed(value);
                break;
            }
            case 'u':
            { // Print an unsigned integer in decimal.
                unsigned long long value;
                if (long_mod >= 2)
                    value = va_arg(vargs, unsigned long long);
                else if (long_mod == 1)
                    value = va_arg(vargs, unsigned long);
                else
                    value = va_arg(vargs, unsigned);
                print_unsigned(value, 10);
                break;
            }
            case 'x':
            { // Print an integer in hexadecimal.
                unsigned long long value;
                if (long_mod >= 2)
                    value = va_arg(vargs, unsigned long long);
                else if (long_mod == 1)
                    value = va_arg(vargs, unsigned long);
                else
                    value = va_arg(vargs, unsigned);
                print_unsigned(value, 16);
                break;
            }
            default:
                putchar('%');
                while (long_mod--)
                    putchar('l');
                putchar(*fmt);
                break;
            }
        }
        else
        {
            putchar(*fmt);
        }

        fmt++;
    }

end:
    va_end(vargs);
}

void *memset(void *buf, char c, size_t n)
{
    uint8_t *p = (uint8_t *)buf;
    while (n--)
        *p++ = c;
    return buf;
}

void *memcpy(void *dst, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;
    while (n--)
        *d++ = *s++;
    return dst;
}

char *strcpy(char *dst, const char *src)
{
    char *d = dst;
    while (*src)
        *d++ = *src++;
    *d = '\0';
    return dst;
}

int strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            break;
        s1++;
        s2++;
    }

    return *(unsigned char *)s1 - *(unsigned char *)s2;
}
