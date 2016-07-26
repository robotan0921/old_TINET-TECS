/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tTINET_template.c => src/tTINET.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * Don't edit the comments between #[<...>]# and #[</...>]#
 * These comment are used by tecsmerege when merging.
 *
 * attr access macro #_CAAM_#
 * next             uint32_t         VAR_next        
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tTINET_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eTINET
 * entry port: eTINET
 * signature:  sTINET
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eTINET_netRand
 * name:         eTINET_netRand
 * global_name:  tTINET_eTINET_netRand
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
uint32_t
eTINET_netRand()
{
	VAR_next = (VAR_next * 1103515245 + 12345) % (ULONG_C(0x7fffffff) + 1);
	return VAR_next;
}

/* #[<ENTRY_FUNC>]# eTINET_netSrand
 * name:         eTINET_netSrand
 * global_name:  tTINET_eTINET_netSrand
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
void
eTINET_netSrand(uint32_t speed)
{
	VAR_next += speed;
}

/* #[<POSTAMBLE>]#
 *   Put non-entry functions below.
 * #[</POSTAMBLE>]#*/




#ifdef SIL_ENDIAN_LITTLE

/*
 *  rev_memcpy_word -- ���]�������R�s�[�i4 �o�C�g�j
 *
 *    �o�C�g�P�ʂɃA�N�Z�X���鎖�ɂ��A
 *    ���E�ւ̃A���C���̖�����������B
 */

void
rev_memcpy_word (uint8_t *dst, uint8_t *src)
{
	*(dst    ) = *(src + 3);
	*(dst + 1) = *(src + 2);
	*(dst + 2) = *(src + 1);
	*(dst + 3) = *(src    );
	}

/*
 *  rev_memcmp_word -- ���]��������r�i4 �o�C�g�j
 *
 *    �o�C�g�P�ʂɃA�N�Z�X���鎖�ɂ��A
 *    ���E�ւ̃A���C���̖�����������B
 */

int_t
rev_memcmp_word (uint8_t *data1, uint8_t *data2)
{
	int_t	ix, diff;

	for (ix = 4; ix -- > 0; ) {
		diff = *(data1 + ix) -  *(data2 + (3 - ix));
		if (diff != 0)
			return diff;
		}
	return 0;
	}

#endif	/* of #ifdef SIL_ENDIAN_LITTLE */