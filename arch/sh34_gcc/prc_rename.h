/* This file is generated from prc_rename.def by genrename. */

#ifndef TOPPERS_PRC_RENAME_H
#define TOPPERS_PRC_RENAME_H

#define ret_int						_kernel_ret_int
#define ret_exc						_kernel_ret_exc
#define inh_tbl						_kernel_inh_tbl
#define int_iipm_tbl				_kernel_int_iipm_tbl
#define ipr_info_tbl				_kernel_ipr_info_tbl
#define exch_tbl					_kernel_exch_tbl
#define lock_flag					_kernel_lock_flag
#define saved_iipm					_kernel_saved_iipm
#define undefined_expevt			_kernel_undefined_expevt
#define undefined_interrupt			_kernel_undefined_interrupt
#define x_config_int				_kernel_x_config_int
#define prc_initialize				_kernel_prc_initialize
#define prc_terminate				_kernel_prc_terminate

#ifdef TOPPERS_LABEL_ASM

#define _ret_int					__kernel_ret_int
#define _ret_exc					__kernel_ret_exc
#define _inh_tbl					__kernel_inh_tbl
#define _int_iipm_tbl				__kernel_int_iipm_tbl
#define _ipr_info_tbl				__kernel_ipr_info_tbl
#define _exch_tbl					__kernel_exch_tbl
#define _lock_flag					__kernel_lock_flag
#define _saved_iipm					__kernel_saved_iipm
#define _undefined_expevt			__kernel_undefined_expevt
#define _undefined_interrupt		__kernel_undefined_interrupt
#define _x_config_int				__kernel_x_config_int
#define _prc_initialize				__kernel_prc_initialize
#define _prc_terminate				__kernel_prc_terminate

#endif /* TOPPERS_LABEL_ASM */


#endif /* TOPPERS_PRC_RENAME_H */
