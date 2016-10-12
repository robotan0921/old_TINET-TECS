/*
 * このファイルは tecsgen によりテンプレートとして自動生成されました
 * このファイルを編集して使用することが意図されていますが
 * tecsgen の再実行により上書きされてしまうため、通常
 *   gen/tMbed_template.c => src/tMbed.c
 * のように名前, フォルダを変更してから修正します
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * macaddr0         uint8_t          ATTR_macaddr0   
 * macaddr1         uint8_t          ATTR_macaddr1   
 * macaddr2         uint8_t          ATTR_macaddr2   
 * macaddr3         uint8_t          ATTR_macaddr3   
 * macaddr4         uint8_t          ATTR_macaddr4   
 * macaddr5         uint8_t          ATTR_macaddr5   
 * Timer            uint16_t         VAR_Timer       
 *
 * 呼び口関数 #_TCPF_#
 * require port: signature:sKernel context:task
 *   ER             getExtendedInformation( intptr_t* p_exinf );
 *   ER             sleep( );
 *   ER             sleepTimeout( TMO timeout );
 *   ER             delay( RELTIM delayTime );
 *   ER             exit( );
 *   ER             disableTerminate( );
 *   ER             enableTerminate( );
 *   bool_t         senseTerminate( );
 *   ER             setTime( SYSTIM systemTime );
 *   ER             getTime( SYSTIM* p_systemTime );
 *   ER             adjustTime( int32_t adjustTime );
 *   HRTCNT         fetchHighResolutionTimer( );
 *   ER             rotateReadyQueue( PRI taskPriority );
 *   ER             getTaskId( ID* p_taskId );
 *   ER             getLoad( PRI taskPriority, uint_t* p_load );
 *   ER             getNthTask( PRI taskPriority, uint_t nth, ID* p_taskID );
 *   ER             lockCpu( );
 *   ER             unlockCpu( );
 *   ER             disableDispatch( );
 *   ER             enableDispatch( );
 *   bool_t         senseContext( );
 *   bool_t         senseLock( );
 *   bool_t         senseDispatch( );
 *   bool_t         senseDispatchPendingState( );
 *   bool_t         senseKernel( );
 *   ER             exitKernel( );
 *   ER             changeInterruptPriorityMask( PRI interruptPriority );
 *   ER             getInterruptPriorityMask( PRI* p_interruptPriority );
 * call port: cSemaphoreSend signature: sSemaphore context:task
 *   ER             cSemaphoreSend_signal( );
 *   ER             cSemaphoreSend_wait( );
 *   ER             cSemaphoreSend_waitPolling( );
 *   ER             cSemaphoreSend_waitTimeout( TMO timeout );
 *   ER             cSemaphoreSend_initialize( );
 *   ER             cSemaphoreSend_refer( T_RSEM* pk_semaphoreStatus );
 * call port: ciSemaphoreReceive signature: siSemaphore context:non-task
 *   ER             ciSemaphoreReceive_signal( );
 * call port: cInterruptRequest signature: sInterruptRequest context:task
 *   ER             cInterruptRequest_disable( );
 *   ER             cInterruptRequest_enable( );
 * call port: cNetworkTimer signature: sNetworkTimer context:task
 *   ER             cNetworkTimer_Timeout( RELTIM timout );
 * allocator port for call port:eNicDriver func:start param: outputp
 *   ER             eNicDriver_start_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             eNicDriver_start_outputp_dealloc( const void* buf );
 *   ER             eNicDriver_start_outputp_reuse( void* buf );
 *   ER_UINT        eNicDriver_start_outputp_bufferSize( const void* buf );
 *   uint32_t       eNicDriver_start_outputp_bufferMaxSize( );
 * allocator port for call port:eNicDriver func:read param: inputp
 *   ER             eNicDriver_read_inputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             eNicDriver_read_inputp_dealloc( const void* buf );
 *   ER             eNicDriver_read_inputp_reuse( void* buf );
 *   ER_UINT        eNicDriver_read_inputp_bufferSize( const void* buf );
 *   uint32_t       eNicDriver_read_inputp_bufferMaxSize( );
 *
 * #[</PREAMBLE>]# */

/* プロトタイプ宣言や変数の定義をここに書きます #_PAC_# */
#include "tMbed_tecsgen.h"

#include "lan9221.h"
#include "if_mbed.h"

//#include <tinet_defs.h>
#include "tinet_nic_defs.h"
//#include <tinet_config.h>


#include "ethernet_api.h"
#include "ethernetext_api.h"
#include "iodefine.h"

