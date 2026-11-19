// ip_basics.c - IP addresses, masks, and networks with uint32_t
// Compile: gcc -Wall -Wextra ip_basics.c -o ip_basics && ./ip_basics

#include <stdio.h>
#include <stdint.h>

// Pack four octets into one 32-bit number.
// GOTCHA: a plain int 192 << 24 overflows (undefined behavior). Taking uint32_t
// parameters converts each octet to unsigned before the shift, which avoids it.
uint32_t make_ip(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    return (a << 24) | (b << 16) | (c << 8) | d;
}

// Unpack: shift each octet to the bottom, then & 0xFF keeps just those 8 bits.
void print_ip(uint32_t ip) {
    printf("%u.%u.%u.%u\n", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF,
                            (ip >> 8) & 0xFF,   ip & 0xFF);
}

// /26 -> 255.255.255.192: start with all 1s, shift 0s in for the host bits.
// GOTCHA: shifting a 32-bit value by 32 is undefined behavior, so /0 needs its own check.
uint32_t prefix_to_mask(int prefix) {
    if (prefix == 0) return 0;
    return 0xFFFFFFFFu << (32 - prefix);
}

int main(void) {
    uint32_t ip   = make_ip(172, 16, 5, 100);   // 172.16.5.100/27
    uint32_t mask = prefix_to_mask(27);

    printf("Mask:      "); print_ip(mask);
    printf("Network:   "); print_ip(ip & mask);    // host bits forced to 0
    printf("Broadcast: "); print_ip(ip | ~mask);   // host bits forced to 1

    // Same network if the network parts match.
    // GOTCHA: == runs before &, so the parentheses are required.
    uint32_t other = make_ip(172, 16, 5, 130);
    printf("Same network as 172.16.5.130? %s\n",
           (ip & mask) == (other & mask) ? "yes" : "no");
    return 0;
}
