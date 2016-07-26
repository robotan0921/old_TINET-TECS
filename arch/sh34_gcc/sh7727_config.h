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
 *  @(#) $Id: sh7727_config.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH7727�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_SH7727_CONFIG_H
#define TOPPERS_SH7727_CONFIG_H

/*
 * �ץ��å��μ���
 */
#define SH3

/*
 * ����ߥϥ�ɥ��ֹ�˴ؤ������
 */ 
#define TMIN_INHNO 0x1C0U
#define TMAX_INHNO 0xB60U
#define TNUM_INH   0x05CU

/*
 * ������ֹ�˴ؤ������
 */ 
#define TMIN_INTNO 0x1C0U
#define TMAX_INTNO 0xB60U
#define TNUM_INT   0x05CU

/*
 * ����ߥϥ�ɥ��ֹ������������ɽ������Ѵ�
 */
#define EXT_INHNO(iintno) (CAST(uint16_t, (iinhno) << 5)) /* ����ɽ������ɽ���� */
#define INT_INHNO(intno)  (CAST(uint16_t, (inhno) >> 5))  /* ����ɽ��������ɽ���� */

/*
 * ������ֹ������������ɽ������Ѵ�
 */
#define EXT_INTNO(iintno) (CAST(uint16_t, (iintno) << 5)) /* ����ɽ������ɽ���� */
#define INT_INTNO(intno)  (CAST(uint16_t, (intno) >> 5))  /* ����ɽ��������ɽ���� */

/*
 * ������ֹ�Ȥ���INTEVT2���ͤ���Ѥ���
 */
#define USE_INTEVT2

/*
 * ������֥�ǳ�����ֹ椫�� inh_tbl ���������Υޥ���
 * reg�ˤϡ�������ֹ���ݻ����Ƥ���
 * �쥸��������ꤹ�� 
 */
#ifdef TOPPERS_ASM_MACRO
.macro index_intno reg
    shlr2 \reg
    shlr  \reg
.endm
#endif /* TOPPERS_ASM_MACRO */
     
/*
 * CPU�㳰�ϥ�ɥ��ֹ�˴ؤ������
 */ 
#define TMIN_EXCNO 0x040U
#define TMAX_EXCNO 0x5C0U
#define TNUM_EXC   0x5DU
     
/*
 * CPU�㳰�ϥ�ɥ��ֹ������������ɽ������Ѵ�
 */
#define EXT_EXCNO(iexcno)  (CAST(uint16_t, (iexcno) << 4)) /* ����ɽ������ɽ���� */
#define INT_EXCNO(excno)   (CAST(uint16_t, (excno)  >> 4)) /* ����ɽ��������ɽ���� */

/*
 * ������֥��CPU�㳰�ֹ椫�� exch_tbl ���������Υޥ���
 * reg�ˤϡ�EXPEVT�쥸�������ͤ��ݻ����Ƥ���
 * �쥸��������ꤹ�� 
 */
#ifdef TOPPERS_ASM_MACRO
.macro index_excno reg
    shlr2 \reg
.endm
#endif /* TOPPERS_ASM_MACRO */

#ifndef TOPPERS_MACRO_ONLY

/*
 * ������׵�饤�����ͥ��������쥸�������������
 */
#define IPR_INFO_TBL_DATA   \
    {0U, 0},   /* 0x000(0x000) */ \
    {0U, 0},   /* 0x020(0x001) */ \
    {0U, 0},   /* 0x040(0x002) */ \
    {0U, 0},   /* 0x060(0x003) */ \
    {0U, 0},   /* 0x080(0x004) */ \
    {0U, 0},   /* 0x0A0(0x005) */ \
    {0U, 0},   /* 0x0C0(0x006) */ \
    {0U, 0},   /* 0x100(0x007) */ \
    {0U, 0},   /* 0x100(0x008) */ \
    {0U, 0},   /* 0x120(0x009) */ \
    {0U, 0},   /* 0x140(0x00A) */ \
    {0U, 0},   /* 0x160(0x00B) */ \
    {0U, 0},   /* 0x180(0x00C) */ \
    {0U, 0},   /* 0x1A0(0x00D) */ \
\
    {0U, 0},   /* 0x1C0(0x00E) NMI */ \
\
    {0U, 0},   /* 0x1E0(0x00F) */ \
\
    {0U, 0},   /* 0x200(0x010) IPL 0000 */ \
    {0U, 0},   /* 0x220(0x011) IPL 0001 */ \
    {0U, 0},   /* 0x240(0x012) IPL 0010 */ \
    {0U, 0},   /* 0x260(0x013) IPL 0011 */ \
    {0U, 0},   /* 0x280(0x014) IPL 0100 */ \
    {0U, 0},   /* 0x2A0(0x015) IPL 0101 */ \
    {0U, 0},   /* 0x2C0(0x016) IPL 0110 */ \
    {0U, 0},   /* 0x2E0(0x017) IPL 0111 */ \
    {0U, 0},   /* 0x300(0x018) IPL 1000 */ \
    {0U, 0},   /* 0x320(0x019) IPL 1001 */ \
    {0U, 0},   /* 0x340(0x01A) IPL 1010 */ \
    {0U, 0},   /* 0x360(0x01B) IPL 1011 */ \
    {0U, 0},   /* 0x380(0x01C) IPL 1100 */ \
    {0U, 0},   /* 0x3A0(0x01D) IPL 1101 */ \
    {0U, 0},   /* 0x3C0(0x01E) IPL 1110 */ \
\
    {0U, 0},   /* 0x3E0(0x01F)  */ \
\
    {IPRA, 12},/* 0x400(0x020) TMU0 TUNI0  */ \
\
    {IPRA, 8}, /* 0x420(0x021) TMU1 TUNI1  */ \
\
    {IPRA, 4}, /* 0x440(0x022) TMU2 TUNI2  */ \
    {IPRA, 4}, /* 0x460(0x023)      TICPI2 */ \
\
    {IPRA, 0}, /* 0x480(0x024) RTC  ATI    */ \
    {IPRA, 0}, /* 0x4A0(0x025)      PRI    */ \
    {IPRA, 0}, /* 0x4C0(0x026)      CUI    */ \
\
    {IPRB, 4}, /* 0x4E0(0x027) SCI0 ERI    */ \
    {IPRB, 4}, /* 0x500(0x028)      RXI    */ \
    {IPRB, 4}, /* 0x520(0x029)      TXI    */ \
    {IPRB, 4}, /* 0x540(0x02A)      TEI    */ \
\
    {IPRB,12}, /* 0x560(0x02B) WDT  ITI    */ \
\
    {IPRB, 8}, /* 0x580(0x02C) REF  RCMI   */ \
    {IPRB, 8}, /* 0x5A0(0x02D)      ROVI   */ \
\
    {0U, 0},   /* 0x5C0(0x02E)             */ \
\
    {0U, 0},   /* 0x5E0(0x02F) HUDI        */ \
\
    {IPRC, 0}, /* 0x600(0x030) IRQ IRQ0    */ \
    {IPRC, 4}, /* 0x620(0x031)     IRQ1    */ \
    {IPRC, 8}, /* 0x640(0x032)     IRQ2    */ \
    {IPRC,12}, /* 0x660(0x033)     IRQ3    */ \
    {IPRD, 0}, /* 0x680(0x034)     IRQ4    */ \
    {IPRD, 4}, /* 0x6A0(0x035)     IRQ5    */ \
\
    {0U, 0},   /* 0x6C0(0x036)             */ \
    {0U, 0},   /* 0x6E0(0x037)             */ \
\
    {IPRD,12}, /* 0x700(0x038) PINT PINT0-7  */ \
    {IPRD, 8}, /* 0x720(0x039)      PINT80U5 */ \
\
    {0U, 0},   /* 0x740(0x03A)             */ \
    {0U, 0},   /* 0x760(0x03B)             */ \
    {0U, 0},   /* 0x780(0x03C)             */ \
    {0U, 0},   /* 0x7A0(0x03D)             */ \
    {0U, 0},   /* 0x7C0(0x03E)             */ \
    {0U, 0},   /* 0x7E0(0x03F)             */ \
\
    {IPRE,12}, /* 0x800(0x040) DMAC DEI0 */ \
    {IPRE,12}, /* 0x820(0x041)      DEI1 */ \
    {IPRE,12}, /* 0x840(0x042)      DEI2 */ \
    {IPRE,12}, /* 0x860(0x043)      DEI3 */ \
\
    {0U, 0},   /* 0x880(0x044)             */ \
    {0U, 0},   /* 0x8A0(0x045)             */ \
    {0U, 0},   /* 0x8C0(0x046)             */ \
    {0U, 0},   /* 0x8E0(0x047)             */ \
\
    {IPRE, 4}, /* 0x900(0x048) SCIF ERI2 */ \
    {IPRE, 4}, /* 0x920(0x049)      RXI2 */ \
    {IPRE, 4}, /* 0x940(0x04A)      BRI2 */ \
    {IPRE, 4}, /* 0x960(0x04B)      TXI2 */ \
\
    {IPRE, 0}, /* 0x980(0x04C) ADC   ADI   */ \
\
    {IPRF, 8}, /* 0x9A0(0x04D) LCDC  LCDCI */ \
\
    {IPRF, 4}, /* 0x9C0(0x04E) PCC0        */ \
\
    {0U, 0},   /* 0x9E0(0x04F)             */ \
\
    {IPRG,12}, /* 0xA00(0x050) USBH  USBHI */ \
    {IPRG, 8}, /* 0xA20(0x051) USBF  USBFI0*/ \
    {IPRG, 4}, /* 0xA40(0x052)       USBFI1*/ \
\
    {IPRG, 0}, /* 0xA60(0x053) AFEIF AFEIFI*/ \
\
    {0U, 0},   /* 0xA80(0x054)             */ \
    {0U, 0},   /* 0xAA0(0x055)             */ \
    {0U, 0},   /* 0xAC0(0x056)             */ \
    {0U, 0},   /* 0xAE0(0x057)             */ \
\
    {IPRF, 0}, /* 0xB00(0x058) SIOF  SIFERI*/ \
    {IPRF, 0}, /* 0xB20(0x059)       SIFTXI*/ \
    {IPRF, 0}, /* 0xB40(0x05A)       SIFRXI*/ \
    {IPRF, 0}, /* 0xB60(0x05B)       SIFCCI*/ \


/*
 * IRC�ν����
 */
Inline void
init_irc(void)
{
    sil_wrh_mem((void*)ICR1, 0x4000);
    sil_wrh_mem((void*)ICR2, 0x0000);     
    sil_wrh_mem((void*)PINTER, 0x0000);
    sil_wrh_mem((void*)IPRC, 0x0000);
    sil_wrh_mem((void*)IPRD, 0x0000);
    sil_wrh_mem((void*)IPRE, 0x0000);
    sil_wrh_mem((void*)IPRF, 0x0000);
    sil_wrh_mem((void*)IPRG, 0x0000);
    sil_wrb_mem((void*)IRR0, 0x0000);   
    sil_wrb_mem((void*)IRR1, 0x0000);
    sil_wrb_mem((void*)IRR2, 0x0000);   
}

/*
 * �����ͥ���٥쥸����������
 */
Inline void
set_irc_ipr(uint32_t address, uint32_t offset, uint8_t val)
{
    uint16_t ipr_val;
    
    ipr_val = sil_reh_mem((void *) address);
    ipr_val &= ~(0x0FU << offset);
    ipr_val |= (uint32_t)val << offset;    
    sil_wrh_mem((void *) address, ipr_val);
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �ץ��å���¸�⥸�塼���SH34�ѡ�
 */
#include "sh34_gcc/prc_config.h"

#endif /* TOPPERS_SH7727_CONFIG_H */
