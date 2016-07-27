/*
 *  LAN9221 (LAN Controller)
 * 
 *  Copyright (C) 2001-2009 by Dep. of Computer Science and Engineering
 *                   Tomakomai National College of Technology, JAPAN
 *
 *  ???L????쌠?҂?́C??ȉ????? (1)?`(4) ??̎����??CFree Software Foundation 
 *  ??ɂ?悎��?Č???\?????ꂎĂ????? GNU General Public License ??? Version 2 ??ɋL
 *  q?????ꂎĂ??????����𖞂??????ꍇ??Ɍ?��???C?{?\?t?g?E?F?A?i?{?\?t?g?E?F?A
 *  ????????ς???????���̂????܂?ށD??ȉ?????????j??????p?E???????E?????ρE??Ĕz?z?i??ȉ???C
 *  ???p??ƌ?Ă?ԁj?????邎???Ƃ?𖎳???ŋ???�����???D
 *  (1) ?{?\?t?g?E?F?A????\?[?X?R?[?h??̌`??ŗ??p???????ꍇ??ɂ?́C???L??̒????
 *      ???\???C?????̗??p?����???悎щ???L??̖????ێ؋K??肎??C?????̂?܂?܂?̌`??Ń\?[
 *      ?X?R?[?h????Ɋ?܂?܂?ꂎĂ????邎???ƁD
 *  (2) ?{?\?t?g?E?F?A????C???C?u?????`????Ȃ?ǁC?????̃\?t?g?E?F?A?J?????Ɏ?
 *      ?p??ł??????`??ō?Ĕz?z???????ꍇ??ɂ?́C??Ĕz?z??ɔ??????h?L???????g?i???p
 *      ?҃}?j???A????Ȃ?ǁj??ɁC???L??̒???쌠?\???C?????̗??p?����???悎щ???L
 *      ??̖????ێ؋K??肎??f??ڂ????邎???ƁD
 *  (3) ?{?\?t?g?E?F?A????C?@??킎ɑg??ݍ???ނ?Ȃ?ǁC?????̃\?t?g?E?F?A?J?????Ɏ?
 *      ?p??ł????Ȃ???`??ō?Ĕz?z???????ꍇ??ɂ?́C???̎����𖞂??????????ƁD
 *    (a) ??Ĕz?z??ɔ??????h?L???????g?i???p?҃}?j???A????Ȃ?ǁj??ɁC???L??̒?
 *        ??쌠?\???C?????̗??p?����???悎щ???L??̖????ێ؋K??肎??f??ڂ????邎???ƁD
 *  (4) ?{?\?t?g?E?F?A??̗??p??ɂ?悎蒎???ړI??܂????͊?Ԑ?ړI??ɐ???????邎??????Ȃ?鑎?
 *      ?Q?????炎??C???L????쌠?҂????????OPPERS?v???W?F?N?g?????Ɛ?ӂ????邎???ƁD
 *
 *  ?{?\?t?g?E?F?A??́C?????ێ؂?Œ?񋟂????ꂎĂ????邎���̂?ł?????D???L????쌠?҂??
 *  ??????OPPERS?v???W?F?N?g??́C?{?\?t?g?E?F?A??Ɋ?ւ????āC?????̓K?p??\??????
 *  ??܂?߂?āC????????Ȃ?镎ێ؂???s??킎Ȃ???D??܂???C?{?\?t?g?E?F?A??̗??p??ɂ?悎蒎?
 *  ??ړI??܂????͊?Ԑ?ړI??ɐ????????????????Ȃ?鑎??Q??Ɋ?ւ????Ă???C?????̐?ӔC??𕉂?킎Ȃ???D
 * 
 *  @(#) $Id: echos4.cfg,v 1.5 2009/12/24 06:20:39 abe Exp abe $
 */

//#include "arch/gcc/tool_stddef.h"

#include "arch/sh34_gcc/sh7780.h"

extern void lan_initialize(long exinf);

typedef unsigned short u16_t;
typedef u16_t uip_ip4addr_t[2];
typedef uip_ip4addr_t uip_ipaddr_t;


typedef unsigned char u8_t;
struct uip_eth_addr {
  u8_t addr[6];
};

union utmp
{
	unsigned long l;
	unsigned char c[4];
}UTMP;


