typedef struct {
	uint8_t tphdrlen; //トランスポート層のヘッダ長
	uint8_t iphdrlen; //IP層のヘッダ長
	uint16_t ipmss; //ip層を考慮したMSS
	//uint8_t ipaddlen; //IPアドレス長
	uint8_t ifhdrlen; //データリンク層のヘッダ長
	uint8_t ifmtu; //データリンク層を考慮したMTU
	uint8_t ifalign; //データリンク層のアライメント補正値
	uint8_t protocolflag; //protocolflag
	uint16_t tphdrlenall; //トランスポート層のヘッダ長（動的変化分含む）
	uint16_t iphdrlenall; //IP層のヘッダ長（動的変化分含む）
}T_OFF_BUF;

typedef struct {
    uint16_t len;
    uint8_t idix;
    uint8_t flags;

	T_OFF_BUF off;

	uint8_t buf[4];
}T_NET_BUF;
