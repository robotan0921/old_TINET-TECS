/*
 *  TOPPERS/ASP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Advanced Standard Profile Kernel
 * 
 *  Copyright (C) 2007-2008 by Embedded and Real-Time Systems Laboratory
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
 *  @(#) $Id: prc_config.h 1662 2009-11-04 00:26:05Z ertl-honda $
 */

/*
 *		プロセッサ依存モジュール（SH34用）
 *
 *  このインクルードファイルは，target_config.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_PRC_CONFIG_H
#define TOPPERS_PRC_CONFIG_H

#ifndef TOPPERS_MACRO_ONLY

/*
 *  プロセッサの特殊命令のインライン関数定義
 */
#include "prc_insn.h"

/*
 *  非タスクコンテキスト用のスタック初期値
 */
#define TOPPERS_ISTKPT(istk, istksz) ((STK_T *)((char_t *)(istk) + (istksz)))

/*
 *  タスクコンテキストブロックの定義
 */
typedef struct task_context_block {
	void	*sp;		/* スタックポインタ */
	FP		pc;			/* プログラムカウンタ */
} CTXB;

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  割込み優先度マスク操作ライブラリ
 *  
 *  SH34では，ステータスレジスタ（SR）の4〜7ビットめの4ビットに割込み優先度
 *  マスク（ハードウェアの割込み優先度マスク，IPM）が置かれている．IPMを保
 *  存しておくために，割込み優先度の外部表現（-1から連続した負の値）を使う
 *  ことも可能であるが，余計な左右ビットシフトと符号反転が必要になる．これ
 *  を避けるために，IPMを保存する場合には，SRの4〜7ビットめを取り出した値
 *  を使うことにする．この値を割込み優先度マスクの内部表現と呼び，IIPMと書
 *  くことにする．
 */

/*
 *  割込み優先度マスクの外部表現と内部表現の変換
 *
 *  アセンブリ言語のソースファイルからインクルードする場合のために，CASTを使用
 */
#define EXT_IPM(iipm)    (-CAST(PRI,(iipm) >> 4))       /* 内部表現を外部表現に */
#define INT_IPM(ipm)     (CAST(uint16_t, -(ipm)) << 4)  /* 外部表現を内部表現に */

#ifndef TOPPERS_MACRO_ONLY

/*
 *  IPM（ハードウェアの割込み優先度マスク，内部表現）の現在値の読出し
 */
Inline uint8_t
current_iipm(void)
{
    return((uint8_t)(current_sr() & 0xF0U));
}

/*
 *  IPM（ハードウェアの割込み優先度マスク，内部表現）の現在値の設定
 */
Inline void
set_iipm(uint8_t iipm)
{
    set_sr((current_sr() & ~0xF0U) | iipm);
}

/*
 *  TOPPERS標準割込み処理モデルの実現
 *
 *  SH34はステータスレジスタ(SR)内に割込み優先度マスク(IPM)を持っている．
 *  CPUロックフラグに相当機能を持たない．そのため，擬似的にCPUロックフ
 *  ラグを実現する．
 *
 *  まず，CPUロック状態を管理すための変数(lock_flag)を用意する．
 *
 *  CPUロックフラグがクリアされている間は，IPMをモデル上の割込み優先度
 *  マスクの値に設定する．この間は，モデル上の割込み優先度マスクは，
 *  IPMを用いる．
 * 
 *  それに対してCPUロックフラグがセットされいる間は，IPMを，カーネル管
 *  理外のものを除くすべての割込み要求をマスクする値(TIPM_LOCK)と，モデ
 *  ル上の割込み優先度マスクとの高い方に設定する．この間のモデル上の割
 *  込み優先度マスクは，そのための変数(saved_iipm, 内部表現で保持)を用
 *  意して保持する．
 */

/*
 *  コンテキストの参照
 *
 *  SH34では，コンテキストの判定に，割込みのネスト回数を管理する
 *  R7_BANK1を用いる．
 * 
 */
Inline bool_t
sense_context(void)
{
    uint32_t nest;

    Asm("stc r7_bank,%0" : "=r"(nest));
    return(nest > 0U);
}

