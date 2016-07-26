
/*
 *  ITRON TCP/IPv4 �A�h���X/�|�[�g�ԍ��̒�`
 */

typedef struct t_ipv4ep {
	uint32_t	ipaddr;		/* IPv4 �A�h���X	*/
	uint16_t	portno;		/* �|�[�g�ԍ�		*/
} T_IPV4EP;



/* TCP �^�C�}�ϐ� */

#define NUM_TCP_TIMERS		4	/* TCP �̃^�C�}��	*/

#define TCP_TIM_REXMT		0	/* �đ��^�C�}		*/
#define TCP_TIM_PERSIST		1	/* �����^�C�}		*/
#define TCP_TIM_KEEP		2	/* �ۗ� (keep alive) �^�C�}*/
#define TCP_TIM_2MSL		3	/* 2MSL �^�C�}		*/



/*
 *  �ǉ� API �@�\�E���ۃR�[�h
 */

#define TMO_TCP_OUTPUT			ULONG_C(1000)	/* [ms]�ATCP �o�̓^�C���A�E�g				*/


/* TCP �֌W */

#define TFN_TCP_UNDEF		(0)

#define IN4_COPY_TO_HOST(d,s)		(*(d)=ntohl(*(s)))


/*
 *  ���̑��̒萔
 */

#define TCP_MAX_REXMT_SHIFT	12	/* �ő�đ���		*/


#define TCP_TOTAL_BACK_OFF	511	/* �o�b�N�I�t���Ԃ̍��v */

/*
 *  TCP �w�b�_�\���̃����o�A�N�Z�X�}�N��
 */

#define TCP_MAKE_DATA_OFF(o)	((uint8_t)(((uint8_t)(o) << 2) & 0xf0))
#define TCP_DATA_OFF(o)		(((uint8_t)(o) & UINT_C(0xf0)) >> 2)
#define TCP_HDR_LEN(o)		(TCP_DATA_OFF(o))


/*
 *  TCP �w�b�_�ARFC 793 �Q��
 */

typedef struct t_tcp_hdr {
	uint16_t	sport;		/* ���M���|�[�g�ԍ�			*/
	uint16_t	dport;		/* ����|�[�g�ԍ�			*/

	uint32_t	seq;		/* SEQ �ԍ�				*/

	uint32_t	ack;		/* ACK �ԍ�				*/

	uint8_t		doff;		/* �f�[�^�I�t�Z�b�g(���4�r�b�g)	*/
	uint8_t		flags;		/* �t���O(����6�r�b�g)			*/
	uint16_t	win;		/* �E�B���h�T�C�Y			*/

	uint16_t	sum;		/* �`�F�b�N�T��				*/
	uint16_t	urp;		/* �ً}�|�C���^				*/
	} T_TCP_HDR;

#define TCP_HDR_SIZE			(sizeof(T_TCP_HDR))

#define GET_TCP_HDR(nbuf,thoff)		((T_TCP_HDR*)((uint8_t*)((nbuf)->buf) + thoff))
#define GET_TCP_HDR_SIZE2(nbuf,thoff)	(TCP_HDR_LEN(GET_TCP_HDR(nbuf,thoff)->doff))
#define GET_TCP_SDU(nbuf,thoff)		((uint8_t*)((nbuf)->buf) + thoff + GET_TCP_HDR_SIZE2(nbuf,thoff))


/*
 *  ��M�č\���L���[�ł� TCP �w�b�_
 */

typedef struct t_tcp_q_hdr {
	uint16_t	sport;		/* ���M���|�[�g�ԍ�			*/
	uint16_t	dport;		/* ����|�[�g�ԍ�			*/

	uint32_t	seq;		/* SEQ �ԍ�				*/

	T_NET_BUF 	*next;		/* ���̃Z�O�����g�A���� ACK �ԍ�(ack)	*/

	uint8_t		doff;		/* �f�[�^�I�t�Z�b�g(���4�r�b�g)	*/
	uint8_t		flags;		/* �t���O(����6�r�b�g)			*/
	uint16_t	soff;		/* SDU �I�t�Z�b�g�A���̓E�B���h�T�C�Y(win)	*/

	uint16_t	slen;		/* SDU ���A���̓`�F�b�N�T��(sum)	*/
	uint16_t	urp;		/* �ً}�|�C���^�iSDU ���␳�j		*/
	} T_TCP_Q_HDR;

