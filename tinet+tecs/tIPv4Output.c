/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tIPv4Output_template.c => src/tIPv4Output.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * Don't edit the comments between #[<...>]# and #[</...>]#
 * These comment are used by tecsmerege when merging.
 *
 * attr access macro #_CAAM_#
 * fragId           uint16_t         VAR_fragId      
 *
 * call port function #_TCPF_#
 * call port : cEthernetOutput  signature: sEthernetOutput context: task
 *   ER             cEthernetOutput_ethernetOutput( int8_t* outputp, int32_t size, T_IN4_ADDR dstaddr, TMO tmout );
 * call port : cFunctions  signature: sIPv4Functions context: task
 *   uint16_t       cFunctions_checkSum( const int8_t* data, uint32_t len );
 *   T_IN4_ADDR     cFunctions_getIPv4Address( );
 *   T_IN4_ADDR     cFunctions_getIPv4Mask( );
 * call port : cRoutingTable  signature: sIPv4RoutingTable context: task
 *   T_IN4_ADDR     cRoutingTable_routeAlloc( T_IN4_ADDR dst );
 *   void           cRoutingTable_redirect( T_IN4_ADDR gateway, T_IN4_ADDR target, uint8_t flags, uint32_t tmo );
 * call port : cIPv4CheckSum  signature: sIPv4CheckSum context: task
 *   uint16_t       cIPv4CheckSum_ipv4CheckSum( int8_t* data, int32_t size, uint32_t offset, uint8_t proto );
 * allocator port for call port: cEthernetOutput func: ethernetOutput param: outputp
 *   ER             cEthernetOutput_ethernetOutput_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             cEthernetOutput_ethernetOutput_outputp_dealloc( const void* buf );
 *   ER             cEthernetOutput_ethernetOutput_outputp_reuse( void* buf );
 *   ER_UINT        cEthernetOutput_ethernetOutput_outputp_bufferSize( const void* buf );
 *   uint32_t       cEthernetOutput_ethernetOutput_outputp_bufferMaxSize( );
 * allocator port for call port: eOutput func: IPv4Output param: outputp
 *   ER             eOutput_IPv4Output_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             eOutput_IPv4Output_outputp_dealloc( const void* buf );
 *   ER             eOutput_IPv4Output_outputp_reuse( void* buf );
 *   ER_UINT        eOutput_IPv4Output_outputp_bufferSize( const void* buf );
 *   uint32_t       eOutput_IPv4Output_outputp_bufferMaxSize( );
 * allocator port for call port: eOutput func: IPv4Reply param: outputp
 *   ER             eOutput_IPv4Reply_outputp_alloc( void** buf, const int32_t minlen, TMO tmout );
 *   ER             eOutput_IPv4Reply_outputp_dealloc( const void* buf );
 *   ER             eOutput_IPv4Reply_outputp_reuse( void* buf );
 *   ER_UINT        eOutput_IPv4Reply_outputp_bufferSize( const void* buf );
 *   uint32_t       eOutput_IPv4Reply_outputp_bufferMaxSize( );
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tIPv4Output_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eOutput
 * entry port: eOutput
 * signature:  sIPv4Output
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eOutput_IPv4Output
 * name:         eOutput_IPv4Output
 * global_name:  tIPv4Output_eOutput_IPv4Output
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eOutput_IPv4Output(CELLIDX idx, int8_t* outputp, int32_t size,TMO tmout)
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


	/****IPSeC�̏���   mikan*********/

	T_IP4_HDR	*ip4h;
	T_IN4_ADDR	gw;
	T_NET_BUF *output=(T_NET_BUF *)outputp;

	/*******IP�t���O�����g�����@mikan*******/

	int32_t offset,mtu;

	uint8_t proto;
	if(output->off.protocolflag & FLAG_USE_UDP)
	  proto = IPPROTO_UDP;
	if(output->off.protocolflag & FLAG_USE_TCP)
	  proto = IPPROTO_TCP;
	if(output->off.protocolflag & FLAG_USE_ETHER)
	  mtu = ETHER_MTU;
	
	ip4h = GET_IP4_HDR(output,output->off.ifhdrlen);
	
	/* IP �w�b�_��ݒ肷�� ---------------------*/
	ip4h->vhl	= IP4_MAKE_VHL(IPV4_VERSION, IP4_HDR_SIZE >> 2);
	ip4h->len	= htons(output->len - output->off.ifhdrlen + output->off.ifalign);
	ip4h->proto	= proto;
	ip4h->ttl	= IP4_DEFTTL;
	ip4h->type	= 0;
	ip4h->id	= ip4h->flg_off = ip4h->sum = 0;


	
	/*IPheader �����܂�---------------------*/

	syslog(LOG_EMERG,"IPv4 OUTPUT dst is %d ~~~ %d",(0xFF & ip4h->dst),ip4h->dst>>24 );


	/* �f�[�^�O�����T�C�Y���l�b�g���[�N�� MTU �𒴂��Ă���΃G���[ */
	if (ntohs(ip4h->len) > mtu)
		return E_PAR;

	/* �w�b�_�𖄂߂�B*/
	ip4h->id  = htons(VAR_fragId);
	VAR_fragId ++;
	ip4h->sum = 0;
	ip4h->sum = cFunctions_checkSum((void*)ip4h, (uint_t)GET_IP4_HDR_SIZE(ip4h));
	
	gw = cRoutingTable_routeAlloc(ntohl(ip4h->dst));

	if((is_cEthernetOutput_joined()) && (output->off.protocolflag & FLAG_USE_ETHER)){
		if ((ercd = cEthernetOutput_ethernetOutput(output,size,gw,tmout )) != E_OK)
		  return ercd;
		return ercd;
	}

	eOutput_IPv4Output_outputp_dealloc((void*)outputp);
	return E_ID;
}

