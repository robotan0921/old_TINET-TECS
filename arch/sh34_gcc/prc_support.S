/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_support.S 1708 2010-01-25 02:00:10Z ertl-honda $
 */

/*
 *  �ץ����å���¸�⥸�塼�� ������֥��������SH34�ѡ�
 */

#define TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t�����������ޥ��� */
#define ULONG_C(val)	(val)		/* ulong_t�����������ޥ��� */
#define CAST(type, val)	(val)		/* �����㥹�Ȥ�Ԥ��ޥ��� */

/*
 *  ������֥��ѤΥޥ�����ͭ���ˤ���
 */
#define TOPPERS_ASM_MACRO
#include "kernel_impl.h"
#include "offset.h"
     
#ifdef FPU_ENABLE

/*
 *  FPU��Ϣ�쥸��������¸
 */        
#ifdef FPU_SAVE_BANKED_REG

#define OFFSET_OF_SSR (11 + 14 + 16)

.macro save_banked_fpureg
    frchg  /* �Х󥯤��ڤ��ؤ� */
    fmov.s  fr15, @-r15
    fmov.s  fr14, @-r15
    fmov.s  fr13, @-r15
    fmov.s  fr12, @-r15
    fmov.s  fr11, @-r15
    fmov.s  fr10, @-r15
    fmov.s  fr9, @-r15
    fmov.s  fr8, @-r15
    fmov.s  fr7, @-r15
    fmov.s  fr6, @-r15
    fmov.s  fr5, @-r15
    fmov.s  fr4, @-r15
    fmov.s  fr3, @-r15
    fmov.s  fr2, @-r15
    fmov.s  fr1, @-r15
    fmov.s  fr0, @-r15
    frchg  /* �Х󥯤��᤹ */
.endm

.macro restore_banked_fpureg
#ifdef FPU_SAVE_BANKED_REG
    frchg  /* �Х󥯤��ڤ��ؤ� */
    fmov.s  @r15+, fr0
    fmov.s  @r15+, fr1
    fmov.s  @r15+, fr2
    fmov.s  @r15+, fr3
    fmov.s  @r15+, fr4
    fmov.s  @r15+, fr5
    fmov.s  @r15+, fr6
    fmov.s  @r15+, fr7
    fmov.s  @r15+, fr8
    fmov.s  @r15+, fr9
    fmov.s  @r15+, fr10
    fmov.s  @r15+, fr11
    fmov.s  @r15+, fr12
    fmov.s  @r15+, fr13
    fmov.s  @r15+, fr14
    fmov.s  @r15+, fr15
    frchg  /* �Х󥯤��᤹ */
#endif /* FPU_SAVE_BANKED_REG */
.endm

#else /* FPU_SAVE_BANKED_REG */

#define OFFSET_OF_SSR (11 + 14)

.macro save_banked_fpureg
.endm

.macro restore_banked_fpureg
.endm

#endif /* FPU_SAVE_BANKED_REG */

.macro save_scratch_fpureg label
    save_banked_fpureg
    sts.l   fpul, @-r15
    fmov.s  fr11, @-r15
    fmov.s  fr10, @-r15
    fmov.s  fr9,  @-r15
    fmov.s  fr8,  @-r15
    fmov.s  fr7,  @-r15
    fmov.s  fr6,  @-r15
    fmov.s  fr5,  @-r15
    fmov.s  fr4,  @-r15
    fmov.s  fr3,  @-r15
    fmov.s  fr2,  @-r15
    fmov.s  fr1,  @-r15
    fmov.s  fr0,  @-r15
    sts.l   fpscr, @-r15
    mov.l   _fpscr_init_\label, r0 /* fpscr �ν���ͤ����� */
    lds     r0,   fpscr
.endm

.macro restore_scratch_fpureg 
    lds.l   @r15+, fpscr
    fmov.s  @r15+, fr0
    fmov.s  @r15+, fr1
    fmov.s  @r15+, fr2
    fmov.s  @r15+, fr3
    fmov.s  @r15+, fr4
    fmov.s  @r15+, fr5
    fmov.s  @r15+, fr6
    fmov.s  @r15+, fr7
    fmov.s  @r15+, fr8
    fmov.s  @r15+, fr9
    fmov.s  @r15+, fr10
    fmov.s  @r15+, fr11
    lds.l   @r15+, fpul
    restore_banked_fpureg
.endm

.macro save_fpureg_data label
_fpscr_init_\label:    
    .long     (FPSCR_PR_INIT|FPSCR_INIT)
.endm

.macro save_callsaved_fpureg_dis
    save_banked_fpureg
    fmov.s  fr15, @-r15
    fmov.s  fr14, @-r15
    fmov.s  fr13, @-r15
    fmov.s  fr12, @-r15
    sts.l   fpscr, @-r15
.endm

.macro restore_callsaved_fpureg_dis
    lds.l   @r15+, fpscr
    fmov.s  @r15+, fr12
    fmov.s  @r15+, fr13
    fmov.s  @r15+, fr14
    fmov.s  @r15+, fr15
    save_banked_fpureg
.endm

.macro save_callsaved_fpureg_int
    lds.l   @r15+, fpscr   /* �����å�����fpscr��������� */
    sts.l   fpscr, @-r15   /* ������å��������Ѥ���¸    */
    fmov.s  fr15, @-r15
    fmov.s  fr14, @-r15
    fmov.s  fr13, @-r15
    fmov.s  fr12, @-r15
    sts.l   fpscr, @-r15
.endm

.macro restore_callsaved_fpureg_int
    lds.l   @r15+, fpscr
    fmov.s  @r15+, fr12
    fmov.s  @r15+, fr13
    fmov.s  @r15+, fr14
    fmov.s  @r15+, fr15
.endm

.macro set_fpscr label
    mov.l   _fpscr_init_\label, r2
    lds     r2, fpscr
.endm

#else /* FPU_ENABLE */

#define OFFSET_OF_SSR  11

.macro save_scratch_fpureg label
.endm

.macro restore_scratch_fpureg
.endm

.macro save_fpureg_data label
.endm

