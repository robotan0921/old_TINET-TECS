/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2007-2010 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_support.S 1708 2010-01-25 02:00:10Z ertl-honda $
 */

/*
 *  プロセッサ依存モジュール アセンブリ言語部（SH34用）
 */

#define TOPPERS_MACRO_ONLY
#define UINT_C(val)		(val)		/* uint_t型の定数を作るマクロ */
#define ULONG_C(val)	(val)		/* ulong_t型の定数を作るマクロ */
#define CAST(type, val)	(val)		/* 型キャストを行うマクロ */

/*
 *  アセンブラ用のマクロを有効にする
 */
#define TOPPERS_ASM_MACRO
#include "kernel_impl.h"
#include "offset.h"
     
#ifdef FPU_ENABLE

/*
 *  FPU関連レジスタの保存
 */        
#ifdef FPU_SAVE_BANKED_REG

#define OFFSET_OF_SSR (11 + 14 + 16)

.macro save_banked_fpureg
    frchg  /* バンクを切り替え */
    fmov.s  fr15, @-r15
    fmov.s  fr14, @-r15
    fmov.s  fr13, @-r15
    fmov.s  fr12, @-r15
    fmov.s  fr11, @-r15
    fmov.s  fr10, @-r15
    fmov.s  fr9, @-r15
    fmov.s  fr8, @-r15
    fmov.s  fr7, @-r15
    fmov.s  fr6, @-r15
    fmov.s  fr5, @-r15
    fmov.s  fr4, @-r15
    fmov.s  fr3, @-r15
    fmov.s  fr2, @-r15
    fmov.s  fr1, @-r15
    fmov.s  fr0, @-r15
    frchg  /* バンクを戻す */
.endm

.macro restore_banked_fpureg
#ifdef FPU_SAVE_BANKED_REG
    frchg  /* バンクを切り替え */
    fmov.s  @r15+, fr0
    fmov.s  @r15+, fr1
    fmov.s  @r15+, fr2
    fmov.s  @r15+, fr3
    fmov.s  @r15+, fr4
    fmov.s  @r15+, fr5
    fmov.s  @r15+, fr6
    fmov.s  @r15+, fr7
    fmov.s  @r15+, fr8
    fmov.s  @r15+, fr9
    fmov.s  @r15+, fr10
    fmov.s  @r15+, fr11
    fmov.s  @r15+, fr12
    fmov.s  @r15+, fr13
    fmov.s  @r15+, fr14
    fmov.s  @r15+, fr15
    frchg  /* バンクを戻す */
#endif /* FPU_SAVE_BANKED_REG */
.endm

#else /* FPU_SAVE_BANKED_REG */

#define OFFSET_OF_SSR (11 + 14)

.macro save_banked_fpureg
.endm

.macro restore_banked_fpureg
.endm

#endif /* FPU_SAVE_BANKED_REG */

.macro save_scratch_fpureg label
    save_banked_fpureg
    sts.l   fpul, @-r15
    fmov.s  fr11, @-r15
    fmov.s  fr10, @-r15
    fmov.s  fr9,  @-r15
    fmov.s  fr8,  @-r15
    fmov.s  fr7,  @-r15
    fmov.s  fr6,  @-r15
    fmov.s  fr5,  @-r15
    fmov.s  fr4,  @-r15
    fmov.s  fr3,  @-r15
    fmov.s  fr2,  @-r15
    fmov.s  fr1,  @-r15
    fmov.s  fr0,  @-r15
    sts.l   fpscr, @-r15
    mov.l   _fpscr_init_\label, r0 /* fpscr の初期値に設定 */
    lds     r0,   fpscr
.endm

.macro restore_scratch_fpureg 
    lds.l   @r15+, fpscr
    fmov.s  @r15+, fr0
    fmov.s  @r15+, fr1
    fmov.s  @r15+, fr2
    fmov.s  @r15+, fr3
    fmov.s  @r15+, fr4
    fmov.s  @r15+, fr5
    fmov.s  @r15+, fr6
    fmov.s  @r15+, fr7
    fmov.s  @r15+, fr8
    fmov.s  @r15+, fr9
    fmov.s  @r15+, fr10
    fmov.s  @r15+, fr11
    lds.l   @r15+, fpul
    restore_banked_fpureg
.endm

.macro save_fpureg_data label
_fpscr_init_\label:    
    .long     (FPSCR_PR_INIT|FPSCR_INIT)
.endm

.macro save_callsaved_fpureg_dis
    save_banked_fpureg
    fmov.s  fr15, @-r15
    fmov.s  fr14, @-r15
    fmov.s  fr13, @-r15
    fmov.s  fr12, @-r15
    sts.l   fpscr, @-r15
.endm

.macro restore_callsaved_fpureg_dis
    lds.l   @r15+, fpscr
    fmov.s  @r15+, fr12
    fmov.s  @r15+, fr13
    fmov.s  @r15+, fr14
    fmov.s  @r15+, fr15
    save_banked_fpureg
.endm

.macro save_callsaved_fpureg_int
    lds.l   @r15+, fpscr   /* スタックからfpscr設定を復帰 */
    sts.l   fpscr, @-r15   /* スクラッチの復帰用に保存    */
    fmov.s  fr15, @-r15
    fmov.s  fr14, @-r15
    fmov.s  fr13, @-r15
    fmov.s  fr12, @-r15
    sts.l   fpscr, @-r15
