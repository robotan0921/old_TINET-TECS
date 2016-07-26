/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                                  Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007      by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: start.S 1663 2009-11-04 00:32:24Z ertl-honda $
 */
        
/*
 *  �����ͥ��б��Υ������ȥ��åץ⥸�塼��(SH34��)
 */

#define TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t�����������ޥ��� */
#define ULONG_C(val)	(val)		/* ulong_t�����������ޥ��� */
#define CAST(type, val)	(val)		/* �����㥹�Ȥ�Ԥ��ޥ��� */
#include "kernel_impl.h"

    .text
    .global _start
    .align  2
_start:
    /*
     *  SR���������롣
     *  MD=1, RB=0, BL=0, I3��I0=f(�������ߥޥ���)
     */
    mov.l _init_sr, r0
    ldc   r0, sr

    /*
     *  R7_BANK1��1�ˤ����󥿥�������ƥ����ȤȤ���
     */
    mov   #0x01, r0
    ldc   r0, r7_bank

    /*
     *  �󥿥�������ƥ������ѤΥ����å��ν����
     */
    mov.l  _kernel_istkpt_p, r1
    mov.l  @r1, r15

    /*
     *  _hardware_init_hook ��ƤӽФ���(0�Ǥʤ����)
     *
     *  �������åȥϡ��ɥ������˰�¸����ɬ�פʽ����������������ϡ�
     *  hardware_init_hook�Ȥ����ؿ����Ѱդ��롥
     */
start_0:
    mov.l  _hardware_init_hook_p, r0
    tst    r0, r0
    bt     start_1
    jsr    @r0
     or     r0, r0
    
    /*
     * bss���������򥯥ꥢ
     */
start_1:        
    mov.l  _bss_start_p, r0
    mov.l  _end_p, r1
    cmp/eq r0, r1
    bt     start_3
    mov    #0, r2
start_2:
    mov.l  r2, @r0
    add    #4, r0
    cmp/hi r0, r1
    bt     start_2

    /*
     *  data�������������������ROM���б��ˡ�
     *
     *  __idata_start ���� __idata_end �ޤǤ�__data_start �ʹߤ�
     *  ���ԡ����롥
     */
start_3:
    mov.l  __idata_start_p, r1
    mov.l  __idata_end_p, r2
    cmp/eq r1, r2
    bt     start_5
    mov.l  __data_start_p, r0
start_4:    
    mov.l  @r1+, r4
    mov.l  r4, @r0
    cmp/hi r1, r2
    add    #4, r0
    bt     start_4

        
    /*
     *  _software_init_hook ��ƤӽФ���0 �Ǥʤ����ˡ�
     *
     *  ���եȥ������Ķ����ä˥饤�֥��ˤ˰�¸����ɬ�פʽ������
     *  ����������ϡ�software_init_hook �Ȥ����ؿ����Ѱդ����
     *  �褤��
     */
start_5:    
    mov.l  _software_init_hook_p, r0
    tst    r0, r0
    bt     start_6        
    jsr    @r0
     nop
        
start_6:

	/*
	 *  FPU�ν����
	 */
#ifdef FPU_ENABLE
	/*
	 *  gcc���Ѥ���ǡ�����___fpscr_values�ˤ�����
	 */
	mov.l _set_fpscr_p, r1
    mov.l _fpscr_init_p, r4
	jsr   @r1
     nop
	lds   r3, fpscr 
	/*
	 *  FPU��ͭ����
	 */
	stc   sr, r0
	mov.l _sr_fpu_enable, r1
	and   r0, r1
	ldc   r1, sr
#endif /* FPU_ENABLE */

    /*    
     *  �����ͥ��ư����
     */
    mov.l  _sta_ker_p, r0
    jsr    @r0
     nop


    .align 4
_init_sr:    
    .long (0x400000f0)
_kernel_istkpt_p:
    .long __kernel_istkpt
_hardware_init_hook_p:    
    .long _hardware_init_hook
_bss_start_p:    
    .long __bss_start    
_end_p:    
    .long _end   
__idata_start_p:    
    .long __idata_start
__idata_end_p:    
    .long __idata_end
__data_start_p:    
    .long __data_start
_software_init_hook_p:    
    .long _software_init_hook    
_sta_ker_p:    
    .long _sta_ker
#ifdef FPU_ENABLE
_set_fpscr_p:
	.long ___set_fpscr
_sr_fpu_enable:
	.long   ~0x00008000
_fpscr_init_p:
	.long    FPSCR_INIT 
#endif /* FPU_ENABLE */