#endif /* TOPPERS_MACRO_ONLY */

/*
 *  CPUロック状態での割込み優先度マスク
 *
 *  TIPM_LOCKは，CPUロック状態での割込み優先度マスク，すなわち，カーネ
 *  ル管理外のものを除くすべての割込みをマスクする値に定義する．
 */
#define TIPM_LOCK    TMIN_INTPRI

/*
 *  CPUロック状態での割込み優先度マスクの内部表現
 */
#define IIPM_LOCK    INT_IPM(TIPM_LOCK)

/*
 *  TIPM_ENAALL（割込み優先度マスク全解除）の内部表現
 */
#define IIPM_ENAALL  INT_IPM(TIPM_ENAALL)

#ifndef TOPPERS_MACRO_ONLY

/*
 *  CPUロックフラグ実現のための変数
 * 
 *  これらの変数は，CPUロック状態の時のみ書き換えてもよいとする．
 *  インライン関数中で，アクセスの順序が変化しないよう，volatile を指定． 
 */
extern volatile bool_t    lock_flag;   /* CPUロックフラグの値を保持する変数 */
extern volatile uint8_t saved_iipm;  /* 割込み優先度をマスクする変数 */

/*
 *  CPUロック状態への移行
 *
 *  IPM（ハードウェアの割込み優先度マスク）を，saved_iipmに保存し，カー
 *  ネル管理外のものを除くすべての割込みをマスクする値（TIPM_LOCK）に設
 *  定する．また，lock_flagをtrueにする．
 *
 *  IPMが，最初からTIPM_LOCKと同じかそれより高い場合には，それを
 *  saved_iipmに保存するのみで，TIPM_LOCKには設定しない．これは，モデル
 *  上の割込み優先度マスクが，TIPM_LOCKと同じかそれより高いレベルに設定
 *  されている状態にあたる．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）で呼ばれることは
 *  ないものと想定している．
 */
Inline void
x_lock_cpu(void)
{
    uint8_t iipm;

    /*
     *  current_iipm()の返り値を直接saved_iipmに保存せず，一時変数iipm
     *  を用いているのは，current_iipm()を呼んだ直後に割込みが発生し，
     *  起動された割込み処理でsaved_iipmが変更される可能性があるためで
     *  ある．
     */
    iipm = current_iipm();
    if (IIPM_LOCK > iipm) {
        set_iipm(IIPM_LOCK);
    }
    saved_iipm = iipm;
    lock_flag = true;
    /* クリティカルセクションの前後でメモリが書き換わる可能性がある */
    Asm("":::"memory");
}

#define t_lock_cpu()    x_lock_cpu()
#define i_lock_cpu()    x_lock_cpu()

/*
 *  CPUロック状態の解除
 *
 *  lock_flagをfalseにし，IPM（ハードウェアの割込み優先度マスク）を，
 *  saved_iipmに保存した値に戻す．
 *
 *  この関数は，CPUロック状態（lock_flagがtrueの状態）でのみ呼ばれるも
 *  のと想定している．
 */
Inline void
x_unlock_cpu(void)
{
    /* クリティカルセクションの前後でメモリが書き換わる可能性がある */
    Asm("":::"memory");
    lock_flag = false;
    set_iipm(saved_iipm);
}

#define t_unlock_cpu()    x_unlock_cpu()
#define i_unlock_cpu()    x_unlock_cpu()

/*
 *  CPUロック状態の参照
 */
Inline bool_t
x_sense_lock(void)
{
    return(lock_flag);
}

#define t_sense_lock()    x_sense_lock()
#define i_sense_lock()    x_sense_lock()

/*
 *  chg_ipmで有効な割込み優先度の範囲の判定
 *
 *  TMIN_INTPRIの値によらず，chg_ipmでは，-15〜TIPM_ENAALL（＝0）の範囲
 *  に設定できることとする（ターゲット定義の拡張）．
 */
#define VALID_INTPRI_CHGIPM(intpri) \
				((-15 <= (intpri) && (intpri) <= TIPM_ENAALL))

