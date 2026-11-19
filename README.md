# Comp210-Checkoff-3
**Assignment for Checkoff 3**

**How Does the Internet Know Where to Send Your Stuff?**

**Jeffrey Liu**

**Topic**

Applications of Bitwise Operators: Network IP Addresses. I explored how subnet masks and bitwise AND decide which network an IPv4 address belongs to.

**What I learned**
An IP address is a mailing address for a device. It has a network part (the street) and a host part (the house number).
A subnet mask is the rule that says where the street ends. 255.255.255.0 means the first three numbers are the street and the last one is the house.
Bitwise AND applies the rule. 255 is all 1s, so it keeps the number. 0 is all 0s, so it erases it. IP & mask gives the street, called the network address.
Before sending anything, your computer asks: is this on my street? Same street means send it straight there. Different street means hand it to the router, which works like a post office.

The most surprising part: the mask never leaves your device. It's only used for this check.

**Code example**

ip_basics.c takes the address 172.16.5.100/27 and:

- packs the four numbers into one 32-bit uint32_t with shifts and |
- turns the prefix /27 into a mask (255.255.255.224)
- finds the network address with ip & mask (house bits set to 0)
- finds the broadcast address with ip | ~mask (house bits set to 1)
- checks if 172.16.5.130 is on the same street by comparing ip & mask with other & mask

**How to run it**
gcc -Wall -Wextra ip_basics.c -o ip_basics && ./ip_basics


**Output**
Mask:      255.255.255.224
Network:   172.16.5.96
Broadcast: 172.16.5.127
Same network as 172.16.5.130? no

172.16.5.130 is on a different street because a /27 street only holds 32 addresses, so 172.16.5.100's street ends at .127.

**Presentation**

Slides: Attached in the Repository (But if it isn't working, here is the Canva Link: https://canva.link/1mewobq5vifmivh)

**Resources**
My AI learning conversation: https://claude.ai/share/f556f2f1-773a-478a-b47f-cb1c84216f53
