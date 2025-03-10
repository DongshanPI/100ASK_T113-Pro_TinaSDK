#include "asn1.h"
#include "asn1_mac.h"
#include "limits.h"
#include "err.h"

static void asn1_put_length(unsigned char **pp, int length);
static int asn1_get_length(const unsigned char **pp,int *inf,long *rl,int max);

/////////////ASN1_put_object/////////////////////////////////////////ok

void ASN1_put_object(unsigned char **pp, int constructed, int length, int tag,
	     int xclass)
{
	unsigned char *p= *pp;
	int i, ttag;

	i=(constructed)?V_ASN1_CONSTRUCTED:0;
	i|=(xclass&V_ASN1_PRIVATE);
	if (tag < 31)
		*(p++)=i|(tag&V_ASN1_PRIMITIVE_TAG);
	else
		{
		*(p++)=i|V_ASN1_PRIMITIVE_TAG;
		for(i = 0, ttag = tag; ttag > 0; i++) ttag >>=7;
		ttag = i;
		while(i-- > 0)
			{
			p[i] = tag & 0x7f;
			if(i != (ttag - 1)) p[i] |= 0x80;
			tag >>= 7;
			}
		p += ttag;
		}
	if (constructed == 2)
		*(p++)=0x80;
	else
		asn1_put_length(&p,length);
	*pp=p;
}

//////////////asn1_put_length///////////////////////////////////////ok

static void asn1_put_length(unsigned char **pp, int length)
	{
	unsigned char *p= *pp;
	int i,l;

	if (length <= 127)
		*(p++)=(unsigned char)length;
	else
		{
		l=length;
		for (i=0; l > 0; i++)
			l>>=8;
		*(p++)=i|0x80;
		l=i;
		while (i-- > 0)
			{
			p[i]=length&0xff;
			length>>=8;
			}
		p+=l;
		}
	*pp=p;
	}


////////////////ASN1_object_size//////////////////////////////////ok

int ASN1_object_size(int constructed, int length, int tag)
	{
	int ret;

	ret=length;
	ret++;
	if (tag >= 31)
		{
		while (tag > 0)
			{
			tag>>=7;
			ret++;
			}
		}
	if (constructed == 2)
		return ret + 3;
	ret++;
	if (length > 127)
		{
		while (length > 0)
			{
			length>>=8;
			ret++;
			}
		}
	return(ret);
	}

/////////ASN1_get_object//////////////////////////////////////////////ok
//	--YXY	���֤����ʲô�ṹ���ͣ�����sequence
int ASN1_get_object(const unsigned char **pp, long *plength, int *ptag,
	int *pclass, long omax)
	{
	int i,ret;
	long l;
	const unsigned char *p= *pp;
	int tag,xclass,inf;
	long max=omax;

	if (!max) goto err;
	ret=(*p&V_ASN1_CONSTRUCTED);//0x20
	xclass=(*p&V_ASN1_PRIVATE);//0xc0
	i= *p&V_ASN1_PRIMITIVE_TAG;//0x1f
	if (i == V_ASN1_PRIMITIVE_TAG)
		{		/* high-tag */
		p++;
		if (--max == 0) goto err;
		l=0;
		while (*p&0x80)
			{
			l<<=7L;
			l|= *(p++)&0x7f;
			if (--max == 0) goto err;
			if (l > (INT_MAX >> 7L)) goto err;
			}
		l<<=7L;
		l|= *(p++)&0x7f;
		tag=(int)l;
		if (--max == 0) goto err;
		}
	else
		{
		tag=i;//ȷ����ʲô����,��universal��ֵ
		p++;
		if (--max == 0) goto err;
		}
	*ptag=tag;
	*pclass=xclass;
	if (!asn1_get_length(&p,&inf,plength,(int)max)) goto err;//intenger

	if (*plength > (omax - (p - *pp)))//�ж�֤��ʣ��Ĵ�С
		{
		ASN1err(ASN1_F_ASN1_GET_OBJECT,ASN1_R_TOO_LONG);
		ret|=0x80;
		}
	*pp=p;//֤���ƫ�Ƶ�ַ
	return(ret|inf);
err:
	ASN1err(ASN1_F_ASN1_GET_OBJECT,ASN1_R_HEADER_TOO_LONG);
	return(0x80);
	}

/////////////////asn1_get_length//////////////////////////////////////////ok
//--YXY	��ȡ֤��Ľṹ�еĳ���
static int asn1_get_length(const unsigned char **pp, int *inf, long *rl, int max)
	{
	const unsigned char *p= *pp;
	unsigned long ret=0;
	unsigned int i;

	if (max-- < 1) return(0);
	if (*p == 0x80)
		{
		*inf=1;
		ret=0;
		p++;
		}
	else
		{
		*inf=0;
		i= *p&0x7f;//��ö��ٸ��ֽ�0x82����2���ֽ�
		if (*(p++) & 0x80)//��ó���0x04,0x51,��1105
			{
			if (i > sizeof(long))
				return 0;
			if (max-- == 0) return(0);
			while (i-- > 0)
				{
				ret<<=8L;
				ret|= *(p++);
				if (max-- == 0) return(0);
				}
			}
		else
			ret=i;
		}
	if (ret > LONG_MAX)
		return 0;
	*pp=p;//����֤���ƫ�Ƶ�ַ
	*rl=(long)ret;//���س���ֵ



	return(1);
	}

