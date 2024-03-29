/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel  
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
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
 *  @(#) $Id: apsh4a.h 1598 2009-06-29 09:43:33Z ertl-honda $
 */

/*
 *  APSH4A CPUボードののハードウェア資源の定義
 */

#ifndef TOPPERS_APSH4A_H
#define TOPPERS_APSH4A_H

#include <sil.h>

/*
 *  プロセッサのハードウェア資源の定義のインクルード
 */
#include "sh34_gcc/sh7780.h"

/*
 *  内蔵周辺クロック P = 33.333MHz
 */
//#define	PCLOCK			33333000
#define	PCLOCK			44444000

/*
 *  DDR先頭アドレス
 */
#define	DDR_BASE_ADDR	0x0c000000

/*
 *  DDR関連のレジスタ
 */
#define DDR_DMWR_B	0xfe800604		/* dummy write for big endian */
#define DDR_DMWR_L	0xfe800600		/* dummy write for little endian */
#define DDR_SDMR1	0xFEC02000		/* EMRS reg : DLL enable - BA0:1,A1=A0=0 */
#define DDR_SDMR2	0xFEC00b08		/* MRS  reg : BurtsLength=2,BurstSequence=Sequencial,CL=2.5,DLL=reset */
#define DDR_SDMR3	0xFEC00308		/* MRS  reg : BurtsLength=2,BurstSequence=Sequencial,CL=2.5,DLL=mormal */

#define DDRIF_MIM_H	0xFE800008		/* DDRIF MIM register */
#define DDRIF_MIM_L	0xFE80000c		/* DDRIF MIM register */
#define DDRIF_SDR_H	0xFE800030		/* DDRIF SDR register */
#define DDRIF_SDR_L	0xFE800034		/* DDRIF SDR register */
#define DDRIF_STR_H	0xFE800018		/* DDRIF STR register */
#define DDRIF_STR_L	0xFE80001c		/* DDRIF STR register */
#define DDRIF_SCR_H	0xFE800010		/* DDRIF SCR register */
#define DDRIF_SCR_L	0xFE800014		/* DDRIF SCR register */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  開発環境依存の処理
 */
Inline void
apsh4a_exit(void)
{
    uint32_t sr = 0x10000000U;
    
    /*
     * 強制的にリセットを発生させる
     */
    /*
     * BLビットを立てる
     */
    Asm("ldc %0, sr" : : "r"(sr) );
    
    /*
     * 書込み例外
     */
    *((volatile int *) 0xFFFFFEC1U) = 0;
} 
#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_APSH4A_H */
