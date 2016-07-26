
/*
 *  ITRON TCP/IPv4 アドレス/ポート番号の定義
 */

typedef struct t_ipv4ep {
	uint32_t	ipaddr;		/* IPv4 アドレス	*/
	uint16_t	portno;		/* ポート番号		*/
} T_IPV4EP;



/* TCP タイマ変数 */

#define NUM_TCP_TIMERS		4	/* TCP のタイマ数	*/

#define TCP_TIM_REXMT		0	/* 再送タイマ		*/
#define TCP_TIM_PERSIST		1	/* 持続タイマ		*/
#define TCP_TIM_KEEP		2	/* 保留 (keep alive) タイマ*/
#define TCP_TIM_2MSL		3	/* 2MSL タイマ		*/



/*
 *  追加 API 機能・事象コード
 */

#define TMO_TCP_OUTPUT			ULONG_C(1000)	/* [ms]、TCP 出力タイムアウト				*/


/* TCP 関係 */

#define TFN_TCP_UNDEF		(0)

#define IN4_COPY_TO_HOST(d,s)		(*(d)=ntohl(*(s)))


/*
 *  その他の定数
 */

#define TCP_MAX_REXMT_SHIFT	12	/* 最大再送回数		*/


#define TCP_TOTAL_BACK_OFF	511	/* バックオフ時間の合計 */

/*
 *  TCP ヘッダ構造体メンバアクセスマクロ
 */

#define TCP_MAKE_DATA_OFF(o)	((uint8_t)(((uint8_t)(o) << 2) & 0xf0))
#define TCP_DATA_OFF(o)		(((uint8_t)(o) & UINT_C(0xf0)) >> 2)
#define TCP_HDR_LEN(o)		(TCP_DATA_OFF(o))


/*
 *  TCP ヘッダ、RFC 793 参照
 */

typedef struct t_tcp_hdr {
	uint16_t	sport;		/* 送信元ポート番号			*/
	uint16_t	dport;		/* 宛先ポート番号			*/

	uint32_t	seq;		/* SEQ 番号				*/

	uint32_t	ack;		/* ACK 番号				*/

	uint8_t		doff;		/* データオフセット(上位4ビット)	*/
	uint8_t		flags;		/* フラグ(下位6ビット)			*/
	uint16_t	win;		/* ウィンドサイズ			*/

	uint16_t	sum;		/* チェックサム				*/
	uint16_t	urp;		/* 緊急ポインタ				*/
	} T_TCP_HDR;

#define TCP_HDR_SIZE			(sizeof(T_TCP_HDR))

#define GET_TCP_HDR(nbuf,thoff)		((T_TCP_HDR*)((uint8_t*)((nbuf)->buf) + thoff))
#define GET_TCP_HDR_SIZE2(nbuf,thoff)	(TCP_HDR_LEN(GET_TCP_HDR(nbuf,thoff)->doff))
#define GET_TCP_SDU(nbuf,thoff)		((uint8_t*)((nbuf)->buf) + thoff + GET_TCP_HDR_SIZE2(nbuf,thoff))


/*
 *  受信再構成キューでの TCP ヘッダ
 */

typedef struct t_tcp_q_hdr {
	uint16_t	sport;		/* 送信元ポート番号			*/
	uint16_t	dport;		/* 宛先ポート番号			*/

	uint32_t	seq;		/* SEQ 番号				*/

	T_NET_BUF 	*next;		/* 次のセグメント、元は ACK 番号(ack)	*/

	uint8_t		doff;		/* データオフセット(上位4ビット)	*/
	uint8_t		flags;		/* フラグ(下位6ビット)			*/
	uint16_t	soff;		/* SDU オフセット、元はウィンドサイズ(win)	*/

	uint16_t	slen;		/* SDU 長、元はチェックサム(sum)	*/
	uint16_t	urp;		/* 緊急ポインタ（SDU 長補正）		*/
	} T_TCP_Q_HDR;

/*
 *  TCP の再構成キューにおける IPv4 ヘッダの定義
 */

