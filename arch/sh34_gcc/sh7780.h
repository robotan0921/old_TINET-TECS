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
 *  @(#) $Id: sh7780.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *  SH7780のハードウェア資源の定義
 */

#ifndef TOPPERS_SH7780_H
#define TOPPERS_SH7780_H

#include <sil.h>

/*
 *  例外イベントレジスタ
 */
#define TRA         0xff000020
#define EXPEVT      0xff000024
#define INTEVT      0xff000028

/*
 *   バスステートコントローラ関連
 */
#define RFCR        0xff800028   /* H */

#define RFCR_CLEAR  0xa400

/*
 *  割り込みによって INTEVT レジスタに設定される値
 */
//#define TMU0_INTEVT         UINT_C(0x580) //change
#define TMU0_INTEVT         UINT_C(0x400)
#define SCIF0_RXI_INTEVT    UINT_C(0x720)
#define SCIF0_TXI_INTEVT    UINT_C(0x760)
#define SCIF0_BRI_INTEVT    UINT_C(0x740)
#define SCIF1_RXI_INTEVT    UINT_C(0xBA0)
#define SCIF1_TXI_INTEVT    UINT_C(0xBE0)
#define SCIF1_BRI_INTEVT    UINT_C(0xBC0)
//#ifndef IRQ0_INTEVT//tecs用にコメントアウト
//#define IRQ0_INTEVT         UINT_C(0x200)
//#endif


/*
 *  IRC関連のレジスタ
 */
#define ICR0     UINT_C(0xFE410000) /* W */
#define ICR1     UINT_C(0xFE41001C) /* W */
#define INTPRI   UINT_C(0xFE410010) //add 11/07/29
#define C0INTMSK0 UINT_C(0xFE410030)
#define C0INTMSKCLR0 UINT_C(0xFE410050)
#define ICR0_ENABLE UINT_C(0x00C00000)
#define INTREQ UINT_C(0xFE410024)

#define INT2PRI0 UINT_C(0xFE410800) /* W */
#define INT2PRI1 UINT_C(0xFE410804) /* W */
#define INT2PRI2 UINT_C(0xFE410808) /* W */
#define INT2PRI3 UINT_C(0xFE41080C) /* W */
#define INT2PRI4 UINT_C(0xFE410810) /* W */
#define INT2PRI5 UINT_C(0xFE410814) /* W */
#define INT2PRI6 UINT_C(0xFE410818) /* W */
#define INT2PRI7 UINT_C(0xFE41081C) /* W */

//#define INT2MSKR  UINT_C(0xFFD40038 ) //change
#define INT2MSKR  UINT_C(0xFE410A24) 
//#define INT2MSKCR UINT_C(0xFFD4003C) //change
#define INT2MSKCR UINT_C(0xFE410A34)

#define IRQ_LOWLEVEL    UINT_C(0x02)
#define IRQ_POSEDGE     UINT_C(0x01)
#define IRQ_NEGEDGE     UINT_C(0x00)

/*
 * タイマーレジスタ
 */
#define TMU_TOCR   UINT_C(0xffd80000)  /* B */
#define TMU_TSTR   UINT_C(0xffd80004)  /* B */
#define TMU_TCOR0  UINT_C(0xffd80008)  /* W */
#define TMU_TCNT0  UINT_C(0xffd8000c)  /* W */
#define TMU_TCR0   UINT_C(0xffd80010)  /* H */
#define TMU_TCOR1  UINT_C(0xffd80014)  /* W */
#define TMU_TCNT1  UINT_C(0xffd80018)  /* W */
#define TMU_TCR1   UINT_C(0xffd8001c)  /* H */
#define TMU_TCOR2  UINT_C(0xffd80020)  /* W */
#define TMU_TCNT2  UINT_C(0xffd80024)  /* W */
#define TMU_TCR2   UINT_C(0xffd80028)  /* H */

#define TMU_STR0   UINT_C(0x01)
#define TMU_STR1   UINT_C(0x02)
#define TMU_STR2   UINT_C(0x04)
#define TCR_UNF    UINT_C(0x0100)    

/*
 *  FIFO付きシリアルコミュニケーションインターフェース(SCIF)レジスタ
 */
//#define SH_SCIF0_BASE UINT_C(0xFFE00000) // change
#define SH_SCIF0_BASE UINT_C(0xFFEA0000)
#define SH_SCIF1_BASE UINT_C(0xFFEB0000)

/*
 *  GPIO関連レジスタ
 */
//#define GPIO_PHCP UINT_C(0xFFEA000E) /* H */ // change
#define GPIO_PHCP UINT_C(0xFFCC000E) /* H */
//#define GPIO_PHCP_SCIF0_ENABLE (~UINT_C(0x007F)) //change
#define GPIO_PHCP_SCIF0_ENABLE UINT_C(0xFC00)
#define GPIO_PGCP UINT_C(0xFFCC000C) /* G */ //change
#define GPIO_PGCP_LED_ENABLE UINT_C(0xD7FF) //change
#define GPIO_PGDP UINT_C(0xFFCC002C) //change


/*
 *  キャッシュ制御レジスタ
 */
#define CCR           UINT_C(0xff00001c)   /* W */
#define CCR_DISABLE   UINT_C(0x00000808)  /* キャッシュ無効 */

/*
 *  ローカルバスステートコントローラ関連
 */
#define LBSC_MMSELR UINT_C(0xff400020) /* W */
#define LBSC_CS0BCR UINT_C(0xff802000) /* W */
#define LBSC_CS0WCR UINT_C(0xff802008) /* W */

#endif /* TOPPERS_SH7780_H */