/*
extern void lan9221_mdelay(unsigned long count);
extern unsigned long lan9221_get_mac_csr(unsigned char addr);
extern void lan9221_set_mac_csr(unsigned char addr, unsigned long data);
extern void lan9221_reset(void);
extern void lan9221_handle_mac_address(void);
extern int lan9221_miiphy_read(unsigned char phy, unsigned char addr, unsigned long *data);
extern int lan9221_miiphy_write(unsigned char phy, unsigned char addr, unsigned long  data);
extern int lan9221_phy_reset(void);
extern void lan9221_phy_configure(void);
extern void lan9221_enable(void);
extern int lan9221_send(void *packet, int length);
extern int lan9221_recv(void *packet);
extern int lan9221_recvcheck(void);
*/

//?X?^?b?N?T?C?Y
#define TINET_STACK 4096

/*	?x?[?X?A?h???X	*/
#define LAN9221_BASE					0xA4000000//mikan ?????l?Őݒ??ł????ق????ǂ?
/*	???W?X?^?A?N?Z?X	*/
#define	lan9221_reg_write(addr,data)	(*((volatile unsigned long  *)(LAN9221_BASE + addr)) = (unsigned long) (data))
#define	lan9221_reg_read(addr)			(*((volatile unsigned long  *)(LAN9221_BASE + addr)))




/*	?R???g???[?????W?X?^	*/
#define LAN9221_RX_DATA_FIFO		 		0x00

#define LAN9221_TX_DATA_FIFO		 		0x20
#define LAN9221_TX_CMD_A_INT_ON_COMP		0x80000000
#define LAN9221_TX_CMD_A_INT_BUF_END_ALGN	0x03000000
#define LAN9221_TX_CMD_A_INT_4_BYTE_ALGN	0x00000000
#define LAN9221_TX_CMD_A_INT_16_BYTE_ALGN	0x01000000
#define LAN9221_TX_CMD_A_INT_32_BYTE_ALGN	0x02000000
#define LAN9221_TX_CMD_A_INT_DATA_OFFSET	0x001F0000
#define LAN9221_TX_CMD_A_INT_FIRST_SEG		0x00002000
#define LAN9221_TX_CMD_A_INT_LAST_SEG		0x00001000
#define LAN9221_TX_CMD_A_BUF_SIZE			0x000007FF
#define LAN9221_TX_CMD_B_PKT_TAG			0xFFFF0000
#define LAN9221_TX_CMD_B_ADD_CRC_DISABLE	0x00002000
#define LAN9221_TX_CMD_B_DISABLE_PADDING	0x00001000
#define LAN9221_TX_CMD_B_PKT_BYTE_LENGTH	0x000007FF

#define LAN9221_RX_STATUS_FIFO				0x40
#define LAN9221_RX_STS_PKT_LEN				0x3FFF0000
#define LAN9221_RX_STS_ES					0x00008000
#define LAN9221_RX_STS_BCST					0x00002000
#define LAN9221_RX_STS_LEN_ERR				0x00001000
#define LAN9221_RX_STS_RUNT_ERR				0x00000800
#define LAN9221_RX_STS_MCAST				0x00000400
#define LAN9221_RX_STS_TOO_LONG				0x00000080
#define LAN9221_RX_STS_COLL					0x00000040
#define LAN9221_RX_STS_ETH_TYPE				0x00000020
#define LAN9221_RX_STS_WDOG_TMT				0x00000010
#define LAN9221_RX_STS_MII_ERR				0x00000008
#define LAN9221_RX_STS_DRIBBLING			0x00000004
#define LAN9221_RX_STS_CRC_ERR				0x00000002

#define LAN9221_RX_STATUS_FIFO_PEEK			0x44

#define LAN9221_TX_STATUS_FIFO				0x48
#define LAN9221_TX_STS_TAG					0xFFFF0000
#define LAN9221_TX_STS_ES					0x00008000
#define LAN9221_TX_STS_LOC					0x00000800
#define LAN9221_TX_STS_NO_CARR				0x00000400
#define LAN9221_TX_STS_LATE_COLL			0x00000200
#define LAN9221_TX_STS_MANY_COLL			0x00000100
#define LAN9221_TX_STS_COLL_CNT				0x00000078
#define LAN9221_TX_STS_MANY_DEFER			0x00000004
#define LAN9221_TX_STS_UNDERRUN				0x00000002
#define LAN9221_TX_STS_DEFERRED				0x00000001

#define LAN9221_TX_STATUS_FIFO_PEEK			0x4C