typedef struct t_tcp_ip4_q_hdr {
	uint8_t		vhl;		/* version << 4 | header length >> 2	*/
					/* length は 4 octets 単位		*/
	uint8_t		type;		/* type of services			*/
	uint16_t	len;		/* total length				*/

	uint16_t	id;		/* identification			*/
	uint16_t	flg_off;	/* fragment flag & offset		*/

	uint8_t		ttl;		/* time to live				*/
	uint8_t		proto;		/* protocol				*/
	uint16_t	thoff;		/* TCP ヘッダのオフセット		*/

	T_IN4_ADDR	src;		/* source address			*/
	T_IN4_ADDR	dst;		/* destination address			*/
	} T_TCP_IP4_Q_HDR;


#define GET_TCP_Q_HDR(nbuf,thoff)	((T_TCP_Q_HDR*)((uint8_t*)((nbuf)->buf) + thoff))



/* TCP タイマ値の型 */

typedef int16_t T_TCP_TIME;

/*
 *  TCP 通信端点
 */

typedef uint32_t T_TCP_SEQ;
typedef uint16_t T_TCP_SEG;
typedef uint16_t T_TCP_WND;

typedef struct t_tcp_cep {
	ID		snd_tskid;	/* 送信タスク識別子		*/
	ID		rcv_tskid;	/* 受信タスク識別子		*/
	
	uint8_t		*sbuf_rptr;	/* 送信用読み出しポインタ	*/
	uint8_t		*sbuf_wptr;	/* 送信用書き込みポインタ	*/
	uint8_t		*rbuf_rptr;	/* 受信用読み出しポインタ	*/
	uint8_t		*rbuf_wptr;	/* 受信用書き込みポインタ	*/
	T_TCP_SEQ	snd_ssthresh;	/* 輻輳ウィンドサイズ(snd_cwnd)	*/
					/* のしきい値			*/
	T_TCP_TIME	rxtcur;		/* 現在の再送タイムアウト	*/
	T_TCP_TIME	srtt;		/* 平滑化された RTT		*/
	T_TCP_TIME	rttvar;		/* 平滑化された分散		*/
	T_TCP_WND	snd_cwnd;	/* 輻輳ウィンドサイズ		*/

	/*
	 *  相手の最大受信セグメントサイズ	
	 *
	 *    オリジナルでは、一般のセグメントの最大サイズ (t_maxseg) と、
	 *    オプション付きのセグメントの最大サイズ (t_maxopd) が別に
	 *    なっている。これは、現在のインターネットでは、オプション付きの
	 *    セグメントのほうが多いからと説明されているためである。
	 *    本実装では、最大セグメントサイズオプション以外のオプションは
	 *    実装しないので、t_maxseg の使用する。
	 */
	T_TCP_SEG	maxseg;

	int16_t		snd_tfn;	/* 送信動作中の API 機能コード	*/
	int16_t		rcv_tfn;	/* 受信動作中の API 機能コード	*/


	/*
	 *  これ以降のメンバーは tcp_init_cep() 関数でゼロクリアーされる。
	 */

	T_TCP_TIME	timer[NUM_TCP_TIMERS];	/* TCP のタイマ		*/
	//T_TCP4_REP	*rep;		/* 受付口			*/
	T_NET_BUF	*reassq;	/* 受信再構成キュー		*/

	T_TCP_SEQ	snd_una;	/* 未確認の最小送信 SEQ つまり	*/
					/* 確認された最大送信 SEQ	*/
	T_TCP_SEQ	snd_max;	/* 送信した最大 SEQ		*/
	T_TCP_SEQ	snd_nxt;	/* 次に送信する SEQ		*/
	T_TCP_SEQ	snd_old_nxt;	/* 元の snd_nxt			*/
	T_TCP_SEQ	snd_wl1;	/* 前回ウィンドを更新した SEQ	*/
	T_TCP_SEQ	snd_wl2;	/* 前回ウィンドを更新した ACK	*/
	T_TCP_SEQ	iss;		/* 自分の SEQ の初期値		*/
	T_TCP_SEQ	irs;		/* 相手の SEQ の初期値		*/
	T_TCP_SEQ	rcv_nxt;	/* 受信を期待している最小の SEQ	*/
	T_TCP_SEQ	rcv_adv;	/* 受信を期待している最大の SEQ	*/
	T_TCP_SEQ	rcv_wnd;	/* 受信可能なウィンドサイズ	*/
	T_TCP_SEQ	rtseq;		/* 時間計測を始めた SEQ		*/
	T_TCP_SEQ	last_ack_sent;	/* 最後に送信した ACK		*/
	T_TCP_TIME	idle;		/* アイドル時間			*/
	ER		error;		/* 非同期に発生したエラー	*/
	ER		net_error;	/* ネットワークのエラー状態	*/
	T_TCP_WND	snd_wnd;	/* 相手の受信可能ウィンドサイズ	*/
	T_TCP_WND	max_sndwnd;	/* 今までの最大送信ウィンドサイズ	*/
	T_TCP_TIME	rtt;		/* 往復時間				*/
	uint16_t	swbuf_count;	/* 送信ウィンドバッファの使用中サイズ	*/
	uint16_t	rwbuf_count;	/* 受信ウィンドバッファの使用中サイズ	*/
	uint16_t	rcv_buf_len;	/* tcp_rcv_buf の割当て長	*/
	uint16_t	get_buf_len;	/* tcp_rcv_buf の割当て長	*/
	uint8_t		rxtshift;	/* 再送信回数の log(2)		*/
	uint8_t		fsm_state;	/* FSM 状態			*/
	uint8_t		dupacks;	/* 再送 ACK 数			*/
}T_TCP_CEP;