/* #[<ENTRY_FUNC>]# eOutput_getOffset
 * name:         eOutput_getOffset
 * global_name:  tIPv4Output_eOutput_getOffset
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eOutput_getOffset(CELLIDX idx, T_OFF_BUF* offset)
{

	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		return(E_ID);
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */

	offset->iphdrlen = IP4_HDR_SIZE;
	offset->ipmss = TCP_MSS;
	
	if(is_cEthernetOutput_joined()){//mikan ���܂�������
		offset->protocolflag |= FLAG_USE_ETHER;
		offset->ifhdrlen = ETHER_HDR_SIZE;
		offset->ifalign = NETBUFFER_ALIGN;
		return E_OK;
	}
		


	return E_ID;
}

/* #[<ENTRY_FUNC>]# eOutput_getIPv4Address
 * name:         eOutput_getIPv4Address
 * global_name:  tIPv4Output_eOutput_getIPv4Address
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_IN4_ADDR
eOutput_getIPv4Address(CELLIDX idx)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	return cFunctions_getIPv4Address();

}

/* #[<ENTRY_FUNC>]# eOutput_setHeader
 * name:         eOutput_setHeader
 * global_name:  tIPv4Output_eOutput_setHeader
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eOutput_setHeader(CELLIDX idx, int8_t* outputp, int32_t size, T_IN4_ADDR dstaddr, T_IN4_ADDR srcaddr)
{
	CELLCB	*p_cellcb;
	if (VALID_IDX(idx)) {
		p_cellcb = GET_CELLCB(idx);
	}
	else {
		/* Write error processing code here */
	} /* end if VALID_IDX(idx) */

	/* Put statements here #_TEFB_# */
	T_NET_BUF *output=(T_NET_BUF*)outputp;
	T_IP4_HDR	*ip4h = GET_IP4_HDR(output,output->off.ifhdrlen);

	/* IP �A�h���X��ݒ肷��B*/
	ip4h->dst	= htonl(dstaddr);

	if (srcaddr == IPV4_ADDRANY)
		ip4h->src = htonl(cFunctions_getIPv4Address());
	else
		ip4h->src = htonl(srcaddr);
	
	
}

/* #[<ENTRY_FUNC>]# eOutput_IPv4Reply
 * name:         eOutput_IPv4Reply
 * global_name:  tIPv4Output_eOutput_IPv4Reply
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
ER
eOutput_IPv4Reply(CELLIDX idx, int8_t* outputp, int32_t size,  TMO tmout)
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
	T_NET_BUF *output=(T_NET_BUF*)outputp;
	T_IP4_HDR	*ip4h;
	T_IN4_ADDR	gw;



	ip4h = GET_IP4_HDR(output,output->off.ifhdrlen);
	/* �w�b�_�𖄂߂�B*/
	ip4h->id  = htons(VAR_fragId);
	VAR_fragId ++;
	ip4h->sum = 0;
	ip4h->sum = cFunctions_checkSum((void*)ip4h, (uint_t)GET_IP4_HDR_SIZE(ip4h));

	syslog(LOG_EMERG,"IPv4 REPLY dst is %d ~~~ %d",(0xFF & ip4h->dst),ip4h->dst>>24 );
	
	gw = cRoutingTable_routeAlloc(ntohl(ip4h->dst));

	if((output->off.protocolflag & FLAG_USE_ETHER) && is_cEthernetOutput_joined()){
		return cEthernetOutput_ethernetOutput(outputp,size,gw,tmout );
	}

	eOutput_IPv4Reply_outputp_dealloc((void*)outputp);
}

/* #[<POSTAMBLE>]#
 *   Put non-entry functions below.
 * #[</POSTAMBLE>]#*/