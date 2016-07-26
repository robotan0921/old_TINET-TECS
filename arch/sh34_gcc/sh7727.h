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
 *  @(#) $Id: sh7727.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *  SH7727のハードウェア資源の定義
 */

#ifndef TOPPERS_SH7727_H
#define TOPPERS_SH7727_H

#include <sil.h>

/*
 *  例外イベントレジスタ
 */
#define TRA           0xFFFFFFD0
#define EXPEVT        0xFFFFFFD4        
#define INTEVT        0xFFFFFFD8        
#define INTEVT2       0xA4000000

/*
 *   バスステートコントローラ関連
 */
#define RFCR          0xffffff74    /* H */
#define RFCR_CLEAR        0xa400

/*
 * 割り込みによってINTEVT2レジスタに設定される値
 */
#define TMU0_INTEVT        0x400
#define IRQ0_INTEVT        0x600
#define SCI_RXI_INTEVT     0x500
#define SCI_TXI_INTEVT     0x520
#define SCI_BRI_INTEVT     0x4ed
#define PINT0_7_INTEVT     0x700
#define PINT8_15_INTEVT    0x720
#define SCI1_RXI_INTEVT    0x8a0
#define SCI1_TXI_INTEVT    0x8e0
#define SCI1_BRI_INTEVT    0x8c0
#define SCIF_RXI_INTEVT    0x920
#define SCIF_TXI_INTEVT    0x960
#define SCIF_BRI_INTEVT    0x940

/*
 * 割り込みコントローラレジスター
 */
#define ICR0    0xfffffee0    /* H */
#define ICR1    0xa4000010    /* H */
#define ICR2    0xa4000012    /* H */
#define PINTER  0xa4000014    /* H */
#define IPRA    0xfffffee2    /* H */
#define IPRB    0xfffffee4    /* H */
#define IPRC    0xa4000016    /* H */
#define IPRD    0xa4000018    /* H */
#define IPRE    0xa400001a    /* H */
#define IPRF    0xa4000220    /* H */
#define IPRG    0xa4000222    /* H */
#define IRR0    0xa4000004    /* B */
#define IRR1    0xa4000006    /* B */
#define IRR2    0xa4000008    /* B */

#define ICR2_PINT7S     0x80
#define ICR2_PINT6S     0x40
#define PINTER_PINT7E   0x80
#define PINTER_PINT6E   0x40

#define IRQ_LOWLEVEL    0x2    
#define IRQ_POSEDGE     0x1
#define IRQ_NEGEDGE     0x0

/*
 * タイマーレジスタ
 */
#define TMU_TOCR   0xfffffe90  /* B */
#define TMU_TSTR   0xfffffe92  /* B */
#define TMU_TCOR0  0xfffffe94  /* W */
#define TMU_TCNT0  0xfffffe98  /* W */
#define TMU_TCR0   0xfffffe9c  /* H */
#define TMU_TCOR1  0xfffffea0  /* W */
#define TMU_TCNT1  0xfffffea4  /* W */
#define TMU_TCR1   0xfffffea8  /* H */
#define TMU_TCOR2  0xfffffeac  /* W */
#define TMU_TCNT2  0xfffffeb0  /* W */
#define TMU_TCR2   0xfffffeb4  /* H */

#define TMU_STR0   0x01
#define TMU_STR1   0x02
#define TMU_STR2   0x04
#define TCR_UNF    0x0100    

/*
 *  シリアルコミュニケーションインターフェース(SCI)
 */
#define SCI_SCSMR    0xfffffe80  /* B */
#define SCI_SCBRR    0xfffffe82  /* B */
#define SCI_SCSCR    0xfffffe84  /* B */
#define SCI_SCTDR    0xfffffe86  /* B */
#define SCI_SCSSR    0xfffffe88  /* B */
#define SCI_SCRDR    0xfffffe8a  /* B */

/*
 *  シリアルコミュニケーションインターフェース(SCI)の
 *  ポートSCコントロール/データレジスタ
 *  SH7709及びSH7709Aのみ
 */
#define SCPDR     0xa4000136   /* B */
#define SCPCR     0xa4000116   /* H */

/*
 *  シリアルコミュニケーションインターフェース(SCI)の
 *  シリアルポートレジスタ
 *  SH7708のみ
 */
#define SCSPTR      0xffffff7c  /* H */

#define SCSMR_CHR     0x0040
#define SCSMR_PE      0x0020
#define SCSMR_OE      0x0010
#define SCSMR_STOP    0x0008
#define SCSMR_CKS1    0x0002
#define SCSMR_CKS0    0x0001

#define SCSCR_TIE     0x0080
#define SCSCR_RIE     0x0040
#define SCSCR_TE      0x0020
#define SCSCR_RE      0x0010
#define SCSCR_CKE1    0x0002
#define SCSCR_CKE0    0x0001

#define SCSSR_TDRE    0x80
#define SCSSR_RDRF    0x40
#define SCSSR_ORER    0x20
#define SCSSR_FER     0x10
#define SCSSR_PER     0x08
#define SCSSR_TEND    0x04
#define SCSSR_MPB     0x02
#define SCSSR_MPBT    0x01

/*
 * キャッシュ制御レジスタ
 */
#define CCR           0xffffffec   /* W */
#define CCR_DISABLE   0x00000008   /* キャッシュの無効化 */

#endif /* TOPPERS_SH7727_H */