.macro save_callsaved_fpureg_dis
.endm

.macro restore_callsaved_fpureg_dis
.endm

.macro save_callsaved_fpureg_int
.endm

.macro restore_callsaved_fpureg_int
.endm

.macro set_fpscr label
.endm

#endif /* FPU_ENABLE */

/*
 *  �㳰/�����߽�����������롼����
 *  SH34�ϥ٥����ơ��֥����������㳰,TRAPA��ȯ�������VBR+0x100���Ϥ�
 *  ����/����/NMI�����ߤ�ȯ������ȡ�VBR+0x600���Ϥ�¹Ԥ��롣
 */

/*
 *  VBR �����ꤹ����
 */
    .section .text
    .align 2
    .global _base_vec
_base_vec:
     nop 
     nop
     nop

/*
 *  Exception 100 vector
 *  ���ɥ쥹���顼,�����å�����̿���㳰��Trapa�㳰����ȯ������ȼ¹Ԥ���롣
 *
 *  CPU�㳰�ϥ�ɥ�ϡ��󥿥�������ƥ����ȤǼ¹Ԥ��롢���Τ��ᡢCPU�㳰�ϥ�
 *  �ɥ��ƤӽФ������㳰/�����ߤ򼨤��쥸�����Х�1�� r7 �쥸�����򥤥�
 *  �����Ȥ����꥿���󤷤Ƥ�����˥ǥ�����Ȥ��롣CPU�㳰�ϥ�ɥ齪λ��ϡ�
 *  ret_exc �ˤ����ơ��и�������Ԥ���
 * 
 *  regflg ������å��������˳����ߤ�ػߤ��ʤ��ȡ�reqflg ������å���˵�
 *  ư���줿�����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ����ѥå�
 *  ����ʤ���
 *
 *
 *  �㳰��ȯ������ȡ��㳰ȯ�����Υ���ƥ����ȤǤ���spc,pr,ssr,r0��r7������
 *  ���롣�㳰��ȯ�����������ǤΥ���ƥ����Ȥ�Ĵ���󥿥�������ƥ����Ȥʤ�
 *  _exception_from_int����¹Ԥ򳫻Ϥ��롣�㳰���װ���EXPEVT�쥸�����ɤߡ�
 *  exc_table����CPU�㳰�ϥ�ɥ�γ������Ϥ��ɤ߹��ࡣCPU�㳰�ϥ�ɥ餫��
 *  �꥿���󤷤Ƥ����顢reqflg��Ĵ��0�ʳ��ʤ�rec_exc()�����ӡ�0�ʤ鸵��
 *  �����˥꥿���󤹤롣
 *
 *
 *  BL�ӥåȤΰ����ˤĤ���
 *  ssr,spc �������Υ���ƥ����Ȥ��ᤷ�� rte ��ȯ�Ԥ���ݤˤϡ�����ߡ�NMI 
 *  ��ޤ�ˤ�����դ��ʤ��褦�� BL �ӥåȤ�1�ˤ���ɬ�פ����롥�㳰/����ߥ�
 *  ��ɥ齪λ���ˤ� BL ��ӥåȤ�1�ˤ��� ��öIPM �� MAX_IPM �����ꤹ�롥
 *  ����ϡ�BL �ӥåȤ�1�ξ����㳰��ȯ������� CPU ���ꥻ�åȤ���뤳�Ȥ�
 *  ��θ���ơ������Τ��ᡤssr,spc����������ľ����BL��1�����ꤷ�Ƥ��롥
 *       
 *          ----------------------
 *  0      |       EXPEVT         |  <-- p_excinf
 *          ----------------------
 *  1      |         R7           |
 *          ----------------------
 *  2      |         R6           |
 *          ----------------------
 *  3      |         R5           |
 *          ----------------------
 *  4      |         R4           |
 *          ----------------------
 *  5      |         R3           |
 *          ----------------------
 *  6      |         R2           |
 *         ----------------------
 *  7      |         R1           |
 *          ----------------------
 *  8      |         R0           |
 *          ----------------------
 *  9      |        MACH          |
 *          ----------------------
 * 10      |        MACL          |
 *          ----------------------
 * 11      |        GBR           |
 *          ----------------------
 * 12      |         SR           |
 *          ----------------------
 * 13      |         PR           |
 *          ----------------------
 * 14      |         PC           |
 *          ----------------------
 */


    .org   0x0100              /*  _BASE_VBR + 0x0100���Ϥ�����   */
    .align 2
    .global _general_exc_vec
_general_exc_vec:
    stc.l  spc,@-r15           /* spc,pr,ssr �򥹥��å�����¸���� */
    sts.l  pr,@-r15
    stc.l  ssr,@-r15
    stc.l  gbr,@-r15
    sts.l  macl,@-r15
    sts.l  mach,@-r15                                            
    stc.l  r0_bank,@-r15       /* �㳰ȯ������r0��r7����¸        */
    stc.l  r1_bank,@-r15
    stc.l  r2_bank,@-r15
    stc.l  r3_bank,@-r15
    stc.l  r4_bank,@-r15
    stc.l  r5_bank,@-r15
    stc.l  r6_bank,@-r15
    stc.l  r7_bank,@-r15
    save_scratch_fpureg exc
    mov.l  _expevt_exc,r0      /* �㳰����Ĥ���Ⱦä���쥸��������¸      */
    mov.l  @r0,r5              /* EXPEVT�쥸���������                      */
    mov.l  r5,@-r15            /* �����å�����¸(̤��Ͽ���㳰ȯ��������)    */
    ldc    r15,r4_bank         /* CPU�㳰�ϥ�ɥ�ؤΰ���                   */
    ldc    r5, r5_bank         /* EXPEVT�쥸��������                        */
    tst    r7,r7               /* �㳰ȯ�����Υ���ƥ����Ȥ�Ƚ��            */
    bf/s   _general_exc_vec_1  /* ȯ�������㳰/�����ߥϥ�ɥ�ʤ饸���� */
     add    #0x01,r7           /* �㳰/�����ߥͥ��Ȳ���򥤥󥯥����   */
    mov.l  _kernel_istkpt_exc, r2
    mov    r15,r4
    mov.l  @r2,r15
    mov.l  r4,@-r15            /* �����å��������ؤ����Υ����å��ݥ��󥿤���¸ */
