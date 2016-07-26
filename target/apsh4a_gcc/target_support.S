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
 *  @(#) $Id: target_support.S 1598 2009-06-29 09:43:33Z ertl-honda $
 */

/*
 *  ターゲット依存モジュール アセンブリ言語部（APSH4A）
 */

#define  TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)	(val)		/* ulong_t型の定数を作るマクロ */
#include "kernel_impl.h"

/*
 *  低レベルのターゲット依存の初期化
 *
 *  スタートアップモジュールの中で，メモリの初期化の前に呼び出される．
 */
    .text
    .globl _hardware_init_hook
_hardware_init_hook:
#ifdef ROM_BOOT
	/*
	 * エリア3をDDR空間にその他をLBSC空間に設定
	 */
	mov.l _lbsc_mmselr_addr, r1
	mov.l _lbsc_mmselr_val, r2
	mov.l r2, @r1

	/*
	 * フラッシュメモリの設定(CS0)
	 */
	mov.l _lbsc_cs0bcr_addr, r1
	mov.l _lbsc_cs0bcr_val, r2
	mov.l r2, @r1
	mov.l _lbsc_cs0wcr_addr, r1
	mov.l _lbsc_cs0wcr_val, r2
	mov.l r2, @r1

	/*
	 *  DDR SDRAM 
     *  256Mbit(16Mx16bit) :CL=2.5, 8192REFA @ 64mS MCLK=160MHz@6.25nS
 	 */
	/*
	 *  DDR Dummy Read
	 */
	mov.l _ddr_base_addr, r1
	mov.l @r1, r2
	/*
	 *  dummy write for Little endian
	 */
	mov.l _ddr_dmwr_l_addr, r1
	mov.l _ddr_dmwr_l_val,  r2
	mov.l r2, @r1

	/*
	 *  DCE=1:DDR,DLL=1 enable,!**BANK CLOSE MODE**!
	 */
	mov.l _ddrif_min_h_addr, r1
	mov.l _ddrif_min_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_min_l_addr, r1
	mov.l _ddrif_min_l_val, r2
	mov.l r2, @r1

	/*
	 *  SPLIT=3:16Mx16bit	
	 */
	mov.l _ddrif_sdr_h_addr, r1
	mov.l _ddrif_sdr_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_sdr_l_addr, r1
	mov.l _ddrif_sdr_l_val, r2
	mov.l r2, @r1

	/*
	 *   WR  =0:W-R min cycle 3,RW=0:R-W min cycle 3
     *    SRFC=:12cycle=75.0nS, Trfc=72nS
     *    SWR =: 3cycle=18.7nS, Twr =15nS
     *    SRRD=: 2cycle=12.5nS, Trrd=12nS
     *    SRAS=: 7cycle=43.7nS, Tras=42nS
     *    SRC =:10cycle=62.5nS, Trc =60nS
     *    SCL =0: CL=2.5 only
     *    SRCD=: 3cycle=18.7nS, Trcd=18nS
     *    SRP =: 3cycle=18.7nS, Trp =18nS
	 */
	mov.l _ddrif_str_h_addr, r1
	mov.l _ddrif_str_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_str_l_addr, r1
	mov.l _ddrif_str_l_val, r2
	mov.l r2, @r1	

	/*
	 *  DESELECT command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2,r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_3, r2
	mov.l r2, @r1	

	/*
	 *  PREALL   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2,r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_2, r2
	mov.l r2, @r1	

	/*
	 *  DDR-EMRS write
	 */
	mov.l _ddr_sdmr1_addr, r1          
	mov.l _ddr_sdmr1_val, r2
	mov.w r2, @r1

	/*
	 *  DDR-MRS write
	 */
	mov.l _ddr_sdmr2_addr, r1
	mov.l _ddr_sdmr2_val, r2
	mov.w r2, @r1	
    
	/*
	 *  PREALL   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2, r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_2, r2
	mov.l r2, @r1	

	/*
	 *  REFA 1   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2, r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_4, r2
	mov.l r2, @r1	

	/*
	 *  REFA 2   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2, r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_4, r2
	mov.l r2, @r1	

	/*
	 *  DDR-MRS write
	 */
	mov.l _ddr_sdmr3_addr, r1
	mov.l _ddr_sdmr3_val, r2
	mov.w r2, @r1	

	/*
	 *  RMODE=0:Auto Reflesh
	 *  DRI=4E1cyc:4E1x6.25ns=7.8uS, 64mS/8192REFA=7.81uS
	 *  DRE=1:refresh enable,DLLEN=1:DLL enable
	 *  DCE=1:DDR controller enable
	 */
	mov.l _ddrif_min_h_addr, r1
	mov.l _ddrif_min_h_val, r2
	mov.l r2, @r1
	mov.l _ddrif_min_l_addr, r1
	mov.l _ddrif_min_l_val, r2
	mov.l r2, @r1

	/*
	 *  waiting for MCLK200cycle(=1.25uS)
	 */
	mov.l _loop_from, r1
	mov.l _loop_dec,  r2
_loop:
	add    r2, r1		
	cmp/pl r1
	bt     _loop

	/*
	 *  NORMAL   command issue
	 */
	mov.l _ddrif_scr_h_addr, r1
	xor   r2,r2
	mov.l r2, @r1
	mov.l _ddrif_scr_l_addr, r1
	mov.l _ddrif_scr_l_val_0, r2
	mov.l r2, @r1
	
#endif

	mov.l _ccr_addr, r1
	mov.l _ccr_disable, r2
	mov.l r2, @r1
	mov.l _ccr_mode, r2
	mov.l r2, @r1
	
    rts
     nop


    .align 4
#ifdef ROM_BOOT
_lbsc_mmselr_addr:
	.long LBSC_MMSELR
_lbsc_mmselr_val:
	.long 0xa5a50000

_lbsc_cs0bcr_addr:
	.long LBSC_CS0BCR
_lbsc_cs0bcr_val:
	.long 0x00000000
_lbsc_cs0wcr_addr:
	.long LBSC_CS0WCR
_lbsc_cs0wcr_val:
	.long 0x00020005

_ddr_base_addr:
	.long DDR_BASE_ADDR

_ddr_dmwr_l_addr:
	.long DDR_DMWR_L
_ddr_dmwr_l_val:
	.long 0xa5000000

_ddrif_min_h_addr:
	.long DDRIF_MIM_H
_ddrif_min_h_val:
	.long 0x00004000
_ddrif_min_l_addr:
	.long DDRIF_MIM_L
_ddrif_min_l_val:
	.long 0x04e10209
_ddrif_sdr_h_addr:
	.long DDRIF_SDR_H
_ddrif_sdr_h_val:
	.long 0x00000000
_ddrif_sdr_l_addr:
	.long DDRIF_SDR_L
_ddrif_sdr_l_val:
	.long 0x00000300
_ddrif_str_h_addr:
	.long DDRIF_STR_H
_ddrif_str_h_val:
	.long 0x00000000
_ddrif_str_l_addr:
	.long DDRIF_STR_L
_ddrif_str_l_val:
	.long 0x00003180

_ddrif_scr_h_addr:
	.long DDRIF_SCR_H
_ddrif_scr_l_addr:
	.long DDRIF_SCR_L

_ddrif_scr_l_val_0:
	.long 0x00000000
_ddrif_scr_l_val_2:
	.long 0x00000002
_ddrif_scr_l_val_3:
	.long 0x00000003
_ddrif_scr_l_val_4:
	.long 0x00000004

_ddr_sdmr1_addr:
	.long DDR_SDMR1
_ddr_sdmr1_val:
	.long  0x0000
_ddr_sdmr2_addr:
	.long DDR_SDMR2
_ddr_sdmr2_val:
	.long  0x0000
_ddr_sdmr3_addr:
	.long DDR_SDMR3
_ddr_sdmr3_val:
	.long  0x0000

_loop_from:
	.long 200
_loop_dec:
	.long   -1	
	
#endif
_ccr_addr:
	.long CCR
_ccr_disable:
	.long CCR_DISABLE
_ccr_mode:
	.long CCR_MODE
