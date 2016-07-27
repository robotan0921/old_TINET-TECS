typedef uint32_t T_IN4_ADDR;

#define MAKE_IPV4_ADDR(a,b,c,d)		((T_IN4_ADDR)(((uint32_t)(a)<<24)|((uint32_t)(b)<<16)|((uint32_t)(c)<<8)|(d)))

/*
 *  IP アドレスの定義
 */

#define IPV4_ADDRANY		ULONG_C(0x00000000)	/* ITRON TCP/IP 標準	*/

#define IPV4_ADDR_LOOPBACK	ULONG_C(0x7f000001)
#define IPV4_ADDR_BROADCAST	ULONG_C(0xffffffff)


/*
 *  IPv4 の定義、RFC791 参照
 */

#define IPV4_VERSION		4

/*
 *  インターネットシステムの定義、RFC790 参照
 */

/*
 *  プロトコル (RFC1700)
 */

#define IPPROTO_IP		UINT_C(0)	/* IP のダミー				*/
#define IPPROTO_HOPOPTS		UINT_C(0)	/* IPv6 中継点 (Hop-by-Hop) オプション	*/
#define IPPROTO_ICMP		UINT_C(1)	/* ICMP					*/
#define IPPROTO_TCP		UINT_C(6)	/* TCP					*/
#define IPPROTO_UDP		UINT_C(17)	/* UDP					*/
#define IPPROTO_IPV6		UINT_C(41)	/* IPv6					*/
#define IPPROTO_ROUTING		UINT_C(43)	/* 経路制御オプション			*/
#define IPPROTO_FRAGMENT	UINT_C(44)	/* 断片化オプション			*/
#define IPPROTO_RSVP		UINT_C(46)	/* RSVP					*/
#define IPPROTO_ESP		UINT_C(50)	/* IPv6 暗号化オプション		*/
#define IPPROTO_AH		UINT_C(51)	/* IPv6 認証オプション			*/
#define IPPROTO_ICMPV6		UINT_C(58)	/* ICMPv6				*/
#define IPPROTO_NONE		UINT_C(59)	/* IPv6 次ヘッダ無し			*/
#define IPPROTO_DSTOPTS		UINT_C(60)	/* IPv6 終点オプション			*/
#define IPPROTO_IPCOMP		UINT_C(108)	/* ペイロード圧縮			*/
#define IPPROTO_DONE		UINT_C(257)	/* IPv6 で上位プロトコル入力終了	*/


/*
 *  ルーティング表エントリ構造体
 */

typedef struct t_in4_rtentry {
	T_IN4_ADDR	target;		/* 目標ネットワークアドレス			*/
	T_IN4_ADDR	mask;		/* 目標ネットワークアドレスのサブネットマスク	*/
	T_IN4_ADDR	gateway;	/* ゲートウェイの IP アドレス			*/
	uint32_t	expire;		/* 有効時間が切れる時刻 [s]			*/
	uint8_t		flags;		/* フラグ					*/
	} T_IN4_RTENTRY;

/*
 *  ルーティングエントリ状態フラグ
 */

#define IN_RTF_DEFINED		UINT_C(0x01)	/* 定義済み			*/
#define IN_RTF_REDIRECT		UINT_C(0x10)	/* 向け直しにより自動設定された	*/



/*
 *  IPv4 ヘッダの定義
 */

