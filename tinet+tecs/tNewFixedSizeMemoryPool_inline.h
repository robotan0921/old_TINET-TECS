/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tNewFixedSizeMemoryPool_inline_template.h => src/tNewFixedSizeMemoryPool_inline.h
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * Don't edit the comments between #[<...>]# and #[</...>]#
 * These comment are used by tecsmerege when merging.
 *
 * attr access macro #_CAAM_#
 * id               ID               ATTR_id         
 * blockSize        uint32_t         ATTR_blockSize  
 *
 * #[</PREAMBLE>]# */

/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eFixedSizeMemoryPool
 * entry port: eFixedSizeMemoryPool
 * signature:  sFixedSizeMemoryPool
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eFixedSizeMemoryPool_get
 * name:         eFixedSizeMemoryPool_get
 * global_name:  tNewFixedSizeMemoryPool_eFixedSizeMemoryPool_get
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline ER
eFixedSizeMemoryPool_get(CELLIDX idx, void** p_block)
{
	CELLCB	*p_cellcb = GET_CELLCB(idx);
	return(get_mpf( ATTR_id, p_block));
}

/* #[<ENTRY_FUNC>]# eFixedSizeMemoryPool_getPolling
 * name:         eFixedSizeMemoryPool_getPolling
 * global_name:  tNewFixedSizeMemoryPool_eFixedSizeMemoryPool_getPolling
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline ER
eFixedSizeMemoryPool_getPolling(CELLIDX idx, void** p_block)
{
	CELLCB	*p_cellcb = GET_CELLCB(idx);
	return(pget_mpf(ATTR_id, p_block));
}

/* #[<ENTRY_FUNC>]# eFixedSizeMemoryPool_getTimeout
 * name:         eFixedSizeMemoryPool_getTimeout
 * global_name:  tNewFixedSizeMemoryPool_eFixedSizeMemoryPool_getTimeout
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline ER
eFixedSizeMemoryPool_getTimeout(CELLIDX idx, void** p_block, TMO timeout)
{
	CELLCB	*p_cellcb = GET_CELLCB(idx);
	return(tget_mpf(ATTR_id, p_block, timeout));
}

/* #[<ENTRY_FUNC>]# eFixedSizeMemoryPool_release
 * name:         eFixedSizeMemoryPool_release
 * global_name:  tNewFixedSizeMemoryPool_eFixedSizeMemoryPool_release
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline ER
eFixedSizeMemoryPool_release(CELLIDX idx, const void* block)
{
	CELLCB	*p_cellcb = GET_CELLCB(idx);
	return(rel_mpf(ATTR_id, (void *)block));
}

/* #[<ENTRY_FUNC>]# eFixedSizeMemoryPool_initialize
 * name:         eFixedSizeMemoryPool_initialize
 * global_name:  tNewFixedSizeMemoryPool_eFixedSizeMemoryPool_initialize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline ER
eFixedSizeMemoryPool_initialize(CELLIDX idx)
{
	CELLCB	*p_cellcb = GET_CELLCB(idx);
	return(ini_mpf(ATTR_id));
}

/* #[<ENTRY_FUNC>]# eFixedSizeMemoryPool_refer
 * name:         eFixedSizeMemoryPool_refer
 * global_name:  tNewFixedSizeMemoryPool_eFixedSizeMemoryPool_refer
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline ER
eFixedSizeMemoryPool_refer(CELLIDX idx, T_RMPF* pk_memoryPoolFixedSizeStatus)
{
	CELLCB	*p_cellcb = GET_CELLCB(idx);
	return(ref_mpf(ATTR_id, pk_memoryPoolFixedSizeStatus));
}

/* #[<ENTRY_PORT>]# eMemoryPoolStatus
 * entry port: eMemoryPoolStatus
 * signature:  sMemoryPoolStatus
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eMemoryPoolStatus_getSize
 * name:         eMemoryPoolStatus_getSize
 * global_name:  tNewFixedSizeMemoryPool_eMemoryPoolStatus_getSize
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
Inline uint32_t
eMemoryPoolStatus_getSize(CELLIDX idx)
{
	CELLCB	*p_cellcb = GET_CELLCB(idx);
	return ATTR_blockSize;
}
