/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tTCPOutputBody_template.c => src/tTCPOutputBody.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 呼び口関数 #_TCPF_#
 * require port: signature:sTINET context:task
 *   uint32_t       netRand( );
 *   void           netSrand( uint32_t speed );
 * call port: cIPv4Output signature: sIPv4Output context:task optional:true
 *   bool_t     is_cIPv4Output_joined()                     check if joined
 *   ER             cIPv4Output_IPv4Output( int8_t* outputp, int32_t size, TMO tmout );
 *   ER             cIPv4Output_getOffset( T_OFF_BUF* offset );
 *   T_IN4_ADDR     cIPv4Output_getIPv4Address( );
 *   void           cIPv4Output_setHeader( int8_t* outputp, int32_t size, T_IN4_ADDR dstaddr, T_IN4_ADDR srcaddr );
 *   ER             cIPv4Output_IPv4Reply( int8_t* outputp, int32_t size, TMO tmout );
 * call port: cIPv4CheckSum signature: sIPv4CheckSum context:task optional:true
 *   bool_t     is_cIPv4CheckSum_joined()                     check if joined
 *   uint16_t       cIPv4CheckSum_ipv4CheckSum( int8_t* data, int32_t size, uint32_t offset, uint8_t proto );
 * call port: cTCPOutputStart signature: sTCPOutputStart context:task
 *   ER             cTCPOutputStart_outputStart( subscript );
 *   ER             cTCPOutputStart_timerFunction( subscript );
 *       subscript:  0...(NCP_cTCPOutputStart-1)
 * call port: cSemaphore signature: sSemaphore context:task
 *   ER             cSemaphore_signal( );
 *   ER             cSemaphore_wait( );
 *   ER             cSemaphore_waitPolling( );
 *   ER             cSemaphore_waitTimeout( TMO timeout );
 *   ER             cSemaphore_initialize( );
 *   ER             cSemaphore_refer( T_RSEM* pk_semaphoreStatus );
 * call port: cTCPFunctions signature: sTCPFunctions context:task
 *   T_TCP_SEQ      cTCPFunctions_getTcpIss( );
 *   void           cTCPFunctions_setTcpIss( T_TCP_SEQ iss );
 *   T_TCP_SEQ      cTCPFunctions_initTcpIss( );
 *   T_TCP_TIME     cTCPFunctions_tcpRexmtValue( T_TCP_TIME srtt, T_TCP_TIME rttvar );
 *   T_TCP_TIME     cTCPFunctions_tcpRangeSet( T_TCP_TIME value, T_TCP_TIME tvmin, T_TCP_TIME tvmax );
 * call port: cNetworkTimer signature: sNetworkTimer context:task
 *   ER             cNetworkTimer_Timeout( RELTIM timout );
 * allocator port for call port:cIPv4Output func:IPv4Output param: outputp
 *   ER             cIPv4Output_IPv4Output_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             cIPv4Output_IPv4Output_outputp_dealloc( const void* buf );
 *   ER             cIPv4Output_IPv4Output_outputp_reuse( void* buf );
 *   ER_UINT        cIPv4Output_IPv4Output_outputp_bufferSize( const void* buf );
 *   uint32_t       cIPv4Output_IPv4Output_outputp_bufferMaxSize( );
 * allocator port for call port:cIPv4Output func:IPv4Reply param: outputp
 *   ER             cIPv4Output_IPv4Reply_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             cIPv4Output_IPv4Reply_outputp_dealloc( const void* buf );
 *   ER             cIPv4Output_IPv4Reply_outputp_reuse( void* buf );
 *   ER_UINT        cIPv4Output_IPv4Reply_outputp_bufferSize( const void* buf );
 *   uint32_t       cIPv4Output_IPv4Reply_outputp_bufferMaxSize( );
 * allocator port for call port:eTCPOutput func:output param: outputp
 *   ER             eTCPOutput_output_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             eTCPOutput_output_outputp_dealloc( const void* buf );
 *   ER             eTCPOutput_output_outputp_reuse( void* buf );
 *   ER_UINT        eTCPOutput_output_outputp_bufferSize( const void* buf );
 *   uint32_t       eTCPOutput_output_outputp_bufferMaxSize( );
 * allocator port for call port:eTCPOutput func:respond param: outputp
 *   ER             eTCPOutput_respond_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             eTCPOutput_respond_outputp_dealloc( const void* buf );
 *   ER             eTCPOutput_respond_outputp_reuse( void* buf );
 *   ER_UINT        eTCPOutput_respond_outputp_bufferSize( const void* buf );
 *   uint32_t       eTCPOutput_respond_outputp_bufferMaxSize( );
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tTCPOutputBody_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eBody
 * entry port: eBody
 * signature:  sTaskBody
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eBody_main
 * name:         eBody_main
 * global_name:  tTCPOutputBody_eBody_main
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eBody_main(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	static int_t last_ix = 0;

 	int_t		ix, sel_ix;

	syslog(LOG_EMERG, "[[[[[[[TCP OUTPUT started.]]]]]]]");

	cNetworkTimer_Timeout(5);//500ms間隔で呼び出されるタイマ関数

#if 0// SUPPORT_INET6

	/* IPv6 のステートレス・アドレス自動設定を実行する。*/
	in6_if_up(IF_GET_IFNET());

#endif	/* of #ifdef SUPPORT_INET6 */

	while (true) {

		/* 出力がポストされるまで待つ。*/
		cSemaphore_wait();

		syslog(LOG_EMERG, "----------------TCP OUTPUT -------------");

		if (++ last_ix == NCP_cTCPOutputStart)
		  last_ix = 0;
		sel_ix = ix = last_ix;
		do {
			if(cTCPOutputStart_outputStart(ix) == E_OK)
			  sel_ix = ix;
			
			if (++ ix == NCP_cTCPOutputStart)
			  ix = 0;
			} while (ix != last_ix);

		/* 次回は、処理した通信端点を後回しにする。*/
		last_ix = sel_ix;
		syslog(LOG_EMERG, "---------------waiting next-------------");
	}
}

