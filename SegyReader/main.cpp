#include <iostream>
#include "INSMSegyReader.h"
#define PI 3.1415926535

//int main() {
//	printf("float size %d\n",sizeof(float));
//	printf("char size %d\n", sizeof(char));
//	printf("short size %d\n", sizeof(short));
//	printf("long size %d\n", sizeof(long));
//	printf("unsigned short size %d\n", sizeof(unsigned short));
//	printf("int size %d\n", sizeof(int));
//	/*union SI si;
//	strcpy(si.s,"a");
//	printf("%d,%s", si.a, si.s);
//	return 0;*/
//}

//��С����
float deal(float x[5], float y[5])//���ÿ���Ĭ������ⷽ��
{
	int select = 2;
	int i;
	float k;
	float a0, a1, a2, temp, temp0, temp1, temp2;
	float sy = 0, sx = 0, sxx = 0, syy = 0, sxy = 0, sxxy = 0, sxxx = 0, sxxxx = 0;//������ر���
	for (i = 0; i<5; i++)
	{
		sx += x[i];//����xi�ĺ�
		sy += y[i];//����yi�ĺ�
		sxx += x[i] * x[i];//����xi��ƽ���ĺ�
		sxxx += powf(x[i], 3);//����xi�������ĺ�
		sxxxx += powf(x[i], 4);//����xi��4�η��ĺ�
		sxy += x[i] * y[i];//����xi��yi�ĵĺ�
		sxxy += x[i] * x[i] * y[i];//����xiƽ����yi�ĺ�
	}
	temp = 5 * sxx - sx*sx;//���̵�ϵ������ʽ
	temp0 = sy*sxx - sx*sxy;
	temp1 = 5 * sxy - sy*sx;
	a0 = temp0 / temp;
	a1 = temp1 / temp;
	temp = 5 * (sxx*sxxxx - sxxx*sxxx) - sx*(sx*sxxxx - sxx*sxxx)//���̵�ϵ������ʽ
		+ sxx*(sx*sxxx - sxx*sxx);
	temp0 = sy*(sxx*sxxxx - sxxx*sxxx) - sxy*(sx*sxxxx - sxx*sxxx)
		+ sxxy*(sx*sxxx - sxx*sxx);
	temp1 = 5 * (sxy*sxxxx - sxxy*sxxx) - sx*(sy*sxxxx - sxx*sxxy)
		+ sxx*(sy*sxxx - sxy*sxx);
	temp2 = 5 * (sxx*sxxy - sxy*sxxx) - sx*(sx*sxxy - sy*sxxx)
		+ sxx*(sx*sxy - sy*sxx);
	a0 = temp0 / temp;
	a1 = temp1 / temp;
	a2 = temp2 / temp;
	if (select == 2)
	{
		//printf("����С���˷���ϵõ��Ķ��ν��Ʒ���Ϊ:\n");
		//printf("f(x)=%3.3fx2+%3.3fx+%3.3f\n", a2, a1, a0);
		k = 2 * a2*x[3] + a1;
		//printf("�õ��б��Ϊ%3.3f\n", k);
	}
	return k;
}

