$ 
$     �ѥ�2�Υ������ƥ������¸�ƥ�ץ졼�ȡ�SH34�ѡ�
$ 

$ 
$  ATT_ISR�ǻ��ѤǤ��������ֹ�Ȥ�����б��������ߥϥ�ɥ��ֹ�
$ 
$INTNO_ATTISR_VALID = INTNO_VALID$
$INHNO_ATTISR_VALID = INHNO_VALID$

$ 
$  DEF_INT��DEF_EXC�ǻ��ѤǤ������ߥϥ�ɥ��ֹ桿CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INHNO_DEFINH_VALID = INHNO_VALID$
$EXCNO_DEFEXC_VALID = EXCNO_VALID$

$ 
$  �����å���ˡ�λ���
$ 
$CHECK_STKSZ_ALIGN = 4$

$ 
$  CFG_INT�ǻ��ѤǤ��������ֹ�ȳ����ͥ����
$ 
$INTNO_CFGINT_VALID = INTNO_VALID$
$INTPRI_CFGINT_VALID = { -1,-2,...,-15 }$

$ 
$  �����°����Υ������åȰ�¸���Ѥ���ӥå�
$ 
$TARGET_INTATR = TA_NEGEDGE|TA_POSEDGE$
           
$ 
$  ɸ��ƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE "kernel/kernel.tf"$

/*$NL$
$SPC$*  Target-dependent Definitions (SH34)$NL$
$SPC$*/$NL$
$NL$

$ 
$  CFG_INT�Υ������ƥ������¸�Υ��顼�����å�
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
$  �����ͥ���٥ơ��֥������ɽ����
$ 
const uint32_t _kernel_int_iipm_tbl[TNUM_INT] = {$NL$
$FOREACH intno INTNO_RANGE$
	$IF LENGTH(INT.INTNO[intno])$
		$intmask = 0x40000000 | (-INT.INTPRI[intno] << 4)$
	$ELSE$
$		// LSB��1�ˤ��Ƥ���Τϡ������°�������ꤵ��Ƥ��ʤ����Ȥ�Ƚ
$		// �̤��뤿��Ǥ��롥
		$intmask = 0x400000F0 | 0x01 $
	$END$
	$TAB$$FORMAT("UINT32_C(0x%08x), /* 0x%03x */", intmask, +intno)$$NL$
$END$
$NL$};$NL$
$NL$

$ 
$  ����ߥϥ�ɥ�ơ��֥�
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
$  �㳰�ϥ�ɥ�ơ��֥�
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
