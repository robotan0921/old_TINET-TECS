/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tSCIF_template.c => src/tSCIF.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * baseAddress      uintptr_t        ATTR_baseAddress
 * baudRate         uint32_t         ATTR_baudRate   
 * initialized      bool_t           VAR_initialized 
 *
 * 呼び口関数 #_TCPF_#
 * call port: ciSIOCBR signature: siSIOCBR context:task
 *   void           ciSIOCBR_readySend( );
 *   void           ciSIOCBR_readyReceive( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tSCIF_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* 受け口関数 #_TEPF_# */
/* #[<ENTRY_PORT>]# eSIOPort
 * entry port: eSIOPort
 * signature:  sSIOPort
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eSIOPort_open
 * name:         eSIOPort_open
 * global_name:  tSCIF_eSIOPort_open
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eSIOPort_open(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_FUNC>]# eSIOPort_close
 * name:         eSIOPort_close
 * global_name:  tSCIF_eSIOPort_close
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eSIOPort_close(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_FUNC>]# eSIOPort_putChar
 * name:         eSIOPort_putChar
 * global_name:  tSCIF_eSIOPort_putChar
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
bool_t
eSIOPort_putChar(CELLIDX idx, char c)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_FUNC>]# eSIOPort_getChar
 * name:         eSIOPort_getChar
 * global_name:  tSCIF_eSIOPort_getChar
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
int_t
eSIOPort_getChar(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_FUNC>]# eSIOPort_enableCBR
 * name:         eSIOPort_enableCBR
 * global_name:  tSCIF_eSIOPort_enableCBR
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eSIOPort_enableCBR(CELLIDX idx, uint_t cbrtn)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_FUNC>]# eSIOPort_disableCBR
 * name:         eSIOPort_disableCBR
 * global_name:  tSCIF_eSIOPort_disableCBR
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eSIOPort_disableCBR(CELLIDX idx, uint_t cbrtn)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_PORT>]# eiRxISR
 * entry port: eiRxISR
 * signature:  siHandlerBody
 * context:    non-task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eiRxISR_main
 * name:         eiRxISR_main
 * global_name:  tSCIF_eiRxISR_main
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eiRxISR_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<ENTRY_PORT>]# eiTxISR
 * entry port: eiTxISR
 * signature:  siHandlerBody
 * context:    non-task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eiTxISR_main
 * name:         eiTxISR_main
 * global_name:  tSCIF_eiTxISR_main
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eiTxISR_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* エラー処理コードをここに記述します */
	} /* end if VALID_IDX(idx) */

	/* ここに処理本体を記述します #_TEFB_# */

}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