.endm

.macro restore_callsaved_fpureg_int
    lds.l   @r15+, fpscr
    fmov.s  @r15+, fr12
    fmov.s  @r15+, fr13
    fmov.s  @r15+, fr14
    fmov.s  @r15+, fr15
.endm

.macro set_fpscr label
    mov.l   _fpscr_init_\label, r2
    lds     r2, fpscr
.endm

#else /* FPU_ENABLE */

#define OFFSET_OF_SSR  11

.macro save_scratch_fpureg label
.endm

.macro restore_scratch_fpureg
.endm

.macro save_fpureg_data label
.endm

.macro save_callsaved_fpureg_dis
.endm

.macro restore_callsaved_fpureg_dis
.endm

.macro save_callsaved_fpureg_int
.endm

.macro restore_callsaved_fpureg_int
.endm

.macro set_fpscr label
.endm

#endif /* FPU_ENABLE */

/*
 *  例外/割り込み出入り口処理ルーチン
 *  SH34はベクタテーブルを持たず、例外,TRAPAが発生するとVBR+0x100番地を、
 *  内部/外部/NMI割り込みが発生すると、VBR+0x600番地を実行する。
 */

/*
 *  VBR に設定する値
 */
    .section .text
    .align 2
    .global _base_vec
_base_vec:
     nop 
     nop
     nop

/*
 *  Exception 100 vector
 *  アドレスエラー,スロット不当命令例外、Trapa例外等が発生すると実行される。
 *
 *  CPU例外ハンドラは、非タスクコンテキストで実行する、そのため、CPU例外ハン
 *  ドラを呼び出す前に例外/割り込みを示すレジスタバンク1の r7 レジスタをイン
 *  クメントし、リターンしてきた後にデクリメントする。CPU例外ハンドラ終了後は，
 *  ret_exc において，出口処理を行う．
 * 
 *  regflg をチェックする前に割り込みを禁止しないと、reqflg をチェック後に起
 *  動された割り込みハンドラ内でディスパッチが要求された場合に、ディスパッチ
 *  されない。
 *
 *
 *  例外が発生すると、例外発生元のコンテキストであるspc,pr,ssr,r0〜r7を退避
 *  する。例外が発生した時点でのコンテキストを調べ非タスクコンテキストなら
 *  _exception_from_intから実行を開始する。例外の要因はEXPEVTレジスタ読み、
 *  exc_tableからCPU例外ハンドラの開始番地を読み込む。CPU例外ハンドラから
 *  リターンしてきたら、reqflgを調べ0以外ならrec_exc()に飛び、0なら元の
 *  処理にリターンする。
 *
 *
 *  BLビットの扱いについて
 *  ssr,spc に戻り先のコンテキストを戻して rte を発行する際には，割込み（NMI 
 *  も含む）を受け付けないように BL ビットを1にする必要がある．例外/割込みハ
 *  ンドラ終了時には BL をビットを1にせず 一旦IPM を MAX_IPM に設定する．
 *  これは，BL ビットが1の場合に例外が発生すると CPU がリセットされることを
 *  考慮して，安全のため，ssr,spcを復帰する直前でBLを1に設定している．
 *       
 *          ----------------------
 *  0      |       EXPEVT         |  <-- p_excinf
 *          ----------------------
 *  1      |         R7           |
 *          ----------------------
 *  2      |         R6           |
 *          ----------------------
 *  3      |         R5           |
 *          ----------------------
 *  4      |         R4           |
 *          ----------------------
 *  5      |         R3           |
 *          ----------------------
 *  6      |         R2           |
 *         ----------------------
 *  7      |         R1           |
 *          ----------------------
 *  8      |         R0           |
 *          ----------------------
 *  9      |        MACH          |
 *          ----------------------
 * 10      |        MACL          |
 *          ----------------------
 * 11      |        GBR           |
 *          ----------------------
 * 12      |         SR           |
 *          ----------------------
 * 13      |         PR           |
 *          ----------------------
 * 14      |         PC           |
 *          ----------------------
 */


    .org   0x0100              /*  _BASE_VBR + 0x0100番地に配置   */
    .align 2
    .global _general_exc_vec
_general_exc_vec:
    stc.l  spc,@-r15           /* spc,pr,ssr をスタックに保存する */
    sts.l  pr,@-r15
    stc.l  ssr,@-r15
    stc.l  gbr,@-r15
    sts.l  macl,@-r15
    sts.l  mach,@-r15                                            
    stc.l  r0_bank,@-r15       /* 例外発生時のr0〜r7を保存        */
    stc.l  r1_bank,@-r15
    stc.l  r2_bank,@-r15
    stc.l  r3_bank,@-r15
    stc.l  r4_bank,@-r15
    stc.l  r5_bank,@-r15
    stc.l  r6_bank,@-r15
    stc.l  r7_bank,@-r15
    save_scratch_fpureg exc
    mov.l  _expevt_exc,r0      /* 例外を許可すると消えるレジスタを保存      */
    mov.l  @r0,r5              /* EXPEVTレジスタを取得                      */
    mov.l  r5,@-r15            /* スタックに保存(未登録の例外発生時使用)    */
    ldc    r15,r4_bank         /* CPU例外ハンドラへの引数                   */
    ldc    r5, r5_bank         /* EXPEVTレジスタの値                        */
    tst    r7,r7               /* 例外発生元のコンテキストを判定            */
    bf/s   _general_exc_vec_1  /* 発生元が例外/割り込みハンドラならジャンプ */
     add    #0x01,r7           /* 例外/割り込みネスト回数をインクリメント   */
    mov.l  _kernel_istkpt_exc, r2
    mov    r15,r4
    mov.l  @r2,r15
    mov.l  r4,@-r15            /* スタックを入れ替え元のスタックポインタを保存 */
