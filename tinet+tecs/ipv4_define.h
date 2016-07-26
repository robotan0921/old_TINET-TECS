typedef uint32_t T_IN4_ADDR;

#define MAKE_IPV4_ADDR(a,b,c,d)		((T_IN4_ADDR)(((uint32_t)(a)<<24)|((uint32_t)(b)<<16)|((uint32_t)(c)<<8)|(d)))

/*
 *  IP �A�h���X�̒�`
 */

#define IPV4_ADDRANY		ULONG_C(0x00000000)	/* ITRON TCP/IP �W��	*/

#define IPV4_ADDR_LOOPBACK	ULONG_C(0x7f000001)
#define IPV4_ADDR_BROADCAST	ULONG_C(0xffffffff)


/*
 *  IPv4 �̒�`�ARFC791 �Q��
 */

#define IPV4_VERSION		4

/*
 *  �C���^�[�l�b�g�V�X�e���̒�`�ARFC790 �Q��
 */

/*
 *  �v���g�R�� (RFC1700)
 */

#define IPPROTO_IP		UINT_C(0)	/* IP �̃_�~�[				*/
#define IPPROTO_HOPOPTS		UINT_C(0)	/* IPv6 ���p�_ (Hop-by-Hop) �I�v�V����	*/
#define IPPROTO_ICMP		UINT_C(1)	/* ICMP					*/
#define IPPROTO_TCP		UINT_C(6)	/* TCP					*/
#define IPPROTO_UDP		UINT_C(17)	/* UDP					*/
#define IPPROTO_IPV6		UINT_C(41)	/* IPv6					*/
#define IPPROTO_ROUTING		UINT_C(43)	/* �o�H����I�v�V����			*/
#define IPPROTO_FRAGMENT	UINT_C(44)	/* �f�Љ��I�v�V����			*/
#define IPPROTO_RSVP		UINT_C(46)	/* RSVP					*/
#define IPPROTO_ESP		UINT_C(50)	/* IPv6 �Í����I�v�V����		*/
#define IPPROTO_AH		UINT_C(51)	/* IPv6 �F�؃I�v�V����			*/
#define IPPROTO_ICMPV6		UINT_C(58)	/* ICMPv6				*/
#define IPPROTO_NONE		UINT_C(59)	/* IPv6 ���w�b�_����			*/
#define IPPROTO_DSTOPTS		UINT_C(60)	/* IPv6 �I�_�I�v�V����			*/
#define IPPROTO_IPCOMP		UINT_C(108)	/* �y�C���[�h���k			*/
#define IPPROTO_DONE		UINT_C(257)	/* IPv6 �ŏ�ʃv���g�R�����͏I��	*/


/*
 *  ���[�e�B���O�\�G���g���\����
 */

typedef struct t_in4_rtentry {
	T_IN4_ADDR	target;		/* �ڕW�l�b�g���[�N�A�h���X			*/
	T_IN4_ADDR	mask;		/* �ڕW�l�b�g���[�N�A�h���X�̃T�u�l�b�g�}�X�N	*/
	T_IN4_ADDR	gateway;	/* �Q�[�g�E�F�C�� IP �A�h���X			*/
	uint32_t	expire;		/* �L�����Ԃ��؂�鎞�� [s]			*/
	uint8_t		flags;		/* �t���O					*/
	} T_IN4_RTENTRY;

/*
 *  ���[�e�B���O�G���g����ԃt���O
 */

#define IN_RTF_DEFINED		UINT_C(0x01)	/* ��`�ς�			*/
#define IN_RTF_REDIRECT		UINT_C(0x10)	/* ���������ɂ�莩���ݒ肳�ꂽ	*/



/*
 *  IPv4 �w�b�_�̒�`
 */

typedef struct t_ip4_hdr {
	uint8_t		vhl;		/* version << 4 | header length >> 2	*/
					/* length �� 4 octets �P��		*/
	uint8_t		type;		/* type of services			*/
	uint16_t	len;		/* total length				*/

	uint16_t	id;		/* identification			*/
	uint16_t	flg_off;	/* fragment flag & offset		*/

	uint8_t		ttl;		/* time to live				*/
	uint8_t		proto;		/* protocol				*/
	uint16_t	sum;		/* checksum				*/

	T_IN4_ADDR	src;		/* source address			*/
	T_IN4_ADDR	dst;		/* destination address			*/
	} T_IP4_HDR;

