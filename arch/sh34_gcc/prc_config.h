/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007-2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.h 1662 2009-11-04 00:26:05Z ertl-honda $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH34�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  �ץ��å����ü�̿��Υ���饤��ؿ����
 */
#include "prc_insn.h"

/*
 *  �󥿥�������ƥ������ѤΥ����å������
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char_t *)(istk) + (istksz)))

/*
 *  ����������ƥ����ȥ֥�å������
 */
typedef struct task_context_block {
	void	*sp;		/* �����å��ݥ��� */
	FP		pc;			/* �ץ���५���� */
} CTXB;

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �����ͥ���٥ޥ������饤�֥��
 *  
 *  SH34�Ǥϡ����ơ������쥸������SR�ˤ�4��7�ӥåȤ��4�ӥåȤ˳����ͥ����
 *  �ޥ����ʥϡ��ɥ������γ����ͥ���٥ޥ�����IPM�ˤ��֤���Ƥ��롥IPM����
 *  ¸���Ƥ�������ˡ������ͥ���٤γ���ɽ����-1����Ϣ³��������͡ˤ�Ȥ�
 *  ���Ȥ��ǽ�Ǥ��뤬��;�פʺ����ӥåȥ��եȤ����ȿž��ɬ�פˤʤ롥����
 *  ���򤱤뤿��ˡ�IPM����¸������ˤϡ�SR��4��7�ӥåȤ����Ф�����
 *  ��Ȥ����Ȥˤ��롥�����ͤ�����ͥ���٥ޥ���������ɽ���ȸƤӡ�IIPM�Ƚ�
 *  �����Ȥˤ��롥
 */

/*
 *  �����ͥ���٥ޥ����γ���ɽ��������ɽ�����Ѵ�
 *
 *  ������֥����Υ������ե����뤫�饤�󥯥롼�ɤ�����Τ���ˡ�CAST�����
 */
#define EXT_IPM(iipm)    (-CAST(PRI,(iipm) >> 4))       /* ����ɽ������ɽ���� */
#define INT_IPM(ipm)     (CAST(uint16_t, -(ipm)) << 4)  /* ����ɽ��������ɽ���� */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ��ɽФ�
 */
Inline uint8_t
current_iipm(void)
{
    return((uint8_t)(current_sr() & 0xF0U));
}

/*
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ���ˤθ����ͤ�����
 */
Inline void
set_iipm(uint8_t iipm)
{
    set_sr((current_sr() & ~0xF0U) | iipm);
}

/*
 *  TOPPERSɸ�����߽�����ǥ�μ¸�
 *
 *  SH34�ϥ��ơ������쥸����(SR)��˳����ͥ���٥ޥ���(IPM)����äƤ��롥
 *  CPU��å��ե饰��������ǽ������ʤ������Τ��ᡤ����Ū��CPU��å���
 *  �饰��¸����롥
 *
 *  �ޤ���CPU��å����֤������������ѿ�(lock_flag)���Ѱդ��롥
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ���֤ϡ�IPM���ǥ��γ����ͥ����
 *  �ޥ������ͤ����ꤹ�롥���δ֤ϡ���ǥ��γ����ͥ���٥ޥ����ϡ�
 *  IPM���Ѥ��롥
 * 
 *  ������Ф���CPU��å��ե饰�����åȤ��줤��֤ϡ�IPM�򡤥����ͥ��
 *  �����Τ�Τ�������٤Ƥγ�����׵��ޥ���������(TIPM_LOCK)�ȡ����
 *  ���γ����ͥ���٥ޥ����Ȥι⤤�������ꤹ�롥���δ֤Υ�ǥ��γ�
 *  ����ͥ���٥ޥ����ϡ����Τ�����ѿ�(saved_iipm, ����ɽ�����ݻ�)����
 *  �դ����ݻ����롥
 */

/*
 *  ����ƥ����Ȥλ���
 *
 *  SH34�Ǥϡ�����ƥ����Ȥ�Ƚ��ˡ�����ߤΥͥ��Ȳ�����������
 *  R7_BANK1���Ѥ��롥
 * 
 */