int main() {
	CINSMSegyReader st("C:\\Users\\skx\\Desktop\\new\\zdm_imp.sgy", 6);

	st.ReadSegyFile();
	std::cout << st.getTraceCount() << "," << st.getiLineCount() << "," << st.getxLineCount() << "," << st.getiLineStart() << "," << st.getxLineStart();
	auto data = st.getData()[0];
	std::cout << std::endl;
	for (auto v : data) {
		std::cout << v.a << " ";
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}
/*
int main_2()
{
   std::vector<float> A;
   std::vector<float> A_; //����ԭʼ����
   std::vector<float> Tn_len;
   std::vector<float> BW;
   std::vector<float> AZCF;
   long Tn;
   int i,j;
   int k;
   char ch;
   float dat;
   union SI si;//��������
   union SP sp;//���������
   union Data data;//��������
   union Line line;//�ߺ�
   union Trace trace;//����
   union X_cor x_cor;//X����
   union Y_cor y_cor;//Y����
 
   FILE* fp, *fp1,*fp2;
   fp = fopen_s("C:\\Users\\skx\\Desktop\\new\\zdm_imp.sgy","rb");//��SEGY�����ļ�
   //fp = fopen_s("E:\\test.sgy","rb");//��SEGY�����ļ�
   if(!fp)
   {
       printf("can't open file!");
       exit(1);
   }

   fseek(fp,3220L,0);
   fread(si.s,2,1,fp);//��ȡ�����㣬�������big endian ת���� little endian
   ch=si.s[0];
   si.s[0]=si.s[1];
   si.s[1]=ch;
   fseek(fp,3216L,0);//��ȡ�����ʣ��������big endian ת���� little endian
   fread(sp.s,2,1,fp);
   ch=sp.s[0];
   sp.s[0]=sp.s[1];
   sp.s[1]=ch;
   j=0;
   rewind(fp);
   while(!feof(fp))//����ļ���С,��������1
   {
      fread(&k,1,1,fp);
	  j+=1;
   }
   j=j-1;
   
   Tn = (short)((j-3600)/(float)(si.a*4+240));//������� 
   if(!(fp1=fopen_s("C:\\Users\\skx\\Desktop\\new\\test.txt","w+")))//�½��ı��ļ��洢����
   { 
	   printf("can't open text file!");
       exit(1);  
   }
   if (!(fp2 = fopen_s("C:\\Users\\skx\\Desktop\\new\\test1.txt", "w+")))//�½��ı��ļ��洢����
   {
	   printf("can't open text file!");
	   exit(1);
   }
   fprintf(fp1,"si = %u, sp =%u, Tn =%d, j=%d\n",si.a, sp.i, Tn, j);

   for(j=0;j<Tn;j++)
   {
//	fprintf(fp1,"�¡¡¡¡¡¡¡¡¡¡¡¡¡�The %d trace:����������������������������\n ", j+1);
    //printf("The %f percent trace  \n ",100*(float)(j+1)/(float)Tn);
	for(i=0;i<si.a;i++)
    {
      
      fseek(fp,3600L+j*240L+j*si.a*4L+8L,0);//��ȡ�ߺţ��������big endian ת���� little endian
	  fread(line.s,4,1,fp);
	  ch=line.s[0];
	  line.s[0]=line.s[3];
	  line.s[3]=ch;
	  ch=line.s[1];
	  line.s[1]=line.s[2];
	  line.s[2]=ch;

	  fseek(fp,3600L+j*240L+j*si.a*4L+20L,0);//��ȡ���ţ��������big endian ת���� little endian
	  fread(trace.s,4,1,fp);
	  ch=trace.s[0];
	  trace.s[0]=trace.s[3];
	  trace.s[3]=ch;
	  ch=trace.s[1];
	  trace.s[1]=trace.s[2];
	  trace.s[2]=ch;

	  fseek(fp,3600L+j*240L+j*si.a*4L+72L,0);//��ȡX���꣬�������big endian ת���� little endian
	  fread(x_cor.s,4,1,fp);
	  ch=x_cor.s[0];
	  x_cor.s[0]=x_cor.s[3];
	  x_cor.s[3]=ch;
	  ch=x_cor.s[1];
	  x_cor.s[1]=x_cor.s[2];
	  x_cor.s[2]=ch;

	  fseek(fp,3600L+j*240L+j*si.a*4L+76L,0);//��ȡY���꣬�������big endian ת���� little endian
	  fread(y_cor.s,4,1,fp);
	  ch=y_cor.s[0];
	  y_cor.s[0]=y_cor.s[3];
	  y_cor.s[3]=ch;
	  ch=y_cor.s[1];
	  y_cor.s[1]=y_cor.s[2];
	  y_cor.s[2]=ch;

	  fseek(fp,3600L+(j+1)*240L+j*si.a*4L+i*4L,0);
	  fread(data.dat,4,1,fp);//��ȡ�������ݣ��������big endian ת���� little endian
	  ch=data.dat[0];
	  data.dat[0]=data.dat[3];
	  data.dat[3]=ch;
	  ch=data.dat[1];
	  data.dat[1]=data.dat[2];
	  data.dat[2]=ch;

	  

	  //���㷴��ǿ��
	  float h = data.a / (PI*(i + 1));
	  A.push_back(sqrt(data.a*data.a + h*h));
	  A_.push_back(data.a);
	 // fprintf(fp1,"	%d     %d     %d     %u      %u     %d \n ",j+1,line.a,trace.a,x_cor.a,y_cor.a,i*sp.i/2000+1);
	  //fprintf(fp1,"	 %.3f\n ",data.a);
	  fprintf(fp1,"	%d     %d     %d     %u      %u     %d     %.3f\n ",j+1,line.a,trace.a,x_cor.a,y_cor.a,i+1,data.a);
//	  fprintf(fp1," %d    %d      %f\n ",line.a,-i*sp.i/2000+1,data.a);

	  //���˳���ܵĵ��š��ߺš����š�X���ꡢY���ꡢ������š���������
	  if(fabs(data.a)>1e6)
		  printf("error");
    }
   }
   //--------���--------
   //--------���㻡��-------
   for (j = 0; j < Tn; j++)
   {
	   float T_len = 0;
	   float temp = si.a*sp.i;
	   for (i = 0; i < si.a; i++) {
		   if (((j*si.a) + i + 1) >= (((Tn-1)*si.a) + si.a)) break;
		   T_len += sqrt(powf((A[(j*si.a)+i+1]-A[(j*si.a)+i]),2) + pow(sp.i,2));
	   }
	   T_len /= temp;
	   Tn_len.push_back(T_len);
   }
   //-----�������-----
   bool isH = false,isT = false;
   for (i = 0; i < Tn*si.a; i++) {
	   if (i < 2) {
		   i += 2;
		   isH = true;
	   }
	   else if (i > Tn*si.a - 3) {
		   i -= 2;
		   isT = true;
	   }
	   //���õ�ǰֵ��Ϊ�м�������ǰ��5��������õ�������ǰ������������б�ʰ�������ļ���
	   float aa[5] = {A[i-2],A[i - 1] ,A[i] ,A[i + 1] ,A[i + 2] };
	   float bb[5] = {i-2,i-1,i,i+1,i+2};
	   
	   if (isH) {
		   i -= 2;
		   isH = 0;
	   }
	   else if (isT) {
		   i += 2;
		   isT = 0;
	   }

	   BW.push_back((deal(bb,aa)) / (2 * PI*A[i]));
   }
	   

	  
   //-----����ֵƽ��Ƶ��----ʹ��ԭʼ�������ݼ���
   for (j = 0; j < Tn; j++) {
	   int n=0, t1=-1, t2=-1;
	   int oldtag=0, newtag=0; //ǰ������ֵ��״̬��¼ -1 ��;1 �� ;0 ��

	   if (A_[j*si.a] < 0) oldtag = newtag = -1;
	   else if(A_[j*si.a] > 0) oldtag = newtag = 1;
	   else {
		   oldtag = newtag = 0; t1 = 0; n++;
	   }

	   for (i = 1; i < si.a; i++) {
			if (A_[(j*si.a) + i] < 0) newtag = -1;
			else if (A_[(j*si.a) + i] > 0) newtag = 1;
			else {
				newtag = 0;
				t2 = i;// *sp.i;
				n++;
				if (t1 == -1)t1 = i;// *sp.i;
				oldtag = newtag;
				continue;
			}
			if (newtag != oldtag && oldtag != 0 ) {
				if (t1 == -1)t1 = i;// *sp.i;
				t2 = i;// *sp.i;
				n++;
			}
			oldtag = newtag;
	   }
	   AZCF.push_back((n-1)/(2*(t2-t1)));
   }
   fprintf(fp2,"����     ����     �����     ����\n");
   for (j = 0; j < Tn; j++) {
	   for (i = 0; i < si.a; i++) {
		   fprintf(fp2, "%-8d %-8.3f %-8.3f %-8.5f\n", j + 1, Tn_len[j], AZCF[j], BW[(j*si.a) + i]);
	   }

   }
   fclose(fp1);
   fclose(fp);
   return 0;

}
*/