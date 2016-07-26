/* kernel_cfg.h */
#ifndef TOPPERS_KERNEL_CFG_H
#define TOPPERS_KERNEL_CFG_H

#define TNUM_TSKID	13
#define TSKID_tTask_LogTask_Task	1
#define TASK1	2
#define TASK2	3
#define MAIN_TASK	4
#define EXC_TASK	5
#define IF_MBED_PHY_TASK	6
#define NET_TIMER_TASK	7
#define ETHER_OUTPUT_TASK	8
#define ETHER_INPUT_TASK	9
#define TCP_OUTPUT_TASK	10

#define TNUM_SEMID	17
#define SEMID_tSemaphore_SerialPort1_ReceiveSemaphore	1
#define SEMID_tSemaphore_SerialPort1_SendSemaphore	2
#define SEM_IF_MBED_SBUF_READY	3
#define SEM_IF_MBED_RBUF_READY	4
#define SEM_CALL_OUT_LOCK	5
#define SEM_CALL_OUT_TIMEOUT	6
#define SEM_IP2STR_BUFF_LOCK	7
#define SEM_MAC2STR_BUFF_LOCK	8
#define SEM_ARP_CACHE_LOCK	9
#define SEM_IP4_FRAG_QUEUE	10
#define SEM_IN_ROUTING_TBL	11
#define SEM_TCP_POST_OUTPUT	12
#define SEM_TCP_CEP	13
#define SEM_TCP_SYSLOG	14
#define SEM_NET_SEND	15
#define SEM_TCP_REP_LOCK1	16
#define SEM_TCP_CEP_LOCK1	17

#define TNUM_FLGID	3
#define FLG_TCP_CEP_EST1	1
#define FLG_TCP_CEP_SND1	2
#define FLG_TCP_CEP_RCV1	3

#define TNUM_DTQID	1
#define DTQ_ETHER_OUTPUT	1

#define TNUM_PDQID	0

#define TNUM_MTXID	0

#define TNUM_MPFID	7
#define MPF_NET_BUF_64	1
#define MPF_NET_BUF_128	2
#define MPF_NET_BUF_256	3
#define MPF_NET_BUF_512	4
#define MPF_NET_BUF_1024	5
#define MPF_NET_BUF_IF_PDU	6
#define MPF_NET_BUF_REASSM	7

#define TNUM_CYCID	2
#define CYCHDR1	1
#define NET_TIMER_HANDLER	2

#define TNUM_ALMID	1

#define TNUM_ISRID	3
#define ISRID_tISR_SIOPortTarget1_RxISRInstance	1
#define ISRID_tISR_SIOPortTarget1_TxISRInstance	2
#define INTNO1_ISR	3

#endif /* TOPPERS_KERNEL_CFG_H */
