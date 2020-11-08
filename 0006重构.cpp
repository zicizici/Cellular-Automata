#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define gl 1
#define nx 640
#define ny 360
using namespace std;

unsigned char coo[]={66,77,56,136,3,0,0,0,0,0,54,4,0,0,40,0,0,0,128,2,0,0,104,1,0,0,1,0,8,0,0,0,0,0,2,132,3,0,195,14,0,0,195,14,0,0,0,0,0,0,0,0,0,0};
int spee,cp=0,fi,gi,fj,gj,ct[ny][nx],tn,p,c=0,temp,tc=1,ord[9]={-2,-1,-1,1,-1,-1,1,1};
unsigned char m[ny][nx];
string str="0000000";

void itos () {
	temp=c,tc=6;
	while (temp!=0) str[tc--]='0'+(temp%10),temp/=10;
}

void pri () {
	itos();
	unsigned char tsb[4]={0,0,0,0};
	fstream file ((str+".bmp").c_str(),ios::out|ios::binary);
	file.write(reinterpret_cast<char*>(coo),sizeof(coo));
	for (int i=0;i<=255;i++) {
		if (i<158) tsb[0]=i*195/158,tsb[1]=i,tsb[2]=i*255/158;
		if (i>=158) tsb[0]=195+(i-158)*60/97,tsb[1]=i,tsb[2]=255;
		file.write(reinterpret_cast<char*>(tsb),sizeof(tsb));
	}
	file.write(reinterpret_cast<char*>(m),sizeof(m));
	file.close ();
}
	
int fz (int ya,int xa,int num) {
	if (num>255) num=255;
	if (num<0) num=0;
	if (num==m[ya][xa]) return 0;
	for (int i=ya;i<ya+gl;i++) for (int j=xa;j<xa+gl;j++) m[i][j]=num;
}

int main () {
	srand(1919810);
	for (int i=0;i<ny;i+=gl) for (int j=0;j<nx;j+=gl) fz(i,j,rand()%256);
	pri();
	c++;
	cp++;
	cin>>spee;
	while (1) {
		for (int i=0;i<ny;i+=gl) for (int j=0;j<nx;j+=gl) {
			fi=i+gl,fj=j+gl,gi=i-gl,gj=j-gl,ct[i][j]=0;
			if (fi==360) fi=0;
			else if (gi==-gl) gi=360-gl;
			if (fj==640) fj=0;
			else if (gj==-gl) gj=640-gl;
			if (m[fi][j]>=m[i][j]) ct[i][j]++;
			if (m[gi][j]>=m[i][j]) ct[i][j]++;
			if (m[i][fj]>=m[i][j]) ct[i][j]++;
			if (m[i][gj]>=m[i][j]) ct[i][j]++;
			if (m[fi][fj]>=m[i][j]) ct[i][j]++;
			if (m[fi][gj]>=m[i][j]) ct[i][j]++;
			if (m[gi][fj]>=m[i][j]) ct[i][j]++;
			if (m[gi][gj]>=m[i][j]) ct[i][j]++;
		}
		for (int i=0;i<ny;i+=gl) for (int j=0;j<nx;j+=gl) fz(i,j,m[i][j]+ord[ct[i][j]]*4);
		pri();
		c++;
		cp++;
		if (cp==spee) {
			//pri();
			cout<<"done"<<endl;
			cp=0;
			cin>>spee;
		}
	}
	return 0;
}
