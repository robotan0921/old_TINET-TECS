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
 *  @(#) $Id: prc_timer.c 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *  �����ޥɥ饤�С�SH34�ѡ�
 */

#include "kernel_impl.h"
#include "time_event.h"
#include <sil.h>
#include "target_timer.h"
#ifdef TRACE_ENABLE
SYSTIM target_time;
#endif /* TRACE_ENABLE */

/*
 *  �����ޤε�ư����
 */
void
target_timer_initialize(intptr_t exinf)
{
    CLOCK    cyc = TO_CLOCK(TIC_NUME, TIC_DENO);

    /*
     *  �����޼��������ꤷ�������ޤ�ư��򳫻Ϥ��롥
     */
    sil_wrb_mem((void*)TMU_TSTR,
                (sil_reb_mem((void*)TMU_TSTR) & ~TMU_STR0));  /* ��������� */
    assert(cyc <= MAX_CLOCK);             /* �����޾���ͤΥ����å� */

    /* ʬ�������ꡢ�����ߵ��� */
    sil_wrh_mem((void*)TMU_TCR0,(0x020 | TCR0_TPSC));
    
    sil_wrw_mem((void*)TMU_TCOR0, cyc); /* timer constant�쥸�����򥻥å� */
    sil_wrw_mem((void*)TMU_TCNT0, cyc); /* �����󥿡��򥻥å� */    
    /* ������0�������� */
    sil_wrb_mem((void*)TMU_TSTR,
                (sil_reb_mem((void*)TMU_TSTR) | TMU_STR0));

    /*
     *  �����޳�����׵�򥯥ꥢ���롥
     */
    /* �������׵�򥯥ꥢ */
    sil_wrh_mem((void*)TMU_TCR0,
                (sil_reh_mem((void*)TMU_TCR0) & ~TCR_UNF));

#ifdef TRACE_ENABLE
    target_time = 0;
#endif /* TRACE_ENABLE */    
}

/*
 *  �����ޤ���߽���
 */
void
target_timer_terminate(intptr_t exinf)
{
    /* �����ޤ���� */
    sil_wrb_mem((void*)TMU_TSTR,
                (sil_reb_mem((void*)TMU_TSTR) & ~TMU_STR0));
    /* �������׵�򥯥ꥢ */
    sil_wrh_mem((void*)TMU_TCR0,0);
}

/*
 *  �����޳���ߥϥ�ɥ�
 */
void
target_timer_handler(void)
{
    /* �������׵�򥯥ꥢ */
    sil_wrh_mem((void*)TMU_TCR0,
                (sil_reh_mem((void*)TMU_TCR0) & ~TCR_UNF));

#ifdef TRACE_ENABLE    
    target_time++;
#endif /* TRACE_ENABLE */    
      
    i_begin_int(INTNO_TIMER);
    signal_time();                    /* ������ƥ��å��ζ��� */
    i_end_int(INTNO_TIMER);
}