extern ER		dly_tsk(RELTIM dlytim);

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

#define DEFAULT_MAC_H	0x00000100				/* デフォルトMACアドレス */
#define DEFAULT_MAC_L	0x2A7B0C00				/* 00-0C-7B-2A-00-01     */

#define ETHER_EESR0_TC 0x00200000

/*
 *  ネットワークインタフェースに依存するソフトウェア情報 
 */
typedef struct t_mbed_softc {
	bool_t link_pre;
	bool_t link_now;
	bool_t over_flow;
} T_MBED_SOFTC;



static unsigned long lan9221_get_mac_csr(CELLCB *p_cellcb,unsigned char addr) {
	unsigned long csr;

	while(lan9221_reg_read(LAN9221_MAC_CSR_CMD) & LAN9221_MAC_CSR_CMD_CSR_BUSY);

	lan9221_reg_write(LAN9221_MAC_CSR_CMD,
			LAN9221_MAC_CSR_CMD_CSR_BUSY | LAN9221_MAC_CSR_CMD_R_NOT_W | addr);

	while(lan9221_reg_read(LAN9221_MAC_CSR_CMD) & LAN9221_MAC_CSR_CMD_CSR_BUSY);

	csr = lan9221_reg_read(LAN9221_MAC_CSR_DATA);

	return csr;
}

static void lan9221_set_mac_csr(CELLCB *p_cellcb,unsigned char addr, unsigned long data) {
	while(lan9221_reg_read(LAN9221_MAC_CSR_CMD) & LAN9221_MAC_CSR_CMD_CSR_BUSY);

	lan9221_reg_write(LAN9221_MAC_CSR_DATA, data);
	lan9221_reg_write(LAN9221_MAC_CSR_CMD, LAN9221_MAC_CSR_CMD_CSR_BUSY | addr);

	while(lan9221_reg_read(LAN9221_MAC_CSR_CMD) & LAN9221_MAC_CSR_CMD_CSR_BUSY);
}



static void lan9221_reset(CELLCB *p_cellcb) {
	int timeout;

	if(lan9221_reg_read(LAN9221_PMT_CTRL) & LAN9221_PMT_CTRL_READY) {

		lan9221_reg_write(LAN9221_BYTE_TEST, 0x0);

		timeout = 10;

		while(timeout-- &&
			!(lan9221_reg_read(LAN9221_PMT_CTRL) & LAN9221_PMT_CTRL_READY)) {
			delay(10);
		}
		if(!timeout) {
			return;
		}
	}

	lan9221_reg_write(LAN9221_INT_EN, 0);

	lan9221_reg_write(LAN9221_HW_CFG, LAN9221_HW_CFG_SRST);

	timeout = 1000;
	while(timeout-- && lan9221_reg_read(LAN9221_E2P_CMD) & LAN9221_E2P_CMD_EPC_BUSY) {
		delay(10);
	}

	if(!timeout) {
		return;
	}

	lan9221_set_mac_csr(p_cellcb,LAN9221_FLOW, LAN9221_FLOW_FCPT | LAN9221_FLOW_FCEN);
	lan9221_reg_write(LAN9221_AFC_CFG, 0x0050287F);

	lan9221_reg_write(LAN9221_GPIO_CFG, 0x70070000);
}


static void lan9221_handle_mac_address(CELLCB *p_cellcb) {
	unsigned long addrh, addrl;

	addrl = lan9221_get_mac_csr(p_cellcb,LAN9221_ADDRL);
	addrh = lan9221_get_mac_csr(p_cellcb,LAN9221_ADDRH);
	if( addrl != DEFAULT_MAC_L ) {

		addrl = DEFAULT_MAC_L;
		addrh = DEFAULT_MAC_H;

		lan9221_set_mac_csr(p_cellcb,LAN9221_ADDRL, addrl);
		lan9221_set_mac_csr(p_cellcb,LAN9221_ADDRH, addrh);
	}

//	my_macaddr_l = lan9221_get_mac_csr(LAN9221_ADDRL);
//	my_macaddr_h = lan9221_get_mac_csr(LAN9221_ADDRH);
}