#define LAN9221_ID_REV						0x50
#define LAN9221_ID_REV_CHIP_ID				0xFFFF0000
#define LAN9221_ID_REV_REV_ID				0x0000FFFF

#define LAN9221_INT_CFG						0x54
#define LAN9221_INT_CFG_INT_DEAS			0xFF000000
#define LAN9221_INT_CFG_INT_DEAS_CLR		0x00004000
#define LAN9221_INT_CFG_INT_DEAS_STS		0x00002000
#define LAN9221_INT_CFG_IRQ_INT				0x00001000
#define LAN9221_INT_CFG_IRQ_EN				0x00000100
#define LAN9221_INT_CFG_IRQ_POL				0x00000010
#define LAN9221_INT_CFG_IRQ_TYPE			0x00000001

#define LAN9221_INT_STS						0x58
#define LAN9221_INT_STS_SW_INT				0x80000000
#define LAN9221_INT_STS_TXSTOP_INT			0x02000000
#define LAN9221_INT_STS_RXSTOP_INT			0x01000000
#define LAN9221_INT_STS_RXDFH_INT			0x00800000
#define LAN9221_INT_STS_RXDF_INT			0x00400000
#define LAN9221_INT_STS_TX_IOC				0x00200000
#define LAN9221_INT_STS_RXD_INT				0x00100000
#define LAN9221_INT_STS_GPT_INT				0x00080000
#define LAN9221_INT_STS_PHY_INT				0x00040000
#define LAN9221_INT_STS_PME_INT				0x00020000
#define LAN9221_INT_STS_TXSO				0x00010000
#define LAN9221_INT_STS_RWT					0x00008000
#define LAN9221_INT_STS_RXE					0x00004000
#define LAN9221_INT_STS_TXE					0x00002000
#define LAN9221_INT_STS_TDFU				0x00000800
#define LAN9221_INT_STS_TDFO				0x00000400
#define LAN9221_INT_STS_TDFA				0x00000200
#define LAN9221_INT_STS_TSFF				0x00000100
#define LAN9221_INT_STS_TSFL				0x00000080
#define LAN9221_INT_STS_RDFO				0x00000040
#define LAN9221_INT_STS_RDFL				0x00000020
#define LAN9221_INT_STS_RSFF				0x00000010
#define LAN9221_INT_STS_RSFL				0x00000008
#define LAN9221_INT_STS_GPIO2_INT			0x00000004
#define LAN9221_INT_STS_GPIO1_INT			0x00000002
#define LAN9221_INT_STS_GPIO0_INT			0x00000001

#define LAN9221_INT_EN						0x5C
#define LAN9221_INT_EN_SW_INT_EN			0x80000000
#define LAN9221_INT_EN_TXSTOP_INT_EN		0x02000000
#define LAN9221_INT_EN_RXSTOP_INT_EN		0x01000000
#define LAN9221_INT_EN_RXDFH_INT_EN			0x00800000
#define LAN9221_INT_EN_TIOC_INT_EN			0x00200000
#define LAN9221_INT_EN_RXD_INT_EN			0x00100000
#define LAN9221_INT_EN_GPT_INT_EN			0x00080000
#define LAN9221_INT_EN_PHY_INT_EN			0x00040000
#define LAN9221_INT_EN_PME_INT_EN			0x00020000
#define LAN9221_INT_EN_TXSO_EN				0x00010000
#define LAN9221_INT_EN_RWT_EN				0x00008000
#define LAN9221_INT_EN_RXE_EN				0x00004000
#define LAN9221_INT_EN_TXE_EN				0x00002000
#define LAN9221_INT_EN_TDFU_EN				0x00000800
#define LAN9221_INT_EN_TDFO_EN				0x00000400
#define LAN9221_INT_EN_TDFA_EN				0x00000200
#define LAN9221_INT_EN_TSFF_EN				0x00000100
#define LAN9221_INT_EN_TSFL_EN				0x00000080
#define LAN9221_INT_EN_RDFO_EN				0x00000040
#define LAN9221_INT_EN_RDFL_EN				0x00000020
#define LAN9221_INT_EN_RSFF_EN				0x00000010
#define LAN9221_INT_EN_RSFL_EN				0x00000008
#define LAN9221_INT_EN_GPIO2_INT			0x00000004
#define LAN9221_INT_EN_GPIO1_INT			0x00000002
#define LAN9221_INT_EN_GPIO0_INT			0x00000001

