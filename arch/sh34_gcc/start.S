/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                                  Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007      by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: start.S 1663 2009-11-04 00:32:24Z ertl-honda $
 */
        
/*
 *  カーネル対応のスタートアップモジュール(SH34用)
 */

#define TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)	(val)		/* ulong_t型の定数を作るマクロ */
#define CAST(type, val)	(val)		/* 型キャストを行うマクロ */
#include "kernel_impl.h"

    .text
    .global _start
    .align  2
_start:
    /*
     *  SRを初期化する。
     *  MD=1, RB=0, BL=0, I3〜I0=f(全割り込みマスク)
     */
    mov.l _init_sr, r0
    ldc   r0, sr

    /*
     *  R7_BANK1を1にして非タスクコンテキストとする
     */
    mov   #0x01, r0
    ldc   r0, r7_bank

    /*
     *  非タスクコンテキスト用のスタックの初期化
     */
    mov.l  _kernel_istkpt_p, r1
    mov.l  @r1, r15

    /*
     *  _hardware_init_hook を呼び出す。(0でない場合)
     *
     *  ターゲットハードウェアに依存して必要な初期化処理がある場合は，
     *  hardware_init_hookという関数を用意する．
     */
start_0:
    mov.l  _hardware_init_hook_p, r0
    tst    r0, r0
    bt     start_1
    jsr    @r0
     or     r0, r0
    
    /*
     * bssセクションをクリア
     */
start_1:        
    mov.l  _bss_start_p, r0
    mov.l  _end_p, r1
    cmp/eq r0, r1
    bt     start_3
    mov    #0, r2
start_2:
    mov.l  r2, @r0
    add    #4, r0
    cmp/hi r0, r1
    bt     start_2

    /*
     *  dataセクションを初期化する（ROM化対応）．
     *
     *  __idata_start から __idata_end までを，__data_start 以降に
     *  コピーする．
     */
start_3:
    mov.l  __idata_start_p, r1
    mov.l  __idata_end_p, r2
    cmp/eq r1, r2
    bt     start_5
    mov.l  __data_start_p, r0
start_4:    
    mov.l  @r1+, r4
    mov.l  r4, @r0
    cmp/hi r1, r2
    add    #4, r0
    bt     start_4

        
    /*
     *  _software_init_hook を呼び出す（0 でない場合）．
     *
     *  ソフトウェア環境（特にライブラリ）に依存して必要な初期化処
     *  理がある場合は，software_init_hook という関数を用意すれば
     *  よい．
     */
start_5:    
    mov.l  _software_init_hook_p, r0
    tst    r0, r0
    bt     start_6        
    jsr    @r0
     nop
        
start_6:

	/*
	 *  FPUの初期化
	 */
#ifdef FPU_ENABLE
	/*
	 *  gccが用いるデータ（___fpscr_values）を初期化
	 */
	mov.l _set_fpscr_p, r1
    mov.l _fpscr_init_p, r4
	jsr   @r1
     nop
	lds   r3, fpscr 
	/*
	 *  FPUを有効に
	 */
	stc   sr, r0
	mov.l _sr_fpu_enable, r1
	and   r0, r1
	ldc   r1, sr
#endif /* FPU_ENABLE */

    /*    
     *  カーネルを起動する
     */
    mov.l  _sta_ker_p, r0
    jsr    @r0
     nop


    .align 4
_init_sr:    
    .long (0x400000f0)
_kernel_istkpt_p:
    .long __kernel_istkpt
_hardware_init_hook_p:    
    .long _hardware_init_hook
_bss_start_p:    
    .long __bss_start    
_end_p:    
    .long _end   
__idata_start_p:    
    .long __idata_start
__idata_end_p:    
    .long __idata_end
__data_start_p:    
    .long __data_start
_software_init_hook_p:    
    .long _software_init_hook    
_sta_ker_p:    
    .long _sta_ker
#ifdef FPU_ENABLE
_set_fpscr_p:
	.long ___set_fpscr
_sr_fpu_enable:
	.long   ~0x00008000
_fpscr_init_p:
	.long    FPSCR_INIT 
#endif /* FPU_ENABLE */
