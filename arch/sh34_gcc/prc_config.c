/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2005-2009 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.c 1602 2009-07-03 06:30:16Z ertl-honda $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH34�ѡ�
 */

#include "kernel_impl.h"
#include "check.h"
#include "task.h"

/*
 *  CPU��å��ե饰�¸��Τ�����ѿ�
 */
volatile bool_t		lock_flag;		/* CPU��å��ե饰���ͤ��ݻ������ѿ� */
volatile uint8_t	saved_iipm;		/* �����ͥ���٥ޥ�������¸�����ѿ� */

/*
 *  �Ƴ�����ֹ����IPR�ξ�������ơ��֥�
 *  ���Ƥ�����ϡ��ץ��å�������˰ۤʤ�Τ��ᡤ
 *  �ץ��å������������ե�������������
 */
const IPR_INFO ipr_info_tbl[TNUM_INH] = {
    IPR_INFO_TBL_DATA 
};

/*
 *  �٥������١�������¸��
 */
static void *saved_vbr;

/*
 *  �����ͥ�Υ٥������١���
 */
extern void base_vec(void);

/*
 *  �ץ��å���¸�ν����
 */
void
prc_initialize(void)
{
    /*
     *  CPU��å��ե饰�¸��Τ�����ѿ��ν����
     */
    lock_flag = true;
    saved_iipm = IIPM_ENAALL;
    
    /*
     *  ����ߥ���ȥ���ν����
     *  �ץ��å����������� 
     */
    init_irc();

    /*
     *  �٥������١����쥸�����ν����
     */
    saved_vbr = current_vbr();
    set_vbr(base_vec);
}

/*
 *  �ץ��å���¸�ν�λ����
 */
void
prc_terminate(void)
{
    extern void    software_term_hook(void);
    void (*volatile fp)(void) = software_term_hook;

    /*
     *  software_term_hook�ؤΥݥ��󥿤򡤰�övolatile����Τ���fp����
     *  �����Ƥ���Ȥ��Τϡ�0�Ȥ���Ӥ���Ŭ���Ǻ������ʤ��褦�ˤ��뤿
     *  ��Ǥ��롥
     */
    if (fp != 0) {
        (*fp)();
    }

    set_vbr(saved_vbr);
}

/*
 *  ������׵�饤��°��������
 */
void
x_config_int(INTNO intno, ATR intatr, PRI intpri)
{
    assert(VALID_INTNO_CFGINT(intno));
    assert(-15 <= intpri && intpri <= TMAX_INTPRI);

    /* 
     *  ��ö����ߤ�ػߤ���
     */    
    (void)x_disable_int(intno);

    /*
     *  ��٥�ȥꥬ/���å��ȥꥬ������
     *  IRQ�Τߥ��ݡ��Ȥ���
     */
    if(INTNO_IRQ(intno) != 0U){
        uint16_t icr1_val = sil_rew_mem((void*)ICR1);
        uint16_t offset   = INTNO_IRQ_OFFSET(intno) * 2U;

        icr1_val &=  ~(0x03U << offset);
        
        if((intatr & TA_POSEDGE) != 0U) {
            /*
             *  �ݥ��ƥ��֥��å�
             */
            icr1_val |= IRQ_POSEDGE << offset;            
        }else if((intatr & TA_NEGEDGE) != 0U) {
            /*
             *  �ͥ��ƥ��֥��å�
             */
            icr1_val |= IRQ_NEGEDGE << offset;                        
        }else {
            /*
             *  ����٥�ȥꥬ
             */
            icr1_val |= IRQ_LOWLEVEL << offset;
        }
        
        sil_wrw_mem((void*)ICR1, icr1_val);
    }

    /*
     *  ������׵�ޥ������(ɬ�פʾ��)
     *  Ʊ���˳����ͥ���٤⥻�åȤ����
     */
    if ((intatr & TA_ENAINT) != 0U) {
        (void) x_enable_int(intno);
    }    
}


#ifndef OMIT_DEFAULT_EXC_HANDLER
/*
 *  Trapa�ʳ����㳰����Ͽ����Ƥ��ʤ��㳰��ȯ������ȸƤӽФ����
 */
void
default_exc_handler(void *p_excinf)
{
    uint32_t expevt = *(((uint32_t*)p_excinf) + P_EXCINF_EXC_OFFSET_EXPEVT);
    uint32_t spc    = *(((uint32_t*)p_excinf) + P_EXCINF_EXC_OFFSET_SPC);
    uint32_t ssr    = *(((uint32_t*)p_excinf) + P_EXCINF_EXC_OFFSET_SSR);
    uint32_t pr     = *(((uint32_t*)p_excinf) + P_EXCINF_EXC_OFFSET_PR);
    
    syslog(LOG_EMERG, "Unregistered Expevt error occurs.");
    syslog(LOG_EMERG, "Expevt = %08x SPC = %08x SR = %08x PR=%08X",
           expevt, spc, ssr, pr);
    target_exit();
}
#endif /* OMIT_DEFAULT_EXC_HANDLER */

#ifndef OMIT_DEFAULT_INT_HANDLER
/*
 *  ̤��Ͽ�γ���ߤ�ȯ���������˸ƤӽФ����
 */
void
default_int_handler(void *p_excinf)
{
    uint32_t spc     = *(((uint32_t*)p_excinf) + P_EXCINF_INT_OFFSET_SPC);
    uint32_t ssr     = *(((uint32_t*)p_excinf) + P_EXCINF_INT_OFFSET_SSR);
    uint32_t pr      = *(((uint32_t*)p_excinf) + P_EXCINF_INT_OFFSET_PR);
    uint32_t intevt  = sil_rew_mem((void*)INTEVT);
#ifdef USE_INTEVT2    
    uint32_t intevt2 = sil_rew_mem((void*)INTEVT2);
#endif /* USE_INTEVT2 */      
    syslog(LOG_EMERG, "Unregistered Interrupt occurs.");
#ifdef USE_INTEVT2    
    syslog(LOG_EMERG, "INTEVT = %08x INTEVT2 = %08x SPC = %08x SR = %08x PR = %08x ",
           intevt, intevt2, spc, ssr, pr);
#else
    syslog(LOG_EMERG, "INTEVT = %08x SPC = %08x SR = %08x PR = %08x ",
           intevt, spc, ssr, pr);    
#endif /* USE_INTEVT2 */      
    target_exit();
}
#endif /* OMIT_DEFAULT_INT_HANDLER */