_general_exc_vec_1:
    mov.l  _lock_flag_exc,r3   /* 元の lock_flag をスタックに保存           */
    mov.l  @r3, r2
    mov.l  r2,@-r15
    mov.l _saved_iipm_exc,r3   /* 元の saved_iipm をスタックに保存          */
    mov.b  @r3, r2
    mov.l  r2,@-r15
    mov.l  _unmak_rb_bl_exc,r2 /* BLビットを0に，レジスタバンクを切り替え   */
    stc    sr,r3               
    and    r3,r2            
    ldc    r2,sr

    mov.l r5, @-r15              /* EXPEVTをスタックに保存        */
#ifdef LOG_EXC_ENTER
    mov.l  r4,@-r15              /* r4をスタックに保存            */
    mov.l _log_exc_enter_exc, r1 /* ログ出力関数                  */
    jsr   @r1
     mov  r5, r4                 /* 引数 */
    mov.l @r15+, r4              /* r4を復帰                      */
    mov.l @r15, r5               /* 例外要因を復帰(スタックに入れたまま) */
#endif /* LOG_EXC_ENTER */

    index_excno r5             /* EXPEVTからexc_tableのインデックスを求める */
    mov.l  _exch_tbl_exc,r0    /* exch_tblのアドレスをr0に                  */
    mov.l  @(r0,r5),r2         /* ハンドラのアドレスを取得                  */
    jsr    @r2                 /* CPU例外ハンドラへ                         */
     nop

    mov.l @r15+, r4              /* EXPEVTを復帰                   */
#ifdef LOG_EXC_LEAVE
    mov.l _log_exc_leave_exc, r1 /* ログ出力関数                   */
    jsr  @r1
     nop
#endif /* LOG_EXC_LEAVE */

    /*
     * CPU例外ハンドラ出口処理
     */
_ret_exc:
    mov.l  _mask_md_ipm_exc,r0 /* 割り込み禁止                              */
    ldc    r0,sr               
    mov.l  @r15+,r2            /* saved_iipm を元に戻す                     */
    mov.l  _saved_iipm_exc,r3  
    mov.b  r2,@r3
    mov.l  @r15+,r2            /* lock_flag を元に戻す                      */
    mov.l  _lock_flag_exc,r3   
    mov.l  r2,@r3
    /*
     * 割込みのネスト段数を管理する r7_bank1 とスタックポインタ(r15)
     * の内容は不可分に行う必要がある．
     * 単に割込みを禁止しただけでは，カーネル管理外の割込みを禁止できない
     * ため，BLビットを1にセットして，カーネル管理外の割込みも禁止する．
     */
    mov.l  _mask_md_bl_exc,r0  /* BLビット を 1 に                          */
    ldc    r0,sr               /* 全割込み禁止                              */
    stc    r7_bank,r7          /* 例外/割り込みのネスト回数をデクリメント   */
    dt     r7
    ldc    r7,r7_bank
    tst    r7,r7
    bf     _ret_exc_1          /* 発生元がタスク以外ならすぐにリターン      */
    mov.l  @r15, r15           /* 戻り先がタスクなのでスタックを戻す        */
    mov.l  _reqflg_exc,r2      /* reqflgのチェック                          */
    mov.l  @r2,r1
    xor    r0,r0
    tst    r1,r1               /* reqflgがfalseなら_ret_exc_1へ             */
    bt/s   _ret_exc_1          
     mov.l  r0,@r2             /* reqflgをクリア                            */
    mov.l  _mask_md_ipm_exc,r0 /* BLビット を 0 に                       */
    ldc    r0, sr              /* カーネル管理外の割込み許可             */
    mov.l  _ret_int_2_exc, r1  /* ret_int_2へ                               */
    jmp    @r1
     mov.l  @r15+,r2           /* EXPEVTをスタックから取り出す              */

_ret_exc_1:
    mov.l  @r15+,r2            /* EXPEVTをスタックから取り出す              */
    restore_scratch_fpureg
    mov.l  @r15+,r7            /* r0〜r1,ssr,pr,spcを復帰しタスクに戻る     */
    mov.l  @r15+,r6
    mov.l  @r15+,r5
    mov.l  @r15+,r4
    mov.l  @r15+,r3
    mov.l  @r15+,r2
    mov.l  @r15+,r1
    mov.l  @r15+,r0
    lds.l  @r15+,mach
    lds.l  @r15+,macl
    ldc.l  @r15+,gbr
    ldc.l  @r15+,ssr
    lds.l  @r15+,pr
    ldc.l  @r15+,spc
    rte
     nop

    .align  4
_kernel_istkpt_exc:
    .long __kernel_istkpt
_expevt_exc:
    .long  EXPEVT
_unmak_rb_bl_exc:
    .long  0x4fffffff
_exch_tbl_exc:
    .long  _exch_tbl
_mask_md_ipm_exc:
    .long  (0x40000000 + INT_IPM(TMIN_INTPRI))
_reqflg_exc:
    .long  _reqflg