/* 
 *  セグメントの順番を入れ替えるときに新たにネットワークバッファを割当てて、
 *  データをコピーするサイズのしきい値
 */
#define MAX_TCP_REALLOC_SIZE	1024

#define TMO_TCP_GET_NET_BUF		ULONG_C(1000)	/* [ms]、TCP のネットワークバッファ獲得タイムアウト	*/


/*
 *  TCP ヘッダのフラグフィールドの値の定義
 */

#define TCP_FLG_FIN		UINT_C(0x01)	/* FIN:	最終			*/
#define TCP_FLG_SYN		UINT_C(0x02)	/* SYN:	同期			*/
#define TCP_FLG_RST		UINT_C(0x04)	/* RST:	コネクションのリセット	*/
#define TCP_FLG_PUSH		UINT_C(0x08)	/* PUSH:プッシュ機能		*/
#define TCP_FLG_ACK		UINT_C(0x10)	/* ACK:	肯定応答		*/
#define TCP_FLG_URG		UINT_C(0x20)	/* URG:	緊急情報		*/


/*
 *  TCP FSM 状態の定義、RFC 793 参照
 */

#define TCP_FSM_CLOSED		0	/* クローズ				*/
#define TCP_FSM_LISTEN		1	/* 受動オープン				*/
#define TCP_FSM_SYN_SENT	2	/* 能動オープン、SYN 送信済み		*/
#define TCP_FSM_SYN_RECVD	3	/* 受動オープン、SYN 受信済み		*/
#define TCP_FSM_ESTABLISHED	4	/* コネクション開設完了			*/
#define TCP_FSM_CLOSE_WAIT	5	/* 相手から FIN 受信、APP の終了待ち	*/
#define TCP_FSM_FIN_WAIT_1	6	/* APP が終了、FIN 送信済み、ACK 待ち	*/
#define TCP_FSM_CLOSING		7	/* 同時クローズ、FIN 交換済み、ACK 待ち	*/
#define TCP_FSM_LAST_ACK	8	/* APP が終了、ACK 待ち			*/
#define TCP_FSM_FIN_WAIT_2	9	/* 相手からの FIN 待ち			*/
#define TCP_FSM_TIME_WAIT	10	/* 相手からの FIN 受信済み、時間待ち	*/