#define LAN9221_BYTE_TEST					0x64
#define LAN9221_BYTE_TEST_VAL				0x87654321

#define LAN9221_FIFO_INT					0x68
#define LAN9221_FIFO_INT_TX_AVAIL_LEVEL		0xFF000000
#define LAN9221_FIFO_INT_TX_STS_LEVEL		0x00FF0000
#define LAN9221_FIFO_INT_RX_AVAIL_LEVEL		0x0000FF00
#define LAN9221_FIFO_INT_RX_STS_LEVEL		0x000000FF

#define LAN9221_RX_CFG						0x6C
#define LAN9221_RX_CFG_RX_END_ALGN			0xC0000000
#define LAN9221_RX_CFG_RX_END_ALGN4			0x00000000
#define LAN9221_RX_CFG_RX_END_ALGN16		0x40000000
#define LAN9221_RX_CFG_RX_END_ALGN32		0x80000000
#define LAN9221_RX_CFG_RX_DMA_CNT			0x0FFF0000
#define LAN9221_RX_CFG_RX_DUMP				0x00008000
#define LAN9221_RX_CFG_RXDOFF				0x00001F00

#define LAN9221_TX_CFG						0x70
#define LAN9221_TX_CFG_TXS_DUMP				0x00008000
#define LAN9221_TX_CFG_TXD_DUMP				0x00004000
#define LAN9221_TX_CFG_TXSAO				0x00000004
#define LAN9221_TX_CFG_TX_ON				0x00000002
#define LAN9221_TX_CFG_STOP_TX				0x00000001

#define LAN9221_HW_CFG						0x74
#define LAN9221_HW_CFG_FPORTEND				0x20000000
#define LAN9221_HW_CFG_FSELEND				0x10000000
#define LAN9221_HW_CFG_AMDIX				0x01000000
#define LAN9221_HW_CFG_MBO					0x00100000
#define LAN9221_HW_CFG_TX_FIF_SZ			0x000F0000
#define LAN9221_HW_CFG_SRST_TO				0x00000002
#define LAN9221_HW_CFG_SRST					0x00000001

#define LAN9221_RX_DP_CTRL					0x78
#define LAN9221_RX_DP_CTRL_RX_FFWD			0x80000000

#define LAN9221_RX_FIFO_INF					0x7C
#define LAN9221_RX_FIFO_INF_RXSUSED			0x00FF0000
#define LAN9221_RX_FIFO_INF_RXDUSED			0x0000FFFF

#define LAN9221_TX_FIFO_INF					0x80
#define LAN9221_TX_FIFO_INF_TSUSED			0x00FF0000
#define LAN9221_TX_FIFO_INF_TDFREE			0x0000FFFF

#define LAN9221_PMT_CTRL					0x84
#define LAN9221_PMT_CTRL_PM_MODE			0x00003000
#define LAN9221_PMT_CTRL_PHY_RST			0x00000400
#define LAN9221_PMT_CTRL_WOL_EN				0x00000200
#define LAN9221_PMT_CTRL_ED_EN				0x00000100
#define LAN9221_PMT_CTRL_PME_TYPE			0x00000040
#define LAN9221_PMT_CTRL_WUPS				0x00000030
#define LAN9221_PMT_CTRL_WUPS_NOWAKE		0x00000000
#define LAN9221_PMT_CTRL_WUPS_ED			0x00000010
#define LAN9221_PMT_CTRL_WUPS_WOL			0x00000020
#define LAN9221_PMT_CTRL_WUPS_MULTI			0x00000030
#define LAN9221_PMT_CTRL_PME_IND			0x00000008
#define LAN9221_PMT_CTRL_PME_POL			0x00000004
#define LAN9221_PMT_CTRL_PME_EN				0x00000002
#define LAN9221_PMT_CTRL_READY				0x00000001