_general_exc_vec_1:
    mov.l  _lock_flag_exc,r3   /* ���� lock_flag �򥹥��å�����¸           */
    mov.l  @r3, r2
    mov.l  r2,@-r15
    mov.l _saved_iipm_exc,r3   /* ���� saved_iipm �򥹥��å�����¸          */
    mov.b  @r3, r2
    mov.l  r2,@-r15
    mov.l  _unmak_rb_bl_exc,r2 /* BL�ӥåȤ�0�ˡ��쥸�����Х󥯤��ڤ��ؤ�   */
    stc    sr,r3               
    and    r3,r2            
    ldc    r2,sr

    mov.l r5, @-r15              /* EXPEVT�򥹥��å�����¸        */
#ifdef LOG_EXC_ENTER
    mov.l  r4,@-r15              /* r4�򥹥��å�����¸            */
    mov.l _log_exc_enter_exc, r1 /* �������ϴؿ�                  */
    jsr   @r1
     mov  r5, r4                 /* ���� */
    mov.l @r15+, r4              /* r4������                      */
    mov.l @r15, r5               /* �㳰�װ�������(�����å������줿�ޤ�) */
#endif /* LOG_EXC_ENTER */

    index_excno r5             /* EXPEVT����exc_table�Υ���ǥå�������� */
    mov.l  _exch_tbl_exc,r0    /* exch_tbl�Υ��ɥ쥹��r0��                  */
    mov.l  @(r0,r5),r2         /* �ϥ�ɥ�Υ��ɥ쥹�����                  */
    jsr    @r2                 /* CPU�㳰�ϥ�ɥ��                         */
     nop

    mov.l @r15+, r4              /* EXPEVT������                   */
#ifdef LOG_EXC_LEAVE
    mov.l _log_exc_leave_exc, r1 /* �������ϴؿ�                   */
    jsr  @r1
     nop
#endif /* LOG_EXC_LEAVE */

    /*
     * CPU�㳰�ϥ�ɥ�и�����
     */
_ret_exc:
    mov.l  _mask_md_ipm_exc,r0 /* �����߶ػ�                              */
    ldc    r0,sr               
    mov.l  @r15+,r2            /* saved_iipm �򸵤��᤹                     */
    mov.l  _saved_iipm_exc,r3  
    mov.b  r2,@r3
    mov.l  @r15+,r2            /* lock_flag �򸵤��᤹                      */
    mov.l  _lock_flag_exc,r3   
    mov.l  r2,@r3
    /*
     * ����ߤΥͥ����ʿ���������� r7_bank1 �ȥ����å��ݥ���(r15)
     * �����Ƥ��Բ�ʬ�˹Ԥ�ɬ�פ����롥
     * ñ�˳���ߤ�ػߤ��������Ǥϡ������ͥ�������γ���ߤ�ػߤǤ��ʤ�
     * ���ᡤBL�ӥåȤ�1�˥��åȤ��ơ������ͥ�������γ���ߤ�ػߤ��롥
     */
    mov.l  _mask_md_bl_exc,r0  /* BL�ӥå� �� 1 ��                          */
    ldc    r0,sr               /* ������߶ػ�                              */
    stc    r7_bank,r7          /* �㳰/�����ߤΥͥ��Ȳ����ǥ������   */
    dt     r7
    ldc    r7,r7_bank
    tst    r7,r7
    bf     _ret_exc_1          /* ȯ�������������ʳ��ʤ餹���˥꥿����      */
    mov.l  @r15, r15           /* ����褬�������ʤΤǥ����å����᤹        */
    mov.l  _reqflg_exc,r2      /* reqflg�Υ����å�                          */
    mov.l  @r2,r1
    xor    r0,r0
    tst    r1,r1               /* reqflg��false�ʤ�_ret_exc_1��             */
    bt/s   _ret_exc_1          
     mov.l  r0,@r2             /* reqflg�򥯥ꥢ                            */
    mov.l  _mask_md_ipm_exc,r0 /* BL�ӥå� �� 0 ��                       */
    ldc    r0, sr              /* �����ͥ�������γ���ߵ���             */
    mov.l  _ret_int_2_exc, r1  /* ret_int_2��                               */
    jmp    @r1
     mov.l  @r15+,r2           /* EXPEVT�򥹥��å�������Ф�              */

_ret_exc_1:
    mov.l  @r15+,r2            /* EXPEVT�򥹥��å�������Ф�              */
    restore_scratch_fpureg
    mov.l  @r15+,r7            /* r0��r1,ssr,pr,spc�������������������     */
    mov.l  @r15+,r6
    mov.l  @r15+,r5
    mov.l  @r15+,r4
    mov.l  @r15+,r3
    mov.l  @r15+,r2
    mov.l  @r15+,r1
    mov.l  @r15+,r0
    lds.l  @r15+,mach
    lds.l  @r15+,macl
    ldc.l  @r15+,gbr
    ldc.l  @r15+,ssr
    lds.l  @r15+,pr
    ldc.l  @r15+,spc
    rte
     nop

    .align  4
_kernel_istkpt_exc:
    .long __kernel_istkpt
_expevt_exc:
    .long  EXPEVT
_unmak_rb_bl_exc:
    .long  0x4fffffff
_exch_tbl_exc:
    .long  _exch_tbl
_mask_md_ipm_exc:
    .long  (0x40000000 + INT_IPM(TMIN_INTPRI))
_reqflg_exc:
    .long  _reqflg
_mask_md_bl_exc:
    .long  (0x50000000 + INT_IPM(TMIN_INTPRI))
_lock_flag_exc:
    .long _lock_flag
_saved_iipm_exc:
    .long _saved_iipm
_ret_int_2_exc:
    .long _ret_int_2
#ifdef LOG_EXC_ENTER
_log_exc_enter_exc:
    .long _log_exc_enter