/*
 *  TCP �̍č\���L���[�ɂ����� IPv4 �w�b�_�̒�`
 */

typedef struct t_tcp_ip4_q_hdr {
	uint8_t		vhl;		/* version << 4 | header length >> 2	*/
					/* length �� 4 octets �P��		*/
	uint8_t		type;		/* type of services			*/
	uint16_t	len;		/* total length				*/

	uint16_t	id;		/* identification			*/
	uint16_t	flg_off;	/* fragment flag & offset		*/

	uint8_t		ttl;		/* time to live				*/
	uint8_t		proto;		/* protocol				*/
	uint16_t	thoff;		/* TCP �w�b�_�̃I�t�Z�b�g		*/

	T_IN4_ADDR	src;		/* source address			*/
	T_IN4_ADDR	dst;		/* destination address			*/
	} T_TCP_IP4_Q_HDR;


#define GET_TCP_Q_HDR(nbuf,thoff)	((T_TCP_Q_HDR*)((uint8_t*)((nbuf)->buf) + thoff))



/* TCP �^�C�}�l�̌^ */

typedef int16_t T_TCP_TIME;

/*
 *  TCP �ʐM�[�_
 */

typedef uint32_t T_TCP_SEQ;
typedef uint16_t T_TCP_SEG;
typedef uint16_t T_TCP_WND;

typedef struct t_tcp_cep {
	ID		snd_tskid;	/* ���M�^�X�N���ʎq		*/
	ID		rcv_tskid;	/* ��M�^�X�N���ʎq		*/
	
	uint8_t		*sbuf_rptr;	/* ���M�p�ǂݏo���|�C���^	*/
	uint8_t		*sbuf_wptr;	/* ���M�p�������݃|�C���^	*/
	uint8_t		*rbuf_rptr;	/* ��M�p�ǂݏo���|�C���^	*/
	uint8_t		*rbuf_wptr;	/* ��M�p�������݃|�C���^	*/
	T_TCP_SEQ	snd_ssthresh;	/* �t�s�E�B���h�T�C�Y(snd_cwnd)	*/
					/* �̂������l			*/
	T_TCP_TIME	rxtcur;		/* ���݂̍đ��^�C���A�E�g	*/
	T_TCP_TIME	srtt;		/* ���������ꂽ RTT		*/
	T_TCP_TIME	rttvar;		/* ���������ꂽ���U		*/
	T_TCP_WND	snd_cwnd;	/* �t�s�E�B���h�T�C�Y		*/

	/*
	 *  ����̍ő��M�Z�O�����g�T�C�Y	
	 *
	 *    �I���W�i���ł́A��ʂ̃Z�O�����g�̍ő�T�C�Y (t_maxseg) �ƁA
	 *    �I�v�V�����t���̃Z�O�����g�̍ő�T�C�Y (t_maxopd) ���ʂ�
	 *    �Ȃ��Ă���B����́A���݂̃C���^�[�l�b�g�ł́A�I�v�V�����t����
	 *    �Z�O�����g�̂ق�����������Ɛ�������Ă��邽�߂ł���B
	 *    �{�����ł́A�ő�Z�O�����g�T�C�Y�I�v�V�����ȊO�̃I�v�V������
	 *    �������Ȃ��̂ŁAt_maxseg �̎g�p����B
	 */
	T_TCP_SEG	maxseg;

	int16_t		snd_tfn;	/* ���M���쒆�� API �@�\�R�[�h	*/
	int16_t		rcv_tfn;	/* ��M���쒆�� API �@�\�R�[�h	*/


	/*
	 *  ����ȍ~�̃����o�[�� tcp_init_cep() �֐��Ń[���N���A�[�����B
	 */

	T_TCP_TIME	timer[NUM_TCP_TIMERS];	/* TCP �̃^�C�}		*/
	//T_TCP4_REP	*rep;		/* ��t��			*/
	T_NET_BUF	*reassq;	/* ��M�č\���L���[		*/

	T_TCP_SEQ	snd_una;	/* ���m�F�̍ŏ����M SEQ �܂�	*/
					/* �m�F���ꂽ�ő呗�M SEQ	*/
	T_TCP_SEQ	snd_max;	/* ���M�����ő� SEQ		*/
	T_TCP_SEQ	snd_nxt;	/* ���ɑ��M���� SEQ		*/
	T_TCP_SEQ	snd_old_nxt;	/* ���� snd_nxt			*/
	T_TCP_SEQ	snd_wl1;	/* �O��E�B���h���X�V���� SEQ	*/
	T_TCP_SEQ	snd_wl2;	/* �O��E�B���h���X�V���� ACK	*/
	T_TCP_SEQ	iss;		/* ������ SEQ �̏����l		*/
	T_TCP_SEQ	irs;		/* ����� SEQ �̏����l		*/
	T_TCP_SEQ	rcv_nxt;	/* ��M�����҂��Ă���ŏ��� SEQ	*/
	T_TCP_SEQ	rcv_adv;	/* ��M�����҂��Ă���ő�� SEQ	*/
	T_TCP_SEQ	rcv_wnd;	/* ��M�\�ȃE�B���h�T�C�Y	*/
	T_TCP_SEQ	rtseq;		/* ���Ԍv�����n�߂� SEQ		*/
	T_TCP_SEQ	last_ack_sent;	/* �Ō�ɑ��M���� ACK		*/
	T_TCP_TIME	idle;		/* �A�C�h������			*/
	ER		error;		/* �񓯊��ɔ��������G���[	*/
	ER		net_error;	/* �l�b�g���[�N�̃G���[���	*/
	T_TCP_WND	snd_wnd;	/* ����̎�M�\�E�B���h�T�C�Y	*/
	T_TCP_WND	max_sndwnd;	/* ���܂ł̍ő呗�M�E�B���h�T�C�Y	*/
	T_TCP_TIME	rtt;		/* ��������				*/
	uint16_t	swbuf_count;	/* ���M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint16_t	rwbuf_count;	/* ��M�E�B���h�o�b�t�@�̎g�p���T�C�Y	*/
	uint16_t	rcv_buf_len;	/* tcp_rcv_buf �̊����Ē�	*/
	uint16_t	get_buf_len;	/* tcp_rcv_buf �̊����Ē�	*/
	uint8_t		rxtshift;	/* �đ��M�񐔂� log(2)		*/
	uint8_t		fsm_state;	/* FSM ���			*/
	uint8_t		dupacks;	/* �đ� ACK ��			*/
}T_TCP_CEP;