_mask_md_bl_exc:
    .long  (0x50000000 + INT_IPM(TMIN_INTPRI))
_lock_flag_exc:
    .long _lock_flag
_saved_iipm_exc:
    .long _saved_iipm
_ret_int_2_exc:
    .long _ret_int_2
#ifdef LOG_EXC_ENTER
_log_exc_enter_exc:
    .long _log_exc_enter
#endif /* LOG_EXC_ENTER */
#ifdef LOG_EXC_LEAVE
_log_exc_leave_exc:
    .long _log_exc_leave
#endif /* LOG_EXC_LEAVE */
save_fpureg_data exc

    
/*
 *  タスクディスパッチャ
 *
 *  このルーチンは，タスクコンテキスト(r7_bank1 = 0)・CPUロック状態・
 *  ディスパッチ許可状態・（モデル上の）割込み優先度マスク前回状態で
 *  呼び出される．
 */

    .text
    .align 2
    .global _dispatch
_dispatch:
    save_callsaved_fpureg_dis
    sts.l  pr,@-r15          /* pr,r8〜r14 をスタックに保存           */
    mov.l  r14,@-r15         /* r0〜r7は呼び出し元で保存しているため  */
    mov.l  r13,@-r15         /* 保存する必要が無い                    */
    mov.l  r12,@-r15
    mov.l  r11,@-r15
    mov.l  r10,@-r15
    mov.l  r9, @-r15
    mov.l  r8, @-r15
    mov.l  _p_runtsk_dis,r2  /* r0 <- p_runtsk                      */
    mov.l  @r2,r0
    mov.l  r15,@(TCB_sp,r0)  /* タスクスタックをTCBに保存 60以下ならOK*/
    mov.l  _dispatch_r_dis,r1/* 実行再開番地を保存                    */
    bra    _dispatcher
     mov.l  r1,@(TCB_pc,r0)  /* 実行再開番地をTCBに保存  60以下ならOK */
 

_dispatch_r:
    mov.l  @r15+,r8         /* レジスタを復帰                       */
    mov.l  @r15+,r9
    mov.l  @r15+,r10
    mov.l  @r15+,r11
    mov.l  @r15+,r12
    mov.l  @r15+,r13
    mov.l  @r15+,r14
    lds.l  @r15+,pr
    set_fpscr dis           /* fpscr の初期化 r2を破壊 */
    /*
     *  タスク例外処理ルーチンの起動
     *  dispatch_rはdispatcherから呼び出されるため，
     *  tcbのアドレスはr0に入っている．
     */
    mov    r0,r1
    mov.b  @(TCB_enatex,r1),r0
    mov.l  _enatex_mask_dis,r2
    tst    r0,r2
    bt/s   _dispatch_r_1        /* enatex が false ならリターン */
     mov.l  @(TCB_texptn,r1),r0  /* texptnをロード               */
    tst    r0,r0
    bt     _dispatch_r_1        /* texptn が 0で無ければ        */
    mov.l  _call_texrtn_dis,r1  /* タスク例外ルーチンの呼び出し */
    jmp    @r1
     nop
_dispatch_r_1:
    restore_callsaved_fpureg_dis
    rts
     nop

/*
 * ディスパッチャの動作開始（prc_support.S）
 */
    .global _start_dispatch
_start_dispatch:
    /*
     *  このルーチンは，カーネル起動時に，すべての割込みを禁止した状態
     * （割込みロック状態と同等）で呼び出される．また，割込みモード（非
     *  タスクコンテキストと同等）で呼び出されることを想定している．
     *
     *  prc_initializeで，lock_flagをtrueに，saved_iipmをIIPM_ENAALLに
     *  初期化しているため，カーネル管理外の割込みを許可することで，
     *  CPUロック状態・（モデル上の）割込み優先度マスク全解除状態になる．
     *  また，task_initializeでdisdspをfalseに初期化しているため，ディ
     *  スパッチ許可状態になっている．
     *  
     *  ここでは，r7_bank1は0クリアしない，これは，カーネル管理外の割込
     *  みをサポートする場合，このでのスタックは非タスクコンテキスト用の
     *  スタックであるため，r7_bank1が0の状態でカーネル管理外の割込みが
     *  入ると，スタックの上書きが発生してしまうためである．
     */
    bra    _dispatcher_0
     nop

/*
 *  現在のコンテキストを捨ててディスパッチ
 */
    .globl _exit_and_dispatch
_exit_and_dispatch:
    /* ディスパッチャ本体（dispatcher）へ */

/*
 * ディスパッチャ本体
 */
_dispatcher:
#ifdef LOG_DSP_ENTER
    mov.l _log_dsp_enter_dis, r1 /* ログ出力関数 */
    mov.l _p_runtsk_dis, r2      /* 引数      */
    jsr   @r1
     mov.l  @r2,r4 
