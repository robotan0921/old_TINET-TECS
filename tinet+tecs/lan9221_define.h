/*
 *  ネットワークインタフェース用タイマの定義
 */

#define IF_TIMER_HZ		1		/* タイマの周波数、1 [s]	*/

/*
 *  ネットワークインタフェースのフラグ
 */

#define IFF_UP			UINT_C(0x0001)	/* 起動済み		*/
#define IFF_RUNNING		UINT_C(0x0002)	/* 動作中		*/