/*
 * （モデル上の）割込み優先度マスクの設定
 *
 *  CPUロックフラグがクリアされている時は，ハードウェアの割込み優先度マ
 *  スクを設定する．CPUロックフラグがセットされている時は，saved_iipm
 *  を設定し，さらに，ハードウェアの割込み優先度マスクを，設定しようと
 *  した（モデル上の）割込み優先度マスクとTIPM_LOCKの高い方に設定する．
 */
Inline void
x_set_ipm(PRI intpri)
{
    uint8_t   iipm = INT_IPM(intpri);

    if (!lock_flag) {
        set_iipm(iipm);
    }
    else {
        saved_iipm = iipm;
#if TIPM_LOCK == -15
        /*
         *  TIPM_LOCKが-15の場合には，この時点でハードウェアの割込み優先
         *  度マスクが必ず15に設定されているため，設定しなおす必要がない．
         */
#else /* TIPM_LOCK == -15 */
        set_iipm(iipm > IIPM_LOCK ? iipm : IIPM_LOCK);
#endif /* TIPM_LOCK == -15 */
    }
}

#define t_set_ipm(intpri)    x_set_ipm(intpri)
#define i_set_ipm(intpri)    x_set_ipm(intpri)

/*
 * （モデル上の）割込み優先度マスクの参照
 *
 *  CPUロックフラグがクリアされている時はハードウェアの割込み優先度マ
 *  スクを，セットされている時はsaved_iipmを参照する．
 */
Inline PRI
x_get_ipm(void)
{
    uint8_t iipm;

    if (!lock_flag) {
        iipm = current_iipm();
    }
    else {
        iipm = saved_iipm;
    }
    return(EXT_IPM(iipm));
}

#define t_get_ipm()    x_get_ipm()
#define i_get_ipm()    x_get_ipm()

/*
 *  最高優先順位タスクへのディスパッチ（prc_support.S）
 *
 *  dispatchは，タスクコンテキストから呼び出されたサービスコール処理か
 *  ら呼び出すべきもので，タスクコンテキスト・CPUロック状態・ディスパッ
 *  チ許可状態・（モデル上の）割込み優先度マスク全解除状態で呼び出さな
 *  ければならない．
 */
extern void dispatch(void);

/*
 *  ディスパッチャの動作開始（prc_support.S）
 *
 *  start_dispatchは，カーネル起動時に呼び出すべきもので，すべての割込
 *  みを禁止した状態（割込みロック状態と同等の状態）で呼び出さなければ
 *  ならない．
 */
extern void start_dispatch(void) NoReturn;

/*
 *  現在のコンテキストを捨ててディスパッチ（prc_support.S）
 *
 *  exit_and_dispatchは，ext_tskから呼び出すべきもので，タスクコンテキ
 *  スト・CPUロック状態・ディスパッチ許可状態・（モデル上の）割込み優先
 *  度マスク全解除状態で呼び出さなければならない．
 */
extern void exit_and_dispatch(void) NoReturn;

/*
 *  カーネルの終了処理の呼出し（prc_support.S）
 *
 *  call_exit_kernelは，カーネルの終了時に呼び出すべきもので，非タスク
 *  コンテキストに切り換えて，カーネルの終了処理（exit_kernel）を呼び出
 *  す．
 */
extern void call_exit_kernel(void) NoReturn;

/*
 *  タスクコンテキストの初期化
 *
 *  タスクが休止状態から実行できる状態に移行する時に呼ばれる．この時点
 *  でスタック領域を使ってはならない．
 *
 *  activate_contextを，インライン関数ではなくマクロ定義としているのは，
 *  この時点ではTCBが定義されていないためである．
 */
extern void    start_r(void);

#define activate_context(p_tcb)                                         \
{                                                                       \
    (p_tcb)->tskctxb.sp = (void *)((char_t *)((p_tcb)->p_tinib->stk)    \
                                        + (p_tcb)->p_tinib->stksz);     \
    (p_tcb)->tskctxb.pc = (void *) start_r;                             \
}

/*
 *  calltexは使用しない
 */
#define OMIT_CALLTEX

/*
 * ターゲット非依存部に含まれる標準の例外管理機能の初期化処理を用いない
 */
#define OMIT_INITIALIZE_EXCEPTION