#endif /* LOG_EXC_ENTER */
#ifdef LOG_EXC_LEAVE
_log_exc_leave_exc:
    .long _log_exc_leave
#endif /* LOG_EXC_LEAVE */
save_fpureg_data exc

    
/*
 *  �������ǥ����ѥå���
 *
 *  ���Υ롼����ϡ�����������ƥ�����(r7_bank1 = 0)��CPU���å����֡�
 *  �ǥ����ѥå����ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ���������֤�
 *  �ƤӽФ���롥
 */

    .text
    .align 2
    .global _dispatch
_dispatch:
    save_callsaved_fpureg_dis
    sts.l  pr,@-r15          /* pr,r8��r14 �򥹥��å�����¸           */
    mov.l  r14,@-r15         /* r0��r7�ϸƤӽФ�������¸���Ƥ��뤿��  */
    mov.l  r13,@-r15         /* ��¸����ɬ�פ�̵��                    */
    mov.l  r12,@-r15
    mov.l  r11,@-r15
    mov.l  r10,@-r15
    mov.l  r9, @-r15
    mov.l  r8, @-r15
    mov.l  _p_runtsk_dis,r2  /* r0 <- p_runtsk                      */
    mov.l  @r2,r0
    mov.l  r15,@(TCB_sp,r0)  /* �����������å���TCB����¸ 60�ʲ��ʤ�OK*/
    mov.l  _dispatch_r_dis,r1/* �¹ԺƳ����Ϥ���¸                    */
    bra    _dispatcher
     mov.l  r1,@(TCB_pc,r0)  /* �¹ԺƳ����Ϥ�TCB����¸  60�ʲ��ʤ�OK */
 

_dispatch_r:
    mov.l  @r15+,r8         /* �쥸����������                       */
    mov.l  @r15+,r9
    mov.l  @r15+,r10
    mov.l  @r15+,r11
    mov.l  @r15+,r12
    mov.l  @r15+,r13
    mov.l  @r15+,r14
    lds.l  @r15+,pr
    set_fpscr dis           /* fpscr �ν���� r2���˲� */
    /*
     *  �������㳰�����롼����ε�ư
     *  dispatch_r��dispatcher����ƤӽФ���뤿�ᡤ
     *  tcb�Υ��ɥ쥹��r0�����äƤ��롥
     */
    mov    r0,r1
    mov.b  @(TCB_enatex,r1),r0
    mov.l  _enatex_mask_dis,r2
    tst    r0,r2
    bt/s   _dispatch_r_1        /* enatex �� false �ʤ�꥿���� */
     mov.l  @(TCB_texptn,r1),r0  /* texptn�������               */
    tst    r0,r0
    bt     _dispatch_r_1        /* texptn �� 0��̵�����        */
    mov.l  _call_texrtn_dis,r1  /* �������㳰�롼����θƤӽФ� */
    jmp    @r1
     nop
_dispatch_r_1:
    restore_callsaved_fpureg_dis
    rts
     nop

/*
 * �ǥ����ѥå����ư��ϡ�prc_support.S��
 */
    .global _start_dispatch
_start_dispatch:
    /*
     *  ���Υ롼����ϡ������ͥ뵯ư���ˡ����٤Ƥγ���ߤ�ػߤ�������
     * �ʳ���ߥ��å����֤�Ʊ���ˤǸƤӽФ���롥�ޤ�������ߥ⡼�ɡ���
     *  ����������ƥ����Ȥ�Ʊ���ˤǸƤӽФ���뤳�Ȥ����ꤷ�Ƥ��롥
     *
     *  prc_initialize�ǡ�lock_flag��true�ˡ�saved_iipm��IIPM_ENAALL��
     *  ��������Ƥ��뤿�ᡤ�����ͥ�������γ���ߤ���Ĥ��뤳�Ȥǡ�
     *  CPU���å����֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ˤʤ롥
     *  �ޤ���task_initialize��disdsp��false�˽�������Ƥ��뤿�ᡤ�ǥ�
     *  ���ѥå����ľ��֤ˤʤäƤ��롥
     *  
     *  �����Ǥϡ�r7_bank1��0���ꥢ���ʤ�������ϡ������ͥ�������γ��
     *  �ߤ򥵥ݡ��Ȥ����硤���ΤǤΥ����å����󥿥�������ƥ������Ѥ�
     *  �����å��Ǥ��뤿�ᡤr7_bank1��0�ξ��֤ǥ����ͥ�������γ���ߤ�
     *  ����ȡ������å��ξ�񤭤�ȯ�����Ƥ��ޤ�����Ǥ��롥
     */
    bra    _dispatcher_0
     nop

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå�
 */
    .globl _exit_and_dispatch
_exit_and_dispatch:
    /* �ǥ����ѥå������Ρ�dispatcher�ˤ� */

/*
 * �ǥ����ѥå�������
 */
_dispatcher:
#ifdef LOG_DSP_ENTER
    mov.l _log_dsp_enter_dis, r1 /* �������ϴؿ� */
    mov.l _p_runtsk_dis, r2      /* ����      */
    jsr   @r1
     mov.l  @r2,r4 
#endif /* LOG_DSP_ENTER */
_dispatcher_0:
    /*
     *  ���Υ롼����ϡ�����������ƥ����ȡ�CPU���å����֡��ǥ����ѥå�
     *  ���ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ�
     *  ��롥
     *
     *  ���ʤ����r7_bank1��0��lock_flag��true��disdsp��false��dspflg
     *  ��true��saved_iipm��IIPM_ENAALL�ȤʤäƤ��롥�¹ԺƳ����Ϥؤ⤳
     *  �ξ��֤Τޤ�ʬ�����롥
     */
    mov.l  _p_schedtsk_dis,r12  /* r0 <- p_schedtsk                 */
    mov.l  @r12,r0             
    mov.l  _p_runtsk_dis,r2
    mov.l  r0,@r2               /* schedtsk��runtsk��               */
    cmp/eq #0,r0                /* schedtsk �����뤫��              */
    bt     _dispatcher_1        /* ̵����Х�����                 */
    mov.l  _mask_md_bl_dis,r1   /* BL �ӥå� �� 1 ��                */
    ldc    r1,sr                /* ������߶ػ�                     */
    mov.l  @(TCB_sp,r0),r15     /* TCB���饿���������å�������      */
    xor    r1,r1                /* r7_bank1��0���ꥢ                */
    ldc    r1,r7_bank
    mov.l  _mask_md_ipm_dis,r1  /* BL bit �� 0 ��                   */
    ldc    r1,sr                /* �����ͥ�������γ���ߵ���       */

