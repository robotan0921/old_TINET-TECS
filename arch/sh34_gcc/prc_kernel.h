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
 *  @(#) $Id: prc_kernel.h 1596 2009-06-29 09:41:45Z ertl-honda $
 */

/*
 *		kernel.hのプロセッサ依存部（SH3用）
 *
 *  このインクルードファイルは，target_kernel.h（または，そこからインク
 *  ルードされるファイル）のみからインクルードされる．他のファイルから
 *  直接インクルードしてはならない．
 */

#ifndef TOPPERS_PRC_KERNEL_H
#define TOPPERS_PRC_KERNEL_H

/*
 *  サポートする機能の定義
 */
#define TOPPERS_SUPPORT_DIS_INT            /* dis_intをサポートする */
#define TOPPERS_SUPPORT_ENA_INT            /* ena_intをサポートする */

/*
 *  カーネル管理の割込み優先度の範囲
 *
 *  TMIN_INTPRIの定義を変更することで，どのレベルよりも高い割込み優先度
 *  を持つものをカーネル管理外の割込みとするかを変更できる．
 *
 *  TMIN_INTPRIに設定できる値は，-15〜-1の範囲である．例えばTMIN_INTPRI
 *  を-14に設定すると，NMIに加えてレベル15の割込みがカーネル管理外とな
 *  る．TMIN_INTPRIを-15に設定すると，NMI以外にカーネル管理外の割込みを
 *  設けないことになる．
 */
#ifndef TMIN_INTPRI
#ifdef GDB_STUB
#define TMIN_INTPRI		(-14)		/* 割込み優先度の最小値（最高値）*/
#else /* GDB_STUB */
#define TMIN_INTPRI		(-15)		/* 割込み優先度の最小値（最高値）*/
#endif /* GDB_STUB */
#endif /* TMIN_INTPRI */

#define TMAX_INTPRI		(-1)		/* 割込み優先度の最大値（最低値）*/

/*
 *  割り込み属性
 */
#define	TA_POSEDGE		TA_EDGE			/* ポジティブエッジトリガ */
#define	TA_NEGEDGE		UINT_C(0x04)	/* ネガティブエッジトリガ */

#endif /* TOPPERS_PRC_KERNEL_H */