typedef struct t_ip4_hdr {
	uint8_t		vhl;		/* version << 4 | header length >> 2	*/
					/* length は 4 octets 単位		*/
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
 *  IPv4 ヘッダ構造体メンバアクセスマクロ
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
 *  IPv4 ヘッダのフィールドの値の定義
 */

#define IP4_VHL_BORING	UINT_C(0x45)	/* オプションがない VHL 値	*/
#define IP4_RF		UINT_C(0x8000)	/* off: 予約			*/
#define IP4_DF		UINT_C(0x4000)	/* off: 分割禁止			*/
#define IP4_MF		UINT_C(0x2000)	/* off: 分割あり			*/
#define IP4_OFFMASK	UINT_C(0x1fff)	/* オフセット部のマスク値		*/

/*
 *  制限値
 */

#define IP4_MAXPACKET	UINT_C(65535)	/* 最大パケットサイズ		*/
#define IP4_MAXTTL	UINT_C(255)	/* TTL 最大値			*/
#define IP4_DEFTTL	UINT_C(64)	/* TTL 規定値 (RFC1340)		*/
#define IP4_FRAGTTL	UINT_C(60)	/* 分割されたデータグラムの生存時間（秒）*/
#define IP4_MSS		UINT_C(576)	/* 最大セグメントサイズの規定値	*/


/****************************************
  ARPに関する定義
******************************************/



typedef struct arp_entry {
    T_NET_BUF	*hold;		/* ARP の解決待ち出力フレーム	*/
    T_IN4_ADDR	ip_addr;	/* IP アドレス			*/
    uint16_t	expire;		/* 破棄までの時間、0 なら未使用	*/
    uint8_t	mac_addr[6];	/* MAC アドレス	*/
} T_ARP_ENTRY;


/* ARP ヘッダ */

typedef struct t_arp_hdr {
	uint16_t	hrd_addr;	/* 物理アドレスフォーマット	*/
	uint16_t	proto;		/* プロトコル			*/
	uint8_t		hdr_len;	/* 物理アドレス長		*/
	uint8_t		proto_len;	/* プロトコル長			*/
	uint16_t	opcode;		/* 命令コード			*/
	} T_ARP_HDR;


#define ARP_HDR_SIZE			(sizeof(T_ARP_HDR))
#define GET_ARP_HDR(nbuf)		((T_ARP_HDR*)((nbuf)->buf + ETHER_HDR_SIZE))


/* ARP 中身 */
typedef struct t_ether_arp_hdr {
	uint8_t		shost[6];	/* 送信ホストの物理アドレス	*/
	uint8_t		sproto[4];	/* 送信ホストの IP アドレス	*/
	uint8_t		thost[6];	/* 解決対象物理アドレス		*/
	uint8_t		tproto[4];	/* 解決対象 IP アドレス		*/
	} T_ETHER_ARP_HDR;

#define ETHER_ARP_HDR_SIZE		(sizeof(T_ETHER_ARP_HDR))

#define IF_ARP_ETHER_HDR_SIZE		(ETHER_HDR_SIZE + ARP_HDR_SIZE + ETHER_ARP_HDR_SIZE)

#define GET_IF_ARP_HDR_SIZE(nbuf)	(ETHER_HDR_SIZE + ARP_HDR_SIZE)
#define GET_ETHER_ARP_HDR(nbuf)		((T_ETHER_ARP_HDR*)((nbuf)->buf + GET_IF_ARP_HDR_SIZE(nbuf)))


/* hrd_addr、物理アドレスフォーマットの値 */

#define ARPHRD_ETHER	1	/* Ethernet	*/

/* opcode, 命令コードの値 */

#define ARPOP_REQUEST		UINT_C(1)	/* アドレス解決要求		*/
#define ARPOP_REPLY		UINT_C(2)	/* アドレス解決応答		*/
#define ARPOP_REV_REQUEST	UINT_C(3)	/* プロトコル・アドレス解決要求	*/
#define ARPOP_REV_REPLY		UINT_C(4)	/* プロトコル・アドレス解決要求	*/
#define ARPOP_INV_REQUEST	UINT_C(8)	/* 終端識別要求			*/
#define ARPOP_INV_REPLY		UINT_C(9)	/* 終端識別要求			*/


#define ARP_CACHE_KEEP		(20*60*10)	/* ARP キャッシュのタイムアウト	*/

#define TMO_ARP_GET_NET_BUF		ULONG_C(1000)	/* [ms]、ARP のネットワークバッファ獲得タイムアウト	*/
#define TMO_ARP_OUTPUT			ULONG_C(1000)	/* [ms]、アドレス解決要求出力タイムアウト		*/



/****************************************
  ICMP4に関する定義
******************************************/
/*
 *  ICMP ヘッダの定義、RFC 792
 */

typedef struct t_icmp_hdr {
	uint8_t		type;		/* メッセージの型	*/
	uint8_t		code;		/* サブ型		*/
	uint16_t	sum;		/* チェックサム		*/
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

#define TMO_ICMP_OUTPUT			ULONG_C(1000)	/* [ms]、ICMP 出力タイムアウト				*/



/*
 *  メッセージの型
 */

#define ICMP4_ECHO_REPLY	UINT_C(0)	/* エコー応答		*/
#define ICMP4_UNREACH		UINT_C(3)	/* エラー		*/
#define ICMP4_SOURCE_QUENCH	UINT_C(4)	/* 発信制限		*/
#define ICMP4_REDIRECT		UINT_C(5)	/* 方向変更		*/
#define ICMP4_ECHO_REQUEST	UINT_C(8)	/* エコー要求		*/
#define ICMP4_TIME_EXCEEDED	UINT_C(11)	/* 発信制限		*/
#define ICMP4_PARAMETER		UINT_C(12)	/* パラメータ異常	*/
#define ICMP4_TIME_REQUEST	UINT_C(13)	/* タイムスタンプ要求	*/
#define ICMP4_TIME_REPLY	UINT_C(14)	/* タイムスタンプ応答	*/
#define ICMP4_MASK_REQUEST	UINT_C(17)	/* アドレスマスク要求	*/
#define ICMP4_MASK_REPLY	UINT_C(18)	/* アドレスマスク応答	*/

/*
 *  サブ型
 */

/* ICMP4_UNREACH (3)	*/

#define ICMP4_UNREACH_NET		UINT_C(0)	/* ネットワーク		*/
#define ICMP4_UNREACH_HOST		UINT_C(1)	/* ホスト		*/
#define ICMP4_UNREACH_PROTOCOL		UINT_C(2)	/* プロトコル		*/
#define ICMP4_UNREACH_PORT		UINT_C(3)	/* ポート		*/
#define ICMP4_UNREACH_FLAG		UINT_C(4)	/* 分割			*/
#define ICMP4_UNREACH_SRC_FAIL		UINT_C(5)	/* ソース経路		*/
#define ICMP4_UNREACH_NET_UNKNOWN	UINT_C(6)	/* ネットワーク不明	*/
#define ICMP4_UNREACH_HOST_UNKNOWN	UINT_C(7)	/* ホスト不明		*/
#define ICMP4_UNREACH_ISOLATED		UINT_C(8)	/* 分離			*/
#define ICMP4_UNREACH_NET_PROHIB	UINT_C(9)	/* 			*/
#define ICMP4_UNREACH_HOST_PROHIB	UINT_C(10)	/* 			*/
#define ICMP4_UNREACH_TOS_NET		UINT_C(11)	/* ネットワークへの不正TOS*/
#define ICMP4_UNREACH_TOS_HOST		UINT_C(12)	/* ホストへの不正TOS	*/
#define ICMP4_UNREACH_FILTER_PROHIB	UINT_C(13)	/* 			*/
#define ICMP4_UNREACH_HOST_PRECEDENCE	UINT_C(14)	/* 			*/
#define ICMP4_UNREACH_PRECEDENCE_CUTOFF	UINT_C(15)	/* 			*/

/* ICMP4_REDIRECT (5)	*/

#define ICMP4_REDIRECT_NET		UINT_C(0)	/* ネットワーク		*/
#define ICMP4_REDIRECT_HOST		UINT_C(1)	/* ホスト		*/
#define ICMP4_REDIRECT_PORT_AND_NET	UINT_C(2)	/* ポート番号とネット	*/
#define ICMP4_REDIRECT_PORT_AND_HOST	UINT_C(3)	/* ポート番号とホスト	*/


/*
 *  独自のエラーコード
 */

#define EV_NOPND		(-97)		/* ペンディングしていない */

/*
 *  ネットワークエラーコード
 */

#define EV_MSIZE		(-98)		/* データグラム長超過	*/
#define EV_NURCH		(-99)		/* ネットワーク到達不能	*/
#define EV_HDOWN		(-100)		/* ホストダウン		*/
#define EV_HURCH		(-101)		/* ホスト到達不能	*/
#define EV_CNNRF		(-102)		/* 接続不能		*/
#define EV_CNRST		(-103)		/* 接続リセット		*/
#define EV_REXMTMO		(-104)		/* 再送タイムアウト	*/

/*
 *  IP アドレスの定義
 */
#define IPV4_CLASS_D(i)		(((i) & ULONG_C(0xf0000000)) == ULONG_C(0xe0000000))

#define IN4_IS_ADDR_MULTICAST(i)	IPV4_CLASS_D(i)

#define IN4_IS_NET_ADDR_MULTICAST(a)	IN4_IS_ADDR_MULTICAST(ntohl(*(a)))

#define IN4_COPY_TO_NET(d,s)		(*(d)=htonl(*(s)))
