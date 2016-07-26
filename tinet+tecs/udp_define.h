/*
 *  UDP �w�b�_�ARFC768 �Q��
 */

typedef struct t_udp_hdr {
	uint16_t	sport;		/* ���M���|�[�g�ԍ�	*/
	uint16_t	dport;		/* ����|�[�g�ԍ�	*/

	uint16_t	ulen;		/* �f�[�^�O������	*/
	uint16_t	sum;		/* �`�F�b�N�T��		*/
	} T_UDP_HDR;

#define UDP_HDR_SIZE			(sizeof(T_UDP_HDR))

#define GET_UDP_HDR(nbuf,uhoff)		((T_UDP_HDR*)((uint8_t*)((nbuf)->buf) + uhoff))
#define GET_UDP_SDU(nbuf,uhoff)		((uint8_t*)((nbuf)->buf) + uhoff+ UDP_HDR_SIZE)



/* UDP �֌W */

#define TFN_UDP_CRE_CEP		(-0x221)
#define TFN_UDP_DEL_CEP		(-0x222)
#define TFN_UDP_SND_DAT		(-0x223)
#define TFN_UDP_RCV_DAT		(-0x224)
#define TFN_UDP_CAN_CEP		(-0x225)
#define TFN_UDP_SET_OPT		(-0x226)
#define TFN_UDP_GET_OPT		(-0x227)
#define TFN_UDP_ALL		(0)

#define TEV_UDP_RCV_DAT		(-0x221)
#define UDP_CEP_NONE		UINT_C(0)

/*
 *  �|�[�g�ԍ��̒�`
 */

#define TCP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP �W��	*/
#define UDP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP �W��	*/


#define UDP_PORT_FIRST_AUTO		UINT_C(1024)	/* �������蓖�ĊJ�n�ԍ�	*/
#define UDP_PORT_LAST_AUTO		UINT_C(4999)	/* �������蓖�ďI���ԍ�	*/


/*
 *  UDP �ʐM�[�_�t���O
 */

#define UDP_CEP_FLG_POST_OUTPUT	UINT_C(0x0200)	/* ���M���J�n����B		*/
#define UDP_CEP_FLG_DYNAMIC	UINT_C(0x0400)	/* ���I�����E�폜�\�ʐM�[�_�B	*/
#define UDP_CEP_FLG_VALID	UINT_C(0x0800)	/* �����ς݂ŗL���ȒʐM�[�_�B	*/




//#define FLAG_USE_TCP	UINT_C(0x02000000)	/* TDP�𗘗p����t���O */

//#define FLAG_USE_IPV4   UINT_C(0x00010000) //IPv4
//#define FLAG_USE_IPV6   UINT_C(0x00020000) //IPv6

//#define FLAG_USE_ETHER  UINT_C(0x00000100) //ethernet