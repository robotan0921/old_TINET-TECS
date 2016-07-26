/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tRelTest_template.c => src/tRelTest.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * Don't edit the comments between #[<...>]# and #[</...>]#
 * These comment are used by tecsmerege when merging.
 *
 * call port function #_TCPF_#
 * call port : cUDPAPI4  signature: sUDPCEPAPI4 context: task
 *   ER_UINT        cUDPAPI4_send( const int8_t* data, int32_t len, T_IN4_ADDR dstaddr, uint16_t dstport, TMO tmout );
 *   ER_UINT        cUDPAPI4_receive( int8_t* data, int32_t len, TMO tmout );
 *   ER             cUDPAPI4_cancelSend( ER error );
 *   ER             cUDPAPI4_cancelReceive( ER error );
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tRelTest_tecsgen.h"

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
 * global_name:  tRelTest_eBody_main
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eBody_main()
{

	cUDPAPI4_cancelSend(E_OK);

	
}

/* #[<POSTAMBLE>]#
 *   Put non-entry functions below.
 * #[</POSTAMBLE>]#*/