#define LAN9221_GPIO_CFG					0x88
#define LAN9221_GPIO_CFG_LED3_EN			0x40000000
#define LAN9221_GPIO_CFG_LED2_EN			0x20000000
#define LAN9221_GPIO_CFG_LED1_EN			0x10000000
#define LAN9221_GPIO_CFG_GPIO2_INT_POL		0x04000000
#define LAN9221_GPIO_CFG_GPIO1_INT_POL		0x02000000
#define LAN9221_GPIO_CFG_GPIO0_INT_POL		0x01000000
#define LAN9221_GPIO_CFG_EEPR_EN			0x00700000
#define LAN9221_GPIO_CFG_GPIOBUF2			0x00040000
#define LAN9221_GPIO_CFG_GPIOBUF1			0x00020000
#define LAN9221_GPIO_CFG_GPIOBUF0			0x00010000
#define LAN9221_GPIO_CFG_GPIODIR2			0x00000400
#define LAN9221_GPIO_CFG_GPIODIR1			0x00000200
#define LAN9221_GPIO_CFG_GPIODIR0			0x00000100
#define LAN9221_GPIO_CFG_GPIOD4				0x00000010
#define LAN9221_GPIO_CFG_GPIOD3				0x00000008
#define LAN9221_GPIO_CFG_GPIOD2				0x00000004
#define LAN9221_GPIO_CFG_GPIOD1				0x00000002
#define LAN9221_GPIO_CFG_GPIOD0				0x00000001

#define LAN9221_GPT_CFG						0x8C
#define LAN9221_GPT_CFG_TIMER_EN			0x20000000
#define LAN9221_GPT_CFG_GPT_LOAD			0x0000FFFF

#define LAN9221_GPT_CNT						0x90
#define LAN9221_GPT_CNT_GPT_CNT				0x0000FFFF

#define LAN9221_WORD_SWAP					0x98
#define LAN9221_WORD_SWAP_DISABLE			0x00000000
#define LAN9221_WORD_SWAP_ENABLE			0xFFFFFFFF


#define LAN9221_FREE_RUN					0x9C

#define LAN9221_RX_DROP						0xA0

#define LAN9221_MAC_CSR_CMD					0xA4
#define LAN9221_MAC_CSR_CMD_CSR_BUSY		0x80000000
#define LAN9221_MAC_CSR_CMD_R_NOT_W			0x40000000
#define LAN9221_MAC_CSR_CMD_CSR_ADDR		0x000000FF

#define LAN9221_MAC_CSR_DATA				0xA8

#define LAN9221_AFC_CFG						0xAC
#define LAN9221_AFC_CFG_AFC_HI				0x00FF0000
#define LAN9221_AFC_CFG_AFC_LO				0x0000FF00
#define LAN9221_AFC_CFG_BACK_DUR			0x000000F0
#define LAN9221_AFC_CFG_FCMULT				0x00000008
#define LAN9221_AFC_CFG_FCBRD				0x00000004
#define LAN9221_AFC_CFG_FCADD				0x00000002
#define LAN9221_AFC_CFG_FCANY				0x00000001

#define LAN9221_E2P_CMD						0xB0
#define LAN9221_E2P_CMD_EPC_BUSY			0x80000000
#define LAN9221_E2P_CMD_EPC_CMD				0x70000000
#define LAN9221_E2P_CMD_EPC_CMD_READ		0x00000000
#define LAN9221_E2P_CMD_EPC_CMD_EWDS		0x10000000
#define LAN9221_E2P_CMD_EPC_CMD_EWEN		0x20000000
#define LAN9221_E2P_CMD_EPC_CMD_WRITE		0x30000000
#define LAN9221_E2P_CMD_EPC_CMD_WRAL		0x40000000
#define LAN9221_E2P_CMD_EPC_CMD_ERASE		0x50000000
#define LAN9221_E2P_CMD_EPC_CMD_ERAL		0x60000000
#define LAN9221_E2P_CMD_EPC_CMD_RELOAD		0x70000000
#define LAN9221_E2P_CMD_EPC_TIMEOUT			0x00000200
#define LAN9221_E2P_CMD_MAC_ADDR_LOADED		0x00000100
#define LAN9221_E2P_CMD_EPC_ADDR			0x000000FF

#define LAN9221_E2P_DATA					0xB4
#define LAN9221_E2P_DATA_EEPROM_DATA		0x000000FF


