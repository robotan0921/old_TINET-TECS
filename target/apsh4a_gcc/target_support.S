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
 *    (b) �����ۤη��֤��̤�������ˡ�ˤ�äơ�TOPPERS�ץ��������Ȥ�
 *        ��𤹤뤳�ȡ�
 *  (4) �ܥ��եȥ����������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������뤤���ʤ�»
 *      ������⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ����դ��뤳�ȡ�
 *      �ޤ����ܥ��եȥ������Υ桼���ޤ��ϥ���ɥ桼������Τ����ʤ���
 *      ͳ�˴�Ť����ᤫ��⡤�嵭����Ԥ����TOPPERS�ץ��������Ȥ�
 *      ���դ��뤳�ȡ�
 * 
 *  �ܥ��եȥ������ϡ�̵�ݾڤ��󶡤���Ƥ����ΤǤ��롥�嵭����Ԥ�
 *  ���TOPPERS�ץ��������Ȥϡ��ܥ��եȥ������˴ؤ��ơ�����λ�����Ū
 *  ���Ф���Ŭ������ޤ�ơ������ʤ��ݾڤ�Ԥ�ʤ����ޤ����ܥ��եȥ���
 *  �������Ѥˤ��ľ��Ū�ޤ��ϴ���Ū�������������ʤ�»���˴ؤ��Ƥ⡤��
 *  ����Ǥ�����ʤ���
 * 
 *  @(#) $Id: target_support.S 1598 2009-06-29 09:43:33Z ertl-honda $
 */

/*
 *  �������åȰ�¸�⥸�塼�� ������֥��������APSH4A��
 */

#define  TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t�����������ޥ��� */
#define ULONG_C(val)	(val)		/* ulong_t�����������ޥ��� */
#include "kernel_impl.h"

/*
 *  ���٥�Υ������åȰ�¸�ν����
 *
 *  �������ȥ��åץ⥸�塼�����ǡ�����ν���������˸ƤӽФ���롥
 */
    .text
    .globl _hardware_init_hook
_hardware_init_hook:
#ifdef ROM_BOOT
	/*
	 * ���ꥢ3��DDR���֤ˤ���¾��LBSC���֤�����
	 */
	mov.l _lbsc_mmselr_addr, r1
	mov.l _lbsc_mmselr_val, r2
	mov.l r2, @r1

	/*
	 * �ե�å�����������(CS0)
	 */
	mov.l _lbsc_cs0bcr_addr, r1
	mov.l _lbsc_cs0bcr_val, r2
	mov.l r2, @r1
	mov.l _lbsc_cs0wcr_addr, r1
	mov.l _lbsc_cs0wcr_val, r2
	mov.l r2, @r1

	/*
	 *  DDR SDRAM 
     *  256Mbit(16Mx16bit) :CL=2.5, 8192REFA @ 64mS MCLK=160MHz@6.25nS
 	 */
	/*
	 *  DDR Dummy Read
	 */
	mov.l _ddr_base_addr, r1
	mov.l @r1, r2
	/*
	 *  dummy write for Little endian
	 */
	mov.l _ddr_dmwr_l_addr, r1
	mov.l _ddr_dmwr_l_val,  r2
	mov.l r2, @r1

	/*
	 *  DCE=1:DDR,DLL=1 enable,!**BANK CLOSE MODE**!
	 */
	mov.l _ddrif_min_h_addr, r1
	mov.l _ddrif_min_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_min_l_addr, r1
	mov.l _ddrif_min_l_val, r2
	mov.l r2, @r1

	/*
	 *  SPLIT=3:16Mx16bit	
	 */
	mov.l _ddrif_sdr_h_addr, r1
	mov.l _ddrif_sdr_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_sdr_l_addr, r1
	mov.l _ddrif_sdr_l_val, r2
	mov.l r2, @r1

	/*
	 *   WR  =0:W-R min cycle 3,RW=0:R-W min cycle 3
     *    SRFC=:12cycle=75.0nS, Trfc=72nS
     *    SWR =: 3cycle=18.7nS, Twr =15nS
     *    SRRD=: 2cycle=12.5nS, Trrd=12nS
     *    SRAS=: 7cycle=43.7nS, Tras=42nS
     *    SRC =:10cycle=62.5nS, Trc =60nS
     *    SCL =0: CL=2.5 only
     *    SRCD=: 3cycle=18.7nS, Trcd=18nS
     *    SRP =: 3cycle=18.7nS, Trp =18nS
	 */
	mov.l _ddrif_str_h_addr, r1
	mov.l _ddrif_str_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_str_l_addr, r1
	mov.l _ddrif_str_l_val, r2
	mov.l r2, @r1	

	/*
	 *  DESELECT command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2,r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_3, r2
	mov.l r2, @r1	

	/*
	 *  PREALL   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2,r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_2, r2
	mov.l r2, @r1	

	/*
	 *  DDR-EMRS write
	 */
	mov.l _ddr_sdmr1_addr, r1          
	mov.l _ddr_sdmr1_val, r2
	mov.w r2, @r1

	/*
	 *  DDR-MRS write
	 */
	mov.l _ddr_sdmr2_addr, r1
	mov.l _ddr_sdmr2_val, r2
	mov.w r2, @r1	
    
	/*
	 *  PREALL   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2, r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_2, r2
	mov.l r2, @r1	

	/*
	 *  REFA 1   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2, r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_4, r2
	mov.l r2, @r1	

	/*
	 *  REFA 2   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2, r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_4, r2
	mov.l r2, @r1	

	/*
	 *  DDR-MRS write
	 */
	mov.l _ddr_sdmr3_addr, r1
	mov.l _ddr_sdmr3_val, r2
	mov.w r2, @r1	

	/*
	 *  RMODE=0:Auto Reflesh
	 *  DRI=4E1cyc:4E1x6.25ns=7.8uS, 64mS/8192REFA=7.81uS
	 *  DRE=1:refresh enable,DLLEN=1:DLL enable
	 *  DCE=1:DDR controller enable
	 */
	mov.l _ddrif_min_h_addr, r1
	mov.l _ddrif_min_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_min_l_addr, r1
	mov.l _ddrif_min_l_val, r2
	mov.l r2, @r1

	/*
	 *  waiting for MCLK200cycle(=1.25uS)
	 */
	mov.l _loop_from, r1
	mov.l _loop_dec,  r2
_loop:
	add    r2, r1		
	cmp/pl r1
	bt     _loop

	/*
	 *  NORMAL   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2,r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_0, r2
	mov.l r2, @r1
	
#endif

	mov.l _ccr_addr, r1
	mov.l _ccr_disable, r2
	mov.l r2, @r1
	mov.l _ccr_mode, r2
	mov.l r2, @r1
	
    rts
     nop


    .align 4
#ifdef ROM_BOOT
_lbsc_mmselr_addr:
	.long LBSC_MMSELR
_lbsc_mmselr_val:
	.long 0xa5a50000

_lbsc_cs0bcr_addr:
	.long LBSC_CS0BCR
_lbsc_cs0bcr_val:
	.long 0x00000000
_lbsc_cs0wcr_addr:
	.long LBSC_CS0WCR
_lbsc_cs0wcr_val:
	.long 0x00020005

_ddr_base_addr:
	.long DDR_BASE_ADDR

_ddr_dmwr_l_addr:
	.long DDR_DMWR_L
_ddr_dmwr_l_val:
	.long 0xa5000000

_ddrif_min_h_addr:
	.long DDRIF_MIM_H
_ddrif_min_h_val:
	.long 0x00004000
_ddrif_min_l_addr:
	.long DDRIF_MIM_L
_ddrif_min_l_val:
	.long 0x04e10209
_ddrif_sdr_h_addr:
	.long DDRIF_SDR_H
_ddrif_sdr_h_val:
	.long 0x00000000
_ddrif_sdr_l_addr:
	.long DDRIF_SDR_L
_ddrif_sdr_l_val:
	.long 0x00000300
_ddrif_str_h_addr:
	.long DDRIF_STR_H
_ddrif_str_h_val:
	.long 0x00000000
_ddrif_str_l_addr:
	.long DDRIF_STR_L
_ddrif_str_l_val:
	.long 0x00003180

_ddrif_scr_h_addr:
	.long DDRIF_SCR_H
_ddrif_scr_l_addr:
	.long DDRIF_SCR_L

_ddrif_scr_l_val_0:
	.long 0x00000000
_ddrif_scr_l_val_2:
	.long 0x00000002
_ddrif_scr_l_val_3:
	.long 0x00000003
_ddrif_scr_l_val_4:
	.long 0x00000004

_ddr_sdmr1_addr:
	.long DDR_SDMR1
_ddr_sdmr1_val:
	.long  0x0000
_ddr_sdmr2_addr:
	.long DDR_SDMR2
_ddr_sdmr2_val:
	.long  0x0000
_ddr_sdmr3_addr:
	.long DDR_SDMR3
_ddr_sdmr3_val:
	.long  0x0000

_loop_from:
	.long 200
_loop_dec:
	.long   -1	
	
#endif
_ccr_addr:
	.long CCR
_ccr_disable:
	.long CCR_DISABLE
_ccr_mode:
	.long CCR_MODE