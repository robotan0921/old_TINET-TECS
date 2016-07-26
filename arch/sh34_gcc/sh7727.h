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
 *  @(#) $Id: sh7727.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *  SH7727�Υϡ��ɥ������񸻤����
 */

#ifndef TOPPERS_SH7727_H
#define TOPPERS_SH7727_H

#include <sil.h>

/*
 *  �㳰���٥�ȥ쥸����
 */
#define TRA           0xFFFFFFD0
#define EXPEVT        0xFFFFFFD4        
#define INTEVT        0xFFFFFFD8        
#define INTEVT2       0xA4000000

/*
 *   �Х����ơ��ȥ���ȥ����Ϣ
 */
#define RFCR          0xffffff74    /* H */
#define RFCR_CLEAR        0xa400

/*
 * �����ߤˤ�ä�INTEVT2�쥸���������ꤵ�����
 */
#define TMU0_INTEVT        0x400
#define IRQ0_INTEVT        0x600
#define SCI_RXI_INTEVT     0x500
#define SCI_TXI_INTEVT     0x520
#define SCI_BRI_INTEVT     0x4ed
#define PINT0_7_INTEVT     0x700
#define PINT8_15_INTEVT    0x720
#define SCI1_RXI_INTEVT    0x8a0
#define SCI1_TXI_INTEVT    0x8e0
#define SCI1_BRI_INTEVT    0x8c0
#define SCIF_RXI_INTEVT    0x920
#define SCIF_TXI_INTEVT    0x960
#define SCIF_BRI_INTEVT    0x940

/*
 * �����ߥ���ȥ���쥸������
 */
#define ICR0    0xfffffee0    /* H */
#define ICR1    0xa4000010    /* H */
#define ICR2    0xa4000012    /* H */
#define PINTER  0xa4000014    /* H */
#define IPRA    0xfffffee2    /* H */
#define IPRB    0xfffffee4    /* H */
#define IPRC    0xa4000016    /* H */
#define IPRD    0xa4000018    /* H */
#define IPRE    0xa400001a    /* H */
#define IPRF    0xa4000220    /* H */
#define IPRG    0xa4000222    /* H */
#define IRR0    0xa4000004    /* B */
#define IRR1    0xa4000006    /* B */
#define IRR2    0xa4000008    /* B */

#define ICR2_PINT7S     0x80
#define ICR2_PINT6S     0x40
#define PINTER_PINT7E   0x80
#define PINTER_PINT6E   0x40

#define IRQ_LOWLEVEL    0x2    
#define IRQ_POSEDGE     0x1
#define IRQ_NEGEDGE     0x0

/*
 * �����ޡ��쥸����
 */
#define TMU_TOCR   0xfffffe90  /* B */
#define TMU_TSTR   0xfffffe92  /* B */
#define TMU_TCOR0  0xfffffe94  /* W */
#define TMU_TCNT0  0xfffffe98  /* W */
#define TMU_TCR0   0xfffffe9c  /* H */
#define TMU_TCOR1  0xfffffea0  /* W */
#define TMU_TCNT1  0xfffffea4  /* W */
#define TMU_TCR1   0xfffffea8  /* H */
#define TMU_TCOR2  0xfffffeac  /* W */
#define TMU_TCNT2  0xfffffeb0  /* W */
#define TMU_TCR2   0xfffffeb4  /* H */

#define TMU_STR0   0x01
#define TMU_STR1   0x02
#define TMU_STR2   0x04
#define TCR_UNF    0x0100    

/*
 *  ���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCI)
 */
#define SCI_SCSMR    0xfffffe80  /* B */
#define SCI_SCBRR    0xfffffe82  /* B */
#define SCI_SCSCR    0xfffffe84  /* B */
#define SCI_SCTDR    0xfffffe86  /* B */
#define SCI_SCSSR    0xfffffe88  /* B */
#define SCI_SCRDR    0xfffffe8a  /* B */

/*
 *  ���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCI)��
 *  �ݡ���SC����ȥ���/�ǡ����쥸����
 *  SH7709�ڤ�SH7709A�Τ�
 */
#define SCPDR     0xa4000136   /* B */
#define SCPCR     0xa4000116   /* H */

/*
 *  ���ꥢ�륳�ߥ�˥�������󥤥󥿡��ե�����(SCI)��
 *  ���ꥢ��ݡ��ȥ쥸����
 *  SH7708�Τ�
 */
#define SCSPTR      0xffffff7c  /* H */

#define SCSMR_CHR     0x0040
#define SCSMR_PE      0x0020
#define SCSMR_OE      0x0010
#define SCSMR_STOP    0x0008
#define SCSMR_CKS1    0x0002
#define SCSMR_CKS0    0x0001

#define SCSCR_TIE     0x0080
#define SCSCR_RIE     0x0040
#define SCSCR_TE      0x0020
#define SCSCR_RE      0x0010
#define SCSCR_CKE1    0x0002
#define SCSCR_CKE0    0x0001

#define SCSSR_TDRE    0x80
#define SCSSR_RDRF    0x40
#define SCSSR_ORER    0x20
#define SCSSR_FER     0x10
#define SCSSR_PER     0x08
#define SCSSR_TEND    0x04
#define SCSSR_MPB     0x02
#define SCSSR_MPBT    0x01

/*
 * ����å�������쥸����
 */
#define CCR           0xffffffec   /* W */
#define CCR_DISABLE   0x00000008   /* ����å����̵���� */

#endif /* TOPPERS_SH7727_H */