#ifdef LOG_DSP_LEAVE
    mov   r0, r8                 /* r0�ϥ�����å��쥸�����ʤΤ� r8�˥��ԡ� */
    mov.l _log_dsp_leave_dis, r1 /* �������ϴؿ� */
    jsr   @r1
     mov   r0, r4                /* ����      */
    mov  r8, r0                  /* r0��TCB�ؤΥݥ��󥿤��᤹ */    
#endif /* LOG_DSP_LEAVE */
    mov.l  @(TCB_pc,r0),r1      /* TCB����¹ԺƳ����Ϥ�����        */
    jmp    @r1 
     nop
_dispatcher_1:
    /* ���ߥǥ��������ͤ�����ɤ߹���Τϸ�Ψ�������Τǻ������Ѱդ���
     * r8  : �����߶ػߤΤ����SR����
     * r9  : �������Ԥ����SR����
     * r10 : reqflg������
     * r11 : 0x01
     * r12 : 0x00
     * r13 : sleep���SR�ξ���
     * r14 : lock_flag������
     */
    mov.l  _mask_md_ipm_dis,r8  /* �����߶ػߤ�SR����             */
#ifdef NO_SLEEP
    mov.l  _mask_md_dis,r9      /* �������Ԥ����SR����           */
#else
    mov.l  _mask_md_bl_dis,r9   /* �������Ԥ����SR����           */
#endif /* NO_SLEEP */
    mov.l  _kernel_istkpt_dis,r11
    mov.l  @r11,r15
    mov.l  _reqflg_dis,r10
    mov    #0x01,r11
    xor    r12,r12
    ldc    r11,r7_bank         /* r7_bank1 ��1�ˤ��Ƴ����߾��֤� */
    mov.l  _lock_flag_dis,r14
    mov.l  r12,@r14            /* CPU���å�������֤� */
_dispatcher_2:
    /*
     *  �����ǳ���ߥ⡼�ɤ��ڤ괹����Τϡ�������ȯ���������߽���
     *  �ˤɤΥ����å���Ȥ����Ȥ�������β��ȡ�����ߥϥ�ɥ����
     *  �Υ������ǥ����ѥå����ɻߤȤ�����Ĥΰ�̣�����롥
     */
     /*
      *  ����ߵ��ĸ��sleep̿���¹Ԥ���ȡ�����ߵ���̿��μ¹�����
      *  ������׵᤬���äƤ����硤����ߵ���̿��μ¹Ԥȶ��˳���ߤ�
      *  �����դ���줽��������ˡ�reqflg�Υ����å��ǤϤʤ� sleep ����
      *  �����äƤ��ޤ���
      *  ��������ϡ�����ߤε��Ĥ� sleep ���֤ؤΰܹԤ����ȥߥå��˼�
      *  �ԤǤ��ʤ����Ȥ˵������롥
      *  ���Τ��ᡤsleep �¹�ľ���� SR �ѹ��Ǥ� BL �ӥåȤ�'1'�����ꤹ
      *  �뤳�Ȥǡ�����ߤε��Ĥ� sleep ���֤ؤΰʹߤ򥢥ȥߥå��˼¹�
      *  ���롥
      *  ldc r9,sr �Ǥ�BL�ӥåȤ����åȤ���뤿�ᡤ����ߤϼ����դ�����
      *  �꡼�ץ⡼�ɤ˰ܹԤ��롥���꡼�ץ⡼����ϡ�BL�ӥåȤ�1�Ǥ��
      *  ���ߤ�����դ��뤿��(SH7709�ϡ��ɥ������ޥ˥奢�� 8-10)�����꡼
      *  �ץ⡼�ɤؤΰܹ�ľ��˳���ߤ���ե��꡼�ץ⡼�ɤ����������롥
      */
               
    ldc    r9,sr               /* �����ߤε���                   */
#ifndef NO_SLEEP
    sleep                      /* ������Ԥ�                       */
#endif /* NO_SLEEP */                
    ldc    r8,sr               /* �����߶ػ�                     */
    mov.l  @r10,r7             /* r7 <- reqflg                     */
    tst    r7,r7               /* reqflg �� false�ʤ�              */
    bt     _dispatcher_2       /* dispatcher_2 ��                  */

    ldc    r12,r7_bank         /* r7_bank1 �򥯥ꥢ                */
    mov.l  r12,@r10            /* reqflg �� false��                */
    /*
     *  CPU���å����֤��᤹��������Ԥ��δ֤˼¹Ԥ�������ߥϥ�ɥ�ˤ�
     *  �ꡤsaved_iipm���񤭴��������ǽ�������뤿�ᡤ�����ͤ��᤹ɬ
     *  �פ����롥dispatcher���¹Ԥ������ϡ�saved_iipm��IIPM_ENAALL
     *  �ȤʤäƤ��뤿�ᡤ�����Ǥ�saved_iipm��IIPM_ENAALL�ʡ�0�ˤ��᤻
     *  �Ф褤��
     */
    mov.l  _saved_iipm_dis, r10
    mov.l  r11,@r14            /* CPU���å����֤� */
    bra    _dispatcher_0
     mov.b r12,@r10            /* saved_iipm��0�ˤ��� */

    .align 4
_dispatch_r_dis:
    .long _dispatch_r
_p_runtsk_dis:
    .long _p_runtsk
_enatex_mask_dis:
    .long TCB_enatex_mask
_call_texrtn_dis:
    .long _call_texrtn
_p_schedtsk_dis:
    .long _p_schedtsk
_kernel_istkpt_dis:
    .long __kernel_istkpt