/*	?_???w???W?X?^	*/
#define LAN9221_MAC_CR					0x01
#define LAN9221_MAC_CR_RXALL			0x80000000
#define LAN9221_MAC_CR_HBDIS			0x10000000
#define LAN9221_MAC_CR_RCVOWN			0x00800000
#define LAN9221_MAC_CR_LOOPBK			0x00200000
#define LAN9221_MAC_CR_FDPX				0x00100000
#define LAN9221_MAC_CR_MCPAS			0x00080000
#define LAN9221_MAC_CR_PRMS				0x00040000
#define LAN9221_MAC_CR_INVFILT			0x00020000
#define LAN9221_MAC_CR_PASSBAD			0x00010000
#define LAN9221_MAC_CR_HFILT			0x00008000
#define LAN9221_MAC_CR_HPFILT			0x00002000
#define LAN9221_MAC_CR_LCOLL			0x00001000
#define LAN9221_MAC_CR_BCAST			0x00000800
#define LAN9221_MAC_CR_DISRTY			0x00000400
#define LAN9221_MAC_CR_PADSTR			0x00000100
#define LAN9221_MAC_CR_BOLMT_MASK		0x000000C0
#define LAN9221_MAC_CR_DFCHK			0x00000020
#define LAN9221_MAC_CR_TXEN				0x00000008
#define LAN9221_MAC_CR_RXEN				0x00000004

#define LAN9221_ADDRH					0x02
#define LAN9221_ADDRL					0x03

#define LAN9221_HASHH					0x04
#define LAN9221_HASHL					0x05

#define LAN9221_MII_ACC					0x06
#define LAN9221_MII_ACC_PHY_ADDR		0x0000F800
#define LAN9221_MII_ACC_MIIRINDA		0x000007C0
#define LAN9221_MII_ACC_MII_WRITE		0x00000002
#define LAN9221_MII_ACC_MII_BUSY		0x00000001

#define LAN9221_MII_DATA				0x07

#define LAN9221_FLOW					0x08
#define LAN9221_FLOW_FCPT				0xFFFF0000
#define LAN9221_FLOW_FCPASS				0x00000004
#define LAN9221_FLOW_FCEN				0x00000002
#define LAN9221_FLOW_FCBSY				0x00000001

#define LAN9221_VLAN1					0x09
#define LAN9221_VLAN1_VTI1				0x0000ffff

#define LAN9221_VLAN2					0x0A
#define LAN9221_VLAN2_VTI2				0x0000ffff

#define LAN9221_WUFF					0x0B

#define LAN9221_WUCSR					0x0C
#define LAN9221_WUCSR_GUE				0x00000200
#define LAN9221_WUCSR_WUFR				0x00000040
#define LAN9221_WUCSR_MPR				0x00000020
#define LAN9221_WUCSR_WAKE_EN			0x00000004
#define LAN9221_WUCSR_MPEN				0x00000002


/*	??????w???W?X?^	*/
#define LAN9221_PHY_BMCR				0x00
#define LAN9221_PHY_BMCR_RESET			0x8000
#define LAN9221_PHY_BMCR_LOOP			0x4000
#define LAN9221_PHY_BMCR_100MB			0x2000
#define LAN9221_PHY_BMCR_AUTON			0x1000
#define LAN9221_PHY_BMCR_POWD			0x0800
#define LAN9221_PHY_BMCR_ISO			0x0400
#define LAN9221_PHY_BMCR_RST_NEG		0x0200
#define LAN9221_PHY_BMCR_DPLX			0x0100
#define LAN9221_PHY_BMCR_COL_TST		0x0080
#define LAN9221_PHY_BMCR_SPEED_MASK		0x2040
#define LAN9221_PHY_BMCR_1000_MBPS		0x0040
#define LAN9221_PHY_BMCR_100_MBPS		0x2000
#define LAN9221_PHY_BMCR_10_MBPS		0x0000

#define LAN9221_PHY_BMSR				0x01
#define LAN9221_PHY_BMSR_100T4			0x8000
#define LAN9221_PHY_BMSR_100TXF			0x4000
#define LAN9221_PHY_BMSR_100TXH			0x2000
#define LAN9221_PHY_BMSR_10TF			0x1000
#define LAN9221_PHY_BMSR_10TH			0x0800
#define LAN9221_PHY_BMSR_EXT_STAT		0x0100
#define LAN9221_PHY_BMSR_PRE_SUP		0x0040
#define LAN9221_PHY_BMSR_AUTN_COMP		0x0020
#define LAN9221_PHY_BMSR_RF				0x0010
#define LAN9221_PHY_BMSR_AUTN_ABLE		0x0008
#define LAN9221_PHY_BMSR_LS				0x0004
#define LAN9221_PHY_BMSR_JD				0x0002
#define LAN9221_PHY_BMSR_EXT			0x0001

#define LAN9221_PHY_PHYIDR1				0x02
#define LAN9221_PHY_PHYIDR2				0x03