#endif /* LOG_DSP_ENTER */
_dispatcher_0:
    /*
     *  このルーチンは，タスクコンテキスト・CPUロック状態・ディスパッチ
     *  許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さ
     *  れる．
     *
     *  すなわち，r7_bank1が0・lock_flagがtrue・disdspがfalse・dspflg
     *  がtrue・saved_iipmがIIPM_ENAALLとなっている．実行再開番地へもこ
     *  の状態のまま分岐する．
     */
    mov.l  _p_schedtsk_dis,r12  /* r0 <- p_schedtsk                 */
    mov.l  @r12,r0             
    mov.l  _p_runtsk_dis,r2
    mov.l  r0,@r2               /* schedtskをruntskに               */
    cmp/eq #0,r0                /* schedtsk があるか？              */
    bt     _dispatcher_1        /* 無ければジャンプ                 */
    mov.l  _mask_md_bl_dis,r1   /* BL ビット を 1 に                */
    ldc    r1,sr                /* 全割込み禁止                     */
    mov.l  @(TCB_sp,r0),r15     /* TCBからタスクスタックを復帰      */
    xor    r1,r1                /* r7_bank1を0クリア                */
    ldc    r1,r7_bank
    mov.l  _mask_md_ipm_dis,r1  /* BL bit を 0 に                   */
    ldc    r1,sr                /* カーネル管理外の割込み許可       */

#ifdef LOG_DSP_LEAVE
    mov   r0, r8                 /* r0はスクラッチレジスタなので r8にコピー */
    mov.l _log_dsp_leave_dis, r1 /* ログ出力関数 */
    jsr   @r1
     mov   r0, r4                /* 引数      */
    mov  r8, r0                  /* r0にTCBへのポインタを戻す */    
#endif /* LOG_DSP_LEAVE */
    mov.l  @(TCB_pc,r0),r1      /* TCBから実行再開番地を復帰        */
    jmp    @r1 
     nop
_dispatcher_1:
    /* イミディエイト値を毎回読み込むのは効率が悪いので事前に用意する
     * r8  : 割り込み禁止のためのSRの値
     * r9  : 割り込み待ち中のSRの値
     * r10 : reqflgの番地
     * r11 : 0x01
     * r12 : 0x00
     * r13 : sleep中のSRの状態
     * r14 : lock_flagの番地
     */
    mov.l  _mask_md_ipm_dis,r8  /* 割り込み禁止のSRの値             */
#ifdef NO_SLEEP
    mov.l  _mask_md_dis,r9      /* 割り込み待ち中のSRの値           */
#else
    mov.l  _mask_md_bl_dis,r9   /* 割り込み待ち中のSRの値           */
#endif /* NO_SLEEP */
    mov.l  _kernel_istkpt_dis,r11
    mov.l  @r11,r15
    mov.l  _reqflg_dis,r10
    mov    #0x01,r11
    xor    r12,r12
    ldc    r11,r7_bank         /* r7_bank1 を1にして割り込み状態に */
    mov.l  _lock_flag_dis,r14
    mov.l  r12,@r14            /* CPUロック解除状態に */
_dispatcher_2:
    /*
     *  ここで割込みモードに切り換えるのは，ここで発生する割込み処理
     *  にどのスタックを使うかという問題の解決と，割込みハンドラ内で
     *  のタスクディスパッチの防止という二つの意味がある．
     */
     /*
      *  割込み許可後にsleep命令を実行すると，割込み許可命令の実行前に
      *  割込み要求が入っている場合，割込み許可命令の実行と共に割込みが
      *  受け付けられその復帰後に，reqflgのチェックではなく sleep 状態
      *  に入ってしまう．
      *  この問題は，割込みの許可と sleep 状態への移行がアトミックに実
      *  行できないことに起因する．
      *  そのため，sleep 実行直前の SR 変更では BL ビットを'1'に設定す
      *  ることで，割込みの許可と sleep 状態への以降をアトミックに実行
      *  する．
      *  ldc r9,sr ではBLビットがセットされるため，割込みは受け付けずス
      *  リープモードに移行する．スリープモード中は，BLビットが1でも割
      *  込みを受け付けるため(SH7709ハードウェアマニュアル 8-10)，スリー
      *  プモードへの移行直後に割込みを受付スリープモードから復帰する．
      */
               
    ldc    r9,sr               /* 割り込みの許可                   */
#ifndef NO_SLEEP
    sleep                      /* 割込み待ち                       */
#endif /* NO_SLEEP */                
    ldc    r8,sr               /* 割り込み禁止                     */
    mov.l  @r10,r7             /* r7 <- reqflg                     */
    tst    r7,r7               /* reqflg が falseなら              */
    bt     _dispatcher_2       /* dispatcher_2 へ                  */

    ldc    r12,r7_bank         /* r7_bank1 をクリア                */
    mov.l  r12,@r10            /* reqflg を falseに                */
    /*
     *  CPUロック状態に戻す．割込み待ちの間に実行した割込みハンドラによ
     *  り，saved_iipmが書き換えられる可能性があるため，元の値に戻す必
     *  要がある．dispatcherが実行される時は，saved_iipmがIIPM_ENAALL
     *  となっているため，ここではsaved_iipmをIIPM_ENAALL（＝0）に戻せ
     *  ばよい．
     */
    mov.l  _saved_iipm_dis, r10
    mov.l  r11,@r14            /* CPUロック状態に */
    bra    _dispatcher_0
     mov.b r12,@r10            /* saved_iipmを0にする */

    .align 4
_dispatch_r_dis:
    .long _dispatch_r
_p_runtsk_dis:
    .long _p_runtsk
_enatex_mask_dis:
    .long TCB_enatex_mask
_call_texrtn_dis:
    .long _call_texrtn
_p_schedtsk_dis:
    .long _p_schedtsk
_kernel_istkpt_dis:
    .long __kernel_istkpt
_mask_md_ipm_dis:
    .long (0x40000000 + INT_IPM(TMIN_INTPRI))