static int lan9221_miiphy_read(CELLCB *p_cellcb,unsigned char phy, unsigned char addr, unsigned long *data) {
	while(lan9221_get_mac_csr(p_cellcb,LAN9221_MII_ACC) & LAN9221_MII_ACC_MII_BUSY);

	lan9221_set_mac_csr(p_cellcb,LAN9221_MII_ACC, 
	        phy << 11 | addr << 6 | LAN9221_MII_ACC_MII_BUSY);

	while(lan9221_get_mac_csr(p_cellcb,LAN9221_MII_ACC) & LAN9221_MII_ACC_MII_BUSY);

	*data = lan9221_get_mac_csr(p_cellcb,LAN9221_MII_DATA);

	return 0;
}

static int lan9221_miiphy_write(CELLCB *p_cellcb,unsigned char phy, unsigned char addr, unsigned long  data) {
	while(lan9221_get_mac_csr(p_cellcb,LAN9221_MII_ACC) & LAN9221_MII_ACC_MII_BUSY)
		;

	lan9221_set_mac_csr(p_cellcb,LAN9221_MII_DATA, data);

	lan9221_set_mac_csr(p_cellcb,LAN9221_MII_ACC, 
	        phy << 11 | addr << 6 | LAN9221_MII_ACC_MII_BUSY | LAN9221_MII_ACC_MII_WRITE);

	while(lan9221_get_mac_csr(p_cellcb,LAN9221_MII_ACC) & LAN9221_MII_ACC_MII_BUSY);

	return 0;
}

static int lan9221_phy_reset(CELLCB *p_cellcb) {
	unsigned long val;

	val = lan9221_reg_read(LAN9221_PMT_CTRL);
	val &= 0xFFFFF030;
    val |= LAN9221_PMT_CTRL_PHY_RST;
	lan9221_reg_write(LAN9221_PMT_CTRL, val);

	//delay(100);opt
	delay(100);

	return 0;
}

static void lan9221_phy_configure(CELLCB *p_cellcb) {
	unsigned long status;
	int timeout;

	lan9221_phy_reset(p_cellcb);

	lan9221_miiphy_write(p_cellcb,1, LAN9221_PHY_BMCR, LAN9221_PHY_BMCR_RESET);
	delay(1);
	lan9221_miiphy_write(p_cellcb,1, LAN9221_PHY_ANAR, 0x01E1);
	lan9221_miiphy_write(p_cellcb,1, LAN9221_PHY_BMCR, LAN9221_PHY_BMCR_AUTON |
				LAN9221_PHY_BMCR_RST_NEG);

	timeout = 5000;
	do {
		//delay(1);//opt
		delay(1);
		if( (timeout--) == 0) {
			goto err_out;
		}

		if(lan9221_miiphy_read(p_cellcb,1, LAN9221_PHY_BMSR, &status) != 0) {
			goto err_out;
		}
	} while(!(status & LAN9221_PHY_BMSR_LS));

err_out:

	return;
}

static void lan9221_enable(CELLCB *p_cellcb) {

	lan9221_reg_write(LAN9221_HW_CFG, 8 << 16 | LAN9221_HW_CFG_MBO);

	lan9221_reg_write(LAN9221_GPT_CFG, LAN9221_GPT_CFG_TIMER_EN | 10000);

	lan9221_reg_write(LAN9221_TX_CFG, LAN9221_TX_CFG_TX_ON);

	lan9221_reg_write(LAN9221_RX_CFG, 0);

	lan9221_set_mac_csr(p_cellcb,LAN9221_MAC_CR, LAN9221_MAC_CR_TXEN | LAN9221_MAC_CR_RXEN |
				LAN9221_MAC_CR_HBDIS);


	//割り込み発生を有効にする

	lan9221_reg_write(LAN9221_INT_CFG,LAN9221_INT_CFG_IRQ_EN | LAN9221_INT_CFG_IRQ_POL |
					  LAN9221_INT_CFG_IRQ_TYPE);
	lan9221_reg_write(LAN9221_INT_EN,LAN9221_INT_EN_RSFL_EN);
	
	//lan9221_reg_write(LAN9221_FIFO_INT,0x00000001);
	
//	lan9221_reg_write(LAN9221_INT_CFG,LAN9221_INT_CFG_INT_DEAS);//割り込み猶予時間を有効に
	
	
}

static int lan9221_open(CELLCB *p_cellcb) {

	if(lan9221_reg_read(LAN9221_BYTE_TEST) != LAN9221_BYTE_TEST_VAL) {
		lan9221_reg_write(LAN9221_WORD_SWAP, LAN9221_WORD_SWAP_DISABLE);
	}

	lan9221_reset(p_cellcb);
	lan9221_phy_configure(p_cellcb);
	lan9221_handle_mac_address(p_cellcb);
	lan9221_enable(p_cellcb);

	//接続確立までディレイを謔?
	delay(2000);

	return 0;
}



