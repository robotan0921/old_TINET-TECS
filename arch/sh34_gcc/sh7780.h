/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  �嵭����Ԥϡ��ʲ���(1)��(4)�ξ������������˸¤ꡤ�ܥ��եȥ���
 *  �����ܥ��եȥ���������Ѥ�����Τ�ޤࡥ�ʲ�Ʊ���ˤ���ѡ�ʣ������
 *  �ѡ������ۡʰʲ������ѤȸƤ֡ˤ��뤳�Ȥ�̵���ǵ������롥
 *  (1) �ܥ��եȥ������򥽡��������ɤη������Ѥ�����ˤϡ��嵭������
 *      ��ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ��꤬�����Τޤޤη��ǥ���
 *      ����������˴ޤޤ�Ƥ��뤳�ȡ�
 *  (2) �ܥ��եȥ������򡤥饤�֥������ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ�����Ǻ����ۤ�����ˤϡ������ۤ�ȼ���ɥ�����ȡ�����
 *      �ԥޥ˥奢��ʤɡˤˡ��嵭�����ɽ�����������Ѿ�浪��Ӳ���
 *      ��̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *  (3) �ܥ��եȥ������򡤵�����Ȥ߹���ʤɡ�¾�Υ��եȥ�������ȯ�˻�
 *      �ѤǤ��ʤ����Ǻ����ۤ�����ˤϡ����Τ����줫�ξ�����������
 *      �ȡ�
 *    (a) �����ۤ�ȼ���ɥ�����ȡ����Ѽԥޥ˥奢��ʤɡˤˡ��嵭����
 *        �ɽ�����������Ѿ�浪��Ӳ�����̵�ݾڵ����Ǻܤ��뤳�ȡ�
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: sh7780.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *  SH7780�Υϡ��ɥ������񸻤����
 */

#ifndef TOPPERS_SH7780_H
#define TOPPERS_SH7780_H

#include <sil.h>

/*
 *  �㳰���٥�ȥ쥸����
 */
#define TRA         0xff000020
#define EXPEVT      0xff000024
#define INTEVT      0xff000028

/*
 *   �Х����ơ��ȥ���ȥ����Ϣ
 */
#define RFCR        0xff800028   /* H */

#define RFCR_CLEAR  0xa400

/*
 *  �����ߤˤ�ä� INTEVT �쥸���������ꤵ�����
 */
//#define TMU0_INTEVT         UINT_C(0x580) //change
#define TMU0_INTEVT         UINT_C(0x400)
#define SCIF0_RXI_INTEVT    UINT_C(0x720)
#define SCIF0_TXI_INTEVT    UINT_C(0x760)
#define SCIF0_BRI_INTEVT    UINT_C(0x740)
#define SCIF1_RXI_INTEVT    UINT_C(0xBA0)
#define SCIF1_TXI_INTEVT    UINT_C(0xBE0)
#define SCIF1_BRI_INTEVT    UINT_C(0xBC0)
//#ifndef IRQ0_INTEVT//tecs�Ѥ˥����ȥ�����
//#define IRQ0_INTEVT         UINT_C(0x200)
//#endif


/*
 *  IRC��Ϣ�Υ쥸����
 */
#define ICR0     UINT_C(0xFE410000) /* W */
#define ICR1     UINT_C(0xFE41001C) /* W */
#define INTPRI   UINT_C(0xFE410010) //add 11/07/29
#define C0INTMSK0 UINT_C(0xFE410030)
#define C0INTMSKCLR0 UINT_C(0xFE410050)
#define ICR0_ENABLE UINT_C(0x00C00000)
#define INTREQ UINT_C(0xFE410024)

#define INT2PRI0 UINT_C(0xFE410800) /* W */
#define INT2PRI1 UINT_C(0xFE410804) /* W */
#define INT2PRI2 UINT_C(0xFE410808) /* W */
#define INT2PRI3 UINT_C(0xFE41080C) /* W */
#define INT2PRI4 UINT_C(0xFE410810) /* W */
#define INT2PRI5 UINT_C(0xFE410814) /* W */
#define INT2PRI6 UINT_C(0xFE410818) /* W */
#define INT2PRI7 UINT_C(0xFE41081C) /* W */

//#define INT2MSKR  UINT_C(0xFFD40038 ) //change
#define INT2MSKR  UINT_C(0xFE410A24) 
//#define INT2MSKCR UINT_C(0xFFD4003C) //change
#define INT2MSKCR UINT_C(0xFE410A34)

#define IRQ_LOWLEVEL    UINT_C(0x02)
#define IRQ_POSEDGE     UINT_C(0x01)
#define IRQ_NEGEDGE     UINT_C(0x00)

/*
 * �����ޡ��쥸����
 */
#define TMU_TOCR   UINT_C(0xffd80000)  /* B */
#define TMU_TSTR   UINT_C(0xffd80004)  /* B */
#define TMU_TCOR0  UINT_C(0xffd80008)  /* W */
#define TMU_TCNT0  UINT_C(0xffd8000c)  /* W */
#define TMU_TCR0   UINT_C(0xffd80010)  /* H */
#define TMU_TCOR1  UINT_C(0xffd80014)  /* W */
#define TMU_TCNT1  UINT_C(0xffd80018)  /* W */
#define TMU_TCR1   UINT_C(0xffd8001c)  /* H */
#define TMU_TCOR2  UINT_C(0xffd80020)  /* W */
#define TMU_TCNT2  UINT_C(0xffd80024)  /* W */
#define TMU_TCR2   UINT_C(0xffd80028)  /* H */

#define TMU_STR0   UINT_C(0x01)
#define TMU_STR1   UINT_C(0x02)
#define TMU_STR2   UINT_C(0x04)
#define TCR_UNF    UINT_C(0x0100)    

/*
 *  FIFO�դ����ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCIF)�쥸����
 */
//#define SH_SCIF0_BASE UINT_C(0xFFE00000) // change
#define SH_SCIF0_BASE UINT_C(0xFFEA0000)
#define SH_SCIF1_BASE UINT_C(0xFFEB0000)

/*
 *  GPIO��Ϣ�쥸����
 */
//#define GPIO_PHCP UINT_C(0xFFEA000E) /* H */ // change
#define GPIO_PHCP UINT_C(0xFFCC000E) /* H */
//#define GPIO_PHCP_SCIF0_ENABLE (~UINT_C(0x007F)) //change
#define GPIO_PHCP_SCIF0_ENABLE UINT_C(0xFC00)
#define GPIO_PGCP UINT_C(0xFFCC000C) /* G */ //change
#define GPIO_PGCP_LED_ENABLE UINT_C(0xD7FF) //change
#define GPIO_PGDP UINT_C(0xFFCC002C) //change


/*
 *  ����å�������쥸����
 */
#define CCR           UINT_C(0xff00001c)   /* W */
#define CCR_DISABLE   UINT_C(0x00000808)  /* ����å���̵�� */

/*
 *  ������Х����ơ��ȥ���ȥ����Ϣ
 */
#define LBSC_MMSELR UINT_C(0xff400020) /* W */
#define LBSC_CS0BCR UINT_C(0xff802000) /* W */
#define LBSC_CS0WCR UINT_C(0xff802008) /* W */

#endif /* TOPPERS_SH7780_H */
