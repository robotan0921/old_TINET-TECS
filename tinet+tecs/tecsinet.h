
#ifdef TECS
#define TOPPERS_MACRO_ONLY
#endif

#include "sil.h"
#include "t_syslog.h"
#include "itron.h"


#define FLAG_USE_UDP	(0x01)	/* TCPを利用するフラグ */
#define FLAG_USE_TCP	(0x02)	/* UDPを利用するフラグ */

#define FLAG_USE_IPV4   (0x04) //IPv4
#define FLAG_USE_IPV6   (0x08) //IPv6

#define FLAG_USE_ETHER  (0x10) //ethernet


#ifdef SIL_ENDIAN_LITTLE

extern void rev_memcpy_word (uint8_t *dst, uint8_t *src);
extern int  rev_memcmp_word (uint8_t *data1, uint8_t *data2);


#define NET_REV_ENDIAN_HWORD(d)	((uint16_t)((((uint16_t)(d)&0xff)<<8)|(((uint16_t)(d)>>8)&0xff)))


#define NET_REV_ENDIAN_WORD(d)	((uint32_t)((((uint32_t)(d)&0xff)<<24)|(((uint32_t)(d)&0xff00)<<8)| \
				            (((uint32_t)(d)>>8)&0xff00)|(((uint32_t)(d)>>24)&0xff)))

#define ntohs(n)		NET_REV_ENDIAN_HWORD(n)
#define htons(h)		NET_REV_ENDIAN_HWORD(h)
#define ntohl(n)		NET_REV_ENDIAN_WORD(n)
#define htonl(h)		NET_REV_ENDIAN_WORD(h)

#define NTOHS(n)		((n)=NET_REV_ENDIAN_HWORD(n))
#define HTONS(h)		((h)=NET_REV_ENDIAN_HWORD(h))
#define NTOHL(n)		((n)=NET_REV_ENDIAN_WORD(n))
#define HTONL(h)		((h)=NET_REV_ENDIAN_WORD(h))

#define ntoahl(h,n)		rev_memcpy_word((uint8_t*)&(h),(n))
#define ahtonl(n,h)		rev_memcpy_word((n),(uint8_t*)&(h))
#define nahcmpl(n,h)		rev_memcmp_word((n),(uint8_t*)&(h))

/*プロトコルフラグに関する定義 */

/*
 * プロトコルフラグ
 */

//#define FLAG_SET_UDP	((uint32_t)(0x01))<<24	/* UDPを利用するフラグ */
//#define FLAG_SET_TCP	((uint32_t)(0x02))<<24	/* TDPを利用するフラグ */

//#define FLAG_SET_IPV4   ((uint32_t)(0x01))<<16 //IPv4
//#define FLAG_SET_IPV6   ((uint32_t)(0x02))<<16 //IPv6

//#define FLAG_SET_ETHER  ((uint32_t)(0x01))<<8 //ethernet

//#define FLAG_SET_UDP	UINT_C(0x00000001)	/* UDPを利用するフラグ */
//#define FLAG_SET_TCP	UINT_C(0x00000002)	/* TDPを利用するフラグ */

//#define FLAG_SET_IPV4   UINT_C(0x00000100) //IPv4
//#define FLAG_SET_IPV6   UINT_C(0x00000200) //IPv6

//#define FLAG_SET_ETHER  UINT_C(0x00010000) //ethernet


//#define FLAG_USE_UDP	UINT_C(0x00000001)	/* TCPを利用するフラグ */
//#define FLAG_USE_TCP	UINT_C(0x00000002)	/* UDPを利用するフラグ */

//#define FLAG_USE_IPV4   UINT_C(0x00000100) //IPv4
//#define FLAG_USE_IPV6   UINT_C(0x00000200) //IPv6

//#define FLAG_USE_ETHER  UINT_C(0x00010000) //ethernet

#endif

/* 一般 */

#define NADR			((void*)(-1))	/* 無効アドレス */
#define IS_PTR_DEFINED(a)	((void*)(a)!=NADR&&(void*)(a)!=NULL)
