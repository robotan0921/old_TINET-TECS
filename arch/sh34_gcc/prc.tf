$ 
$     パス2のアーキテクチャ依存テンプレート（SH34用）
$ 

$ 
$  ATT_ISRで使用できる割込み番号とそれに対応する割込みハンドラ番号
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT／DEF_EXCで使用できる割込みハンドラ番号／CPU例外ハンドラ番号
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  チェック方法の指定
$ 
$CHECK_STKSZ_ALIGN = 4$

$ 
$  CFG_INTで使用できる割込み番号と割込み優先度
$ 
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -1,-2,...,-15 }$

$ 
$  割込み属性中のターゲット依存に用いるビット
$ 
$TARGET_INTATR = TA_NEGEDGE|TA_POSEDGE$
           
$ 
$  標準テンプレートファイルのインクルード
$ 
$INCLUDE "kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (SH34)$NL$
$SPC$*/$NL$
$NL$

$ 
$  CFG_INTのアーキテクチャ依存のエラーチェック
$ 
$FOREACH intno (INT.ORDER_LIST)$
	$IF (0x600 <= INT.INTNO[intno]) && (INT.INTNO[intno] <= 0x6A0)$
		$IF (INT.INTATR[intno] & ~(TA_ENAINT|TA_POSEDGE|TA_NEGEDGE)) != 0
			|| (INT.INTATR[intno] & (TA_POSEDGE|TA_NEGEDGE)) == (TA_POSEDGE|TA_NEGEDGE)$
			$ERROR INT.TEXT_LINE[intno]$E_RSATR: $FORMAT(_("illegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$  
	$ELSE$
		$IF (INT.INTATR[intno] & ~(TA_ENAINT)) != 0$
			$ERROR INT.TEXT_LINE[intno]$E_RSATR: $FORMAT(_("iillegal %1% `%2%\' of `%3%\' in %4%"), "intatr", INT.INTATR[intno], INT.INTNO[intno], "CFG_INT")$$END$
		$END$  
	$END$
$END$

$ 
$  割込み優先度テーブル（内部表現）
$ 
const uint32_t _kernel_int_iipm_tbl[TNUM_INT] = {$NL$
$FOREACH intno INTNO_RANGE$
	$IF LENGTH(INT.INTNO[intno])$
		$intmask = 0x40000000 | (-INT.INTPRI[intno] << 4)$
	$ELSE$
$		// LSBを1にしているのは，割込み属性が設定されていないことを判
$		// 別するためである．
		$intmask = 0x400000F0 | 0x01 $
	$END$
	$TAB$$FORMAT("UINT32_C(0x%08x), /* 0x%03x */", intmask, +intno)$$NL$
$END$
$NL$};$NL$
$NL$

$ 
$  割込みハンドラテーブル
$ 
const FP _kernel_inh_tbl[TNUM_INH] = {$NL$
$FOREACH inhno INHNO_RANGE$
	$IF LENGTH(INH.INHNO[inhno])$
		$TAB$(FP)($INH.INTHDR[inhno]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_int_handler),
	$END$
	$SPC$$FORMAT("/* 0x%03x */", +inhno)$$NL$
$END$
$NL$};$NL$
$NL$

$ 
$  例外ハンドラテーブル
$ 
const FP _kernel_exch_tbl[TNUM_EXC] = {$NL$
$FOREACH excno EXCNO_RANGE$
	$IF LENGTH(EXC.EXCNO[excno])$
		$TAB$(FP)($EXC.EXCHDR[excno]$),
	$ELSE$
		$TAB$(FP)(_kernel_default_exc_handler),
	$END$
	$SPC$$FORMAT("/* 0x%03x */", +excno)$$NL$
$END$
$NL$};$NL$