#define IP4_HDR_SIZE		(sizeof(T_IP4_HDR))

/*
 *  IPv4 �w�b�_�\���̃����o�A�N�Z�X�}�N��
 */

#define IP4_MAKE_VHL(v,hl)	((uint8_t)(((uint8_t)(v)<<4)|(hl)))
#define IP4_VHL_V(vhl)		((uint8_t)((uint8_t)(vhl)>>4))
#define IP4_VHL_HL(vhl)		((uint8_t)((vhl)&0x0f))

#define GET_IP4_HDR_SIZE(iph)		((uint8_t)IP4_VHL_HL((iph)->vhl) << 2)
#define GET_IP4_SDU_SIZE(iph)		(ntohs((iph)->len) - GET_IP4_HDR_SIZE(iph))

#define GET_IP4_HDR(nbuf,off)		((T_IP4_HDR*)((nbuf)->buf + off))

#define GET_IP4_SDU(iph)       ((uint8_t*)(iph + GET_IP4_HDR_SIZE(iph)))


#define SET_IP4_SDU_SIZE(iph,slen)	((iph)->len=(uint16_t)htons((slen) + IP4_HDR_SIZE))


/*
 *  IPv4 �w�b�_�̃t�B�[���h�̒l�̒�`
 */

#define IP4_VHL_BORING	UINT_C(0x45)	/* �I�v�V�������Ȃ� VHL �l	*/
#define IP4_RF		UINT_C(0x8000)	/* off: �\��			*/
#define IP4_DF		UINT_C(0x4000)	/* off: �����֎~			*/
#define IP4_MF		UINT_C(0x2000)	/* off: ��������			*/
#define IP4_OFFMASK	UINT_C(0x1fff)	/* �I�t�Z�b�g���̃}�X�N�l		*/

/*
 *  �����l
 */

#define IP4_MAXPACKET	UINT_C(65535)	/* �ő�p�P�b�g�T�C�Y		*/
#define IP4_MAXTTL	UINT_C(255)	/* TTL �ő�l			*/
#define IP4_DEFTTL	UINT_C(64)	/* TTL �K��l (RFC1340)		*/
#define IP4_FRAGTTL	UINT_C(60)	/* �������ꂽ�f�[�^�O�����̐������ԁi�b�j*/
#define IP4_MSS		UINT_C(576)	/* �ő�Z�O�����g�T�C�Y�̋K��l	*/


/****************************************
  ARP�Ɋւ����`
******************************************/



typedef struct arp_entry {
    T_NET_BUF	*hold;		/* ARP �̉����҂��o�̓t���[��	*/
    T_IN4_ADDR	ip_addr;	/* IP �A�h���X			*/
    uint16_t	expire;		/* �j���܂ł̎��ԁA0 �Ȃ疢�g�p	*/
    uint8_t	mac_addr[6];	/* MAC �A�h���X	*/
} T_ARP_ENTRY;


/* ARP �w�b�_ */

typedef struct t_arp_hdr {
	uint16_t	hrd_addr;	/* �����A�h���X�t�H�[�}�b�g	*/
	uint16_t	proto;		/* �v���g�R��			*/
	uint8_t		hdr_len;	/* �����A�h���X��		*/
	uint8_t		proto_len;	/* �v���g�R����			*/
	uint16_t	opcode;		/* ���߃R�[�h			*/
	} T_ARP_HDR;


#define ARP_HDR_SIZE			(sizeof(T_ARP_HDR))
#define GET_ARP_HDR(nbuf)		((T_ARP_HDR*)((nbuf)->buf + ETHER_HDR_SIZE))


/* ARP ���g */
typedef struct t_ether_arp_hdr {
	uint8_t		shost[6];	/* ���M�z�X�g�̕����A�h���X	*/
	uint8_t		sproto[4];	/* ���M�z�X�g�� IP �A�h���X	*/
	uint8_t		thost[6];	/* �����Ώە����A�h���X		*/
	uint8_t		tproto[4];	/* �����Ώ� IP �A�h���X		*/
	} T_ETHER_ARP_HDR;