/* 
 *  �Z�O�����g�̏��Ԃ����ւ���Ƃ��ɐV���Ƀl�b�g���[�N�o�b�t�@�������ĂāA
 *  �f�[�^���R�s�[����T�C�Y�̂������l
 */
#define MAX_TCP_REALLOC_SIZE	1024

#define TMO_TCP_GET_NET_BUF		ULONG_C(1000)	/* [ms]�ATCP �̃l�b�g���[�N�o�b�t�@�l���^�C���A�E�g	*/


/*
 *  TCP �w�b�_�̃t���O�t�B�[���h�̒l�̒�`
 */

#define TCP_FLG_FIN		UINT_C(0x01)	/* FIN:	�ŏI			*/
#define TCP_FLG_SYN		UINT_C(0x02)	/* SYN:	����			*/
#define TCP_FLG_RST		UINT_C(0x04)	/* RST:	�R�l�N�V�����̃��Z�b�g	*/
#define TCP_FLG_PUSH		UINT_C(0x08)	/* PUSH:�v�b�V���@�\		*/
#define TCP_FLG_ACK		UINT_C(0x10)	/* ACK:	�m�艞��		*/
#define TCP_FLG_URG		UINT_C(0x20)	/* URG:	�ً}���		*/


/*
 *  TCP FSM ��Ԃ̒�`�ARFC 793 �Q��
 */