/*
 *  ed_inter_init -- ターゲット依存部の割込みの初期化
 */
/*
static void
ed_inter_init (CELLCB *p_cellcb) {

	//ICR0のIRLMビットを立てて、割り込み受付可能なようにする
	//while((sil_reh_mem((void *)ICR0) & ICR0_ENABLE) != ICR0_ENABLE)
	sil_wrw_mem((void *)ICR0,ICR0_ENABLE);
	sil_wrw_mem((void *)ICR1, 0xC0000000);
	//sil_wrw_mem((void *)ICR1, 0x40000000);
	//割り込み優先度決定
	sil_wrw_mem((void *)INTPRI, 0x80000000);
	//割り込みマスククリア
	sil_wrw_mem((void *)C0INTMSKCLR0,0x80000000);
	
}
*/

static void rza1_recv_callback(CELLCB *p_cellcb) {
    //sig_sem(if_softc.semid_rxb_ready);
    ciSemaphoreReceive_signal();
}

static void
if_mbed_init_sub (CELLCB *p_cellcb)
{
    ethernet_cfg_t ethcfg;
    uint8_t *macaddress;
    eNicDriver_getMac(p_cellcb, macaddress);

    /* Initialize the hardware */
    ethcfg.int_priority = 6;
    ethcfg.recv_cb      = &rza1_recv_callback;
    //ethcfg.ether_mac    = (char *)ic->ifaddr.lladdr;
    ethcfg.ether_mac    = (char *)macaddress;
    ethernetext_init(&ethcfg);
}

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eWatchdogTimer
 * entry port: eWatchdogTimer
 * signature:  sCallTimerFunction
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eWatchdogTimer_callFunction
 * name:         eWatchdogTimer_callFunction
 * global_name:  tLan9221_eWatchdogTimer_callFunction
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eWatchdogTimer_callFunction(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */

	if(VAR_Timer > 0){
		VAR_Timer--;
		if(VAR_Timer == 0){
		  //MIBの機能をやってから
		  lan9221_reset(p_cellcb);
		}
	}

	cNetworkTimer_Timeout(10);//1s間隔で呼び出される
	
}

/* #[<ENTRY_PORT>]# eNicDriver
 * entry port: eNicDriver
 * signature:  sNicDriver
 * context:    task
 * #[</ENTRY_PORT>]# */




/* #[<ENTRY_FUNC>]# eNicDriver_init
 * name:         eNicDriver_init
 * global_name:  tLan9221_eNicDriver_init
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eNicDriver_init(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	/* VAR_Timer = 0; */
	/* cNetworkTimer_Timeout(10); */

	/* cInterruptRequest_disable(); */
 
	/* lan9221_open(p_cellcb); */
	/* cSemaphoreSend_signal(); */
	/* ed_inter_init(p_cellcb); */
    /*  */
	/* cInterruptRequest_enable();	 */
    
    /* mbed_init 本体を呼び出す。*/
	if_mbed_init_sub(p_cellcb);

	//act_tsk(IF_MBED_PHY_TASK);

	ethernet_set_link(-1, 0);

	ETHER.EESIPR0 |= ETHER_EESR0_TC;
}