_mask_md_ipm_dis:
    .long (0x40000000 + INT_IPM(TMIN_INTPRI))
_mask_md_dis:
    .long 0x40000000
_mask_md_bl_dis:
    .long 0x50000000
_reqflg_dis:
    .long  _reqflg
_lock_flag_dis:
    .long _lock_flag
_saved_iipm_dis:
    .long _saved_iipm
save_fpureg_data dis
#ifdef LOG_DSP_ENTER
_log_dsp_enter_dis:
    .long _log_dsp_enter
#endif /* LOG_DSP_ENTER */
#ifdef LOG_DSP_LEAVE
_log_dsp_leave_dis:
    .long _log_dsp_leave
#endif /* LOG_DSP_LEAVE */

/*
 *  �����ͥ�ν�λ�����θƽФ�
 *
 *  �⡼�ɤȥ����å����󥿥�������ƥ������Ѥ��ڤ��ؤ���
 */
    .globl _call_exit_kernel
_call_exit_kernel:
    mov.l _mask_md_ipm_exit, r0
    ldc   r0,sr    
    mov.l _kernel_istkpt_exit, r1
    mov.l @r1,r15
    mov.l _exit_kernel_exit,r0
    jmp   @r0
     nop

    .align 4
_mask_md_ipm_exit:
    .long 0x400000f0
_kernel_istkpt_exit:
    .long __kernel_istkpt
_exit_kernel_exit:
    .long _exit_kernel


/*
 *  ��������ư����
 *
 *  �ǥ����ѥå��㤫��ƤӽФ���뤿�ᡤTCB�Υ��ɥ쥹��r0��
 *  ���äƤ���
 */ 
    .text
    .align 2
    .globl _start_r
_start_r:
    mov.l  _lock_flag_start, r1 /* CPU���å�������֤� */
    xor    r2,r2 
    mov.l  r2,@r1
    set_fpscr start
    mov.l  _mask_md_start,r4     /* �����ߵ��� */
    ldc    r4,sr
    mov.l  _ext_tsk_start,r2     /* ������Ϥ����� */
    lds    r2,pr 
    mov.l  @(TCB_p_tinib,r0),r3  /* p_runtsk->p_tinib��r3��  */
    mov.l  @(TINIB_task,r3),r1   /* ��������ư���Ϥ�r1��     */
    jmp    @r1
     mov.l  @(TINIB_exinf,r3),r4 /* exinf������쥸����r4��  */

    .align 4
_lock_flag_start:
    .long _lock_flag
_mask_md_start:    
    .long 0x40000000
_ext_tsk_start:
    .long _ext_tsk
save_fpureg_data start


/*
 *  Exception 600 vector
 *  �����ߤ�ȯ������ȼ¹Ԥ���롣
 *
 *
 *  SH34�ϳ����ߤ�ȯ������Ȥ��٤�VBR+0x600���Ϥ���ץ�������¹Ԥ��뤿�ᡢ
 *  ���������֤���롼����Ǥޤ������å����ڤ��ؤ����쥸��������¸,IPM������,
 *  �������װ���Ƚ���Ԥ����θ�BL�ӥåȤ�0�ˤ��Ƴ����ߥϥ�ɥ��Ƥ�ɬ��
 *  �����롣
 *  �������װ����б����������ߥϥ�ɥ�γ������Ϥ�����inh_tbl[]����Ͽ��
 *  �ƸƤӽФ������ե��åȤη׻��ϡ��������װ��쥸����������롥
 *  ������װ��쥸������INTEVT��INTEVT2������ब¸�ߤ��뤬���ɤ�����Ѥ��뤫��
 *  �ץ����å��η�����˻��ꤹ�롥
 *  �����ͥ���٥ޥ����ϡ�int_iipm_tbl[]�����������SR�����ꤹ�롥
 *
 *  reqflg ������å��������˳���ߤ�ػߤ��ʤ��ȡ�reqflg ������å���
 *  �˵�ư���줿����ߥϥ�ɥ���ǥǥ����ѥå����׵ᤵ�줿���ˡ��ǥ�
 *  ���ѥå�����ʤ���
 *
 */

    .org    0x0600         /* _BASE_VBR + 0x0600���Ϥ����� */
    .align 2
    .global _interrupt_vec
_interrupt_vec:
    stc.l  spc,@-r15       /* ¿�ų����ߤ�����Ⱦä��Ƥ��ޤ��Τ�        */
    sts.l  pr,@-r15        /* spc,pr,ssr,gbr,macl,mach                    */
    stc.l  ssr,@-r15    
    stc.l  gbr,@-r15                    
    sts.l  macl,@-r15                    
    sts.l  mach,@-r15                                                    
    stc.l  r0_bank,@-r15   /* ,r0��r7�򥹥��å�����¸   */ 
    stc.l  r1_bank,@-r15
    stc.l  r2_bank,@-r15
    stc.l  r3_bank,@-r15
    stc.l  r4_bank,@-r15
    stc.l  r5_bank,@-r15
    stc.l  r6_bank,@-r15
    stc.l  r7_bank,@-r15
    save_scratch_fpureg int
    tst    r7,r7                 /* ������ȯ�����Υ���ƥ����Ȥ�Ƚ��  */
    bf/s   _interrupt_vec_1      /* �㳰/�����ߥϥ�ɥ�ʤ饸����   */
     add    #0x01,r7             /* �����ߤΥͥ��Ȳ���򥤥󥯥����*/
    mov    r15,r1                /* �����å��������ؤ����Υ����å��ݥ�  */
    mov.l  _kernel_istkpt_int,r2 /* �󥿤���¸                          */
    mov.l  @r2,r15              
    mov.l  r1,@-r15            