Inline bool_t
sense_context(void)
{
    uint32_t nest;

    Asm("stc r7_bank,%0" : "=r"(nest));
    return(nest > 0U);
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  CPU��å����֤Ǥγ����ͥ���٥ޥ���
 *
 *  TIPM_LOCK�ϡ�CPU��å����֤Ǥγ����ͥ���٥ޥ��������ʤ����������
 *  ��������Τ�Τ�������٤Ƥγ���ߤ�ޥ��������ͤ�������롥
 */
#define TIPM_LOCK    TMIN_INTPRI

/*
 *  CPU��å����֤Ǥγ����ͥ���٥ޥ���������ɽ��
 */
#define IIPM_LOCK    INT_IPM(TIPM_LOCK)

/*
 *  TIPM_ENAALL�ʳ����ͥ���٥ޥ���������ˤ�����ɽ��
 */
#define IIPM_ENAALL  INT_IPM(TIPM_ENAALL)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 * 
 *  �������ѿ��ϡ�CPU��å����֤λ��Τ߽񤭴����Ƥ�褤�Ȥ��롥
 *  ����饤��ؿ���ǡ����������ν�����Ѳ����ʤ��褦��volatile ����ꡥ 
 */
extern volatile bool_t    lock_flag;   /* CPU��å��ե饰���ͤ��ݻ������ѿ� */
extern volatile uint8_t saved_iipm;  /* �����ͥ���٤�ޥ��������ѿ� */

/*
 *  CPU��å����֤ؤΰܹ�
 *
 *  IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ����ˤ�saved_iipm����¸��������
 *  �ͥ�������Τ�Τ�������٤Ƥγ���ߤ�ޥ��������͡�TIPM_LOCK�ˤ���
 *  �ꤹ�롥�ޤ���lock_flag��true�ˤ��롥
 *
 *  IPM�����ǽ餫��TIPM_LOCK��Ʊ����������⤤���ˤϡ������
 *  saved_iipm����¸����Τߤǡ�TIPM_LOCK�ˤ����ꤷ�ʤ�������ϡ���ǥ�
 *  ��γ����ͥ���٥ޥ�������TIPM_LOCK��Ʊ����������⤤��٥������
 *  ����Ƥ�����֤ˤ����롥
 *
 *  ���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǸƤФ�뤳�Ȥ�
 *  �ʤ���Τ����ꤷ�Ƥ��롥
 */
Inline void
x_lock_cpu(void)
{
    uint8_t iipm;

    /*
     *  current_iipm()���֤��ͤ�ľ��saved_iipm����¸����������ѿ�iipm
     *  ���Ѥ��Ƥ���Τϡ�current_iipm()��Ƥ��ľ��˳���ߤ�ȯ������
     *  ��ư���줿����߽�����saved_iipm���ѹ�������ǽ�������뤿���
     *  ���롥
     */
    iipm = current_iipm();
    if (IIPM_LOCK > iipm) {
        set_iipm(IIPM_LOCK);
    }
    saved_iipm = iipm;
    lock_flag = true;
    /* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
    Asm("":::"memory");
}

#define t_lock_cpu()    x_lock_cpu()
#define i_lock_cpu()    x_lock_cpu()

/*
 *  CPU��å����֤β��
 *
 *  lock_flag��false�ˤ���IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ����ˤ�
 *  saved_iipm����¸�����ͤ��᤹��
 *
 *  ���δؿ��ϡ�CPU��å����֡�lock_flag��true�ξ��֡ˤǤΤ߸ƤФ���
 *  �Τ����ꤷ�Ƥ��롥
 */
Inline void
x_unlock_cpu(void)
{
    /* ����ƥ����륻������������ǥ��꤬�񤭴�����ǽ�������� */
    Asm("":::"memory");
    lock_flag = false;
    set_iipm(saved_iipm);
}

#define t_unlock_cpu()    x_unlock_cpu()
#define i_unlock_cpu()    x_unlock_cpu()

/*
 *  CPU��å����֤λ���
 */
Inline bool_t
x_sense_lock(void)
{
    return(lock_flag);
}

#define t_sense_lock()    x_sense_lock()
#define i_sense_lock()    x_sense_lock()

/*
 *  chg_ipm��ͭ���ʳ����ͥ���٤��ϰϤ�Ƚ��
 *
 *  TMIN_INTPRI���ͤˤ�餺��chg_ipm�Ǥϡ�-15��TIPM_ENAALL�ʡ�0�ˤ��ϰ�
 *  ������Ǥ��뤳�ȤȤ���ʥ������å�����γ�ĥ�ˡ�
 */
#define VALID_INTPRI_CHGIPM(intpri) \
				((-15 <= (intpri) && (intpri) <= TIPM_ENAALL))

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ���������
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ�����ϡ��ϡ��ɥ������γ����ͥ���٥�
 *  ���������ꤹ�롥CPU��å��ե饰�����åȤ���Ƥ�����ϡ�saved_iipm
 *  �����ꤷ������ˡ��ϡ��ɥ������γ����ͥ���٥ޥ��������ꤷ�褦��
 *  �����ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����TIPM_LOCK�ι⤤�������ꤹ�롥
 */
Inline void
x_set_ipm(PRI intpri)
{
    uint8_t   iipm = INT_IPM(intpri);

    if (!lock_flag) {
        set_iipm(iipm);
    }
    else {
        saved_iipm = iipm;
#if TIPM_LOCK == -15
        /*
         *  TIPM_LOCK��-15�ξ��ˤϡ����λ����ǥϡ��ɥ������γ����ͥ��
         *  �٥ޥ�����ɬ��15�����ꤵ��Ƥ��뤿�ᡤ���ꤷ�ʤ���ɬ�פ��ʤ���
         */
#else /* TIPM_LOCK == -15 */
        set_iipm(iipm > IIPM_LOCK ? iipm : IIPM_LOCK);
#endif /* TIPM_LOCK == -15 */
    }
}

#define t_set_ipm(intpri)    x_set_ipm(intpri)
#define i_set_ipm(intpri)    x_set_ipm(intpri)

/*
 * �ʥ�ǥ��Ρ˳����ͥ���٥ޥ����λ���
 *
 *  CPU��å��ե饰�����ꥢ����Ƥ�����ϥϡ��ɥ������γ����ͥ���٥�
 *  �����򡤥��åȤ���Ƥ������saved_iipm�򻲾Ȥ��롥
 */
Inline PRI
x_get_ipm(void)
{
    uint8_t iipm;

    if (!lock_flag) {
        iipm = current_iipm();
    }
    else {
        iipm = saved_iipm;
    }
    return(EXT_IPM(iipm));
}

#define t_get_ipm()    x_get_ipm()
#define i_get_ipm()    x_get_ipm()

/*
 *  �ǹ�ͥ���̥������ؤΥǥ����ѥå���prc_support.S��
 *
 *  dispatch�ϡ�����������ƥ����Ȥ���ƤӽФ��줿�����ӥ������������
 *  ��ƤӽФ��٤���Τǡ�����������ƥ����ȡ�CPU��å����֡��ǥ����ѥ�
 *  �����ľ��֡��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤ǸƤӽФ���
 *  ����Фʤ�ʤ���
 */
extern void dispatch(void);

/*
 *  �ǥ����ѥå����ư��ϡ�prc_support.S��
 *
 *  start_dispatch�ϡ������ͥ뵯ư���˸ƤӽФ��٤���Τǡ����٤Ƥγ��
 *  �ߤ�ػߤ������֡ʳ���ߥ�å����֤�Ʊ���ξ��֡ˤǸƤӽФ��ʤ����
 *  �ʤ�ʤ���
 */
extern void start_dispatch(void) NoReturn;

/*
 *  ���ߤΥ���ƥ����Ȥ�ΤƤƥǥ����ѥå���prc_support.S��
 *
 *  exit_and_dispatch�ϡ�ext_tsk����ƤӽФ��٤���Τǡ�����������ƥ�
 *  ���ȡ�CPU��å����֡��ǥ����ѥå����ľ��֡��ʥ�ǥ��Ρ˳����ͥ��
 *  �٥ޥ�����������֤ǸƤӽФ��ʤ���Фʤ�ʤ���
 */
extern void exit_and_dispatch(void) NoReturn;

/*
 *  �����ͥ�ν�λ�����θƽФ���prc_support.S��
 *
 *  call_exit_kernel�ϡ������ͥ�ν�λ���˸ƤӽФ��٤���Τǡ��󥿥���
 *  ����ƥ����Ȥ��ڤ괹���ơ������ͥ�ν�λ������exit_kernel�ˤ�Ƥӽ�
 *  ����
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  ����������ƥ����Ȥν����
 *
 *  ���������ٻ߾��֤���¹ԤǤ�����֤˰ܹԤ�����˸ƤФ�롥���λ���
 *  �ǥ����å��ΰ��ȤäƤϤʤ�ʤ���
 *
 *  activate_context�򡤥���饤��ؿ��ǤϤʤ��ޥ�������Ȥ��Ƥ���Τϡ�
 *  ���λ����Ǥ�TCB���������Ƥ��ʤ�����Ǥ��롥
 */
extern void    start_r(void);

#define activate_context(p_tcb)                                         \
{                                                                       \
    (p_tcb)->tskctxb.sp = (void *)((char_t *)((p_tcb)->p_tinib->stk)    \
                                        + (p_tcb)->p_tinib->stksz);     \
    (p_tcb)->tskctxb.pc = (void *) start_r;                             \
}

/*
 *  calltex�ϻ��Ѥ��ʤ�
 */
#define OMIT_CALLTEX

/*
 * �������å����¸���˴ޤޤ��ɸ����㳰������ǽ�ν�����������Ѥ��ʤ�
 */
#define OMIT_INITIALIZE_EXCEPTION

/*
 * CPU�㳰�ϥ�ɥ�ν����
 */
Inline void
initialize_exception(void)
{
}
     
/*
 *  SH34�γ���ߥ������ƥ�����ȳ���߽�����ǥ�μ¸�
 * 
 *  SH34�γ���ߤϡ��������ե⥸�塼�����ߡ�IRQ�����, PINT����ߤ�ʬ
 *  ��Ǥ������줾�찷�����ۤʤ롥���Τ��ᡤ����ߥϥ�ɥ��ֹ椫�顤��
 *  �γ���ߤ�ʬ�ह�뤿��Υޥ�����Ѱդ��롥
 * 
 *  PINT����ߤ�15bit�Υץ��å��ؤγ�����׵�饤��Ǽ¸�����Ƥ��뤬��
 *  IRC�ؤγ�����׵�饤���PINT0��PINT7��PINT0��PINT7�Ȥ��ä�2�ܤˤʤ�
 *  �Ƥ��롥���Τ��ᡤ�����ͥ�Ǥ���̤ˤϰ��鷺��2�ܤγ���ߤȤ��ư�����
 *  PINT�ϡ����̤�PINTER�쥸�����ˤ����Ķػ߲�ǽ�Ǥ��뤬�������ͥ��
 *  �ϡ�PINTER�쥸����������ϼ�갷��ʤ������Τ��ᡤPINTER�쥸������
 *  ����ϡ��桼�����ץ����ǹԤ�ɬ�פ����롥Ʊ�ͤ�PINT���׵��٥�
 *  �����ꤹ��ICR2�������桼�����ץ����ǹԤ�ɬ�פ����롥�ʤ�������
 *  ������ߤ����ꤷ���ݤγ���ߥϥ�ɥ��������Ǥ�IRR0�Υ��ꥢ��
 *  i_begin_int()�ǹԤ���PINT����ߤ��ɤ�����Ƚ�ꤹ��ޥ�����Ѱդ��롥
 *
 *  Ʊ�ͤ�IRQ����ߤ���Ƚ�ꤹ��ޥ�����Ѱդ��롥
 */

/*
 *  PINT����ߤ��ɤ�����Ƚ�ꤹ�뤿��Υޥ���
 */
#define INTNO_PINT(intno) ((0x700 == (intno)) || (0x720 == (intno)))
#define INTNO_PINT_OFFSET(intno) (((intno) - 0x700) >> 5)

/*
 *  IRQ����ߤ��ɤ�����Ƚ�ꤹ�뤿��Υޥ���
 */
#define INTNO_IRQ(intno) ((0x600 <= (intno)) && ((intno) <= 0x6A0))
#define INTNO_IRQ_OFFSET(intno) (((intno) - 0x600) >> 5)
     
/*
 *  �����ͥ����
 *
 *  �Ƴ���ߤγ����ͥ���٤ϳ����ͥ�������쥸����(IPRXX)�ˤ�ä���
 *  �ꤹ�롥�������ե⥸�塼��ξ�硤���ե⥸�塼����������ǽ�Ǥ��롥
 *  �㤨��SCIF�ϡ�ERI2, RXI2, BRI2, TXI2�Ȥ���4�Ĥγ�����׵�饤���
 *  �ݡ��Ȥ��뤬�����Ƥγ�����׵�饤����Ф���Ʊ���ͥ���٤��������
 *  ���ʤ������Τ��ᡤ�Ƴ�����׵�饤����ˤɤγ����ͥ�������쥸��
 *  �������ꤹ�뤫����������ơ��֥���Ѱդ��롥�ޤ���������ֹ��Ϣ³
 *  ���Ƥ����ᡤ���ݡ��Ȥ��Ƥ��ʤ��ֹ�ˤϡ�number��-1�����ꤹ�롥�ơ�
 *  �֥�
 */

/*
 *  �Ƴ�����ֹ�������ꤹ��IPR�ξ�������Τ���ι�¤��  
 */
typedef struct {
    /* IPRA:0, IPRB:1, IPRC:2, IPRD:3, IPRE:4, IPRF:5, IPRG:6 */
    uint32_t address; 
    /* bit5��12:3, bit11��8:2, bit7��4:1, bit3��0:0 */
    uint8_t  offset;
} IPR_INFO;

/*
 *  �Ƴ�����ֹ����IPR�ξ�������ơ��֥�
 */
extern const IPR_INFO ipr_info_tbl[TNUM_INH];
    
/*
 *  ������ֹ桦����ߥϥ�ɥ��ֹ�
 *
 *  ����ߥϥ�ɥ��ֹ�(inhno)�ȳ�����ֹ�(intno)�ϡ������ȯ�����˳��
 *  �߻��ݥ쥸���������ꤵ����ͤ��Ѥ��롥����߻��ݥ쥸�����ϡ�INTEVT
 *  ��INTEVT2��2���ब���ꡤ���줾�����ꤵ����ͤ��ۤʤ롥�����SH34��
 *  ��INTEVT����Ѥ��Ƥ����������ߤ�INTEVT2���Ѥ��롥���Τ��ᡤ�ץ�
 *  �å��η����������ե�������Ѱդ��ơ��ɤ���Υ쥸�������Ѥ��뤬��
 *  �ꤹ�뤳�ȤȤ��롥�ޤ������ݡ��Ȥ������ߤκ������ۤʤ뤿�ᡤ
 *  �����ͤ�ץ��å��η����������ե������������롥
 *
 *  INTENT�����ꤵ����ͤϥ��ѡ������ͤǤ��뤿�ᡤ���Τޤޤ��ͤ�ͥ����
 *  �������Υơ��֥�Υ���ǥå������Ѥ���ȡ�̵�̤��ΰ褬ȯ�����롥��
 *  �Τ��ᡤ�����ͥ������Ǥϡ�INTENT�����ꤵ����ͤ򥷥եȤ����ͤ��Ѥ�
 *  �롥���եȤ����ͤ�ץ��å���˰ۤʤ뤿��ץ��å��η���������
 *  �ե������������롥
 *
 *  ����ɽ����̾���ϡ�iintno,iinhno�Ȥ��롥
 */

/*
 *  ������ֹ���ϰϤ�Ƚ��
 * 
 *  TMIN_INTNO��TMAX_INTNO���ϰϤǤ��äƤ�ͭ�����ֹ�Ǥʤ���礬���뤿
 *  �ᡤipr_info_tbl[]��ͭ�����ֹ椫������å�����
 */
#define VALID_INTNO(intno) \
        ((TMIN_INTNO <= (intno)) && ((intno) <= TMAX_INTNO) && (ipr_info_tbl[INT_INTNO(intno)].address != 0U))
#define VALID_INTNO_DISINT(intno)    VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)    VALID_INTNO(intno)

/*
 *  CPU�㳰�ϥ�ɥ��ֹ�
 *
 *  CPU�㳰�ϥ�ɥ��ֹ�Ȥ��Ƥϡ��㳰���ݥ쥸���������ꤹ���㳰�����ɤ�
 *  �Ѥ��롥���ݡ��Ȥ���CPU�㳰�ϥ�ɥ���ϥץ��å��η�����˰ۤʤ��
 *  �ǡ��ץ��å��η����������ե������������롥
 *
 *  ����ߥϥ�ɥ��ֹ��Ʊ������CPU�㳰�ϥ�ɥ��ֹ�⥹�ѡ����Ǥ��뤿�ᡤ
 *  �����ͥ������Ǥ��ͤ򥷥եȤ�������ɽ�����Ѥ��롥 
 */
#define VALID_EXCNO_DEFEXC(excno) \
        (TMIN_EXCNO <= (excno) && (excno) <= TMAX_EXCNO)

/*
 *  ����ߥϥ�ɥ�
 *
 *  ����ߥϥ�ɥ����Ͽ���롥����ߥϥ�ɥ�ơ��֥���Τϥ���ե�����
 *  �졼������Ū����������
 */ 
extern const FP inh_tbl[TNUM_INH];

/*
 *  ����ߥϥ�ɥ������
 *
 *  �٥��ȥ��ֹ�inhno�γ���ߥϥ�ɥ�ε�ư����int_entry�����ꤹ�롥�����
 *  �ϥ�ɥ�ơ��֥�
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry)
{
}

/*
 *  ����ߥϥ�ɥ�ν����������������ޥ���
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) extern void inthdr(void);

/*
 *  ������׵�ػߥե饰
 *
 *  SH34��IRC�ϳ�����׵�ػߥե饰������ʤ�������ߤ�ػߤ�����ϡ�
 *  �����ͥ�������쥸����(IPRXX)��0�����ꤹ��ɬ�פ����롥�����ͥ
 *  �������쥸������0�ˤ��뤳�Ȥǳ�����׵�ػߥե饰��¸�����Ȥ���
 *  �֡������ͥ���٤򵭲����Ƥ����ΰ褬ɬ�פȤʤ롥����ե�����졼��
 *  �Ǥ��Υơ��֥���Ѱդ��롥�ʤ������Υơ��֥�ϳ���ߤ�������ǳ��
 *  ���װ��˱�����SR�����ꤹ��ɬ�פ����뤿�ᡤ����ɽ���Ȥ��롥�ޤ�����
 *  ���ߥϥ�ɥ��������Ǥ��������Τ��ᡤIPM�����ǤϤʤ�������ߥϥ��
 *  ��¹Ի���SR�������Ʊ���˻��ġ����Τ��ᡤIPM���ͤΤߤ������������
 *  ��ϡ�����8bit�Τߤ򻲾Ȥ���ɬ�פ����롥���Ƥϥ���ե�����졼����
 *  ��Ū���������롥
 */
extern const uint32_t int_iipm_tbl[TNUM_INT];

/*
 *  ������׵�ػߥե饰�Υ��å�
 *
 *  �����ͥ�������쥸����(IPRA��G)��0�����ꤹ�롥
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_disable_int(INTNO intno)
{
    uint16_t iintno  = INT_INTNO(intno);
    uint32_t address = ipr_info_tbl[iintno].address;
    uint32_t offset  = ipr_info_tbl[iintno].offset;
    uint32_t iipm    = int_iipm_tbl[iintno];

    /*
     *  �����°�������ꤵ��Ƥ��ʤ����
     */
    if ((iipm & 0x01U) != 0) {
        return(false);
    }
    
    /* 
     *  ������ֹ���б�����IPR���ͤ�0�ˤ��롥
     */
    set_irc_ipr(address, offset, 0x00);

    return(true);
}

#define t_disable_int(intno) x_disable_int(intno)
#define i_disable_int(intno) x_disable_int(intno)

/*
 *  ������׵�ػߥե饰�β��
 *
 *  �����ͥ�������쥸����(IPRA��G)�򸵤��ͤ��᤹��
 *
 *  �����°�������ꤵ��Ƥ��ʤ�������׵�饤����Ф��Ƴ�����׵�ػ�
 *  �ե饰�򥯥ꥢ���褦�Ȥ������ˤϡ�false���֤���
 */
Inline bool_t
x_enable_int(INTNO intno)
{
    uint16_t iintno  = INT_INTNO(intno);
    uint32_t address = ipr_info_tbl[iintno].address;
    uint32_t offset  = ipr_info_tbl[iintno].offset;
    uint32_t iipm    = int_iipm_tbl[iintno];

    /*
     *  �����°�������ꤵ��Ƥ��ʤ����
     */
    if ((iipm & 0x01U) != 0) {
        return(false);
    }

    /* 
     *  ������ֹ���б�����IPR���ͤ򥻥åȤ���
     */
    set_irc_ipr(address, offset, (-EXT_IPM(iipm & 0xF0U)));
    
    return(true);
}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 *  ������׵�饤���°��������
 *
 *  SH34�Ǥϡ������ͥ�ǰ���������ͥ���٤�16�ʳ��Ǥ��뤿�ᡤintpri
 *  �Ȥ���Ϳ���뤳�Ȥ��Ǥ����ͤ�-15��-1��ɸ��Ǥ��롥
 */
extern void    x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  ����ߥϥ�ɥ�������ɬ�פ�IRC���
 *
 *  PINT��IRQ����ߤǤ��ġ����å��ȥꥬ�ξ��ϳ�����׵�򥯥ꥢ���롥
 *  ���å��ȥꥬ��Ƚ�Ǥ���Τ����ݤʤΤǡ���˥��ꥢ���롥
 */
Inline void
i_begin_int(INTNO intno)
{
#ifdef SH3    
    uint8_t irr0_val;

    if (INTNO_PINT(intno)) {
        irr0_val = sil_reb_mem((void *) IRR0);
        irr0_val &= ~(0x40U << INTNO_PINT_OFFSET(intno));
    }
    else if (INTNO_IRQ(intno)) {
        irr0_val = sil_reb_mem((void *) IRR0);
        irr0_val &= ~(0x01U << INTNO_IRQ_OFFSET(intno));
    }
#endif    
}

/*
 *  ����ߥϥ�ɥ�νи���ɬ�פ�IRC���
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  ̤����γ���ߥϥ�ɥ�(default_int_handler())�ΰ��� p_excinf
 *  ����Ƽ�������Ф�����Υޥ���
 */
#define P_EXCINF_INT_OFFSET_SSR     (13U)
#define P_EXCINF_INT_OFFSET_SPC     (15U)
#define P_EXCINF_INT_OFFSET_PR      (14U)

/*
 *  CPU�㳰�ϥ�ɥ�ط�
 */ 

/*
 *  �㳰�ϥ�ɥ���� p_excinf ����Ƽ�������Ф�����Υޥ���
 */
#ifdef FPU_ENABLE

#ifdef FPU_SAVE_BANKED_REG

#define P_EXCINF_EXC_OFFSET_SSR     (12U + 14U + 16U)
#define P_EXCINF_EXC_OFFSET_SPC     (14U + 14U + 16U)
#define P_EXCINF_EXC_OFFSET_PR      (13U + 14U + 16U)
#define P_EXCINF_EXC_OFFSET_EXPEVT    0U 

#else

#define P_EXCINF_EXC_OFFSET_SSR     (12U + 14U)
#define P_EXCINF_EXC_OFFSET_SPC     (14U + 14U)
#define P_EXCINF_EXC_OFFSET_PR      (13U + 14U)
#define P_EXCINF_EXC_OFFSET_EXPEVT    0U

#endif /* FPU_SAVE_BANKED_REG */

#else

#define P_EXCINF_EXC_OFFSET_SSR     12U
#define P_EXCINF_EXC_OFFSET_SPC     14U
#define P_EXCINF_EXC_OFFSET_PR      13U
#define P_EXCINF_EXC_OFFSET_EXPEVT   0U

#endif /* FPU_ENABLE */

/*
 *  CPU�㳰�ϥ�ɥ����Ͽ�ѥơ��֥�
 */
extern const FP exch_tbl[TNUM_EXC];

/*
 *  CPU�㳰�ϥ�ɥ������
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{       
}

/*
 *  CPU�㳰�ϥ�ɥ�����������������ޥ���
 */
#define EXC_ENTRY(excno, exchdr)    exchdr
#define EXCHDR_ENTRY(excno, excno_num, exchdr) extern void exchdr(void *p_excinf);

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥλ���
 *
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥ�������������ƥ����Ȥλ���false��
 *  �����Ǥʤ�����true���֤���
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
    uint32_t nest;

    Asm("stc r7_bank,%0" : "=r"(nest));
    return(nest > 1U);
}