_mask_md_dis:
    .long 0x40000000
_mask_md_bl_dis:
    .long 0x50000000
_reqflg_dis:
    .long  _reqflg
_lock_flag_dis:
    .long _lock_flag
_saved_iipm_dis:
    .long _saved_iipm
save_fpureg_data dis
#ifdef LOG_DSP_ENTER
_log_dsp_enter_dis:
    .long _log_dsp_enter
#endif /* LOG_DSP_ENTER */
#ifdef LOG_DSP_LEAVE
_log_dsp_leave_dis:
    .long _log_dsp_leave
#endif /* LOG_DSP_LEAVE */

/*
 *  カーネルの終了処理の呼出し
 *
 *  モードとスタックを非タスクコンテキスト用に切り替え．
 */
    .globl _call_exit_kernel
_call_exit_kernel:
    mov.l _mask_md_ipm_exit, r0
    ldc   r0,sr    
    mov.l _kernel_istkpt_exit, r1
    mov.l @r1,r15
    mov.l _exit_kernel_exit,r0
    jmp   @r0
     nop

    .align 4
_mask_md_ipm_exit:
    .long 0x400000f0
_kernel_istkpt_exit:
    .long __kernel_istkpt
_exit_kernel_exit:
    .long _exit_kernel


/*
 *  タスク起動処理
 *
 *  ディスパッチャから呼び出されるため，TCBのアドレスはr0に
 *  入っている
 */ 
    .text
    .align 2
    .globl _start_r
_start_r:
    mov.l  _lock_flag_start, r1 /* CPUロック解除状態に */
    xor    r2,r2 
    mov.l  r2,@r1
    set_fpscr start
    mov.l  _mask_md_start,r4     /* 割り込み許可 */
    ldc    r4,sr
    mov.l  _ext_tsk_start,r2     /* 戻り番地を設定 */
    lds    r2,pr 
    mov.l  @(TCB_p_tinib,r0),r3  /* p_runtsk->p_tinibをr3に  */
    mov.l  @(TINIB_task,r3),r1   /* タスク起動番地をr1に     */
    jmp    @r1
     mov.l  @(TINIB_exinf,r3),r4 /* exinfを引数レジスタr4に  */

    .align 4
_lock_flag_start:
    .long _lock_flag
_mask_md_start:    
    .long 0x40000000
_ext_tsk_start:
    .long _ext_tsk
save_fpureg_data start


/*
 *  Exception 600 vector
 *  割り込みが発生すると実行される。
 *
 *
 *  SH34は割り込みが発生するとすべてVBR+0x600番地からプログラムを実行するため、
 *  ここに配置するルーチンでまずスタックの切り替え、レジスタの保存,IPMの設定,
 *  割り込み要因の判定を行いその後BLビットを0にして割り込みハンドラを呼ぶ必要
 *  がある。
 *  割り込み要因に対応した割り込みハンドラの開始番地は配列inh_tbl[]に登録し
 *  て呼び出す。オフセットの計算は、割り込み要因レジスタから求める．
 *  割込み要因レジスタはINTEVTとINTEVT2の二種類が存在するが，どちらを用いるかは
 *  プロセッサの型番毎に指定する．
 *  割込み優先度マスクは，int_iipm_tbl[]から取得し，SRに設定する．
 *
 *  reqflg をチェックする前に割込みを禁止しないと，reqflg をチェック後
 *  に起動された割込みハンドラ内でディスパッチが要求された場合に，ディ
 *  スパッチされない．
 *
 */

    .org    0x0600         /* _BASE_VBR + 0x0600番地に配置 */
    .align 2
    .global _interrupt_vec
_interrupt_vec:
    stc.l  spc,@-r15       /* 多重割り込みが入ると消えてしまうので        */
    sts.l  pr,@-r15        /* spc,pr,ssr,gbr,macl,mach                    */
    stc.l  ssr,@-r15    
    stc.l  gbr,@-r15                    
    sts.l  macl,@-r15                    
    sts.l  mach,@-r15                                                    
    stc.l  r0_bank,@-r15   /* ,r0〜r7をスタックに保存   */ 
    stc.l  r1_bank,@-r15
    stc.l  r2_bank,@-r15
    stc.l  r3_bank,@-r15
    stc.l  r4_bank,@-r15
    stc.l  r5_bank,@-r15
    stc.l  r6_bank,@-r15
    stc.l  r7_bank,@-r15
    save_scratch_fpureg int
    tst    r7,r7                 /* 割り込み発生時のコンテキストを判定  */
    bf/s   _interrupt_vec_1      /* 例外/割り込みハンドラならジャンプ   */
     add    #0x01,r7             /* 割り込みのネスト回数をインクリメント*/
    mov    r15,r1                /* スタックを入れ替え元のスタックポイ  */
    mov.l  _kernel_istkpt_int,r2 /* ンタを保存                          */
    mov.l  @r2,r15              
    mov.l  r1,@-r15            
_interrupt_vec_1:
    mov.l  _intevt_int,r0        /* 割込み要因レジスタから割込み番号    */
    mov.l  @r0,r4                /* を取得                              */
    mov.l  r4, @-r15             /* 割込み番号をスタックに保存          */
    index_intno r4               /* オフセットを求める                  */
    mov.l  _int_iipm_tbl_int,r0  /* 割り込み優先度マスクの値を取得      */
    mov.l  @(r0,r4),r5        
    mov.l  _inh_tbl_int,r0       /* 割り込みハンドラのアドレスを取得    */
    mov.l  @(r0,r4),r2
    mov    r15, r4               /* default_int_handlerのための引数     */
    ldc    r2,r2_bank            /* バンク0に切り替えるためコピー       */
    ldc    r5,sr                 /* これ以降割り込みを受け付ける。      */