/*
 * CPU例外ハンドラの初期化
 */
Inline void
initialize_exception(void)
{
}
     
/*
 *  SH34の割込みアーキテクチャと割込み処理モデルの実現
 * 
 *  SH34の割込みは，内部周辺モジュール割込み，IRQ割込み, PINT割込みに分
 *  類でき，それぞれ扱いが異なる．そのため，割込みハンドラ番号から，ど
 *  の割込みに分類するためのマクロを用意する．
 * 
 *  PINT割込みは15bitのプロセッサへの割込み要求ラインで実現されているが，
 *  IRCへの割込み要求ラインはPINT0〜PINT7とPINT0〜PINT7といった2本になっ
 *  ている．そのため，カーネルでも個別には扱わず，2本の割込みとして扱う．
 *  PINTは，個別にPINTERレジスタにより許可禁止可能であるが，カーネルで
 *  は，PINTERレジスタの設定は取り扱わない．そのため，PINTERレジスタの
 *  設定は，ユーザープログラムで行う必要がある．同様にPINTの要求レベル
 *  を設定するICR2の設定もユーザープログラムで行う必要がある．なお，エッ
 *  ジ割込みに設定した際の割込みハンドラの入り口でのIRR0のクリアは
 *  i_begin_int()で行う．PINT割込みかどうかを判定するマクロを用意する．
 *
 *  同様にIRQ割込みかを判定するマクロを用意する．
 */

/*
 *  PINT割込みかどうかを判定するためのマクロ
 */
#define INTNO_PINT(intno) ((0x700 == (intno)) || (0x720 == (intno)))
#define INTNO_PINT_OFFSET(intno) (((intno) - 0x700) >> 5)

/*
 *  IRQ割込みかどうかを判定するためのマクロ
 */
#define INTNO_IRQ(intno) ((0x600 <= (intno)) && ((intno) <= 0x6A0))
#define INTNO_IRQ_OFFSET(intno) (((intno) - 0x600) >> 5)
     
/*
 *  割込み優先度
 *
 *  各割込みの割込み優先度は割込み優先順設定レジスタ(IPRXX)によって設
 *  定する．内部周辺モジュールの場合，周辺モジュール毎に設定可能である．
 *  例えばSCIFは，ERI2, RXI2, BRI2, TXI2という4つの割込み要求ラインをサ
 *  ポートするが，全ての割込み要求ラインに対して同一の優先度しか設定で
 *  きない．そのため，各割込み要求ライン毎にどの割込み優先順設定レジス
 *  タを設定するかを定義したテーブルを用意する．また，割込み番号は連続
 *  していため，サポートしていない番号には，numberに-1を設定する．テー
 *  ブル
 */

/*
 *  各割込み番号毎の設定するIPRの情報管理のための構造体  
 */
typedef struct {
    /* IPRA:0, IPRB:1, IPRC:2, IPRD:3, IPRE:4, IPRF:5, IPRG:6 */
    uint32_t address; 
    /* bit5〜12:3, bit11〜8:2, bit7〜4:1, bit3〜0:0 */
    uint8_t  offset;
} IPR_INFO;

/*
 *  各割込み番号毎のIPRの情報管理テーブル
 */
extern const IPR_INFO ipr_info_tbl[TNUM_INH];
    
/*
 *  割込み番号・割込みハンドラ番号
 *
 *  割込みハンドラ番号(inhno)と割込み番号(intno)は，割込み発生時に割込
 *  み事象レジスタに設定される値を用いる．割込み事象レジスタは，INTEVT
 *  とINTEVT2の2種類があり，それぞれ設定される値が異なる．初期のSH34で
 *  はINTEVTを使用していたが，現在はINTEVT2を用いる．そのため，プロセ
 *  ッサの型番毎の定義ファイルを用意して，どちらのレジスタを用いるが設
 *  定することとする．また，サポートする割込みの最大数も異なるため，
 *  最大値もプロセッサの型番毎の定義ファイルに定義する．
 *
 *  INTENTに設定される値はスパースな値であるため，そのままの値を優先度
 *  管理等のテーブルのインデックスに用いると，無駄な領域が発生する．そ
 *  のため，カーネル内部では，INTENTに設定される値をシフトした値を用い
 *  る．シフトする値もプロセッサ毎に異なるためプロセッサの型番毎の定義
 *  ファイルに定義する．
 *
 *  内部表現の名前は，iintno,iinhnoとする．
 */