#define TCP_FSM_CLOSED		0	/* �N���[�Y				*/
#define TCP_FSM_LISTEN		1	/* �󓮃I�[�v��				*/
#define TCP_FSM_SYN_SENT	2	/* �\���I�[�v���ASYN ���M�ς�		*/
#define TCP_FSM_SYN_RECVD	3	/* �󓮃I�[�v���ASYN ��M�ς�		*/
#define TCP_FSM_ESTABLISHED	4	/* �R�l�N�V�����J�݊���			*/
#define TCP_FSM_CLOSE_WAIT	5	/* ���肩�� FIN ��M�AAPP �̏I���҂�	*/
#define TCP_FSM_FIN_WAIT_1	6	/* APP ���I���AFIN ���M�ς݁AACK �҂�	*/
#define TCP_FSM_CLOSING		7	/* �����N���[�Y�AFIN �����ς݁AACK �҂�	*/
#define TCP_FSM_LAST_ACK	8	/* APP ���I���AACK �҂�			*/
#define TCP_FSM_FIN_WAIT_2	9	/* ���肩��� FIN �҂�			*/
#define TCP_FSM_TIME_WAIT	10	/* ���肩��� FIN ��M�ς݁A���ԑ҂�	*/





/*
 *  TCP �ʐM�[�_�̏�ԃt���O
 */

#define TCP_CEP_FLG_ACK_NOW		ULONG_C(0x00000001)	/* �����ɑ���� ACK �𑗂�B	*/
#define TCP_CEP_FLG_DEL_ACK		ULONG_C(0x00000002)	/* ACK ��x������B		*/
#define TCP_CEP_FLG_SENT_FIN		ULONG_C(0x00000004)	/* FIN �𑗂��Ă���B		*/
#define TCP_CEP_FLG_NEED_SYN		ULONG_C(0x00000008)	/* SYN �𑗐M����B		*/
#define TCP_CEP_FLG_NEED_FIN		ULONG_C(0x00000010)	/* FIN �𑗐M����B		*/
#define TCP_CEP_FLG_FORCE		ULONG_C(0x00000020)	/* �������M�B			*/
#define TCP_CEP_FLG_NO_PUSH		ULONG_C(0x00000040)	/* push ���Ȃ��B		*/
#define TCP_CEP_FLG_NO_DELAY		ULONG_C(0x00000080)	/* �x�����Ȃ��B			*/
#define TCP_CEP_FLG_FORCE_CLEAR		ULONG_C(0x00000100)	/* �������M������t���O���N���A�[����B*/
#define TCP_CEP_FLG_POST_OUTPUT		ULONG_C(0x00000200)	/* ���M���J�n����B		*/
#define TCP_CEP_FLG_RESERVE_OUTPUT	ULONG_C(0x00000400)	/* ���M��\�񂷂�B		*/
#define TCP_CEP_FLG_DYNAMIC		ULONG_C(0x00001000)	/* ���I�����E�폜�\�ʐM�[�_�B	*/
#define TCP_CEP_FLG_VALID		ULONG_C(0x00002000)	/* �����ς݂ŗL���ȒʐM�[�_�B	*/
#define TCP_CEP_FLG_CLOSE_AFTER_OUTPUT	ULONG_C(0x00004000)	/* ���M������R�l�N�V���������B*/
#define TCP_CEP_FLG_RESTORE_NEXT_OUTPUT	ULONG_C(0x00008000)	/* ���M������Asnd_nxt �����ɖ߂��B*/



/*
 *  API �@�\�E���ۃR�[�h
 */

/* TCP �֌W */

#define TFN_TCP_CRE_REP		(-0x201)
#define TFN_TCP_DEL_REP		(-0x202)
#define TFN_TCP_CRE_CEP		(-0x203)
#define TFN_TCP_DEL_CEP		(-0x204)
#define TFN_TCP_ACP_CEP		(-0x205)
#define TFN_TCP_CON_CEP		(-0x206)
#define TFN_TCP_SHT_CEP		(-0x207)
#define TFN_TCP_CLS_CEP		(-0x208)
#define TFN_TCP_SND_DAT		(-0x209)
#define TFN_TCP_RCV_DAT		(-0x20a)
#define TFN_TCP_GET_BUF		(-0x20b)
#define TFN_TCP_SND_BUF		(-0x20c)
#define TFN_TCP_RCV_BUF		(-0x20d)
#define TFN_TCP_REL_BUF		(-0x20e)
#define TFN_TCP_SND_OOB		(-0x20f)
#define TFN_TCP_RCV_OOB		(-0x210)
#define TFN_TCP_CAN_CEP		(-0x211)
#define TFN_TCP_SET_OPT		(-0x212)
#define TFN_TCP_GET_OPT		(-0x213)
#define TFN_TCP_ALL		(0)

