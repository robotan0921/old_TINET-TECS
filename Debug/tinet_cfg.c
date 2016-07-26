/* tinet_cfg.c */

#include <kernel.h>
#include <sil.h>
#include "kernel_cfg.h"
#include "tinet_cfg.h"
#include <tinet_defs.h>
#include <tinet_config.h>
#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <netinet/in.h>
#include <netinet/in_var.h>
#include <netinet/in_itron.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/tcp_fsm.h>
#include <netinet/udp_var.h>



/*
 *  Include Directives (#include)
 */

#include "gr_peach.h"
#include "target_timer.h"
#include "sample1n.h"
#include "tTask_tecsgen.h"
#include "tISR_tecsgen.h"
#include "tInitializeRoutine_tecsgen.h"
#include "tTerminateRoutine_tecsgen.h"
#include "sample1.h"
#include <itron.h>
#include <tinet_defs.h>
#include <tinet_config.h>
#include <net/if.h>
#include <net/if_ppp.h>
#include <net/if_loop.h>
#include <net/ethernet.h>
#include <net/if_arp.h>
#include <net/net.h>
#include <net/net_buf.h>
#include <net/net_timer.h>
#include <net/ppp_var.h>
#include <net/ether_var.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <netinet/ip_var.h>
#include <netinet/tcp.h>
#include <netinet/tcp_timer.h>
#include <netinet/tcp_var.h>
#include <netinet/udp_var.h>
#include <netinet6/in6.h>
#include <netinet6/ip6_var.h>
#include "device.h"
#include "tinet_target_config.h"
#include "sample1n.h"

#define TNUM_TCP_REPID	1

const ID tmax_tcp_repid = (TMIN_TCP_REPID + TNUM_TCP_REPID - 1);

T_TCP_REP tcp_rep[TNUM_TCP_REPID] = {
	{
		0,
		{ IPV4_ADDRANY, 23 },
#if defined(TCP_CFG_EXTENTIONS)
		TCP_REP_FLG_VALID,
		SEM_TCP_REP_LOCK1,
#endif
		},
	};

#define TNUM_TCP_CEPID	1

const ID tmax_tcp_cepid = (TMIN_TCP_CEPID + TNUM_TCP_CEPID - 1);

T_TCP_CEP tcp_cep[TNUM_TCP_CEPID] = {
	{
		0,
		(void*)tcp_swbuf,
		TCP_SWBUF_SIZE,
		(void*)tcp_rwbuf,
		TCP_RWBUF_SIZE,
		(t_tcp_callback)(FP)(FP)callback_nblk_tcp,
		TCP_CEP_FLG_VALID,
		SEM_TCP_CEP_LOCK1,
		FLG_TCP_CEP_EST1,
		FLG_TCP_CEP_SND1,
		FLG_TCP_CEP_RCV1,
		},
	};