/*
 *  割込み番号の範囲の判定
 * 
 *  TMIN_INTNOとTMAX_INTNOの範囲であっても有効な番号でない場合があるた
 *  め，ipr_info_tbl[]で有効な番号かをチェックする
 */
#define VALID_INTNO(intno) \
        ((TMIN_INTNO <= (intno)) && ((intno) <= TMAX_INTNO) && (ipr_info_tbl[INT_INTNO(intno)].address != 0U))
#define VALID_INTNO_DISINT(intno)    VALID_INTNO(intno)
#define VALID_INTNO_CFGINT(intno)    VALID_INTNO(intno)

/*
 *  CPU例外ハンドラ番号
 *
 *  CPU例外ハンドラ番号としては，例外事象レジスタに設定する例外コードを
 *  用いる．サポートするCPU例外ハンドラ数はプロセッサの型番毎に異なるの
 *  で，プロセッサの型番毎の定義ファイルに定義する．
 *
 *  割込みハンドラ番号と同じく，CPU例外ハンドラ番号もスパースであるため，
 *  カーネル内部では値をシフトした内部表現を用いる． 
 */
#define VALID_EXCNO_DEFEXC(excno) \
        (TMIN_EXCNO <= (excno) && (excno) <= TMAX_EXCNO)

/*
 *  割込みハンドラ
 *
 *  割込みハンドラを登録する．割込みハンドラテーブル実体はコンフィギュ
 *  レータで静的に生成する
 */ 
extern const FP inh_tbl[TNUM_INH];

/*
 *  割込みハンドラの設定
 *
 *  ベクトル番号inhnoの割込みハンドラの起動番地int_entryに設定する．割込み
 *  ハンドラテーブル
 */
Inline void
x_define_inh(INHNO inhno, FP int_entry)
{
}

/*
 *  割込みハンドラの出入口処理の生成マクロ
 *
 */
#define INT_ENTRY(inhno, inthdr)    inthdr
#define INTHDR_ENTRY(inhno, inhno_num, inthdr) extern void inthdr(void);

/*
 *  割込み要求禁止フラグ
 *
 *  SH34のIRCは割込み要求禁止フラグを持たない．割込みを禁止する場合は，
 *  割込み優先順設定レジスタ(IPRXX)を0に設定する必要がある．割込み優
 *  先順設定レジスタを0にすることで割込み要求禁止フラグを実現するとその
 *  間，割込み優先度を記憶しておく領域が必要となる．コンフィギュレータ
 *  でこのテーブルを用意する．なお，このテーブルは割込みの入り口で割込
 *  み要因に応じてSRに設定する必要があるため，内部表現とする．また，割
 *  込みハンドラの入り口での利便性のため，IPMだけではなく，割込みハンド
 *  ラ実行時のSRの設定も同時に持つ．そのため，IPMの値のみを取得したい場
 *  合は，下位8bitのみを参照する必要がある．内容はコンフィギュレータで
 *  静的に生成する．
 */
extern const uint32_t int_iipm_tbl[TNUM_INT];

/*
 *  割込み要求禁止フラグのセット
 *
 *  割込み優先順設定レジスタ(IPRA〜G)を0に設定する．
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
 */
Inline bool_t
x_disable_int(INTNO intno)
{
    uint16_t iintno  = INT_INTNO(intno);
    uint32_t address = ipr_info_tbl[iintno].address;
    uint32_t offset  = ipr_info_tbl[iintno].offset;
    uint32_t iipm    = int_iipm_tbl[iintno];

    /*
     *  割込み属性が設定されていない場合
     */
    if ((iipm & 0x01U) != 0) {
        return(false);
    }
    
    /* 
     *  割込み番号に対応したIPRの値を0にする．
     */
    set_irc_ipr(address, offset, 0x00);

    return(true);
}