#define TEV_TCP_RCV_OOB		(-0x201)


/*
 *  �ʐM�[�_�C�x���g�t���O
 */

#define TCP_CEP_EVT_ESTABLISHED		ULONG_C(0x00000001)	/* �R�l�N�V�����m��		*/
#define TCP_CEP_EVT_CLOSED		ULONG_C(0x00000002)	/* ���g�p���			*/
#define TCP_CEP_EVT_SWBUF_READY		ULONG_C(0x00000004)	/* ���M�E�B���h�o�b�t�@��	*/
#define TCP_CEP_EVT_RWBUF_READY		ULONG_C(0x00000008)	/* ���M�E�B���h�o�b�t�@�f�[�^����	*/
#define TCP_CEP_EVT_ALL			ULONG_C(0xffffffff)	/* �S�C�x���g			*/



/* ����M�E�B���h�o�b�t�@�̏ȃR�s�[�@�\ */
#define TCP_CEP_FLG_WBCS_NBUF_REQ	ULONG_C(0x00080000)	/* �l�b�g���[�N�o�b�t�@�����ėv��	*/
#define TCP_CEP_FLG_WBCS_MASK		ULONG_C(0x00070000)	/* �}�X�N			*/
#define TCP_CEP_FLG_WBCS_FREE		ULONG_C(0x00000000)	/* ���M�E�B���h�o�b�t�@���g�p	*/
#define TCP_CEP_FLG_WBCS_WOPEN_PEND	ULONG_C(0x00010000)	/* ����̎�M�E�B���h�̊J���҂�	*/
#define TCP_CEP_FLG_WBCS_NBUF_PEND	ULONG_C(0x00020000)	/* �l�b�g���[�N�o�b�t�@�\��҂�	*/
#define TCP_CEP_FLG_WBCS_NBUF_RSVD	ULONG_C(0x00030000)	/* �l�b�g���[�N�o�b�t�@�\��ς�	*/
#define TCP_CEP_FLG_WBCS_NBUF_READY	ULONG_C(0x00040000)	/* �l�b�g���[�N�o�b�t�@�����čς�	*/
#define TCP_CEP_FLG_WBCS_SEND_READY	ULONG_C(0x00050000)	/* ���M�\			*/
#define TCP_CEP_FLG_WBCS_SENT		ULONG_C(0x00060000)	/* ���M�ς݂ŁAACK�҂�		*/
#define TCP_CEP_FLG_WBCS_ACKED		ULONG_C(0x00070000)	/* ���M�ς݂ŁAACK����		*/



/*
 *  �����ē]�����J�n����đ� ACK ���̂������l
 */

#define MAX_TCP_REXMT_THRESH	3



/*
 *  �߂�l
 *
 *      RET_OK		����
 *	RET_DROP	�G���[�A�Z�O�����g��j������B
 *	RET_RST_DROP	�G���[�ARST �𑗐M���A�Z�O�����g��j������B
 */

#define RET_OK		(0)
#define RET_NEED_OUTPUT	(1)
#define RET_RETURN	(2)
#define RET_DROP	(-1)
#define RET_RST_DROP	(-2)



/*
 *  SEQ �� ACK �ԍ��́A32 �r�b�g�����t�����Ŕ�r����B
 */

#define SEQ_LT(a,b)		((int32_t)((a)-(b)) <  0)
#define SEQ_LE(a,b)		((int32_t)((a)-(b)) <= 0)
#define SEQ_GT(a,b)		((int32_t)((a)-(b)) >  0)
#define SEQ_GE(a,b)		((int32_t)((a)-(b)) >= 0)


/*
 *  srtt:   ���������ꂽ RTT
 *  rttvar: ���������ꂽ���U
 *  rtt:    ���肳�ꂽ��������
 *
 *  ���������ꂽ RTT (srtt) �ƕ��������ꂽ���U (rttvar) ��
 *  �����^�Ōv�Z���邽�߂ɁA���V�t�g���ăX�P�[������B
 *  srtt �� 2 �i�����_�ȉ� 3 �r�b�g�A
 *  rttvar �� 2 �i�����_�ȉ� 2 �r�b�g��ێ�����B
 */

