#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "article.h"




//���ҽ��i�ĸ����,ͨ���ݹ�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n);
//���ݳ�ʼȨ�ع�����������
void huffmanTree(int w[],int huffman[][4],int n);
//Ѱ��Ȩ����С�������ڵ�
void findMin(int ii[],int huffman[][4],int n);
//��ÿ��Ҷ�ڵ���й���������
void HuffmanCode(int i,int huffman[][4],int n);
//��������char������
void inplace_swap(char *x,char *y);



int main(int argc, char *argv[]) 
{
	
	int length = strlen(article_string);
	printf("Article length is: %dByte\n", length);

	//��������ַ������м�¼�����ַ����ܸ���count�Լ������ַ��ĳ��ִ���arr_small[]����ͳ��
    char str[100];
    printf("Please Enter the string\n");
    scanf("%s", str);
    int arr_big[27] = {0};  //�����ַ��ĳ��ִ���
    int count = 0;  //�ַ����ܸ���
    for(int i = 0; i < strlen(str); i++)    //���������ַ����е������ַ�
    {
        for(int j = 0; j < 27; j++) //����26����д��ĸ
        {
            if(str[i] == (char)(0x41 + j))//0x��ʮ������
            {
                arr_big[j] += 1;
                if(arr_big[j] == 1)
                {
                                                                                       count++;
                    /*����������*/		//��¼һ�������˼�����ĸ
                }
                break;
            }
        }
    }
    printf("the letter count is %d\n",count);   //��ӡ�����ַ��������˼�����ĸ

    //ͨ��arr_big�������ַ����г��ֵ���ĸ��������ͳ�ƣ���������arr_small��
    int count2 = 0;     //�ַ����г��ֵ��ַ��ܸ���
    int arr_small[count] ;  //ͳ�������ַ�������ĸ�ĳ��ִ���
    for(int i = 0; i < 27; i++)
    {
        if(arr_big[i]>0/*����������*/)
        {
            
            arr_small[count2++] = arr_big[i];	/*����ע�ͣ�˵�����ã�
            ʵ����arr-small����������ĸ��˳���¼�ַ��������˵���ĸ��Ȩֵ*/
            //count2++��ִ���˱��ʽ���ټ�1
        }
    }

    //����int�Ͷ�ά���飬���鳤��[*]Ϊ���������Ľڵ����
    //c[*][0]��ŵ��Ǹýڵ��[���ڵ��λ��]��c[*][1]Ϊ�ýڵ��[�������ڵ��λ��]
    //c[*][2]��Ÿýڵ��[�������ڵ��λ��]��c[*][3]Ϊ�ýڵ��Ȩֵ
    int huffman[2 * count - 1][4];  //ǰn��ΪҶ��㣬��n-1��Ϊ�м���

    //���ݳ�ʼȨ������arr_small���ַ���������huffman��
    huffmanTree(arr_small,huffman,count);//�Ѿ������˹�������

    //����Huffman���������ܳ���WPL
    int sum = 0;
    for(int i = 0;i < count;i++)
    {
        int length = 0;
        if(huffman[i][1] == -1 && huffman[i][2] == -1)  /*ע�� �ж�i��Ҷ�ڵ㣬ִ���������*/
        {
            length = findParent(i,huffman,count);   //�õ�����Ҷ���Ĵ�Ȩ·������
            /*����������*/ 
            sum=sum+length*huffman[i][3];
            
             	//����Ҷ����Ȩ·�������ۼӵõ��ܳ���WPL
        }
    }
    printf("the tree's WPL  is  %d\n",sum);

    //Huffman����
    for(int i = 0;i < count;i++)
    {
        HuffmanCode(i,huffman,count);
    }

    return 0;
}

//�Ӻ�������������������
void huffmanTree(int w[],int huffman[][4],int n)//n=court w������arrsmall
{
    //����ʼ��
    for(int i = 0; i < 2 * n - 1; i++)
    {
        huffman[i][0] = -1;
        huffman[i][1] = -1;
        huffman[i][2] = -1;
        huffman[i][3] = -1;
    }
    /*����ע�ͣ�˵�����ã�
      ����֮��������е�Ԫ�ؽ��и�ֵ*/
    for(int i = 0; i < n; i++)
    {
        huffman[i][3] = w[i];
    }
    //ÿ�γ������Ȩ����С�Ľ����кϲ���ֱ�����ղ��������
    for(int i = n; i < 2 * n - 1; i++)                   //ִ����n-1��
    {
        int i1,i2;  //Ȩ����С���������
        int ii[2]; 
        //�ҳ�����Ȩ����С�Ľ��
        findMin(ii,huffman,n);
        i1=ii[0];
        i2=ii[1];
        //�ϲ�i1��i2���,���½����Ϣ�������ɽ��������ӽ�㣬�ӽڵ��Ӧ�ĸ���㣬�����ɽ���Ȩ�أ�
        
        /*����������*/
        huffman[i1][0]=i+1;
        huffman[i2][0]=i+1;
        huffman[i+1][1]=i1;
        huffman[i+1][2]=i2;
        huffman[i+1][3]=huffman[i1][3]+huffman[i2][3];
    }
}