_interrupt_vec_1:
    mov.l  _intevt_int,r0        /* ������װ��쥸�������������ֹ�    */
    mov.l  @r0,r4                /* �����                              */
    mov.l  r4, @-r15             /* ������ֹ�򥹥��å�����¸          */
    index_intno r4               /* ���ե��åȤ����                  */
    mov.l  _int_iipm_tbl_int,r0  /* ������ͥ���٥ޥ������ͤ����      */
    mov.l  @(r0,r4),r5        
    mov.l  _inh_tbl_int,r0       /* �����ߥϥ�ɥ�Υ��ɥ쥹�����    */
    mov.l  @(r0,r4),r2
    mov    r15, r4               /* default_int_handler�Τ���ΰ���     */
    ldc    r2,r2_bank            /* �Х�0���ڤ��ؤ��뤿�ᥳ�ԡ�       */
    ldc    r5,sr                 /* ����ʹ߳����ߤ�����դ��롣      */

#ifdef LOG_INH_ENTER
    mov.l @r15, r4               /* ������ֹ�����������              */
    mov.l  r2, @-r15             /* ����ߥϥ�ɥ�Υ��ɥ쥹����¸      */
    mov.l _log_inh_enter_int, r1 /* �������ϴؿ�                        */
    jsr   @r1
     nop
    mov.l  @r15+, r2             /* ����ߥϥ�ɥ�Υ��ɥ쥹������      */
    mov    r15, r4               /* default_int_handler�Τ���ΰ���     */
#endif /* LOG_INH_ENTER */

    jsr    @r2                   /* �����ߥϥ�ɥ��                  */
     nop

    mov.l @r15+, r4              /* ������ֹ������                    */
#ifdef LOG_INH_LEAVE
    mov.l _log_inh_leave_int, r1 /* �������ϴؿ�                        */
    jsr  @r1
     nop
#endif /* LOG_INH_LEAVE */

    /*
     * ����ߥϥ�ɥ�и�����
     */
_ret_int:
    /*
     * ����ߤΥͥ����ʿ���������� r7_bank1 �ȥ����å��ݥ���(r15)
     * �����Ƥ��Բ�ʬ�˹Ԥ�ɬ�פ����롥
     * ñ�˳���ߤ�ػߤ��������Ǥϡ������ͥ�������γ���ߤ�ػߤǤ��ʤ�
     * ���ᡤBL�ӥåȤ�1�˥��åȤ��ơ������ͥ�������γ���ߤ�ػߤ��롥
     */
    mov.l  _mask_md_bl_ret,r0    /* BL�ӥå� �� 1 ��                       */
    ldc    r0,sr                 /* ������߶ػ�                           */
    stc    r7_bank,r7            /* �㳰/�����ߤΥͥ��Ȳ����ǥ������*/
    dt     r7
    ldc    r7,r7_bank
    tst    r7,r7                 /* ����褬�󥿥�������ƥ����Ȥʤ餹���� */
    bf     _ret_int_1            /* �꥿����                               */
    mov.l  @r15, r15             /* ����褬�������ʤΤǥ����å����᤹     */
    mov.l  _reqflg_ret,r4        /* reqflg�Υ����å�                       */
    mov.l  @r4,r1
    tst    r1,r1                 /* reqflg��false�ʤ�ret_int_1��           */
    bt     _ret_int_1
    xor    r1,r1                 /* reqflg�Υ��ꥢ�Τ����r1��0��          */
    mov.l  _mask_md_ipm_ret,r0   /* BL�ӥå� �� 0 ��                       */
    ldc    r0, sr                /* �����ͥ�������γ���ߵ���             */
    bra    _ret_int_2;
     mov.l  r1,@r4               /* reqflg�򥯥ꥢ                         */

_ret_int_1:
    /*
     *  ����߽�������Υ꥿����ˤ�ꡤCPU���å�������֤˰ܹԤ���褦
     *  �������롥�����ͥ���٥ޥ����ϡ�RTE̿��ˤ�긵���ͤ���뤿�ᡤ
     *  lock_flag��false�ˤ��Ƥ����Ф褤��lock_flag��false�ˤ���Τϡ�
     *  CPU���å����֤Τޤ޳���ߥϥ�ɥ餫����ä������к��ˡ�
     */
    mov.l _lock_flag_ret, r0
    xor   r1,r1
    mov.l  r1,@r0
    restore_scratch_fpureg
    mov.l  @r15+,r7                /* �����߸������                 */
    mov.l  @r15+,r6
    mov.l  @r15+,r5
    mov.l  @r15+,r4
    mov.l  @r15+,r3
    mov.l  @r15+,r2
    mov.l  @r15+,r1
    mov.l  @r15+,r0
    lds.l  @r15+,mach
    lds.l  @r15+,macl
    ldc.l  @r15+,gbr
    ldc.l  @r15+,ssr
    lds.l  @r15+,pr
    ldc.l  @r15+,spc
    rte
     nop

