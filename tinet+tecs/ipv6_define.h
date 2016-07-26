/*
 *  IPv6 ƒAƒhƒŒƒX
 */

typedef struct t_in6_addr {
	union {
		uint8_t		__u6_addr8[16];
		uint16_t	__u6_addr16[8];
		uint32_t	__u6_addr32[4];
		} __u6_addr;
	}T_IN6_ADDR;