//�Ӻ��������ҳ�����Ȩ����С�Ľ��
void findMin(int ii[],int huffman[][4],int n)
{
    //�ҳ���һ��Ȩ����С�Ľ��
    int min = 9999999;
    for(int i = 0; i < 2 * n - 1; i++)
    {
        if(huffman[i][3] == -1 && huffman[i][0] == -1)  /*��˵�����ã��ж�һ�ڵ㣨��û��Ȩֵ��û�и��ڵ㣩Ϊδ���ɵĽڵ�   //  &&���� ||�ǻ�   //   */
        {
            break;
        }
        if(huffman[i][3] < min && huffman[i][0] == -1)  /*(˵�����ã��ҵ���Сֵ*/
        {
            min = huffman[i][3];
            ii[0] = i;
        }
    }

    //�ҳ��ڶ���Ȩ����С�Ľ�㣨ģ���ϲ������б�д��
    
    /*����������*/
    int min2 = 9999999;
    for(int i = 0; i < 2 * n - 1; i++)
    {   if(huffman[i][3] == -1 && huffman[i][0] == -1)  
        {
            break;
        }
        
        if(huffman[i][3] < min2 && huffman[i][0] == -1 && min2!=min )
        {
            min2 = huffman[i][3];
            ii[1] = i;
        }


    }


//�Ӻ����������ҽ��i�ĸ����,�õ���㵽���ĳ���
int findParent(int i,int huffman[][4],int n)
{
    int length = 0;
    if(huffman[i][0] == -1)     /*ע�� �ж�Ϊ���ڵ㣬��ʱ���ɵõ���㵽���ĳ��ȣ�����*/
    {
        return 0;
    }
    length += (findParent(huffman[i][0],huffman,n) + 1);    //ͨ���ݹ�õ���㵽����·������  //�˱��ʽ����ɼ��㣬����к����ĵ���
    return length;
}

//�Ӻ���������ÿ��Ҷ�ڵ���й��������벢���д�ӡ
void HuffmanCode(int i,int huffman[][4],int n)//�ڼ���Ҷ�ڵ㣬 ��count
{
    char code[30];  //char����������
    int current=i;  //���嵱ǰ���ʵĽ��
    int father = huffman[i][0]; //���嵱ǰ���ĸ��ڵ�
    int start=0;    //ÿ�α����λ�ã���ʼΪ���뵹��λ��
    int first,last;     //char�����ͷ����β��

    while(father != -1)//(!=�ǲ��Բ�����Ϊ��)
    {
        for(int i = 0; i < 2 * n - 1; i++)
        {
        if(huffman[father][1]=-1)     
        {
        return;
        }   
            
        if(huffman[father][1]=i)		//�жϵ�ǰ���ĸ�����������Ƿ�Ϊ��ǰ���
           code[start++]=0;	//�ӽ���Ǹ�����������������Ϊ0
        if(huffman[father][2]=i)
           code[start++]=1;  		//�ӽ���Ǹ�����������������Ϊ1
        
        i=father;
        father = huffman[i][0];
        		//����˷Դ�����µ�ǰ���
        		//ͬ����ǰ�����º󣩣����µ�ǰ���ĸ��׽��
        		//���±���λ��
        }
    }
    code[start]='\0';   //���������

    //��char�����е�Ԫ��ͷβ���˽��жԵ�
    for(first = 0, last = start-1; first < last; first++,last--)
    {
        //�Ե������ڲ�Ԫ��
        inplace_swap(&code[first], &code[last]);	/*�ú������Լ���д*/
    }

    printf("%c Huffman code:  %s\n",'A'+i,code);    //��ӡ�ַ���huffman����
}

//�Ӻ���������������char�����ݣ�ʹ���˲������㣩�����Լ������ÿɶ��ԽϺõķ�������ʵ�ָĺ���
void inplace_swap(char *x,char *y)
{
	char tem;
	tem=*y;
    *y = *x ;
    *x = tem;
	
}





