/*
 * This file was automatically generated by tecsgen.
 * Move and rename like below before editing,
 *   gen/tIPv4Funtions_template.c => src/tIPv4Funtions.c
 * to avoid to be overwritten by tecsgen.
 */
/* #[<PREAMBLE>]#
 * #[<...>]# から #[</...>]# で囲まれたコメントは編集しないでください
 * tecsmerge によるマージに使用されます
 *
 * 属性アクセスマクロ #_CAAM_#
 * IPv4AddressInit  T_IN4_ADDR       ATTR_IPv4AddressInit
 * IPv4MaskInit     T_IN4_ADDR       ATTR_IPv4MaskInit
 * IPv4GatawayInit  T_IN4_ADDR       ATTR_IPv4GatawayInit
 * IPv4Address      T_IN4_ADDR       VAR_IPv4Address 
 * IPv4Mask         T_IN4_ADDR       VAR_IPv4Mask    
 * IPv4Gataway      T_IN4_ADDR       VAR_IPv4Gataway 
 *
 * #[</PREAMBLE>]# */

/* Put prototype declaration and/or variale definition here #_PAC_# */
#include "tIPv4Functions_tecsgen.h"

#ifndef E_OK
#define	E_OK	0		/* success */
#define	E_ID	(-18)	/* illegal ID */
#endif




/* entry port function #_TEPF_# */
/* #[<ENTRY_PORT>]# eFunctions
 * entry port: eFunctions
 * signature:  sIPv4Functions
 * context:    task
 * #[</ENTRY_PORT>]# */


/*
 *  in_cksum_sum -- チェックサムの合計計算関数
 *
 *  注意: data は 4 オクテット単位でパディングすること。
 *        data が 2 オクテット単位にアラインされていないと
 *        例外が発生する可能性がある。
 *        len  は 4 オクテット単位にアラインされていること。
 *
 *        戻り値はホストバイトオーダ
 */

static uint32_t
in_cksum_sum (void *data, uint_t len /*オクテット単位*/) {
	uint32_t sum = 0;

	for ( ; len > 0; len -= 2) {
		sum += *((uint16_t*)data);
		data = (uint8_t*)data + 2;
		}

#ifdef SIL_ENDIAN_BIG
	return sum;
#endif
#ifdef SIL_ENDIAN_LITTLE
	return ((sum >> 8) & 0xffff) + ((sum & 0xff) << 8) + ((sum >> 24) & 0xff);
#endif	/* #if SIL_ENDIAN == SIL_ENDIAN_BIG */

	}

/*
 *  in_cksum_carry -- チェックサムの桁上げ計算関数
 *
 *  注意: data は 4 オクテット単位でパディングすること。
 *        data が 2 オクテット単位にアラインされていないと
 *        例外が発生する可能性がある。
 *        len  は 4 オクテット単位にアラインされていること。
 */

static uint32_t
in_cksum_carry (uint32_t sum) {
	uint32_t	carry;

	while (sum >= 0x00010000) {
		carry = sum >> 16;
		sum   = (sum & 0xffff) + carry;
		}

	return sum;
	}



/* #[<ENTRY_FUNC>]# eFunctions_checkSum
 * name:         eFunctions_checkSum
 * global_name:  tIPv4Functions_eFunctions_checkSum
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
uint16_t
eFunctions_checkSum(const int8_t* data, uint32_t len)
{
	uint16_t	sum;

	sum = (uint16_t)in_cksum_carry(in_cksum_sum(data, len));
	return (uint16_t)( htons(sum));
}

/* #[<ENTRY_FUNC>]# eFunctions_getIPv4Address
 * name:         eFunctions_getIPv4Address
 * global_name:  tIPv4Functions_eFunctions_getIPv4Address
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_IN4_ADDR
eFunctions_getIPv4Address()
{
	return VAR_IPv4Address;
}

/* #[<ENTRY_FUNC>]# eFunctions_getIPv4Mask
 * name:         eFunctions_getIPv4Mask
 * global_name:  tIPv4Functions_eFunctions_getIPv4Mask
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
T_IN4_ADDR
eFunctions_getIPv4Mask()
{
	return VAR_IPv4Mask;
}

/* #[<ENTRY_PORT>]# eCheckSum
 * entry port: eCheckSum
 * signature:  sIPv4CheckSum
 * context:    task
 * #[</ENTRY_PORT>]# */

/* #[<ENTRY_FUNC>]# eCheckSum_ipv4CheckSum
 * name:         eCheckSum_ipv4CheckSum
 * global_name:  tIPv4Functions_eCheckSum_ipv4CheckSum
 * oneway:       false
 * #[</ENTRY_FUNC>]# */
uint16_t
eCheckSum_ipv4CheckSum(int8_t* data, int32_t size, uint32_t offset, uint8_t proto)
{
	uint32_t sum;
	uint32_t align;
	T_NET_BUF *input = (T_NET_BUF *)data;

	/*IPヘッダの決定*/
	T_IP4_HDR *iphdr;
	iphdr = GET_IP4_HDR(input,input->off.ifhdrlen);
	uint32_t seglen = input->len - offset + input->off.ifalign;

	/* 4 オクテット境界のデータ長 */
	//align = (input->len -offset + 3) >> 2 << 2;
	align = (seglen + 3) >> 2 << 2;

	/* 4 オクテット境界までパディングで埋める。*/
	//if (align > input->len - offset)
	if (align > seglen)
	  memset((uint8_t*)input->buf + offset + seglen, 0, (size_t)(align - seglen));
	//	memset((uint8_t*)input->buf + input->len, 0, (size_t)(align - input->len));

	sum = in_cksum_sum(input->buf + offset, align)
	    + in_cksum_sum(&(iphdr->src), sizeof(T_IN4_ADDR) * 2)
//	    + input->len - offset + proto;
		  +seglen +proto;
	sum = in_cksum_carry(sum);

	return (uint16_t)( htons((uint16_t)sum));
}

/* #[<POSTAMBLE>]#
 *   これより下に非受け口関数を書きます
 * #[</POSTAMBLE>]#*/
