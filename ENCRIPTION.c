#include<stdio.h>
#include<stdlib.h>
char message[1000];
char key;
int s,def;
void string_scan(char *str,int size);
int main()
{
	while(1)
	{
	string_scan(message,1000);
	scanf("%d",&key);
	
	printf("to incript enter 1 to decript enter 2\n");
	scanf("%d",&s);
	key=key%26;
	if(s==1)
	{
		for(char i=0;message[i];i++)
	    {
			if(message[i]>='a'&&message[i]<='z')
			{
				if((message[i]+key)>'z')
			    {
				def=(message[i]+key)-'z';
				message[i]='a'+def-1;
			    }
			   else
			   {
				message[i]=message[i]+key;
			   }
				
			}
			else if(message[i]>='A'&&message[i]<='Z')
			{
				if((message[i]+key)>'Z')
			    {
				def=(message[i]+key)-'Z';
				message[i]='A'+def-1;
			    }
			   else
			   {
				message[i]=message[i]+key;
			   }
				
			}
			
		    
	    }
        printf("%s\n",message);
	}
	else if(s==2)
	{
		for(char i=0;message[i];i++)
	    {
			if(message[i]>='a'&&message[i]<='z')
			{
				if((message[i]-key)<'a')
			    {
				def='a'-(message[i]-key);
				message[i]='z'-def+1;
			    }
			   else
			   {
				message[i]=message[i]-key;
			   }
				
			}
			else if(message[i]>='A'&&message[i]<='Z')
			{
				if((message[i]-key)<'A')
			    {
				def='A'-(message[i]-key);
				message[i]='Z'-def+1;
			    }
			   else
			   {
				message[i]=message[i]-key;
			   }
				
				
			}
			
		    
	    }
        printf("%s\n",message);
	}
	
	
	}
	
	
}
void string_scan(char *str,int size)
{
	int i=0;
	fflush(stdin);
	scanf("%c",&str[i]);
	while(str[i]!='\n'&&i<size-1)
	{
		i++;
		scanf("%c",&str[i]);
		
		
	}
	str[i]=0;
	
}