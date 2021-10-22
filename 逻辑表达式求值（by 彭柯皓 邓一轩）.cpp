/*
	Developed by Peng Kehao and Deng Yixuan
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>

const int N=5005;

char str[N],ch[N];
int lc[N],rc[N],op[N],pos[N],node_cnt;
int tag[N],num[N],val[N],num_cnt,book[N];

int solve(int l,int r){
	if(l>r){
		printf("You have input a wrong representation!\n");
		exit(0);
	}
	if(l==r){
		if(tag[str[l]]){
			printf("You have input a wrong representation!\n");
			exit(0);
		}
		if(str[l]<'a'||'z'<str[l]){
			printf("You have input a wrong representation!\n");
			exit(0);
		}
		int u=++node_cnt;
		pos[u]=num[str[l]];
		return u;
	}
	int cnt=0,pos=-1,flag=0;
	for(int i=l;i<=r;++i){
		if(str[i]=='(') ++cnt;
		if(str[i]==')') --cnt;
		if(cnt<0){
			printf("You have input a wrong representation!\n");
			exit(0);
		}
		if(cnt==0&&tag[str[i]]){
			flag=1;
			if(pos==-1||tag[str[i]]<tag[str[pos]]) pos=i;
		}
	}
	if(cnt>0){
		printf("You have input a wrong representation!\n");
		exit(0);
	}
	else if(flag==0) return solve(l+1,r-1);
	else if(pos==-1){
		printf("You have input a wrong representation!\n");
		exit(0);
	}
	else{
		int u=++node_cnt; op[u]=tag[str[pos]];
		if(op[u]==5){
			if(pos>l){
				printf("You have input a wrong representation!\n");
				exit(0);
			}
			rc[u]=solve(pos+1,r);
			return u;
		}
		else{
			lc[u]=solve(l,pos-1);
			rc[u]=solve(pos+1,r);
			return u;
		}
	}
}

int calc(int u){
	if(op[u]==0) return val[pos[u]];
	else if(op[u]==5) return val[calc(rc[u])]^1;
	else if(op[u]==4) return calc(lc[u])&calc(rc[u]);
	else if(op[u]==3) return calc(lc[u])|calc(rc[u]);
	else if(op[u]==2) return (calc(lc[u])==0)||(calc(rc[u])==1);
	else return calc(lc[u])^calc(rc[u])^1;
}

void out(int len){
	printf("+");
	for(int i=1;i<=num_cnt*3+len+4;++i) printf("%c",i==num_cnt*3+1?'+':'-');
	printf("+"); puts("");
}

int main(){
	printf("Please input a correct representation.\n");
	printf("The variables should be a single lower case letter.\n");
	printf("'<->' should be '['.\n");
	printf("'->' should be ']'.\n");
	printf("OR should be '|'.\n");
	printf("AND should be '&'.\n");
	printf("NOR should be '!'.\n");
	scanf("%s",str); int len=strlen(str);
	for(int i=0;i<len;++i) if(!book[str[i]]) book[str[i]]=1;
	for(int i='a';i<='z';++i) if(book[i]){
		num[i]=++num_cnt; ch[num_cnt]=i;
	}
	tag['[']=1; tag[']']=2; tag['|']=3; tag['&']=4; tag['!']=5;
	int root=solve(0,len-1); int s_lim=(1<<num_cnt);
	out(len); printf("| ");
	for(int i=1;i<=num_cnt;++i) printf("%c %c",ch[i],i==num_cnt?'|':' ');
	printf(" "); printf("%s  |\n",str); out(len);
	for(int s=0;s<s_lim;++s){
		printf("| ");
		for(int i=1;i<=num_cnt;++i) val[num_cnt-i+1]=((s>>(i-1))&1);
		for(int i=1;i<=num_cnt;++i) printf("%d %c",val[i],i==num_cnt?'|':' ');
		for(int i=1;i<=(len+1)/2;i++) printf(" ");
		printf("%d",calc(root));
		for(int i=1;i<=len+2-(len+1)/2;i++) printf(" ");
		printf("|\n");
	}
	out(len); 
	return 0;
}
