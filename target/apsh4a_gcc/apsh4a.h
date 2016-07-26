/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel  
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: apsh4a.h 1598 2009-06-29 09:43:33Z ertl-honda $
 */

/*
 *  APSH4A CPU�ܡ��ɤΤΥϡ��ɥ������񸻤����
 */

#ifndef TOPPERS_APSH4A_H
#define TOPPERS_APSH4A_H

#include <sil.h>

/*
 *  �ץ��å��Υϡ��ɥ������񸻤�����Υ��󥯥롼��
 */
#include "sh34_gcc/sh7780.h"

/*
 *  ��¢���ե���å� P = 33.333MHz
 */
//#define	PCLOCK			33333000
#define	PCLOCK			44444000

/*
 *  DDR��Ƭ���ɥ쥹
 */
#define	DDR_BASE_ADDR	0x0c000000

/*
 *  DDR��Ϣ�Υ쥸����
 */
#define DDR_DMWR_B	0xfe800604		/* dummy write for big endian */
#define DDR_DMWR_L	0xfe800600		/* dummy write for little endian */
#define DDR_SDMR1	0xFEC02000		/* EMRS reg : DLL enable - BA0:1,A1=A0=0 */
#define DDR_SDMR2	0xFEC00b08		/* MRS  reg : BurtsLength=2,BurstSequence=Sequencial,CL=2.5,DLL=reset */
#define DDR_SDMR3	0xFEC00308		/* MRS  reg : BurtsLength=2,BurstSequence=Sequencial,CL=2.5,DLL=mormal */

#define DDRIF_MIM_H	0xFE800008		/* DDRIF MIM register */
#define DDRIF_MIM_L	0xFE80000c		/* DDRIF MIM register */
#define DDRIF_SDR_H	0xFE800030		/* DDRIF SDR register */
#define DDRIF_SDR_L	0xFE800034		/* DDRIF SDR register */
#define DDRIF_STR_H	0xFE800018		/* DDRIF STR register */
#define DDRIF_STR_L	0xFE80001c		/* DDRIF STR register */
#define DDRIF_SCR_H	0xFE800010		/* DDRIF SCR register */
#define DDRIF_SCR_L	0xFE800014		/* DDRIF SCR register */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  ��ȯ�Ķ���¸�ν���
 */
Inline void
apsh4a_exit(void)
{
    uint32_t sr = 0x10000000U;
    
    /*
     * ����Ū�˥ꥻ�åȤ�ȯ��������
     */
    /*
     * BL�ӥåȤ�Ω�Ƥ�
     */
    Asm("ldc %0, sr" : : "r"(sr) );
    
    /*
     * ������㳰
     */
    *((volatile int *) 0xFFFFFEC1U) = 0;
} 
#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_APSH4A_H */
