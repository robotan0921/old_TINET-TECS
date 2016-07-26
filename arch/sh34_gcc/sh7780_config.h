/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007 by Embedded and Real-Time Systems Laboratory
 *              Graduate School of Information Science, Nagoya Univ., JAPAN
 * 
 *  上記著作権者は，以下の(1)〜(4)の条件を満たす場合に限り，本ソフトウェ
 *  ア（本ソフトウェアを改変したものを含む．以下同じ）を使用・複製・改
 *  変・再配布（以下，利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 *      また，本ソフトウェアのユーザまたはエンドユーザからのいかなる理
 *      由に基づく請求からも，上記著作権者およびTOPPERSプロジェクトを
 *      免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，特定の使用目的
 *  に対する適合性も含めて，いかなる保証も行わない．また，本ソフトウェ
 *  アの利用により直接的または間接的に生じたいかなる損害に関しても，そ
 *  の責任を負わない．
 * 
 *  @(#) $Id: sh7780_config.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *		プロセッサ依存モジュール（SH7780用）
 *
 *  このインクルードファイルは，target_config.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_SH7780_CONFIG_H
#define TOPPERS_SH7780_CONFIG_H

/*
 * プロセッサの種類
 */
#define SH4A

#ifdef FPU_ENABLE
/*
 *  FPSCRのPRビットの初期値
 */
#ifdef FPU_DOUBLE
#define FPSCR_PR_INIT 0x00080000  /* 倍精度 */
#else  /* FPU_SINGLE FPU_SINGLE_ONLY */
#define FPSCR_PR_INIT 0x0000000   /* 単精度 */
#endif /* FPU_DOUBLE */

/*
 *  FPSCRのPRビット以外の設定初期値
 */
#ifndef FPSCR_INIT
#define FPSCR_INIT 0x00040000
#endif  /* FPSCR_INIT */
#endif /* FPU_ENABLE */

/*
 * 割込みハンドラ番号に関する定義
 */ 
#define TMIN_INHNO 0x1C0U
#define TMAX_INHNO 0xFE0U
#define TNUM_INH   0x080U

/*
 * 割込み番号に関する定義
 */ 
#define TMIN_INTNO 0x1C0U
#define TMAX_INTNO 0xFE0U
#define TNUM_INT   0x080U

/*
 * 割込みハンドラ番号の内部・外部表現相互変換
 */
#define EXT_INHNO(iintno) (CAST(uint16_t, (iinhno) << 5)) /* 内部表現を外部表現に */
#define INT_INHNO(intno)  (CAST(uint16_t, (inhno) >> 5))  /* 外部表現を内部表現に */

/*
 * 割込み番号の内部・外部表現相互変換
 */
#define EXT_INTNO(iintno)   (CAST(uint16_t, (iintno) << 5)) /* 内部表現を外部表現に */
#define INT_INTNO(intno)    (CAST(uint16_t, (intno) >> 5))  /* 外部表現を内部表現に */

/*
 * アセンブラで割込み番号から inh_tbl を引くためのマクロ
 * regには，割込み番号を保持している
 * レジスタを指定する 
 */
#ifdef TOPPERS_ASM_MACRO
.macro index_intno reg
    shlr2 \reg
    shlr  \reg
.endm
#endif /* TOPPERS_ASM_MACRO */
     
/*
 * CPU例外ハンドラ番号に関する定義
 */ 
#define TMIN_EXCNO 0x040U
#define TMAX_EXCNO 0x820U
#define TNUM_EXC   0x42U
     
/*
 * CPU例外ハンドラ番号の内部・外部表現相互変換
 */
#define EXT_EXCNO(iexcno)  (CAST(uint16_t, (iexcno) << 5)) /* 内部表現を外部表現に */
#define INT_EXCNO(excno)   (CAST(uint16_t, (excno)  >> 5)) /* 外部表現を内部表現に */

/*
 * アセンブラでCPU例外番号から exch_tbl を引くためのマクロ
 * regには，EXPEVTレジスタの値を保持している
 * レジスタを指定する 
 */
#ifdef TOPPERS_ASM_MACRO
.macro index_excno reg
    shlr2 \reg
    shlr  \reg
.endm
#endif /* TOPPERS_ASM_MACRO */

#ifndef TOPPERS_MACRO_ONLY

/*
 * 割込み要求ライン毎の優先度設定レジスタの設定情報
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
 * IRCの初期化
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

    /* 割込みマスクをクリア */
    sil_wrw_mem((void*)INT2MSKCR, 0x80000000U);
}

/*
 * 割込み優先度レジスタの設定
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
 *  プロセッサ依存モジュール（SH34用）
 */
#include "sh34_gcc/prc_config.h"

#endif /* TOPPERS_SH7727_CONFIG_H */