#define TCP_DELTA_SHIFT		2
			/* ���� = rtt/8 + srtt*7/8 �̌v�Z�̂��߂̃V�t�g�l	*/
#define TCP_SRTT_SHIFT		(TCP_DELTA_SHIFT + 3)
					/* srtt �̃V�t�g�l�A3(+2)�r�b�g	*/
#define TCP_RTTVAR_SHIFT	(TCP_DELTA_SHIFT + 2)
					/* rttvar �̃V�t�g�l�A2(+2)�r�b�g	*/
#define TCP_SRTT_SCALE		(1<<TCP_SRTT_SHIFT)
#define TCP_RTTVAR_SCALE	(1<<TCP_RTTVAR_SHIFT)


/*
 *  TCP �I�v�V�����̒�`
 */

/* �I�v�V�����̌^ */

#define TCP_OPT_EOL		UINT_C(0)	/* �ŏI				*/
#define TCP_OPT_NOP		UINT_C(1)	/* �������Ȃ�			*/
#define TCP_OPT_MAXSEG		UINT_C(2)	/* �ő�Z�O�����g��		*/
#define TCP_OPT_WINDOW		UINT_C(3)	/* �E�B���h�X�P�[�����O		*/
#define TCP_OPT_SACK_PERM	UINT_C(4)	/* �I�� ACK ����		*/
#define TCP_OPT_SACK		UINT_C(5)	/* �I�� ACK			*/
#define TCP_OPT_TIMESTAMP	UINT_C(8)	/* �^�C���X�^���v		*/
#define TCP_OPT_CC		UINT_C(11)	/* �ڑ��J�E���g			*/
#define TCP_OPT_CCNEW		UINT_C(12)	/* �ڑ��J�E���g			*/
#define TCP_OPT_CCECHO		UINT_C(13)	/* �ڑ��J�E���g			*/

/* �I�v�V�����̒��� */

#define TCP_OPT_LEN_MAXSEG	4		/* �ő�Z�O�����g��		*/
#define TCP_OPT_LEN_WINDOW	3		/* �E�B���h�X�P�[�����O		*/
#define TCP_OPT_LEN_SACK_PERM	4		/* �I�� ACK ����		*/
#define TCP_OPT_LEN_SACK	5		/* �I�� ACK			*/
#define TCP_OPT_LEN_TIMESTAMP	10		/* �^�C���X�^���v		*/
#define TCP_OPT_LEN_CC		6		/* �ڑ��J�E���g			*/
#define TCP_OPT_LEN_CCNEW	6		/* �ڑ��J�E���g			*/
#define TCP_OPT_LEN_CCECHO	6		/* �ڑ��J�E���g			*/

/*
 *  TCP �ő�Z�O�����g�T�C�Y
 */

/*
 *  IPv4 �� TCP �ő�Z�O�����g�T�C�Y
 *  IP4_MSS �� 576 �ŁA�W���� IPv4 �w�b�_�� (20) ��
 *  TCP �w�b�_�� (20) ���������l 536 �ł��邪�A512 ��W���Ƃ���B
 */

#define TCP_MSS			UINT_C(512)

/*
 *  IPv6 �� TCP �ő�Z�O�����g�T�C�Y
 *  IPV6_MMTU �� 1280 �ŁA�W���� IPv6 �w�b�_�� (40) ��
 *  TCP �w�b�_�� (20) ���������l 1220 �ł��邪�A1024 ��W���Ƃ���B
 */

#define TCP6_MSS		UINT_C(1024)

/*
 *  TCP �ŏ��Z�O�����g�T�C�Y
 *
 *  256�i�ŏ������N MTU�j- 40 = 216
 */

#define TCP_MINMSS		UINT_C(216)


/*
 *  TCP �ő�E�B���h�E�T�C�Y
 */

#define MAX_TCP_WIN_SIZE	UINT_C(65535)


/*
 *  �֐��V�~�����[�V�����}�N��
 */

#define TCP_FSM_HAVE_RCVD_SYN(s)	((s) >= TCP_FSM_SYN_RECVD)
#define TCP_FSM_HAVE_ESTABLISHED(s)	((s) >= TCP_FSM_ESTABLISHED)
#define TCP_FSM_HAVE_RCVD_FIN(s)	((s) >= TCP_FSM_TIME_WAIT)