/*
 *  CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ���������ɽ
 *  ���ˤλ���
 */
Inline uint16_t
exc_get_iipm(void *p_excinf)
{
    return(*(((uint32_t *) p_excinf) + P_EXCINF_EXC_OFFSET_SSR) & 0x00F0U);
}

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥȳ���ߤΥޥ������֤λ���
 *
 *  CPU�㳰��ȯ���������Υ����ƥ���֤��������ͥ�¹���Ǥʤ�����������
 *  ��ƥ����ȤǤ��ꡤ����ߥ�å����֤Ǥʤ���CPU��å����֤Ǥʤ����ʥ�
 *  �ǥ��Ρ˳����ͥ���٥ޥ�����������֤Ǥ������true�������Ǥʤ���
 *  ��false���֤���CPU�㳰�������ͥ�������γ���߽������ȯ���������
 *  �ˤ�false���֤��ˡ�
 *
 *  SH�Ǥϡ�CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥ޥ�����
 *  �����٤Ƥγ���ߤ���Ĥ�����֤Ǥ��뤳�Ȥ�����å����뤳�Ȥǡ�����
 *  �ͥ�¹���Ǥʤ����ȡ�����ߥ�å����֤Ǥʤ����ȡ�CPU��å����֤Ǥ�
 *  �����ȡ��ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����������֤Ǥ��뤳�Ȥ�4�Ĥ�
 *  ��������å����뤳�Ȥ��Ǥ����CPU�㳰��ȯ����������lock_flag��
 *  �Ȥ���ɬ�פϤʤ��ˡ�
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
    return(!exc_sense_context(p_excinf)
                    && exc_get_iipm(p_excinf) == IIPM_ENAALL);
}