/*
 *  TCP 通信端点の状態フラグ
 */

#define TCP_CEP_FLG_ACK_NOW		ULONG_C(0x00000001)	/* 直ちに相手に ACK を送る。	*/
#define TCP_CEP_FLG_DEL_ACK		ULONG_C(0x00000002)	/* ACK を遅延する。		*/
#define TCP_CEP_FLG_SENT_FIN		ULONG_C(0x00000004)	/* FIN を送ってある。		*/
#define TCP_CEP_FLG_NEED_SYN		ULONG_C(0x00000008)	/* SYN を送信する。		*/
#define TCP_CEP_FLG_NEED_FIN		ULONG_C(0x00000010)	/* FIN を送信する。		*/
#define TCP_CEP_FLG_FORCE		ULONG_C(0x00000020)	/* 強制送信。			*/
#define TCP_CEP_FLG_NO_PUSH		ULONG_C(0x00000040)	/* push しない。		*/
#define TCP_CEP_FLG_NO_DELAY		ULONG_C(0x00000080)	/* 遅延しない。			*/
#define TCP_CEP_FLG_FORCE_CLEAR		ULONG_C(0x00000100)	/* 強制送信した後フラグをクリアーする。*/
#define TCP_CEP_FLG_POST_OUTPUT		ULONG_C(0x00000200)	/* 送信を開始する。		*/
#define TCP_CEP_FLG_RESERVE_OUTPUT	ULONG_C(0x00000400)	/* 送信を予約する。		*/
#define TCP_CEP_FLG_DYNAMIC		ULONG_C(0x00001000)	/* 動的生成・削除可能通信端点。	*/
#define TCP_CEP_FLG_VALID		ULONG_C(0x00002000)	/* 生成済みで有効な通信端点。	*/
#define TCP_CEP_FLG_CLOSE_AFTER_OUTPUT	ULONG_C(0x00004000)	/* 送信した後コネクションを閉じる。*/
#define TCP_CEP_FLG_RESTORE_NEXT_OUTPUT	ULONG_C(0x00008000)	/* 送信した後、snd_nxt を元に戻す。*/



/*
 *  API 機能・事象コード
 */

/* TCP 関係 */

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
 *  通信端点イベントフラグ
 */

#define TCP_CEP_EVT_ESTABLISHED		ULONG_C(0x00000001)	/* コネクション確立		*/
#define TCP_CEP_EVT_CLOSED		ULONG_C(0x00000002)	/* 未使用状態			*/
#define TCP_CEP_EVT_SWBUF_READY		ULONG_C(0x00000004)	/* 送信ウィンドバッファ空き	*/
#define TCP_CEP_EVT_RWBUF_READY		ULONG_C(0x00000008)	/* 送信ウィンドバッファデータあり	*/
#define TCP_CEP_EVT_ALL			ULONG_C(0xffffffff)	/* 全イベント			*/



/* 送受信ウィンドバッファの省コピー機能 */
#define TCP_CEP_FLG_WBCS_NBUF_REQ	ULONG_C(0x00080000)	/* ネットワークバッファ割当て要求	*/
#define TCP_CEP_FLG_WBCS_MASK		ULONG_C(0x00070000)	/* マスク			*/
#define TCP_CEP_FLG_WBCS_FREE		ULONG_C(0x00000000)	/* 送信ウィンドバッファ未使用	*/
#define TCP_CEP_FLG_WBCS_WOPEN_PEND	ULONG_C(0x00010000)	/* 相手の受信ウィンドの開き待ち	*/
#define TCP_CEP_FLG_WBCS_NBUF_PEND	ULONG_C(0x00020000)	/* ネットワークバッファ予約待ち	*/
#define TCP_CEP_FLG_WBCS_NBUF_RSVD	ULONG_C(0x00030000)	/* ネットワークバッファ予約済み	*/
#define TCP_CEP_FLG_WBCS_NBUF_READY	ULONG_C(0x00040000)	/* ネットワークバッファ割当て済み	*/
#define TCP_CEP_FLG_WBCS_SEND_READY	ULONG_C(0x00050000)	/* 送信可能			*/
#define TCP_CEP_FLG_WBCS_SENT		ULONG_C(0x00060000)	/* 送信済みで、ACK待ち		*/
#define TCP_CEP_FLG_WBCS_ACKED		ULONG_C(0x00070000)	/* 送信済みで、ACK完了		*/



