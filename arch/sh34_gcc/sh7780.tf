$ 
$		�������ƥ������¸�ƥ�ץ졼�ȡ�SH7780�ѡ�
$ 

$ 
$  ͭ���ʳ�����ֹ桤����ߥϥ�ɥ��ֹ桤CPU�㳰�ϥ�ɥ��ֹ�
$ 
$INTNO_VALID = { 
					0x1C0;
					0x200,0x220,...,0x3c0;
$ // change hara 110421 begin
					0x400,0x420,...,0x4c0;
$ // end
                    0x480;0x4A0;0x4C0;
					0x560,0x580,...,0x600;
     				0x600;
                    0x640,0x660,...,0x6C0;
					0x700,0x720,...,0x7E0;
					0x900;0x980;
					0xA00,0xA20,...,0xB20;
					0xB80,0xBA0,...,0xC00;
					0xC80;
					0xD00,0xD20,...,0xE80;
					0xF00,0xF20,...,0xFE0 
				}$

$INHNO_VALID = INTNO_VALID$

$EXCNO_VALID = {
					0x1E0;0x0E0;0x040;0x0A0;0x180;0x1A0;
					0x800;0x820;0x0E0;0x100;0x040;0x060;
					0x0A0;0x0C0;0x120;0x080;0x160;0x1E0;
					0x1C0
				}$
$ $FILE "stdout"$
$ FOREACH tmp INTNO_VALID$
$    $tmp$$NL$
$ END$

$INTNO_RANGE = { 0,0x20,...,0xFE0;0x400 }$

$INHNO_RANGE = INTNO_RANGE$

$EXCNO_RANGE = { 0,0x20,...,0x820 }$


$ 
$  �ץ����å���¸�Υƥ�ץ졼�ȥե�����Υ��󥯥롼��
$ 
$INCLUDE"sh34_gcc/prc.tf"$