#ifdef LOG_INH_ENTER
    mov.l @r15, r4               /* 割込み番号を引数に設定              */
    mov.l  r2, @-r15             /* 割込みハンドラのアドレスを保存      */
    mov.l _log_inh_enter_int, r1 /* ログ出力関数                        */
    jsr   @r1
     nop
    mov.l  @r15+, r2             /* 割込みハンドラのアドレスを復帰      */
    mov    r15, r4               /* default_int_handlerのための引数     */
#endif /* LOG_INH_ENTER */

    jsr    @r2                   /* 割り込みハンドラへ                  */
     nop

    mov.l @r15+, r4              /* 割込み番号を復帰                    */
#ifdef LOG_INH_LEAVE
    mov.l _log_inh_leave_int, r1 /* ログ出力関数                        */
    jsr  @r1
     nop
#endif /* LOG_INH_LEAVE */

    /*
     * 割込みハンドラ出口処理
     */
_ret_int:
    /*
     * 割込みのネスト段数を管理する r7_bank1 とスタックポインタ(r15)
     * の内容は不可分に行う必要がある．
     * 単に割込みを禁止しただけでは，カーネル管理外の割込みを禁止できない
     * ため，BLビットを1にセットして，カーネル管理外の割込みも禁止する．
     */
    mov.l  _mask_md_bl_ret,r0    /* BLビット を 1 に                       */
    ldc    r0,sr                 /* 全割込み禁止                           */
    stc    r7_bank,r7            /* 例外/割り込みのネスト回数をデクリメント*/
    dt     r7
    ldc    r7,r7_bank
    tst    r7,r7                 /* 戻り先が非タスクコンテキストならすぐに */
    bf     _ret_int_1            /* リターン                               */
    mov.l  @r15, r15             /* 戻り先がタスクなのでスタックを戻す     */
    mov.l  _reqflg_ret,r4        /* reqflgのチェック                       */
    mov.l  @r4,r1
    tst    r1,r1                 /* reqflgがfalseならret_int_1へ           */
    bt     _ret_int_1
    xor    r1,r1                 /* reqflgのクリアのためにr1を0に          */
    mov.l  _mask_md_ipm_ret,r0   /* BLビット を 0 に                       */
    ldc    r0, sr                /* カーネル管理外の割込み許可             */
    bra    _ret_int_2;
     mov.l  r1,@r4               /* reqflgをクリア                         */

_ret_int_1:
    /*
     *  割込み処理からのリターンにより，CPUロック解除状態に移行するよう
     *  準備する．割込み優先度マスクは，RTE命令により元の値に戻るため，
     *  lock_flagをfalseにしておけばよい（lock_flagをfalseにするのは，
     *  CPUロック状態のまま割込みハンドラから戻った時の対策）．
     */
    mov.l _lock_flag_ret, r0
    xor   r1,r1
    mov.l  r1,@r0
    restore_scratch_fpureg
    mov.l  @r15+,r7                /* 割り込み元に戻る                 */
    mov.l  @r15+,r6
    mov.l  @r15+,r5
    mov.l  @r15+,r4
    mov.l  @r15+,r3
    mov.l  @r15+,r2
    mov.l  @r15+,r1
    mov.l  @r15+,r0
    lds.l  @r15+,mach
    lds.l  @r15+,macl
    ldc.l  @r15+,gbr
    ldc.l  @r15+,ssr
    lds.l  @r15+,pr
    ldc.l  @r15+,spc
    rte
     nop

_ret_int_2:
    /*
     *  ここへは，CPU例外ハンドラの出口処理からも分岐してくる．
     *
     *  ここでは，戻り先がタスクであり，スタックは，タスクスタックに
     *  スクラッチレジスタのみが保存された状態になっている．また，
     *  カーネル管理の割込みを禁止した状態となっている．
     */
    /*
     *  CPUロック状態に移行する．カーネル管理の割込みはすでに禁止して
     *  いるので，lock_flagとsaved_iipmを更新する．saved_iipmは，戻り
     *  先の割込み優先度マスク（の内部表現）に設定する．
     *
     *  この時点でCPUロック状態とするのは，dispatcherへ分岐する時と，
     *  call_texrtnを呼び出す時に，CPUロック状態になっている必要がある
     *  ためである．
     */
    mov.l _lock_flag_ret, r2    /* lock_flagをtrueに */
    mov   #0x01,r1
    mov.l r1,@r2
    mov   r15,r0
    mov.l @(OFFSET_OF_SSR*4,r0),r2  /* 割込み前のIPMを取り出して */
    mov   r2,r0
    and   #0xf0,r0              /* saved_iipmに              */
    mov.l _saved_iipm_ret, r1
    mov.b r0,@r1
    /*
     *  dspflgがfalseである場合と，p_runtskとp_schedtskが同じ場合には，
     *  ディスパッチを行わない．このチェックが必要なのは，タスク例外処
     *  理ルーチンの呼出しが必要な場合に，ディスパッチが必要なくても，
     *  reqflgをtrueにするためである．
     */
    mov.l  _p_runtsk_ret,r1     /* r0 <- p_runtsk               */
    mov.l  @r1,r0           
    mov.l  _dspflg_ret,r2       /* dspflgがfalseならret_int_3へ */
    mov.l  @r2,r3
    tst    r3,r3
    bt     _ret_int_3    
    mov.l  _p_schedtsk_ret,r4   /* r5 <- schedtsk                */ 
    mov.l  @r4,r5
    cmp/eq r0,r5                /* runtsk と schedtsk を比較     */
    bt     _ret_int_3           /* 同じならret_int_3へ           */
    save_callsaved_fpureg_int
    mov.l  r14,@-r15            /* 残りのレジスタを保存          */
    mov.l  r13,@-r15
    mov.l  r12,@-r15
    mov.l  r11,@-r15
    mov.l  r10,@-r15
    mov.l  r9,@-r15
    mov.l  r8,@-r15
    mov.l  r15,@(TCB_sp,r0)     /* タスクスタックをTCBに保存 60以下ならOK*/
    mov.l  _ret_int_r_ret,r1    /* 実行再開番地を保存             */
    bra    _dispatcher
     mov.l  r1,@(TCB_pc,r0)