/* #[<ENTRY_PORT>]# eTCPOutput
 * entry port: eTCPOutput
 * signature:  sTCPOutput
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eTCPOutput_output
 * name:         eTCPOutput_output
 * global_name:  tTCPOutputBody_eTCPOutput_output
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTCPOutput_output(CELLIDX idx, int8_t* outputp, int32_t size, const int8_t* dstaddr, const int8_t* srcaddr, int32_t addrlen)
{
	ER		ercd = E_OK;
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		return(E_ID);
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	T_NET_BUF *output = (T_NET_BUF*)outputp;
	if((is_cIPv4Output_joined()) && (output->off.protocolflag & FLAG_USE_IPV4)){
		T_IN4_ADDR dst = *((T_IN4_ADDR *)dstaddr);
		T_IN4_ADDR src = *((T_IN4_ADDR *)srcaddr);
		cIPv4Output_setHeader(output, size, dst, src );
		T_TCP_HDR *tcph =GET_TCP_HDR(output,output->off.ifhdrlen + output->off.iphdrlenall);
		tcph->sum = cIPv4CheckSum_ipv4CheckSum( outputp,size,output->off.ifhdrlen + output->off.iphdrlenall, IPPROTO_TCP );
		return cIPv4Output_IPv4Output(outputp, size, TMO_TCP_OUTPUT);
	}

	return E_ID;
	
}

/* #[<ENTRY_FUNC>]# eTCPOutput_getOffset
 * name:         eTCPOutput_getOffset
 * global_name:  tTCPOutputBody_eTCPOutput_getOffset
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTCPOutput_getOffset(CELLIDX idx, T_OFF_BUF* offset)
{
	ER		ercd = E_OK;
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		return(E_ID);
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	offset->tphdrlen = TCP_HDR_SIZE;

	if((is_cIPv4Output_joined()) && (offset->protocolflag & FLAG_USE_IPV4))
	  return cIPv4Output_getOffset(offset);
	
}

/* #[<ENTRY_FUNC>]# eTCPOutput_getIPv4Address
 * name:         eTCPOutput_getIPv4Address
 * global_name:  tTCPOutputBody_eTCPOutput_getIPv4Address
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_IN4_ADDR
eTCPOutput_getIPv4Address(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	if(is_cIPv4Output_joined())
	  return cIPv4Output_getIPv4Address();

}

/* #[<ENTRY_FUNC>]# eTCPOutput_respond
 * name:         eTCPOutput_respond
 * global_name:  tTCPOutputBody_eTCPOutput_respond
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTCPOutput_respond(CELLIDX idx, int8_t* outputp, int32_t size, T_TCP_CEP* cep, T_TCP_SEQ ack, T_TCP_SEQ seq, uint32_t rbfree, uint8_t flags)
{
	ER		ercd = E_OK;
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		return(E_ID);
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	
	T_IP4_HDR	*iph;
	T_TCP_HDR	*tcph;
	uint_t		win = 0;
	T_NET_BUF *output = (T_NET_BUF*)outputp;

	if ((flags & TCP_FLG_RST) == 0)
		win = rbfree;

	/*
	 *  output が NULL でなければ、これは入力したセグメントの
	 *  net_buf で、そのまま再利用する。
	 */
	T_IN4_ADDR	ipaddr;
	uint16_t		portno;

	
	if (cep == NULL)
	  return;
	/*
	 * IPv4 では、IP ヘッダのオプションを削除する。
	 * IPv6 では、拡張ヘッダを削除する。
	 */
	if(output->off.protocolflag & FLAG_USE_IPV4){
		
		iph  = GET_IP4_HDR(output,output->off.ifhdrlen);
		
		if (GET_IP4_HDR_SIZE(iph) > IP4_HDR_SIZE) {
			memmove((char *)iph + IP4_HDR_SIZE, GET_IP4_SDU(iph),
					(size_t)(iph->len - GET_IP4_HDR_SIZE(iph)));
			iph->vhl   = IP4_MAKE_VHL(IPV4_VERSION, IP4_HDR_SIZE >> 2);
			iph->len  -= (uint16_t)(GET_IP4_HDR_SIZE(iph) - IP4_HDR_SIZE);
			output->len -= (uint16_t)(GET_IP4_HDR_SIZE(iph) - IP4_HDR_SIZE);
		}
		output->off.iphdrlenall = IP4_HDR_SIZE;
		
		/* IP アドレスを交換する。*/
		ipaddr = iph->src;
		iph->src = iph->dst;
		iph->dst = ipaddr;
		
		
		/* TCP SDU 長を 0 にする。*/
		SET_IP4_SDU_SIZE(iph, TCP_HDR_SIZE);
	}
	
	tcph = GET_TCP_HDR(output, output->off.ifhdrlen + output->off.iphdrlen);
	
	/* ポート番号を交換する。*/
	portno = tcph->sport;
	tcph->sport = tcph->dport;
	tcph->dport = portno;
	
	/* TCP ヘッダに情報を設定する。*/
	tcph->doff = TCP_MAKE_DATA_OFF(TCP_HDR_SIZE);
	output->off.tphdrlenall = TCP_HDR_SIZE;
	   
	tcph->seq   = htonl(seq);
	tcph->ack   = htonl(ack);
	tcph->win   = htons(win);
	tcph->flags = flags;
	tcph->urp   = tcph->sum = 0;

	/*
	 *  チェックサムを設定する。
	 */
	if(output->off.protocolflag & FLAG_USE_IPV4){

		iph  = GET_IP4_HDR(output, output->off.ifhdrlen);
		
		/* ネットワークバッファ長を調整する。*/
		output->len = output->off.ifhdrlen -output->off.ifalign+ GET_IP4_HDR_SIZE(iph)  + GET_TCP_HDR_SIZE2(output,output->off.ifhdrlen + output->off.iphdrlen);
		
		tcph->sum = cIPv4CheckSum_ipv4CheckSum( outputp,size,  output->off.ifhdrlen + output->off.iphdrlen, IPPROTO_TCP);

		/* ネットワーク層 (IP) の出力関数を呼び出す。*/
		if(is_cIPv4Output_joined())
		  return cIPv4Output_IPv4Reply(outputp,size,TMO_TCP_OUTPUT);
	}
	
	return E_ID;
	
}