_ret_int_2:
    /*
     *  �����ؤϡ�CPU�㳰�ϥ�ɥ�νи����������ʬ�����Ƥ��롥
     *
     *  �����Ǥϡ�����褬�������Ǥ��ꡤ�����å��ϡ������������å���
     *  ������å��쥸�����Τߤ���¸���줿���֤ˤʤäƤ��롥�ޤ���
     *  �����ͥ�����γ���ߤ�ػߤ������֤ȤʤäƤ��롥
     */
    /*
     *  CPU���å����֤˰ܹԤ��롥�����ͥ�����γ���ߤϤ��Ǥ˶ػߤ���
     *  ����Τǡ�lock_flag��saved_iipm�򹹿����롥saved_iipm�ϡ����
     *  ��γ����ͥ���٥ޥ����ʤ�����ɽ���ˤ����ꤹ�롥
     *
     *  ���λ�����CPU���å����֤Ȥ���Τϡ�dispatcher��ʬ��������ȡ�
     *  call_texrtn��ƤӽФ����ˡ�CPU���å����֤ˤʤäƤ���ɬ�פ�����
     *  ����Ǥ��롥
     */
    mov.l _lock_flag_ret, r2    /* lock_flag��true�� */
    mov   #0x01,r1
    mov.l r1,@r2
    mov   r15,r0
    mov.l @(OFFSET_OF_SSR*4,r0),r2  /* ���������IPM����Ф��� */
    mov   r2,r0
    and   #0xf0,r0              /* saved_iipm��              */
    mov.l _saved_iipm_ret, r1
    mov.b r0,@r1
    /*
     *  dspflg��false�Ǥ�����ȡ�p_runtsk��p_schedtsk��Ʊ�����ˤϡ�
     *  �ǥ����ѥå���Ԥ�ʤ������Υ����å���ɬ�פʤΤϡ��������㳰��
     *  ���롼����θƽФ���ɬ�פʾ��ˡ��ǥ����ѥå���ɬ�פʤ��Ƥ⡤
     *  reqflg��true�ˤ��뤿��Ǥ��롥
     */
    mov.l  _p_runtsk_ret,r1     /* r0 <- p_runtsk               */
    mov.l  @r1,r0           
    mov.l  _dspflg_ret,r2       /* dspflg��false�ʤ�ret_int_3�� */
    mov.l  @r2,r3
    tst    r3,r3
    bt     _ret_int_3    
    mov.l  _p_schedtsk_ret,r4   /* r5 <- schedtsk                */ 
    mov.l  @r4,r5
    cmp/eq r0,r5                /* runtsk �� schedtsk �����     */
    bt     _ret_int_3           /* Ʊ���ʤ�ret_int_3��           */
    save_callsaved_fpureg_int
    mov.l  r14,@-r15            /* �Ĥ�Υ쥸��������¸          */
    mov.l  r13,@-r15
    mov.l  r12,@-r15
    mov.l  r11,@-r15
    mov.l  r10,@-r15
    mov.l  r9,@-r15
    mov.l  r8,@-r15
    mov.l  r15,@(TCB_sp,r0)     /* �����������å���TCB����¸ 60�ʲ��ʤ�OK*/
    mov.l  _ret_int_r_ret,r1    /* �¹ԺƳ����Ϥ���¸             */
    bra    _dispatcher
     mov.l  r1,@(TCB_pc,r0)


_ret_int_r:
    mov.l  @r15+,r8
    mov.l  @r15+,r9
    mov.l  @r15+,r10
    mov.l  @r15+,r11
    mov.l  @r15+,r12
    mov.l  @r15+,r13
    mov.l  @r15+,r14
_ret_int_3:
    /*
     *  �������㳰�����롼����ε�ư
     *  ret_int_r �� dispatcher ����ƤӽФ���뤿�ᡤtcb�Υ��ɥ쥹��r0��
     *  ���äƤ��롥
     *  �ʤ�������ߤνи��ǥ����������å���ȯ�����ʤ����ϥǥ����ѥå���
     *  ���̤餺�� ret_int ����ľ�� ret_int_1 ������
     */
    mov    r0,r1
    mov.b  @(TCB_enatex,r1),r0
    mov.l  _enatex_mask_ret,r2
    tst    r0,r2
    bt/s   _ret_int_4           /* enatex �� false �ʤ�ret_int_4��  */
     mov.l  @(TCB_texptn,r1),r0 /* texptn�������                   */
    tst    r0,r0
    bt     _ret_int_4           /* texptn �� 0�ʤ�ret_int_4��       */
    mov.l _call_texrtn_ret,r1   /* �������㳰�롼����θƤӽФ�     */
    jsr   @r1
     nop
_ret_int_4:
    mov.l  _lock_flag_ret, r2  /* lock_flag��false�� */
    xor    r0,r0 
    mov.l  r0,@r2
    restore_callsaved_fpureg_int
    restore_scratch_fpureg
    mov.l  @r15+,r7            /* spc,pr,ssr,������å��쥸���������� */
    mov.l  @r15+,r6
    mov.l  @r15+,r5
    mov.l  @r15+,r4
    mov.l  @r15+,r3
    mov.l  @r15+,r2
    mov.l  @r15+,r1
    mov.l  _mask_md_bl_ret,r0
    ldc    r0,sr               /* BL��1��                             */
    mov.l  @r15+,r0
    lds.l  @r15+,mach
    lds.l  @r15+,macl
    ldc.l  @r15+,gbr
    ldc.l  @r15+,ssr
    lds.l  @r15+,pr
    ldc.l  @r15+,spc
    rte
     nop


    .align  4
_kernel_istkpt_int:
    .long __kernel_istkpt
_intevt_int:
#ifdef USE_INTEVT2
    .long  INTEVT2
#else
    .long  INTEVT
#endif /* USE_INTEVT2 */
_int_iipm_tbl_int:
    .long  _int_iipm_tbl
_inh_tbl_int:
    .long  _inh_tbl

_mask_md_ipm_ret:
    .long  (0x40000000 + INT_IPM(TMIN_INTPRI))
_lock_flag_ret:
    .long  _lock_flag
_mask_md_bl_ret:
    .long  0x50000000
_reqflg_ret:
    .long  _reqflg
_saved_iipm_ret:
    .long  _saved_iipm
_p_runtsk_ret:
    .long  _p_runtsk
_dspflg_ret:
    .long  _dspflg
_p_schedtsk_ret:
    .long  _p_schedtsk
_ret_int_r_ret:
    .long _ret_int_r
_enatex_mask_ret:
    .long TCB_enatex_mask
_call_texrtn_ret:
    .long _call_texrtn
#ifdef LOG_INH_ENTER
_log_inh_enter_int:
    .long _log_inh_enter
#endif /* LOG_INH_ENTER */
#ifdef LOG_INH_LEAVE
_log_inh_leave_int:
    .long _log_inh_leave
#endif /* LOG_INH_LEAVE */
save_fpureg_data int


/*
 *  ���������Ԥ�
 */
    .globl _sil_dly_nse
_sil_dly_nse:
    mov.l  _sil_dly_tim1, r1
    add    r1, r4
    cmp/pl r4
    bt     _sil_dly_nse1
    rts
     nop
_sil_dly_nse1:
    mov.l  _sil_dly_tim2, r1
    add    r1, r4
    cmp/pl r4
    bt     _sil_dly_nse1
    rts
     nop   
    .align 4
_sil_dly_tim1:
    .long  -SIL_DLY_TIM1
_sil_dly_tim2:
    .long  -SIL_DLY_TIM2