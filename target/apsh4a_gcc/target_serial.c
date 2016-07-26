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
 *  @(#) $Id: target_serial.c 1603 2009-07-03 06:39:20Z ertl-honda $
 */

/*
 *  ���ꥢ��I/O�ǥХ�����SIO�˥ɥ饤�С�APSH4A�ѡ�
 *  SCIF0 ����� 
 */

#include <kernel.h>
#include <t_syslog.h>
#include "target_serial.h"

/*
 *  SIO�ɥ饤�Фν����
 */
void
sio_initialize(intptr_t exinf)
{
    sh_scif_initialize();    
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ����ץ�
 */
SIOPCB *
sio_opn_por(ID siopid, intptr_t exinf)
{
    SIOPCB    *p_siopcb;
    ER        ercd;
    INTNO	intno_sio_tx, intno_sio_rx;

    /*
     *  ���ꥢ��I/O����ߤ�ޥ������롥
     */
    p_siopcb = sh_scif_get_siopcb(siopid);
    intno_sio_tx = sh_scif_intno_tx(p_siopcb);
    intno_sio_rx = sh_scif_intno_rx(p_siopcb);
    ercd = dis_int(intno_sio_tx);
    assert(ercd == E_OK);
    ercd = dis_int(intno_sio_rx);
    assert(ercd == E_OK);

    /*
     *  �ǥХ�����¸�Υ����ץ������
     */
    p_siopcb = sh_scif_opn_por(siopid, exinf);

    /*
     *  ���ꥢ��I/O����ߤΥޥ����������롥
     */
    ercd = ena_int(intno_sio_tx);
    assert(ercd == E_OK);
    ercd = ena_int(intno_sio_rx);
    assert(ercd == E_OK);

    return(p_siopcb);
}

/*
 *  ���ꥢ��I/O�ݡ��ȤΥ�����
 */
void
sio_cls_por(SIOPCB *p_siopcb)
{
    ER        ercd;
    INTNO	intno_sio_tx, intno_sio_rx;

    /*
     *  �ǥХ�����¸�Υ�����������
     */
    sh_scif_cls_por(p_siopcb);

    /*
     *  ���ꥢ��I/O����ߤ�ޥ������롥
     */
    intno_sio_tx = sh_scif_intno_tx(p_siopcb);
    intno_sio_rx = sh_scif_intno_rx(p_siopcb);
    ercd = dis_int(intno_sio_tx);
    assert(ercd == E_OK);
    ercd = dis_int(intno_sio_rx);
    assert(ercd == E_OK);
}

/*
 *  SIO�γ���ߥϥ�ɥ�
 */
void
sio_tx_isr(intptr_t exinf)
{
    sh_scif_tx_isr(1);
}


/*
 *  SIO�γ���ߥϥ�ɥ�
 */
void
sio_rx_isr(intptr_t exinf)
{
    sh_scif_rx_isr(1);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥؤ�ʸ������
 */
bool_t
sio_snd_chr(SIOPCB *siopcb, char_t c)
{
    return(sh_scif_snd_chr(siopcb, c));
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����ʸ������
 */
int_t
sio_rcv_chr(SIOPCB *siopcb)
{
    return(sh_scif_rcv_chr(siopcb));
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ε���
 */
void
sio_ena_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
    sh_scif_ena_cbr(siopcb, cbrtn);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���Υ�����Хå��ζػ�
 */
void
sio_dis_cbr(SIOPCB *siopcb, uint_t cbrtn)
{
    sh_scif_dis_cbr(siopcb, cbrtn);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ����������ǽ������Хå�
 */
void
sh_scif_irdy_snd(intptr_t exinf)
{
//    sio_irdy_snd(exinf);
}

/*
 *  ���ꥢ��I/O�ݡ��Ȥ���μ������Υ�����Хå�
 */
void
sh_scif_irdy_rcv(intptr_t exinf)
{
//    sio_irdy_rcv(exinf);
}