#define t_disable_int(intno) x_disable_int(intno)
#define i_disable_int(intno) x_disable_int(intno)

/*
 *  割込み要求禁止フラグの解除
 *
 *  割込み優先順設定レジスタ(IPRA〜G)を元の値に戻す．
 *
 *  割込み属性が設定されていない割込み要求ラインに対して割込み要求禁止
 *  フラグをクリアしようとした場合には，falseを返す．
 */
Inline bool_t
x_enable_int(INTNO intno)
{
    uint16_t iintno  = INT_INTNO(intno);
    uint32_t address = ipr_info_tbl[iintno].address;
    uint32_t offset  = ipr_info_tbl[iintno].offset;
    uint32_t iipm    = int_iipm_tbl[iintno];

    /*
     *  割込み属性が設定されていない場合
     */
    if ((iipm & 0x01U) != 0) {
        return(false);
    }

    /* 
     *  割込み番号に対応したIPRの値をセットする
     */
    set_irc_ipr(address, offset, (-EXT_IPM(iipm & 0xF0U)));
    
    return(true);
}

#define t_enable_int(intno) x_enable_int(intno)
#define i_enable_int(intno) x_enable_int(intno)

/*
 *  割込み要求ラインの属性の設定
 *
 *  SH34では，カーネルで扱える割込み優先度は16段階であるため，intpri
 *  として与えることができる値は-15〜-1が標準である．
 */
extern void    x_config_int(INTNO intno, ATR intatr, PRI intpri);

/*
 *  割込みハンドラ入口で必要なIRC操作
 *
 *  PINT・IRQ割込みでかつ，エッジトリガの場合は割込み要求をクリアする．
 *  エッジトリガか判断するのが面倒なので，常にクリアする．
 */
Inline void
i_begin_int(INTNO intno)
{
#ifdef SH3    
    uint8_t irr0_val;

    if (INTNO_PINT(intno)) {
        irr0_val = sil_reb_mem((void *) IRR0);
        irr0_val &= ~(0x40U << INTNO_PINT_OFFSET(intno));
    }
    else if (INTNO_IRQ(intno)) {
        irr0_val = sil_reb_mem((void *) IRR0);
        irr0_val &= ~(0x01U << INTNO_IRQ_OFFSET(intno));
    }
#endif    
}

/*
 *  割込みハンドラの出口で必要なIRC操作
 */
Inline void
i_end_int(INTNO intno)
{
}

/*
 *  未定義の割込みハンドラ(default_int_handler())の引数 p_excinf
 *  から各種情報を取り出すためのマクロ
 */
#define P_EXCINF_INT_OFFSET_SSR     (13U)
#define P_EXCINF_INT_OFFSET_SPC     (15U)
#define P_EXCINF_INT_OFFSET_PR      (14U)

/*
 *  CPU例外ハンドラ関係
 */ 

/*
 *  例外ハンドラ引数 p_excinf から各種情報を取り出すためのマクロ
 */
#ifdef FPU_ENABLE

#ifdef FPU_SAVE_BANKED_REG

#define P_EXCINF_EXC_OFFSET_SSR     (12U + 14U + 16U)
#define P_EXCINF_EXC_OFFSET_SPC     (14U + 14U + 16U)
#define P_EXCINF_EXC_OFFSET_PR      (13U + 14U + 16U)
#define P_EXCINF_EXC_OFFSET_EXPEVT    0U 

#else

#define P_EXCINF_EXC_OFFSET_SSR     (12U + 14U)
#define P_EXCINF_EXC_OFFSET_SPC     (14U + 14U)
#define P_EXCINF_EXC_OFFSET_PR      (13U + 14U)
#define P_EXCINF_EXC_OFFSET_EXPEVT    0U

#endif /* FPU_SAVE_BANKED_REG */

#else

#define P_EXCINF_EXC_OFFSET_SSR     12U
#define P_EXCINF_EXC_OFFSET_SPC     14U
#define P_EXCINF_EXC_OFFSET_PR      13U
#define P_EXCINF_EXC_OFFSET_EXPEVT   0U

#endif /* FPU_ENABLE */

/*
 *  CPU例外ハンドラの登録用テーブル
 */