_ret_int_r:
    mov.l  @r15+,r8
    mov.l  @r15+,r9
    mov.l  @r15+,r10
    mov.l  @r15+,r11
    mov.l  @r15+,r12
    mov.l  @r15+,r13
    mov.l  @r15+,r14
_ret_int_3:
    /*
     *  タスク例外処理ルーチンの起動
     *  ret_int_r は dispatcher から呼び出されるため，tcbのアドレスはr0に
     *  入っている．
     *  なお，割込みの出口でタスクスイッチが発生しない場合はディスパッチャ
     *  を通らずに ret_int から直接 ret_int_1 に飛ぶ
     */
    mov    r0,r1
    mov.b  @(TCB_enatex,r1),r0
    mov.l  _enatex_mask_ret,r2
    tst    r0,r2
    bt/s   _ret_int_4           /* enatex が false ならret_int_4へ  */
     mov.l  @(TCB_texptn,r1),r0 /* texptnをロード                   */
    tst    r0,r0
    bt     _ret_int_4           /* texptn が 0ならret_int_4へ       */
    mov.l _call_texrtn_ret,r1   /* タスク例外ルーチンの呼び出し     */
    jsr   @r1
     nop
_ret_int_4:
    mov.l  _lock_flag_ret, r2  /* lock_flagをfalseに */
    xor    r0,r0 
    mov.l  r0,@r2
    restore_callsaved_fpureg_int
    restore_scratch_fpureg
    mov.l  @r15+,r7            /* spc,pr,ssr,スクラッチレジスタを復帰 */
    mov.l  @r15+,r6
    mov.l  @r15+,r5
    mov.l  @r15+,r4
    mov.l  @r15+,r3
    mov.l  @r15+,r2
    mov.l  @r15+,r1
    mov.l  _mask_md_bl_ret,r0
    ldc    r0,sr               /* BLを1に                             */
    mov.l  @r15+,r0
    lds.l  @r15+,mach
    lds.l  @r15+,macl
    ldc.l  @r15+,gbr
    ldc.l  @r15+,ssr
    lds.l  @r15+,pr
    ldc.l  @r15+,spc
    rte
     nop


    .align  4
_kernel_istkpt_int:
    .long __kernel_istkpt
_intevt_int:
#ifdef USE_INTEVT2
    .long  INTEVT2
#else
    .long  INTEVT
#endif /* USE_INTEVT2 */
_int_iipm_tbl_int:
    .long  _int_iipm_tbl
_inh_tbl_int:
    .long  _inh_tbl

_mask_md_ipm_ret:
    .long  (0x40000000 + INT_IPM(TMIN_INTPRI))
_lock_flag_ret:
    .long  _lock_flag
_mask_md_bl_ret:
    .long  0x50000000
_reqflg_ret:
    .long  _reqflg
_saved_iipm_ret:
    .long  _saved_iipm
_p_runtsk_ret:
    .long  _p_runtsk
_dspflg_ret:
    .long  _dspflg
_p_schedtsk_ret:
    .long  _p_schedtsk
_ret_int_r_ret:
    .long _ret_int_r
_enatex_mask_ret:
    .long TCB_enatex_mask
_call_texrtn_ret:
    .long _call_texrtn
#ifdef LOG_INH_ENTER
_log_inh_enter_int:
    .long _log_inh_enter
#endif /* LOG_INH_ENTER */
#ifdef LOG_INH_LEAVE
_log_inh_leave_int:
    .long _log_inh_leave
#endif /* LOG_INH_LEAVE */
save_fpureg_data int


/*
 *  微少時間待ち
 */
    .globl _sil_dly_nse
_sil_dly_nse:
    mov.l  _sil_dly_tim1, r1
    add    r1, r4
    cmp/pl r4
    bt     _sil_dly_nse1
    rts
     nop
_sil_dly_nse1:
    mov.l  _sil_dly_tim2, r1
    add    r1, r4
    cmp/pl r4
    bt     _sil_dly_nse1
    rts
     nop   
    .align 4
_sil_dly_tim1:
    .long  -SIL_DLY_TIM1
_sil_dly_tim2:
    .long  -SIL_DLY_TIM2