/* #[<ENTRY_FUNC>]# eTCPOutput_allocAndRespond
 * name:         eTCPOutput_allocAndRespond
 * global_name:  tTCPOutputBody_eTCPOutput_allocAndRespond
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eTCPOutput_allocAndRespond(CELLIDX idx, const int8_t* dstaddr, const int8_t* srcaddr, int32_t addrlen, uint16_t dstport, uint16_t srcport, T_TCP_SEQ ack, T_TCP_SEQ seq, uint32_t rbfree, uint8_t flags, T_OFF_BUF offset)
{
	ER		ercd = E_OK;
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		return(E_ID);
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	T_IP4_HDR	*iph;
	T_TCP_HDR	*tcph;
	uint_t		win = 0;
	int32_t ipoff = offset.iphdrlen + offset.ifhdrlen;
	T_NET_BUF *output;

	if ((flags & TCP_FLG_RST) == 0)
		win = rbfree;


	if(cIPv4Output_IPv4Output_outputp_alloc( (void**)&output, TCP_HDR_SIZE,TMO_TCP_GET_NET_BUF ) != E_OK)
	  return E_ID;
	
	//offset情報のセット
	output->off = offset;
	output->off.iphdrlenall = output->off.tphdrlenall = 0;
	
	tcph = GET_TCP_HDR(output, ipoff);
	flags |= TCP_FLG_ACK;

	/* TCP ヘッダに情報を設定する。*/
	tcph->sport	= htons(srcport);
	tcph->dport	= htons(dstport);
	tcph->doff	= TCP_MAKE_DATA_OFF(TCP_HDR_SIZE);
	tcph->sum   = 0;
	tcph->seq   = htonl(seq);
	tcph->ack   = htonl(ack);
	tcph->win   = htons(win);
	tcph->flags = flags;
	tcph->urp   = tcph->sum = 0;

	/*
	 *  チェックサムを設定する。
	 */
	if((offset.protocolflag & FLAG_USE_IPV4) && is_cIPv4Output_joined()) {

		iph  = GET_IP4_HDR(output,offset.ifhdrlen);
		
		/* ネットワークバッファ長を調整する。*/
		output->len = ipoff -output->off.ifalign +  GET_TCP_HDR_SIZE2(output,ipoff);
		int32_t len = output->len+sizeof(T_NET_BUF) -4 + output->off.ifalign;

		T_IN4_ADDR dst = *((T_IN4_ADDR *)dstaddr);
		T_IN4_ADDR src = *((T_IN4_ADDR *)srcaddr);
		cIPv4Output_setHeader(output,len, dst, src );
		
		tcph->sum = cIPv4CheckSum_ipv4CheckSum( output,len, ipoff, IPPROTO_TCP );
		
		/* ネットワーク層 (IP) の出力関数を呼び出す。*/
		return cIPv4Output_IPv4Output(output,len,TMO_TCP_OUTPUT );
	}
	
	return E_ID;
}

/* #[<ENTRY_PORT>]# eCallTimerFunction
 * entry port: eCallTimerFunction
 * signature:  sCallTimerFunction
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eCallTimerFunction_callFunction
 * name:         eCallTimerFunction_callFunction
 * global_name:  tTCPOutputBody_eCallTimerFunction_callFunction
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eCallTimerFunction_callFunction(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	int_t		cix;

	for (cix = NCP_cTCPOutputStart; cix -- > 0; ) {
		cTCPOutputStart_timerFunction( cix );
	}

	int_t iss;
	iss = cTCPFunctions_getTcpIss();
	
	if (iss != 0) {
		cTCPFunctions_setTcpIss(iss + ((T_TCP_SEQ)122*1024 + (((T_TCP_SEQ)netRand() >> 14) & 0x3ffff)) / TCP_SLOW_HZ);
	}
	
	cNetworkTimer_Timeout(5);//500ms間隔で呼び出されるタイマ関数

}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