#define ETHER_ARP_HDR_SIZE		(sizeof(T_ETHER_ARP_HDR))

#define IF_ARP_ETHER_HDR_SIZE		(ETHER_HDR_SIZE + ARP_HDR_SIZE + ETHER_ARP_HDR_SIZE)

#define GET_IF_ARP_HDR_SIZE(nbuf)	(ETHER_HDR_SIZE + ARP_HDR_SIZE)
#define GET_ETHER_ARP_HDR(nbuf)		((T_ETHER_ARP_HDR*)((nbuf)->buf + GET_IF_ARP_HDR_SIZE(nbuf)))


/* hrd_addr�A�����A�h���X�t�H�[�}�b�g�̒l */

#define ARPHRD_ETHER	1	/* Ethernet	*/

/* opcode, ���߃R�[�h�̒l */

#define ARPOP_REQUEST		UINT_C(1)	/* �A�h���X�����v��		*/
#define ARPOP_REPLY		UINT_C(2)	/* �A�h���X��������		*/
#define ARPOP_REV_REQUEST	UINT_C(3)	/* �v���g�R���E�A�h���X�����v��	*/
#define ARPOP_REV_REPLY		UINT_C(4)	/* �v���g�R���E�A�h���X�����v��	*/
#define ARPOP_INV_REQUEST	UINT_C(8)	/* �I�[���ʗv��			*/
#define ARPOP_INV_REPLY		UINT_C(9)	/* �I�[���ʗv��			*/


#define ARP_CACHE_KEEP		(20*60*10)	/* ARP �L���b�V���̃^�C���A�E�g	*/

#define TMO_ARP_GET_NET_BUF		ULONG_C(1000)	/* [ms]�AARP �̃l�b�g���[�N�o�b�t�@�l���^�C���A�E�g	*/
#define TMO_ARP_OUTPUT			ULONG_C(1000)	/* [ms]�A�A�h���X�����v���o�̓^�C���A�E�g		*/



/****************************************
  ICMP4�Ɋւ����`
******************************************/
/*
 *  ICMP �w�b�_�̒�`�ARFC 792
 */

typedef struct t_icmp_hdr {
	uint8_t		type;		/* ���b�Z�[�W�̌^	*/
	uint8_t		code;		/* �T�u�^		*/
	uint16_t	sum;		/* �`�F�b�N�T��		*/
	union {
		struct id_seq {
			uint16_t	id;
			uint16_t	seq;
			} id_seq;
		T_IN4_ADDR	addr;
		} data;
	} T_ICMP4_HDR;

#define ICMP4_HDR_SIZE			(sizeof(T_ICMP4_HDR))
#define GET_ICMP4_HDR(nbuf,ihoff)	((T_ICMP4_HDR*)((uint8_t*)((nbuf)->buf) + ihoff))
#define GET_ICMP4_SDU(nbuf,ihoff)	((uint8_t*)((nbuf)->buf) + ihoff + ICMP4_HDR_SIZE)

#define TMO_ICMP_OUTPUT			ULONG_C(1000)	/* [ms]�AICMP �o�̓^�C���A�E�g				*/



/*
 *  ���b�Z�[�W�̌^
 */

#define ICMP4_ECHO_REPLY	UINT_C(0)	/* �G�R�[����		*/
#define ICMP4_UNREACH		UINT_C(3)	/* �G���[		*/
#define ICMP4_SOURCE_QUENCH	UINT_C(4)	/* ���M����		*/
#define ICMP4_REDIRECT		UINT_C(5)	/* �����ύX		*/
#define ICMP4_ECHO_REQUEST	UINT_C(8)	/* �G�R�[�v��		*/
#define ICMP4_TIME_EXCEEDED	UINT_C(11)	/* ���M����		*/
#define ICMP4_PARAMETER		UINT_C(12)	/* �p�����[�^�ُ�	*/
#define ICMP4_TIME_REQUEST	UINT_C(13)	/* �^�C���X�^���v�v��	*/
#define ICMP4_TIME_REPLY	UINT_C(14)	/* �^�C���X�^���v����	*/
#define ICMP4_MASK_REQUEST	UINT_C(17)	/* �A�h���X�}�X�N�v��	*/
#define ICMP4_MASK_REPLY	UINT_C(18)	/* �A�h���X�}�X�N����	*/