/*
 *  高速再転送を開始する再送 ACK 数のしきい値
 */

#define MAX_TCP_REXMT_THRESH	3



/*
 *  戻り値
 *
 *      RET_OK		正常
 *	RET_DROP	エラー、セグメントを破棄する。
 *	RET_RST_DROP	エラー、RST を送信し、セグメントを破棄する。
 */

#define RET_OK		(0)
#define RET_NEED_OUTPUT	(1)
#define RET_RETURN	(2)
#define RET_DROP	(-1)
#define RET_RST_DROP	(-2)



/*
 *  SEQ と ACK 番号は、32 ビット符号付整数で比較する。
 */

#define SEQ_LT(a,b)		((int32_t)((a)-(b)) <  0)
#define SEQ_LE(a,b)		((int32_t)((a)-(b)) <= 0)
#define SEQ_GT(a,b)		((int32_t)((a)-(b)) >  0)
#define SEQ_GE(a,b)		((int32_t)((a)-(b)) >= 0)


/*
 *  srtt:   平滑化された RTT
 *  rttvar: 平滑化された分散
 *  rtt:    測定された往復時間
 *
 *  平滑化された RTT (srtt) と平滑化された分散 (rttvar) を
 *  整数型で計算するために、左シフトしてスケールする。
 *  srtt は 2 進小数点以下 3 ビット、
 *  rttvar は 2 進小数点以下 2 ビットを保持する。
 */

#define TCP_DELTA_SHIFT		2
			/* 差分 = rtt/8 + srtt*7/8 の計算のためのシフト値	*/
#define TCP_SRTT_SHIFT		(TCP_DELTA_SHIFT + 3)
					/* srtt のシフト値、3(+2)ビット	*/
#define TCP_RTTVAR_SHIFT	(TCP_DELTA_SHIFT + 2)
					/* rttvar のシフト値、2(+2)ビット	*/
#define TCP_SRTT_SCALE		(1<<TCP_SRTT_SHIFT)
#define TCP_RTTVAR_SCALE	(1<<TCP_RTTVAR_SHIFT)


/*
 *  TCP オプションの定義
 */

/* オプションの型 */

#define TCP_OPT_EOL		UINT_C(0)	/* 最終				*/
#define TCP_OPT_NOP		UINT_C(1)	/* 何もしない			*/
#define TCP_OPT_MAXSEG		UINT_C(2)	/* 最大セグメント長		*/
#define TCP_OPT_WINDOW		UINT_C(3)	/* ウィンドスケーリング		*/
#define TCP_OPT_SACK_PERM	UINT_C(4)	/* 選択 ACK 許可		*/
#define TCP_OPT_SACK		UINT_C(5)	/* 選択 ACK			*/
#define TCP_OPT_TIMESTAMP	UINT_C(8)	/* タイムスタンプ		*/
#define TCP_OPT_CC		UINT_C(11)	/* 接続カウント			*/
#define TCP_OPT_CCNEW		UINT_C(12)	/* 接続カウント			*/
#define TCP_OPT_CCECHO		UINT_C(13)	/* 接続カウント			*/

/* オプションの長さ */

#define TCP_OPT_LEN_MAXSEG	4		/* 最大セグメント長		*/
#define TCP_OPT_LEN_WINDOW	3		/* ウィンドスケーリング		*/
#define TCP_OPT_LEN_SACK_PERM	4		/* 選択 ACK 許可		*/
#define TCP_OPT_LEN_SACK	5		/* 選択 ACK			*/
#define TCP_OPT_LEN_TIMESTAMP	10		/* タイムスタンプ		*/
#define TCP_OPT_LEN_CC		6		/* 接続カウント			*/
#define TCP_OPT_LEN_CCNEW	6		/* 接続カウント			*/
#define TCP_OPT_LEN_CCECHO	6		/* 接続カウント			*/

