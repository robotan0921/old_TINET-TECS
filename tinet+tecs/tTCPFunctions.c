/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tTCPFunctions_template.c => src/tTCPFunctions.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * tcpIss           T_TCP_SEQ        VAR_tcpIss      
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
 * require port: signature:sTINET context:task
 *   uint32_t       netRand( );
 *   void           netSrand( uint32_t speed );
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tTCPFunctions_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eTCPFunctions
 * entry port: eTCPFunctions
 * signature:  sTCPFunctions
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eTCPFunctions_getTcpIss
 * name:         eTCPFunctions_getTcpIss
 * global_name:  tTCPFunctions_eTCPFunctions_getTcpIss
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_TCP_SEQ
eTCPFunctions_getTcpIss()
{
	return VAR_tcpIss;
}

/* #[<ENTRY_FUNC>]# eTCPFunctions_setTcpIss
 * name:         eTCPFunctions_setTcpIss
 * global_name:  tTCPFunctions_eTCPFunctions_setTcpIss
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eTCPFunctions_setTcpIss(T_TCP_SEQ iss)
{
	VAR_tcpIss = iss;
}

/* #[<ENTRY_FUNC>]# eTCPFunctions_initTcpIss
 * name:         eTCPFunctions_initTcpIss
 * global_name:  tTCPFunctions_eTCPFunctions_initTcpIss
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_TCP_SEQ
eTCPFunctions_initTcpIss()
{
	SYSTIM now;

	getTime(&now);
	netSrand(now);

	VAR_tcpIss = netRand();

	return VAR_tcpIss;
}

/* #[<ENTRY_FUNC>]# eTCPFunctions_tcpRexmtValue
 * name:         eTCPFunctions_tcpRexmtValue
 * global_name:  tTCPFunctions_eTCPFunctions_tcpRexmtValue
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_TCP_TIME
eTCPFunctions_tcpRexmtValue(T_TCP_TIME srtt, T_TCP_TIME rttvar)
{
	T_TCP_TIME val;
	
	val = ((srtt >> (TCP_SRTT_SHIFT - TCP_DELTA_SHIFT)) + rttvar) >> TCP_DELTA_SHIFT;
	if (val < TCP_TVAL_MIN)
		return TCP_TVAL_MIN;
	else
		return val;
}

/* #[<ENTRY_FUNC>]# eTCPFunctions_tcpRangeSet
 * name:         eTCPFunctions_tcpRangeSet
 * global_name:  tTCPFunctions_eTCPFunctions_tcpRangeSet
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_TCP_TIME
eTCPFunctions_tcpRangeSet(T_TCP_TIME value, T_TCP_TIME tvmin, T_TCP_TIME tvmax)
{
	if ((uint32_t)value < (uint32_t)tvmin)
		return tvmin;
	else if ((uint32_t)value > (uint32_t)tvmax)
		return tvmax;
	else
		return value;
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
