typedef struct {
	uint8_t tphdrlen; //�g�����X�|�[�g�w�̃w�b�_��
	uint8_t iphdrlen; //IP�w�̃w�b�_��
	uint16_t ipmss; //ip�w���l������MSS
	//uint8_t ipaddlen; //IP�A�h���X��
	uint8_t ifhdrlen; //�f�[�^�����N�w�̃w�b�_��
	uint8_t ifmtu; //�f�[�^�����N�w���l������MTU
	uint8_t ifalign; //�f�[�^�����N�w�̃A���C�����g�␳�l
	uint8_t protocolflag; //protocolflag
	uint16_t tphdrlenall; //�g�����X�|�[�g�w�̃w�b�_���i���I�ω����܂ށj
	uint16_t iphdrlenall; //IP�w�̃w�b�_���i���I�ω����܂ށj
}T_OFF_BUF;

typedef struct {
    uint16_t len;
    uint8_t idix;
    uint8_t flags;

	T_OFF_BUF off;

	uint8_t buf[4];
}T_NET_BUF;
