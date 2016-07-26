typedef struct {
#if 1//4�o�C�g���E�ɍ��킹��K�v������Ȃ�
	uint16_t    align;
#endif
	uint8_t		dhost[6];
	uint8_t		shost[6];
	uint16_t	type;
} T_ETHER_HDR;

#if 1//4�o�C�g���E�ɍ��킹��K�v������Ȃ�
#define NETBUFFER_ALIGN 2
#else
#define NETBUFFER_ALIGN 0
#endif

#define ETHER_HDR_SIZE (sizeof(T_ETHER_HDR))

#define GET_ETHER_HDR(nbuf)		((T_ETHER_HDR*)((nbuf)->buf))

#define ETHER_MTU 1500


/*
 *  Type �t�B�[���h
 */

#define ETHER_TYPE_IP		UINT_C(0x0800)	/* IPv4	*/
#define ETHER_TYPE_ARP		UINT_C(0x0806)	/* ARP	*/
#define ETHER_TYPE_IPV6		UINT_C(0x86dd)	/* IPv6	*/
