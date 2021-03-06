/*终于要写哈夫曼树啦
 *1.哈夫曼树创建
 *n个叶子节点的哈夫曼树总共会有2n-1个节点
 *一切按照数据结构书上写的：
 * select函数不好写，它要求出第一小 第二小的东西，然后求完以后还要去除掉，还是下标，下标,还在不断变化，，，，，，，
 * 1.找到最小的第一个 找到最小的第二个，然后
 * 哈夫曼树 小demo 仅仅测试一句话英文， 压缩前 压缩后 还原。
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct huff
{
	int parent,lc,rc;
	int wight;
	char s[100];
	int len;
	char code;
}huff,*huffman;
typedef struct wordnum
{
	int num;
	char c;
	int tag;
}wordnum,*word;
void select1(huff *h,int n,int *s1,int *s2);
void huff_code(huff *h,int n)//还真的得用回溯，，，
{
    int i,j,c,f;
    for(i=0;i<n;i++)
    {
	char t[n];
	int l=0;
	c=i;
	f=h[i].parent;
	while(f!=-1)
	{
		if(h[f].lc==c) 
			t[l]='0';
		else
			t[l]='1';
		c=f;f=h[f].parent;
		l++;
	}
        t[l]='\0';
	for(j=l-1;j>=0;j--)
	{
		h[i].s[h[i].len]=t[j];
		h[i].len++;
	}
	h[i].s[h[i].len]='\0';
    }
    
}


void huff_create(huff *h,int n,wordnum *w)//有n个带权节点需要构成一棵哈夫曼树
{
	int m;
	int x[100];
	int s1,s2;
	m=2*n-1;
	int i,j,t;
	for(i=0;i<m;i++)
	{
		h[i].parent=-1;
		h[i].lc=0;
		h[i].rc=0;
		h[i].len=0;
	}
	for(i=0;i<n;i++)
	{
		h[i].code=w[i].c;
		h[i].wight=w[i].num;
	}
	for(i=n;i<m;++i)
	{
		t=i-1;
		select1(h,t,&s1,&s2);
   	        h[s1].parent=i;
                h[s2].parent=i;

		h[i].wight=h[s1].wight+h[s2].wight;
		h[i].lc=s1;
		h[i].rc=s2;
	}
}

void sort(int *x,int n)
{
	int i,j;
	int a;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(x[j]>x[j+1])
			{
				a=x[j];
				x[j]=x[j+1];
				x[j+1]=a;
			}
		}
	}
}
void select1(huff *h,int n,int *s1,int *s2)//可以更简略 但是 总是写得很混乱 所以将就看看
{
	int x=100;
        int min=1000;
	int i;
	int a,b;
        for(i=0;i<=n;i++)
        {
		if(h[i].parent!=-1) continue;
		if(h[i].parent==-1)
		{
                if(h[i].wight<x)
                {
                        min=x;
                        x=h[i].wight;
                }
                else
                {
                        if(h[i].wight<min)
			{
			    	min=h[i].wight;
			}
                }
		}
        }
	for(i=0;i<=n;i++)
	{
		if(h[i].wight==x&&h[i].parent==-1)
		{
			a=i;
			break;
		}
	}
	for(i=0;i<=n;i++)
		if(h[i].wight==min&&h[i].parent==-1&&i!=a)
			b=i;
	
	*s1=a;
	*s2=b;
}
void press(char *origin,huff *h,char *new,int n)//origin为原来的未压缩的，new为压缩的
{
	int i,j;
	int start,end;
	start=0;
	for(i=0;i<strlen(origin);i++)
	{
		for(j=0;j<n;j++)
		{
			if(h[j].code==origin[i])
			{
				int len=strlen(h[j].s);
				memcpy(new+start,h[j].s,len);
				start=start+len;
			}
		}
	}
	new[start]='\0';

}
void unpress(char *new,huff *h,int n,char *o)//
{
	int i,j,f,p,t;
	char x[n];
	int c;
	int m=2*n-1;
	p=0;
	int length=0;
	c=m-1;
	for(i=0;i<strlen(new);i++)
	{
		  t=new[i];
		  if(t=='0')
		  {
		     c=h[c].lc;
		  }
		  else
		  {
			c=h[c].rc;
                  }
		  if(h[c].lc==0&&h[c].rc==0)
		  {
				  o[p++]=h[c].code;
				  c=m-1;
		  }
	}
	o[p]='\0';
	
}
void print(huff *h,int n)
{
	int i;
	for(i=0;i<n;i++)
	{
		printf("id=%d wight=%d c:%c code:%s\n",i,h[i].wight,h[i].code,h[i].s);
	}
}
int count(wordnum *w,char *s,char *old)
{
	int i,j,t;
	t=0;
	j=0;
	for(i=0;i<strlen(s);i++)
	{
		w[i].tag=0;
		w[i].num=1;
		old[i]=s[i];
	}
	old[i]='\0';
	for(i=0;i<strlen(s);i++)
	{
	        if(w[i].tag==0&&s[i]!='0')
		{
			t++;
		for(j=i+1;j<strlen(s);j++)
		{
			if(s[i]==s[j]&&w[i].tag==0)
			{
				w[i].c=s[i];
				w[i].num++;
				s[j]='0';
			}
		}
		w[i].tag=1;
		}
	}
	return t;
}
		
int main()
{
	char sentence[100];
	printf("测试数据:");
	scanf("%s",sentence);
	char old[100];
	char new[100];
	int length,l;
	length=strlen(sentence);
	wordnum w[length];
	l=count(w,sentence,old);
	huff h[l];
	huff_create(h,l,w);
	huff_code(h,l);
	press(old,h,new,l);
	printf("压缩编码:%s\n",new);
	unpress(new,h,l,old);
	printf("解压后原数据:%s\n",old);
}