/* #[<ENTRY_FUNC>]# eNicDriver_start
 * name:         eNicDriver_start
 * global_name:  tLan9221_eNicDriver_start
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eNicDriver_start(CELLIDX idx, int8_t* outputp, int32_t size, uint8_t align)
{

	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
/*
	T_NET_BUF *output = (T_NET_BUF*)outputp;
	unsigned char *tmp = (unsigned char *)(output->buf);
	tmp += align;//アラインが必要な場合は
	size = output->len;
	
	union utmp data;
	int32_t i;
	unsigned long tmplen;
	unsigned long status;
	static unsigned long cmd_a;
	static unsigned long cmd_b;

	//cmd_a = ((unsigned long)tmp & 0x3) |
	cmd_a =  LAN9221_TX_CMD_A_INT_FIRST_SEG | //0x2000
	  LAN9221_TX_CMD_A_INT_LAST_SEG  | (int)size;// | //0x1000
	  //0x00020000;
	cmd_b = (int)size;// | 0x00002000;

	lan9221_reg_write(LAN9221_TX_DATA_FIFO, cmd_a);
	lan9221_reg_write(LAN9221_TX_DATA_FIFO, cmd_b);

	tmplen = ((int)size + 3) / 4;
	while(tmplen--) {
		for(i = 0;i < 4;i++){
			data.c[i] = *tmp;
			tmp++;
		}
		lan9221_reg_write(LAN9221_TX_DATA_FIFO, data.l);
	}

	
	while(!((lan9221_reg_read(LAN9221_TX_FIFO_INF) & LAN9221_TX_FIFO_INF_TSUSED) >> 16));

	status = lan9221_reg_read(LAN9221_TX_STATUS_FIFO) &
			(LAN9221_TX_STS_LOC | LAN9221_TX_STS_LATE_COLL | LAN9221_TX_STS_MANY_COLL |
			LAN9221_TX_STS_MANY_DEFER | LAN9221_TX_STS_UNDERRUN);

	if(!status) {
		cSemaphoreSend_signal();
		eNicDriver_start_outputp_dealloc((void *)outputp);
		return;
	}
	
	eNicDriver_start_outputp_dealloc((void *)outputp);
	
	cSemaphoreSend_signal();
//	ic->timer =
*/
	//T_MBED_SOFTC *sc = ic->sc;
	T_NET_BUF *output = (T_NET_BUF*)outputp;
	int32_t len, res, pos;

	for ( res = output->len, pos = 0; res > 0; res -= len, pos += len ) {
		len = ethernet_write((char *)output->buf + IF_ETHER_NIC_HDR_ALIGN + pos, res);
	}
    ethernet_send();
}

/* #[<ENTRY_FUNC>]# eNicDriver_read
 * name:         eNicDriver_read
 * global_name:  tLan9221_eNicDriver_read
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eNicDriver_read(CELLIDX idx, int8_t** inputp, int32_t* size, uint8_t align)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */	
	
	unsigned char *tmp;
	union utmp data;
	int i;
	unsigned long pktlen, tmplen;
	unsigned long status;

	cInterruptRequest_disable();
	
	if((lan9221_reg_read(LAN9221_RX_FIFO_INF) & LAN9221_RX_FIFO_INF_RXSUSED) >> 16) {
		status = lan9221_reg_read(LAN9221_RX_STATUS_FIFO);
		pktlen = (status & LAN9221_RX_STS_PKT_LEN) >> 16;

		if (pktlen <= 1514){
			
			eNicDriver_read_inputp_alloc((void **)inputp,pktlen,1);
			*size = pktlen + sizeof(T_NET_BUF)-4+align;

			tmp = (unsigned char *)(((T_NET_BUF *)(*inputp))->buf);
			tmp += align;//アラインが必要な場合は


			tmplen = (pktlen + 3) / 4;
			while(tmplen--) {
				data.l =lan9221_reg_read(LAN9221_RX_DATA_FIFO);
				for(i=0;i<4;i++){
					*tmp = data.c[i];
					tmp++;
				}
			}
			
			if(status & LAN9221_RX_STS_ES) {
				return;
			}
		
		}
		else {
			//eNicDriver_nic_reset();
		}

		/* NIC からの割り込みを許可する。*/
		cInterruptRequest_enable();
		return;
	}

	cInterruptRequest_enable();
}

/* #[<ENTRY_FUNC>]# eNicDriver_getMac
 * name:         eNicDriver_getMac
 * global_name:  tLan9221_eNicDriver_getMac
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eNicDriver_getMac(CELLIDX idx, uint8_t* macaddress)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	//mikanちゃんとハードウェアからとってくるべき
	macaddress[0] = ATTR_macaddr0;
	macaddress[1] = ATTR_macaddr1;
	macaddress[2] = ATTR_macaddr2;
	macaddress[3] = ATTR_macaddr3;
	macaddress[4] = ATTR_macaddr4;
	macaddress[5] = ATTR_macaddr5;
	
}

/* #[<ENTRY_PORT>]# eiBody
 * entry port: eiBody
 * signature:  siHandlerBody
 * context:    non-task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eiBody_main
 * name:         eiBody_main
 * global_name:  tLan9221_eiBody_main
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eiBody_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */	
	//ciSemaphoreReceive_signal();
	//割り込み優先度決定
	//sil_wrw_mem((void *)INTPRI, 0x00000000);
	//syslog(LOG_EMERG,"%x",	sil_rew_mem(INTREQ));//debug
	//syslog(LOG_EMERG,"%x",	lan9221_reg_read(LAN9221_RX_FIFO_INF));//debug FIFOの使用量
	//lan9221_reg_write(LAN9221_INT_STS,LAN9221_INT_STS_RSFL);
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