#define TCP_FSM_CAN_SEND_MORE(s)	((s) == TCP_FSM_ESTABLISHED || \
					 (s) == TCP_FSM_CLOSE_WAIT)
#define TCP_FSM_CAN_RECV_MORE(s)	((s) == TCP_FSM_ESTABLISHED || \
					 (s) == TCP_FSM_FIN_WAIT_1  || \
					 (s) == TCP_FSM_FIN_WAIT_2)



/*
 *  TCP/IP �̃^�C�}�̒�`
 */

#define TCP_SLOW_TMO		(ULONG_C(500)/NET_TIMER_CYCLE)	/* 500 [ms]	*/
#define TCP_FAST_TMO		(ULONG_C(200)/NET_TIMER_CYCLE)	/* 200 [ms]	*/

#define TCP_SLOW_HZ		(ULONG_C(1000)/TCP_SLOW_TMO/NET_TIMER_CYCLE)	/* Hz	*/

/* TCP �^�C�}�l */

#define TCP_TVAL_MSL		(TCP_SLOW_HZ * 30)
					/* �ő�Z�O�����g��������	*/

#define TCP_TVAL_SRTT_BASE	0	/* ���炩�ȉ������Ԃ̊�l*/

#define TCP_TVAL_RTO_BASE	(TCP_SLOW_HZ * 3)
		/* ��񂪓����Ȃ��ꍇ�̍đ��^�C���A�E�g�̊�l	*/

#define TCP_TVAL_MIN_PERSIST	(TCP_SLOW_HZ * 5)
				/* �����^�C���A�E�g�̍ŏ��l	*/
#define TCP_TVAL_MAX_PERSIST	(TCP_SLOW_HZ * 60)
				/* �����^�C���A�E�g�̍ő�l	*/

#define TCP_TVAL_KEEP_INIT	(TCP_SLOW_HZ * 75)
					/* �ۗ��^�C�}�̏����l	*/
#define TCP_TVAL_KEEP_IDLE	(TCP_SLOW_HZ * 2 * 60 * 60)
					/* �ۗ��^�C�}�N���܂ł̕W���l*/
#define TCP_TVAL_KEEP_INTERVAL	(TCP_SLOW_HZ * 75)
					/* �ۗ��^�C�}�C���^�[�o���̕W���l*/
#define TCP_TVAL_KEEP_COUNT	8	/* �ۗ��^�C���A�E�g�̍ő�l*/

#define TCP_TVAL_MIN		(TCP_SLOW_HZ * 3)
					/* ���Ԃ̍ŏ��P��	*/
#define TCP_TVAL_MAX_REXMT	(TCP_SLOW_HZ * 64)
					/* �ő�đ�����		*/


#define IS_TFN_TCP_RCV(t)	((t)==TFN_TCP_ACP_CEP||(t)==TFN_TCP_RCV_DAT||\
				 (t)==TFN_TCP_CLS_CEP||\
				 (t)==TFN_TCP_RCV_BUF||(t)==TFN_TCP_REL_BUF||\
				 (t)==TFN_TCP_RCV_OOB)

#define VALID_TCP_CEP	((VAR_flags&TCP_CEP_FLG_VALID)!=0)


#define VALID_TFN_TCP_CAN(t)	((t)==TFN_TCP_ACP_CEP||(t)==TFN_TCP_CON_CEP||\
				 (t)==TFN_TCP_CLS_CEP||\
				 (t)==TFN_TCP_SND_DAT||(t)==TFN_TCP_RCV_DAT||\
				 (t)==TFN_TCP_GET_BUF||(t)==TFN_TCP_RCV_BUF||\
				 (t)==TFN_TCP_SND_OOB||\
				 (t)==TFN_TCP_ALL)

/*
 *  �|�[�g�ԍ��̒�`
 */

#define TCP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP �W��	*/
#define UDP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP �W��	*/

#define TCP_PORT_LAST_WELL_KNOWN	UINT_C(1023)	/* Well Known �I���ԍ�	*/
#define TCP_PORT_FIRST_AUTO		UINT_C(1024)	/* �������蓖�ĊJ�n�ԍ�	*/
#define TCP_PORT_LAST_AUTO		UINT_C(4999)	/* �������蓖�ďI���ԍ�	*/
