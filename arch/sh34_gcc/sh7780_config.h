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
 *  @(#) $Id: sh7780_config.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *		�ץ��å���¸�⥸�塼���SH7780�ѡ�
 *
 *  ���Υ��󥯥롼�ɥե�����ϡ�target_config.h�ʤޤ��ϡ��������饤��
 *  �롼�ɤ����ե�����ˤΤߤ��饤�󥯥롼�ɤ���롥¾�Υե����뤫��
 *  ľ�ܥ��󥯥롼�ɤ��ƤϤʤ�ʤ���
 */

#ifndef TOPPERS_SH7780_CONFIG_H
#define TOPPERS_SH7780_CONFIG_H

/*
 * �ץ��å��μ���
 */
#define SH4A

#ifdef FPU_ENABLE
/*
 *  FPSCR��PR�ӥåȤν����
 */
#ifdef FPU_DOUBLE
#define FPSCR_PR_INIT 0x00080000  /* ������ */
#else  /* FPU_SINGLE FPU_SINGLE_ONLY */
#define FPSCR_PR_INIT 0x0000000   /* ñ���� */
#endif /* FPU_DOUBLE */

/*
 *  FPSCR��PR�ӥåȰʳ�����������
 */
#ifndef FPSCR_INIT
#define FPSCR_INIT 0x00040000
#endif  /* FPSCR_INIT */
#endif /* FPU_ENABLE */

/*
 * ����ߥϥ�ɥ��ֹ�˴ؤ������
 */ 
#define TMIN_INHNO 0x1C0U
#define TMAX_INHNO 0xFE0U
#define TNUM_INH   0x080U

/*
 * ������ֹ�˴ؤ������
 */ 
#define TMIN_INTNO 0x1C0U
#define TMAX_INTNO 0xFE0U
#define TNUM_INT   0x080U

/*
 * ����ߥϥ�ɥ��ֹ������������ɽ������Ѵ�
 */
#define EXT_INHNO(iintno) (CAST(uint16_t, (iinhno) << 5)) /* ����ɽ������ɽ���� */
#define INT_INHNO(intno)  (CAST(uint16_t, (inhno) >> 5))  /* ����ɽ��������ɽ���� */

/*
 * ������ֹ������������ɽ������Ѵ�
 */
#define EXT_INTNO(iintno)   (CAST(uint16_t, (iintno) << 5)) /* ����ɽ������ɽ���� */
#define INT_INTNO(intno)    (CAST(uint16_t, (intno) >> 5))  /* ����ɽ��������ɽ���� */

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
#define TMAX_EXCNO 0x820U
#define TNUM_EXC   0x42U
     
/*
 * CPU�㳰�ϥ�ɥ��ֹ������������ɽ������Ѵ�
 */
#define EXT_EXCNO(iexcno)  (CAST(uint16_t, (iexcno) << 5)) /* ����ɽ������ɽ���� */
#define INT_EXCNO(excno)   (CAST(uint16_t, (excno)  >> 5)) /* ����ɽ��������ɽ���� */

/*
 * ������֥��CPU�㳰�ֹ椫�� exch_tbl ���������Υޥ���
 * reg�ˤϡ�EXPEVT�쥸�������ͤ��ݻ����Ƥ���
 * �쥸��������ꤹ�� 
 */
#ifdef TOPPERS_ASM_MACRO
.macro index_excno reg
    shlr2 \reg
    shlr  \reg
.endm
#endif /* TOPPERS_ASM_MACRO */

#ifndef TOPPERS_MACRO_ONLY

/*
 * ������׵�饤�����ͥ��������쥸�������������
 */
#define IPR_INFO_TBL_DATA \
    {0U, 0},        /* 0x000(0x000) */ \
    {0U, 0},        /* 0x020(0x001) */ \
    {0U, 0},        /* 0x040(0x002) */ \
    {0U, 0},        /* 0x060(0x003) */ \
    {0U, 0},        /* 0x080(0x004) */ \
    {0U, 0},        /* 0x0A0(0x005) */ \
    {0U, 0},        /* 0x0C0(0x006) */ \
    {0U, 0},        /* 0x100(0x007) */ \
    {0U, 0},        /* 0x100(0x008) */ \
    {0U, 0},        /* 0x120(0x009) */ \
    {0U, 0},        /* 0x140(0x00A) */ \
    {0U, 0},        /* 0x160(0x00B) */ \
    {0U, 0},        /* 0x180(0x00C) */ \
    {0U, 0},        /* 0x1A0(0x00D) */ \
\
    {0U, 0},        /* 0x1C0(0x00E) NMI */ \
\
    {0U, 0},        /* 0x1E0(0x00F) */ \
\
    {INTPRI, 28},        /* 0x200(0x010) IRL 0000 */ \
    {0U, 0},        /* 0x220(0x011) IRL 0001 */ \
    {0U, 0},        /* 0x240(0x012) IRL 0010 */ \
    {0U, 0},        /* 0x260(0x013) IRL 0011 */ \
    {0U, 0},        /* 0x280(0x014) IRL 0100 */ \
    {0U, 0},        /* 0x2A0(0x015) IRL 0101 */ \
    {0U, 0},        /* 0x2C0(0x016) IRL 0110 */ \
    {0U, 0},        /* 0x2E0(0x017) IRL 0111 */ \
    {0U, 0},        /* 0x300(0x018) IRL 1000 */ \
    {0U, 0},        /* 0x320(0x019) IRL 1001 */ \
    {0U, 0},        /* 0x340(0x01A) IRL 1010 */ \
    {0U, 0},        /* 0x360(0x01B) IRL 1011 */ \
    {0U, 0},        /* 0x380(0x01C) IRL 1100 */ \
    {0U, 0},        /* 0x3A0(0x01D) IRL 1101 */ \
    {0U, 0},        /* 0x3C0(0x01E) IRL 1110 */ \
\
    {0U, 0},        /* 0x3E0(0x01F) */ \
    {INT2PRI1, 24},        /* 0x400(0x020) */ \
    {0U, 0},        /* 0x420(0x021) */ \
    {0U, 0},        /* 0x440(0x022) */ \
    {0U, 0},        /* 0x460(0x023) */ \
\
    {INT2PRI1,  0}, /* 0x480(0x024) RTC  ATI */ \
    {INT2PRI1,  0}, /* 0x4A0(0x025)      PRI */ \
    {INT2PRI1,  0}, /* 0x4C0(0x026)      CUI */ \
\
    {0U, 0},        /* 0x4E0(0x027) */ \
    {0U, 0},        /* 0x500(0x028) */ \
    {0U, 0},        /* 0x520(0x029) */ \
    {0U, 0},        /* 0x540(0x02A) */ \
\
    {INT2PRI2,  8}, /* 0x560(0x02B) WDT  ITI */ \
\
    {INT2PRI0, 24}, /* 0x580(0x02C) TMU-ch0 TUNI0 */ \
    {INT2PRI0, 16}, /* 0x5A0(0x02D) TMU-ch1 TUNI1 */ \
    {INT2PRI0,  8}, /* 0x5C0(0x02E) TMU-ch2 TUNI2 */ \
    {INT2PRI0,  0}, /* 0x5E0(0x02F)         TICPI2*/ \
\
    {INT2PRI3, 24}, /* 0x600(0x030) H-UDI H-UDII */ \
\
    {0U, 0},        /* 0x620(0x031) */ \
\
    {INT2PRI3, 16}, /* 0x640(0x032) DMAC DMINT0 */ \
    {INT2PRI3, 16}, /* 0x660(0x033)      DMINT1 */ \
    {INT2PRI3, 16}, /* 0x680(0x034)      DMINT2 */ \
    {INT2PRI3, 16}, /* 0x6A0(0x035)      DMINT3 */ \
    {INT2PRI3, 16}, /* 0x6C0(0x036)      DMAE   */ \
\
    {0U, 0},        /* 0x6E0(0x037)             */ \
\
    {INT2PRI2, 24}, /* 0x700(0x038) SCIF-ch0 ERI0 */ \
    {INT2PRI2, 24}, /* 0x720(0x039)          RXI0 */ \
    {INT2PRI2, 24}, /* 0x740(0x03A)          BRI0 */ \
    {INT2PRI2, 24}, /* 0x760(0x03B)          TXI0 */ \
\
    {INT2PRI3, 16}, /* 0x780(0x03C) DMAC(0) DMINT4 */ \
    {INT2PRI3, 16}, /* 0x7A0(0x03D)         DMINT5 */ \
\
    {INT2PRI3,  8}, /* 0x7C0(0x03E) DMAC(1) DMINT6 */ \
    {INT2PRI3,  8}, /* 0x7E0(0x03F)         DMINT7 */ \
\
    {0U, 0},        /* 0x800(0x040) */ \
    {0U, 0},        /* 0x820(0x041) */ \
    {0U, 0},        /* 0x840(0x042) */ \
    {0U, 0},        /* 0x860(0x043) */ \
    {0U, 0},        /* 0x880(0x044) */ \
    {0U, 0},        /* 0x8A0(0x045) */ \
    {0U, 0},        /* 0x8C0(0x046) */ \
    {0U, 0},        /* 0x8E0(0x047) */ \
\
    {INT2PRI4, 24}, /* 0x900(0x048) CMT CMTI*/ \
\
    {0U, 0},        /* 0x920(0x049) */ \
    {0U, 0},        /* 0x940(0x04A) */ \
    {0U, 0},        /* 0x960(0x04B) */ \
\
    {INT2PRI4, 16}, /* 0x980(0x04C) HAC HACI */ \
\
    {0U, 0},        /* 0x9A0(0x04D) */ \
    {0U, 0},        /* 0x9C0(0x04E) */ \
    {0U, 0},        /* 0x9E0(0x04F) */ \
\
    {INT2PRI4,  8}, /* 0xA00(0x050) PCIC(0) PCISERR */ \
\
    {INT2PRI4,  0}, /* 0xA20(0x051) PCIC(1) PCIINTA */ \
\
    {INT2PRI5, 24}, /* 0xA40(0x052) PCIC(2) PCIINTB */ \
\
    {INT2PRI5, 16}, /* 0xA60(0x053) PCIC(3) PCIINTC */ \
\
    {INT2PRI5,  8}, /* 0xA80(0x054) PCIC(4) PCIINTC */ \
\
    {INT2PRI5, 0},  /* 0xAA0(0x055) PCIC(5) PCIERR  */ \
    {INT2PRI5, 0},  /* 0xAC0(0x056)         PCIPWD3 */ \
    {INT2PRI5, 0},  /* 0xAE0(0x057)         PCIPWD2 */ \
    {INT2PRI5, 0},  /* 0xB00(0x058)         PCIPWD1 */ \
    {INT2PRI5, 0},  /* 0xB20(0x059)         PCIPWD0 */ \
\
    {0U, 0},        /* 0xB40(0x05A) */ \
    {0U, 0},        /* 0xB60(0x05B) */ \
\
    {INT2PRI2, 16}, /* 0xB80(0x05C) SCIF-ch1 ERI1 */ \
    {INT2PRI2, 16}, /* 0xBA0(0x05D)          RXI1 */ \
    {INT2PRI2, 16}, /* 0xBC0(0x05E)          BRI1 */ \
    {INT2PRI2, 16}, /* 0xBE0(0x05F)          TXI1 */ \
\
    {INT2PRI6, 24}, /* 0xC00(0x060) SIOF SIOFI */ \
\
    {0U, 8},        /* 0xC20(0x061) */ \
    {0U, 4},        /* 0xC40(0x062) */ \
    {0U, 0},        /* 0xC60(0x063) */ \
\
    {INT2PRI6, 16}, /* 0xC80(0x064) HSPI SPII */ \
\
    {0U, 0},        /* 0xCA0(0x065) */ \
    {0U, 0},        /* 0xCC0(0x066) */ \
    {0U, 0},        /* 0xCE0(0x067) */ \
\
    {INT2PRI6,  8}, /* 0xC00(0x068) MMCIF FSTAT */ \
    {INT2PRI6,  8}, /* 0xD20(0x069)       TRAN  */ \
    {INT2PRI6,  8}, /* 0xD40(0x06A)       ERR   */ \
    {INT2PRI6,  8}, /* 0xD60(0x06B)       FRDY  */ \
\
    {INT2PRI3,  8}, /* 0xD80(0x06C) DMAC(1) DMINT8 */ \
    {INT2PRI3,  8}, /* 0xDA0(0x06D)         DMINT9 */ \
    {INT2PRI3,  8}, /* 0xDC0(0x06E)         DMINT10 */ \
    {INT2PRI3,  8}, /* 0xDE0(0x06F)         DMINT11 */ \
\
    {INT2PRI1, 24}, /* 0xE00(0x070) TMU-ch3 TUNI3 */ \
\
    {INT2PRI1, 16}, /* 0xE20(0x071) TMU-ch4 TUNI4 */ \
\
    {INT2PRI1,  8}, /* 0xE40(0x072) TMU-ch5 TUNI5 */ \
\
    {0U, 0},        /* 0xE60(0x073) */ \
\
    {INT2PRI6, 0},  /* 0xE80(0x074) SSI SII */ \
\
    {0U, 0},        /* 0xEA0(0x075) */ \
    {0U, 0},        /* 0xEC0(0x076) */ \
    {0U, 0},        /* 0xEE0(0x077) */ \
\
    {INT2PRI7, 24}, /* 0xF00(0x078) FLCTL FLSTE  */ \
    {INT2PRI7, 24}, /* 0xF20(0x079)       FLTEND */ \
    {INT2PRI7, 24}, /* 0xF40(0x07A)       FLTRQ0 */ \
    {INT2PRI7, 24}, /* 0xF60(0x07B)       FLTRQ1 */ \
\
    {INT2PRI7, 16}, /* 0xF80(0x07C) GPIO GPIOI0 */ \
    {INT2PRI7, 16}, /* 0xFA0(0x07D)      GPIOI1 */ \
    {INT2PRI7, 16}, /* 0xFC0(0x07E)      GPIOI2 */ \
    {INT2PRI7, 16}, /* 0xFE0(0x07F)      GPIOI3 */ \

/*
 * IRC�ν����
 */
Inline void
init_irc(void)
{
    sil_wrw_mem((void*)ICR0, 0x00000000U);
    sil_wrw_mem((void*)ICR1, 0x00000000U);
    sil_wrw_mem((void*)INT2PRI0, 0x00000000U);
    sil_wrw_mem((void*)INT2PRI1, 0x02000000U); //change
    sil_wrw_mem((void*)INT2PRI2, 0x00000000U);
    sil_wrw_mem((void*)INT2PRI3, 0x00000000U);
    sil_wrw_mem((void*)INT2PRI4, 0x00000000U);
    sil_wrw_mem((void*)INT2PRI5, 0x00000000U);
    sil_wrw_mem((void*)INT2PRI6, 0x00000000U);
    sil_wrw_mem((void*)INT2PRI7, 0x00000000U);

    /* ����ߥޥ����򥯥ꥢ */
    sil_wrw_mem((void*)INT2MSKCR, 0x80000000U);
}

/*
 * �����ͥ���٥쥸����������
 */
Inline void
set_irc_ipr(uint32_t address, uint32_t offset, uint8_t val)
{
    uint32_t ipr_val;
    
    ipr_val = sil_rew_mem((void *) address);
    ipr_val &= ~(0x0FU << offset);
    ipr_val |= (uint32_t)val << offset;    
    sil_wrw_mem((void *) address, ipr_val);
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  �ץ��å���¸�⥸�塼���SH34�ѡ�
 */
#include "sh34_gcc/prc_config.h"

#endif /* TOPPERS_SH7727_CONFIG_H */
