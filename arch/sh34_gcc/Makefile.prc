#
#  @(#) $Id: Makefile.prc 1600 2009-06-29 10:12:42Z ertl-honda $
# 

#
#		Makefile のプロセッサ依存部（SH34用）
#

#
#  コンパイルオプション
#
COPTS := $(COPTS)
LDFLAGS := -nostdlib $(LDFLAGS) 
CDEFS := $(CDEFS) -DTOPPERS_LABEL_ASM
LIBS := $(LIBS) -lgcc

#
#  プロセッサの種類に応じたコンパイルオプション
#
ifeq ($(PRC_ARCH), SH3)
	COPTS := $(COPTS) -m3
endif

ifeq ($(PRC_ARCH), SH4)
	ifeq ($(FPU_ENABLE),true)
		ifeq ($(FPU_MODE),SINGLE)
			COPTS := $(COPTS) -m4-single
		else
		ifeq ($(FPU_MODE),SINGLE_ONLY)
			COPTS := $(COPTS) -m4-single-only
		else
		ifeq ($(FPU_MODE),DOUBLE)
			COPTS := $(COPTS) -m4
		endif
		endif
		endif
	else
		COPTS := $(COPTS) -m4-nofpu
	endif
endif

ifeq ($(PRC_ARCH), SH4A)
	ifeq ($(FPU_ENABLE),true)
		ifeq ($(FPU_MODE),SINGLE)
			COPTS := $(COPTS) -m4a-single
		else
		ifeq ($(FPU_MODE),SINGLE_ONLY)
			COPTS := $(COPTS) -m4a-single-only
		else
		ifeq ($(FPU_MODE),DOUBLE)
			COPTS := $(COPTS) -m4a
		endif
		endif
		endif
	else
		COPTS := $(COPTS) -m4a-nofpu
	endif
endif

#
#  FPUを使用する場合
#
ifeq ($(FPU_ENABLE),true)
CDEFS := $(CDEFS) -DFPU_ENABLE
endif

ifeq ($(FPU_MODE),SINGLE)
CDEFS := $(CDEFS) -DFPU_SINGLE
endif

ifeq ($(FPU_MODE),SINGLE_ONLY)
CDEFS := $(CDEFS) -DFPU_SINGLE_ONLY
endif

ifeq ($(FPU_MODE),DOUBLE)
CDEFS := $(CDEFS) -DFPU_DOUBLE
endif


#
#  カーネルに関する定義
#
KERNEL_DIR := $(KERNEL_DIR) $(SRCDIR)/arch/$(PRC)_$(TOOL)
KERNEL_ASMOBJS := $(KERNEL_ASMOBJS) prc_support.o
KERNEL_COBJS := $(KERNEL_COBJS) prc_config.o prc_timer.o

#
#  コンフィギュレータ関係の変数の定義
#
# CFG_TABS := $(CFG_TABS) --cfg1-def-table $(SRCDIR)/arch/$(PRC)_$(TOOL)/prc_def.csv
CFG_TABS := $(CFG_TABS) --symval-table $(SRCDIR)/arch/$(PRC)_$(TOOL)/prc_sym.def

#
#  依存関係の定義
#
cfg1_out.c: $(SRCDIR)/arch/$(PRC)_$(TOOL)/prc_def.csv
kernel_cfg.timestamp: $(SRCDIR)/arch/$(PRC)_$(TOOL)/prc.tf