#define LAN9221_PHY_ANAR				0x04
#define LAN9221_PHY_ANAR_NXTPG_CAP		0x8000
#define LAN9221_PHY_ANAR_REM_FAULT		0x2000
#define LAN9221_PHY_ANAR_PAUSE_OP_MSK	0x0C00
#define LAN9221_PHY_ANAR_PAUSE_OP_NONE	0x0000
#define LAN9221_PHY_ANAR_PAUSE_OP_ASLP	0x0400
#define LAN9221_PHY_ANAR_PAUSE_OP_SLP	0x0800
#define LAN9221_PHY_ANAR_PAUSE_OP_BOTH	0x0C00
#define LAN9221_PHY_ANAR_100_T4_ABLE	0x0200
#define LAN9221_PHY_ANAR_100_TX_FDPLX	0x0100
#define LAN9221_PHY_ANAR_100_TX_ABLE	0x0080
#define LAN9221_PHY_ANAR_10_FDPLX 		0x0040
#define LAN9221_PHY_ANAR_10_ABLE  		0x0020

#define LAN9221_PHY_ANLPAR				0x05
#define LAN9221_PHY_ANLPAR_NXTPG_CAP	0x8000
#define LAN9221_PHY_ANLPAR_ACK			0x4000
#define LAN9221_PHY_ANLPAR_REM_FAULT	0x2000
#define LAN9221_PHY_ANLPAR_PAUSE_CAP	0x0400
#define LAN9221_PHY_ANLPAR_100_T4_ABLE	0x0200
#define LAN9221_PHY_ANLPAR_100_TX_FDPLX	0x0100
#define LAN9221_PHY_ANLPAR_100_TX_ABLE	0x0080
#define LAN9221_PHY_ANLPAR_10_FDPLX		0x0040
#define LAN9221_PHY_ANLPAR_10_ABLE		0x0020

#define LAN9221_PHY_ANER				0x06
#define LAN9221_PHY_ANER_PARDET_FAULT	0x0010
#define LAN9221_PHY_ANER_LP_NXTPG_CAP	0x0008
#define LAN9221_PHY_ANER_NXTPG_CAP		0x0004
#define LAN9221_PHY_ANER_NEWPG_REC		0x0002
#define LAN9221_PHY_ANER_LP_AN_ABLE		0x0001

#define LAN9221_PHY_SILREV   			0x10

#define LAN9221_PHY_MCSR   				0x11
#define LAN9221_PHY_MCSR_EDPWRDOWN		0x2000
#define LAN9221_PHY_MCSR_ENERGYON 		0x0002

#define LAN9221_PHY_SPMODES   			0x12

#define LAN9221_PHY_CSIR   				0x1B
#define LAN9221_PHY_CSIR_SQEOFF 		0x0800
#define LAN9221_PHY_CSIR_FEFIEN 		0x0020
#define LAN9221_PHY_CSIR_XPOL			0x0010

#define LAN9221_PHY_ISR  				0x1C
#define LAN9221_PHY_ISR_INT7			0x0080
#define LAN9221_PHY_ISR_INT6			0x0040
#define LAN9221_PHY_ISR_INT5			0x0020
#define LAN9221_PHY_ISR_INT4			0x0010
#define LAN9221_PHY_ISR_INT3			0x0008
#define LAN9221_PHY_ISR_INT2			0x0004
#define LAN9221_PHY_ISR_INT1			0x0002

#define LAN9221_PHY_IMR  				0x1E
#define LAN9221_PHY_IMR_INT7			0x0080
#define LAN9221_PHY_IMR_INT6			0x0040
#define LAN9221_PHY_IMR_INT5			0x0020
#define LAN9221_PHY_IMR_INT4			0x0010
#define LAN9221_PHY_IMR_INT3			0x0008
#define LAN9221_PHY_IMR_INT2			0x0004
#define LAN9221_PHY_IMR_INT1			0x0002

#define LAN9221_PHY_PHYSCSR   			0x1F
#define LAN9221_PHY_PHYSCSR_ANDONE		0x1000
#define LAN9221_PHY_PHYSCSR_4B5B_EN		0x0040
#define LAN9221_PHY_PHYSCSR_SPEED_MSK	0x001C
#define LAN9221_PHY_PHYSCSR_SPEED_10HD	0x0004
#define LAN9221_PHY_PHYSCSR_SPEED_10FD	0x0014
#define LAN9221_PHY_PHYSCSR_SPEED_100HD	0x0008
#define LAN9221_PHY_PHYSCSR_SPEED_100FD	0x0018