/*
 *  TCP 最大セグメントサイズ
 */

/*
 *  IPv4 の TCP 最大セグメントサイズ
 *  IP4_MSS は 576 で、標準の IPv4 ヘッダ長 (20) と
 *  TCP ヘッダ長 (20) を引いた値 536 であるが、512 を標準とする。
 */

#define TCP_MSS			UINT_C(512)

/*
 *  IPv6 の TCP 最大セグメントサイズ
 *  IPV6_MMTU は 1280 で、標準の IPv6 ヘッダ長 (40) と
 *  TCP ヘッダ長 (20) を引いた値 1220 であるが、1024 を標準とする。
 */

#define TCP6_MSS		UINT_C(1024)

/*
 *  TCP 最小セグメントサイズ
 *
 *  256（最小リンク MTU）- 40 = 216
 */

#define TCP_MINMSS		UINT_C(216)


/*
 *  TCP 最大ウィンドウサイズ
 */

#define MAX_TCP_WIN_SIZE	UINT_C(65535)


/*
 *  関数シミュレーションマクロ
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
 *  TCP/IP のタイマの定義
 */

#define TCP_SLOW_TMO		(ULONG_C(500)/NET_TIMER_CYCLE)	/* 500 [ms]	*/
#define TCP_FAST_TMO		(ULONG_C(200)/NET_TIMER_CYCLE)	/* 200 [ms]	*/

#define TCP_SLOW_HZ		(ULONG_C(1000)/TCP_SLOW_TMO/NET_TIMER_CYCLE)	/* Hz	*/

/* TCP タイマ値 */

#define TCP_TVAL_MSL		(TCP_SLOW_HZ * 30)
					/* 最大セグメント生存時間	*/

#define TCP_TVAL_SRTT_BASE	0	/* 滑らかな往復時間の基準値*/

#define TCP_TVAL_RTO_BASE	(TCP_SLOW_HZ * 3)
		/* 情報が得られない場合の再送タイムアウトの基準値	*/

#define TCP_TVAL_MIN_PERSIST	(TCP_SLOW_HZ * 5)
				/* 持続タイムアウトの最小値	*/
#define TCP_TVAL_MAX_PERSIST	(TCP_SLOW_HZ * 60)
				/* 持続タイムアウトの最大値	*/

#define TCP_TVAL_KEEP_INIT	(TCP_SLOW_HZ * 75)
					/* 保留タイマの初期値	*/
#define TCP_TVAL_KEEP_IDLE	(TCP_SLOW_HZ * 2 * 60 * 60)
					/* 保留タイマ起動までの標準値*/
#define TCP_TVAL_KEEP_INTERVAL	(TCP_SLOW_HZ * 75)
					/* 保留タイマインターバルの標準値*/
#define TCP_TVAL_KEEP_COUNT	8	/* 保留タイムアウトの最大値*/

#define TCP_TVAL_MIN		(TCP_SLOW_HZ * 3)
					/* 時間の最小単位	*/
#define TCP_TVAL_MAX_REXMT	(TCP_SLOW_HZ * 64)
					/* 最大再送時間		*/


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
 *  ポート番号の定義
 */

#define TCP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP 標準	*/
#define UDP_PORTANY			UINT_C(0x0000)	/* ITRON TCP/IP 標準	*/

#define TCP_PORT_LAST_WELL_KNOWN	UINT_C(1023)	/* Well Known 終了番号	*/
#define TCP_PORT_FIRST_AUTO		UINT_C(1024)	/* 自動割り当て開始番号	*/
#define TCP_PORT_LAST_AUTO		UINT_C(4999)	/* 自動割り当て終了番号	*/