extern const FP exch_tbl[TNUM_EXC];

/*
 *  CPU例外ハンドラの設定
 */
Inline void
x_define_exc(EXCNO excno, FP exc_entry)
{       
}

/*
 *  CPU例外ハンドラの入口処理の生成マクロ
 */
#define EXC_ENTRY(excno, exchdr)    exchdr
#define EXCHDR_ENTRY(excno, excno_num, exchdr) extern void exchdr(void *p_excinf);

/*
 *  CPU例外の発生した時のコンテキストの参照
 *
 *  CPU例外の発生した時のコンテキストが，タスクコンテキストの時にfalse，
 *  そうでない時にtrueを返す．
 */
Inline bool_t
exc_sense_context(void *p_excinf)
{
    uint32_t nest;

    Asm("stc r7_bank,%0" : "=r"(nest));
    return(nest > 1U);
}

/*
 *  CPU例外の発生した時のIPM（ハードウェアの割込み優先度マスク，内部表
 *  現）の参照
 */
Inline uint16_t
exc_get_iipm(void *p_excinf)
{
    return(*(((uint32_t *) p_excinf) + P_EXCINF_EXC_OFFSET_SSR) & 0x00F0U);
}

/*
 *  CPU例外の発生した時のコンテキストと割込みのマスク状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，割込みロック状態でなく，CPUロック状態でなく，（モ
 *  デル上の）割込み優先度マスク全解除状態である時にtrue，そうでない時
 *  にfalseを返す（CPU例外がカーネル管理外の割込み処理中で発生した場合
 *  にもfalseを返す）．
 *
 *  SHでは，CPU例外の発生した時のIPM（ハードウェアの割込み優先度マスク）
 *  がすべての割込みを許可する状態であることをチェックすることで，カー
 *  ネル実行中でないこと，割込みロック状態でないこと，CPUロック状態でな
 *  いこと，（モデル上の）割込み優先度マスク全解除状態であることの4つの
 *  条件をチェックすることができる（CPU例外が発生した時のlock_flagを参
 *  照する必要はない）．
 */
Inline bool_t
exc_sense_intmask(void *p_excinf)
{
    return(!exc_sense_context(p_excinf)
                    && exc_get_iipm(p_excinf) == IIPM_ENAALL);
}

/*
 *  CPU例外の発生した時のコンテキストと割込み／CPUロック状態の参照
 *
 *  CPU例外の発生した時のシステム状態が，カーネル実行中でなく，タスクコ
 *  ンテキストであり，割込みロック状態でなく，CPUロック状態でない時に
 *  true，そうでない時にfalseを返す（CPU例外がカーネル管理外の割込み処
 *  理中で発生した場合にもfalseを返す）．
 *
 *  SH34では，CPU例外の発生した時のIPM（ハードウェアの割込み優先度マ
 *  スク）がTIPM_LOCKより低いことをチェックすることで，カーネル実行中で
 *  ないこと，割込みロック状態でないこと，CPUロック状態でないことの3つ
 *  の条件をチェックしている（CPU例外が発生した時のlock_flagは参照して
 *  いない）．これにより，（モデル上の）割込み優先度マスクをTIPM_LOCK以
 *  上に設定してタスクを実行している時にもfalseが返ってしまうが，判断を
 *  正確にするためのオーバヘッドが大きいことから，許容することにする．
 */
Inline bool_t
exc_sense_unlock(void *p_excinf)
{
    return(!exc_sense_context(p_excinf)
                    && exc_get_iipm(p_excinf) < IIPM_LOCK);
}

/*
 * Trapa以外の例外で登録されていない例外が発生すると呼び出される
 */
extern void default_exc_handler(void *p_excinf);

/*
 * 未登録の割込みが発生した場合に呼び出される
 */
extern void default_int_handler(void *p_excinf);

/*
 *  プロセッサ依存の初期化
 */
extern void prc_initialize(void);

/*
 *  プロセッサ依存の終了時処理
 */
extern void prc_terminate(void);

#endif /* TOPPERS_MACRO_ONLY */
#endif /* TOPPERS_PRC_CONFIG_H */
