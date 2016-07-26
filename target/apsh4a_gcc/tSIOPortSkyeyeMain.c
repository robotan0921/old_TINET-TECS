#include "tSIOPortSkyeyeMain_tecsgen.h"
#include "target_serial.h"
#ifndef E_OK
#define	E_OK		0		/* 正常終了 */
#define	E_ID		(-18)	/* 不正ID番号 */
#endif


/* 属性アクセスマクロ */
/*
 * uartBase         void*            ATTR_uartBase   
 * openFlag         bool_t           VAR_openFlag    
 * receiveFlag      bool_t           VAR_receiveFlag 
 * receiveBuffer    char_t           VAR_receiveBuffer
 * receiveReady     bool_t           VAR_receiveReady
 * sendReady        bool_t           VAR_sendReady   
 *
 * 呼び口関数 
 *
 * call port : ciSIOCBR  signature: siSIOCBR
 *   void           ciSIOCBR_readySend( );
 *   void           ciSIOCBR_readyReceive( );
 */
/* 受け口関数 
 *
 * entry port: eSIOPort
 * signature:  sSIOPort
 */

/*
 *  SIOドライバの初期化
 */
void
eInitialize_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;

	assert(VALID_IDX(idx));
	p_cellcb = GET_CELLCB(idx);

	/*
	 *  シリアルI/Oポート管理ブロックの初期化
	 */
	VAR_openFlag = false;
	/* 受信データの格納先アドレスの設定 */
	sil_wrw_mem((void *)(ATTR_uartBase + USART_RPR), (uint32_t)(&VAR_receiveBuffer));
    sil_wrw_mem((void *)(ATTR_uartBase + USART_RCR), 0x0001);
}

/*
 *  SIOドライバの終了処理
 */
void
eTerminate_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	assert(VALID_IDX(idx));
	p_cellcb = GET_CELLCB(idx);

	/*
	 *  オープンされているシリアルI/Oポートのクローズ
	 */
	if (VAR_openFlag) {
		/*
		 *  本当はeSIOPort_closeを呼びたい
		 */
		VAR_openFlag = false;
		/*
		 *  シリアルI/O割込みをマスクする．
		 */
		dis_int(INTNO_SIO);
	}
}

/*
 * 文字を受信したか?
 */ 
Inline bool_t
uart_getready(CELLCB *p_cellcb)
{
	return(sil_rew_mem((void*)(ATTR_uartBase + USART_RCR)) == 0);
}
/*
 * 文字を送信できるか?
 */
Inline bool_t
uart_putready(CELLCB *p_cellcb)
{
    return(true);
}

/*
 * name:         eSIOPort_open
 * global_name:  tSIOPortSkyeyeMain_eSIOPort_open
 */
void
eSIOPort_open( CELLIDX idx)
{
	CELLCB	*p_cellcb;
	assert( VALID_IDX( idx ) );
	p_cellcb = GET_CELLCB(idx);
	
	VAR_openFlag = true;
	ena_int(INTNO_SIO);
}

/*
 * name:         eSIOPort_close
 * global_name:  tSIOPortSkyeyeMain_eSIOPort_close
 */
void
eSIOPort_close(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	assert( VALID_IDX( idx ) );
	p_cellcb = GET_CELLCB(idx);
	
	VAR_openFlag = false;
	/*
	 *  シリアルI/O割込みをマスクする．
	 */
	dis_int(INTNO_SIO);
}

/*
 * 送信する文字の書き込み 
 * name:         eSIOPort_putchar
 * global_name:  tSIOPortSkyeyeMain_eSIOPort_putchar
 */
bool_t
eSIOPort_putChar( CELLIDX idx, char_t c)
{
	CELLCB	*p_cellcb;
	assert( VALID_IDX( idx ) );
	p_cellcb = GET_CELLCB(idx);

	if (uart_putready(p_cellcb)){
		sil_wrw_mem((void*)(ATTR_uartBase + USART_THR),c); 
        return(true);
    }
    return(false);
}

/*
 * 受信した文字の取り出し
 * name:         eSIOPort_getchar
 * global_name:  tSIOPortSkyeyeMain_eSIOPort_getchar
 */
int_t
eSIOPort_getChar(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	char_t c;
	
	assert( VALID_IDX( idx ) );
	p_cellcb = GET_CELLCB(idx);
	if (uart_getready(p_cellcb)) {
		c = VAR_receiveBuffer;
		sil_wrw_mem((void *)(ATTR_uartBase + USART_RPR), (uint32_t)(&VAR_receiveBuffer));
		sil_wrw_mem((void *)(ATTR_uartBase + USART_RCR), 0x0001);
		return (c);
	}
	return (-1);
}

/*
 * シリアルI/Oポートからのコールバックの許可
 * name:         eSIOPort_enableCBR
 * global_name:  tSIOPortSkyeyeMain_eSIOPort_enableCBR
 */
void
eSIOPort_enableCBR( CELLIDX idx, uint_t cbrtn)
{
	CELLCB	*p_cellcb;

	assert( VALID_IDX( idx ) );
	p_cellcb = GET_CELLCB(idx);

	switch (cbrtn) {
	  case SIO_RDY_SND:
		VAR_sendReady = true;
		break;
	  case SIO_RDY_RCV:
		VAR_receiveReady = true;
		break;
	}

}

/*
 * シリアルI/Oポートからのコールバックの禁止 
 * name:         eSIOPort_disableCBR
 * global_name:  tSIOPortSkyeyeMain_eSIOPort_disableCBR
 */
void
eSIOPort_disableCBR( CELLIDX idx, uint_t cbrtn)
{
	CELLCB	*p_cellcb;

	assert( VALID_IDX( idx ) );
	p_cellcb = GET_CELLCB(idx);
	switch (cbrtn) {
	  case SIO_RDY_SND:
		VAR_sendReady = false;
		break;
	  case SIO_RDY_RCV:
		VAR_receiveReady = false;
		break;
	}
}


/*
 *  SIOの割込みハンドラ
 */
void
eiISR_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;

	assert( VALID_IDX( idx ) );
	p_cellcb = GET_CELLCB(idx);

	if(VAR_receiveReady){
		/*
		 *  受信通知コールバックルーチンを呼び出す．
		 */
		ciSIOCBR_readyReceive();
	}
	if(VAR_sendReady){
		/*
		 *  送信可能コールバックルーチンを呼び出す．
		 */
		ciSIOCBR_readySend();
	}

}