/*
 *  CPU�㳰��ȯ���������Υ���ƥ����Ȥȳ���ߡ�CPU��å����֤λ���
 *
 *  CPU�㳰��ȯ���������Υ����ƥ���֤��������ͥ�¹���Ǥʤ�����������
 *  ��ƥ����ȤǤ��ꡤ����ߥ�å����֤Ǥʤ���CPU��å����֤Ǥʤ�����
 *  true�������Ǥʤ�����false���֤���CPU�㳰�������ͥ�������γ���߽�
 *  �����ȯ���������ˤ�false���֤��ˡ�
 *
 *  SH34�Ǥϡ�CPU�㳰��ȯ����������IPM�ʥϡ��ɥ������γ����ͥ���٥�
 *  �����ˤ�TIPM_LOCK����㤤���Ȥ�����å����뤳�Ȥǡ������ͥ�¹����
 *  �ʤ����ȡ�����ߥ�å����֤Ǥʤ����ȡ�CPU��å����֤Ǥʤ����Ȥ�3��
 *  �ξ�������å����Ƥ����CPU�㳰��ȯ����������lock_flag�ϻ��Ȥ���
 *  ���ʤ��ˡ�����ˤ�ꡤ�ʥ�ǥ��Ρ˳����ͥ���٥ޥ�����TIPM_LOCK��
 *  ������ꤷ�ƥ�������¹Ԥ��Ƥ�����ˤ�false���֤äƤ��ޤ�����Ƚ�Ǥ�
 *  ���Τˤ��뤿��Υ����Хإåɤ��礭�����Ȥ��顤���Ƥ��뤳�Ȥˤ��롥
 */
Inline bool_t
exc_sense_unlock(void *p_excinf)
{
    return(!exc_sense_context(p_excinf)
                    && exc_get_iipm(p_excinf) < IIPM_LOCK);
}

/*
 * Trapa�ʳ����㳰����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
extern void default_exc_handler(void *p_excinf);

/*
 * ̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 */
extern void default_int_handler(void *p_excinf);

/*
 *  �ץ��å���¸�ν����
 */
extern void prc_initialize(void);

/*
 *  �ץ��å���¸�ν�λ������
 */
extern void prc_terminate(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