/*
 *  �T�u�^
 */

/* ICMP4_UNREACH (3)	*/

#define ICMP4_UNREACH_NET		UINT_C(0)	/* �l�b�g���[�N		*/
#define ICMP4_UNREACH_HOST		UINT_C(1)	/* �z�X�g		*/
#define ICMP4_UNREACH_PROTOCOL		UINT_C(2)	/* �v���g�R��		*/
#define ICMP4_UNREACH_PORT		UINT_C(3)	/* �|�[�g		*/
#define ICMP4_UNREACH_FLAG		UINT_C(4)	/* ����			*/
#define ICMP4_UNREACH_SRC_FAIL		UINT_C(5)	/* �\�[�X�o�H		*/
#define ICMP4_UNREACH_NET_UNKNOWN	UINT_C(6)	/* �l�b�g���[�N�s��	*/
#define ICMP4_UNREACH_HOST_UNKNOWN	UINT_C(7)	/* �z�X�g�s��		*/
#define ICMP4_UNREACH_ISOLATED		UINT_C(8)	/* ����			*/
#define ICMP4_UNREACH_NET_PROHIB	UINT_C(9)	/* 			*/
#define ICMP4_UNREACH_HOST_PROHIB	UINT_C(10)	/* 			*/
#define ICMP4_UNREACH_TOS_NET		UINT_C(11)	/* �l�b�g���[�N�ւ̕s��TOS*/
#define ICMP4_UNREACH_TOS_HOST		UINT_C(12)	/* �z�X�g�ւ̕s��TOS	*/
#define ICMP4_UNREACH_FILTER_PROHIB	UINT_C(13)	/* 			*/
#define ICMP4_UNREACH_HOST_PRECEDENCE	UINT_C(14)	/* 			*/
#define ICMP4_UNREACH_PRECEDENCE_CUTOFF	UINT_C(15)	/* 			*/

/* ICMP4_REDIRECT (5)	*/

#define ICMP4_REDIRECT_NET		UINT_C(0)	/* �l�b�g���[�N		*/
#define ICMP4_REDIRECT_HOST		UINT_C(1)	/* �z�X�g		*/
#define ICMP4_REDIRECT_PORT_AND_NET	UINT_C(2)	/* �|�[�g�ԍ��ƃl�b�g	*/
#define ICMP4_REDIRECT_PORT_AND_HOST	UINT_C(3)	/* �|�[�g�ԍ��ƃz�X�g	*/


/*
 *  �Ǝ��̃G���[�R�[�h
 */

#define EV_NOPND		(-97)		/* �y���f�B���O���Ă��Ȃ� */

/*
 *  �l�b�g���[�N�G���[�R�[�h
 */

#define EV_MSIZE		(-98)		/* �f�[�^�O����������	*/
#define EV_NURCH		(-99)		/* �l�b�g���[�N���B�s�\	*/
#define EV_HDOWN		(-100)		/* �z�X�g�_�E��		*/
#define EV_HURCH		(-101)		/* �z�X�g���B�s�\	*/
#define EV_CNNRF		(-102)		/* �ڑ��s�\		*/
#define EV_CNRST		(-103)		/* �ڑ����Z�b�g		*/
#define EV_REXMTMO		(-104)		/* �đ��^�C���A�E�g	*/

/*
 *  IP �A�h���X�̒�`
 */
#define IPV4_CLASS_D(i)		(((i) & ULONG_C(0xf0000000)) == ULONG_C(0xe0000000))

#define IN4_IS_ADDR_MULTICAST(i)	IPV4_CLASS_D(i)

#define IN4_IS_NET_ADDR_MULTICAST(a)	IN4_IS_ADDR_MULTICAST(ntohl(*(a)))

#define IN4_COPY_TO_NET(d,s)		(*(d)=htonl(*(s)))
