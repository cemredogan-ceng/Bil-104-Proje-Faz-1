#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

int oyuna_basla;
int kuyruk_n=0;
int duvar_en=50, duvar_boy=20;
int yilan_x,yilan_y,yem_x,yem_y; // yýlanýn ve yemin x ve y eksenlerindeki koordinatlarý
char kullaniciAdi[15];
char puanGoruntu;
struct oyun {
	int kuyruk_x[100];
	int kuyruk_y[100];
	int toplamPuan;
} ;
struct oyun deger;

enum HAREKET{SOL=1,SAG,ASAGI,YUKARI,DUR}yon;

void oyna(){
	deger.toplamPuan=0;
	oyuna_basla=1;
	yilan_x=duvar_en/2;
	yilan_y=duvar_boy/2;
	yem_x=1+rand()%(duvar_en-1);
	yem_y=1+rand()%(duvar_boy-1);
	}
	
	void grafik(){
		system("cls");
		
		int i=0,j=0;
		
		printf("\t....................YILAN OYUNUNA HOSGELDINIZ....................\n");
		printf("\n");
		printf("\t Oyun Yonergesi:\n");
		printf("\t\t 1)Yilani yon tuslari ile hareket ettiriniz.\n");
		printf("\t\t 2)Duvarlara ve kuyruga carparsaniz oyun sonlanir.\n");
		printf("\n");
		
		
		for(i=0;i<duvar_boy;i++){
			printf("\t");
			
			for(j=0;j<duvar_en;j++){
				
				
				if(i==0 || i==duvar_boy-1 ||j==0 || j==duvar_en-1)
				printf("|");
				
				else if(i==yilan_y && j==yilan_x)
				printf("*");
				else if(i==yem_y && j==yem_x)
				printf("x");
				
				else{
					int k,boslukBas=0;
					
					for(k=0;k<kuyruk_n;k++){
						if(deger.kuyruk_x[k]==j && deger.kuyruk_y[k]==i){
							printf("*");
							boslukBas=1;
						}
					}
					if(!boslukBas)
					printf(" ");
				}
				
				}
				printf("\n");
				
		}
		
		
	}
	
	void kontrol(){
		if(kbhit()){
			switch(getch()){
				
				case 75:
					yon=SOL;
					break;
					
				case 77:
				    yon=SAG;
					break;
					
				case 72:
					yon=YUKARI;
					break;
				
				case 80:
					yon=ASAGI;
					break;
						
			}
		}
	}
	void hareket(){
		
		int i;
		
		for(i=kuyruk_n-1;i>0;i--){
			deger.kuyruk_x[i]=deger.kuyruk_x[i-1];
			deger.kuyruk_y[i]=deger.kuyruk_y[i-1];
		}
		deger.kuyruk_x[0]=yilan_x;
		deger.kuyruk_y[0]=yilan_y;
		
		switch(yon){
			case SOL:
				yilan_x--;
				break;
				
			case SAG:
				yilan_x++;
				break;
				
			case ASAGI:
				yilan_y++;
				break;
				
			case YUKARI:
				yilan_y--;
				break;
				
		}
	    if (yilan_x==0 || yilan_x==duvar_en || yilan_y==0 || yilan_y==duvar_boy){
			oyuna_basla=0;
		}
		if(yilan_x==yem_x && yilan_y==yem_y){
			deger.toplamPuan+=10;
			yem_x=2+rand()%(duvar_en-4);
			yem_y=2+rand()%(duvar_boy-4);
			kuyruk_n++;
		}
		for(i=0;i<kuyruk_n;i++){
			if(yilan_x==deger.kuyruk_x[i] && yilan_y==deger.kuyruk_y[i])
			oyuna_basla=0;	
		}
	}
void playerBilgiYaz(){
	FILE *yilanoyunu;
	yilanoyunu=fopen("bilgiler.txt","w");
	printf("\t Kullanici adinizi giriniz.\n");
	printf("\t Kullani Adi:");
	scanf("%s", kullaniciAdi);
	fprintf(yilanoyunu,"%s %d", kullaniciAdi, deger.toplamPuan);
	fclose(yilanoyunu);
}
void playerBilgiOku(){
	FILE *yilanoyunu;
	yilanoyunu=fopen("bilgiler.txt","r");
	fscanf(yilanoyunu, "%s", kullaniciAdi );
	printf("\t %s'in Puani:%d\n", kullaniciAdi, deger.toplamPuan);
	fclose(yilanoyunu);
}
	
	int main(){
		srand(clock());
		oyna();
		
		while(oyuna_basla){
			grafik();
			kontrol();
			hareket();
			Sleep(50);
			
		}
		do{
			printf("\n\n");
			printf("\t Puaninizi goruntulemek icin p tusuna basiniz.\n");
			puanGoruntu=getchar();
			if(puanGoruntu=='p')
			playerBilgiYaz();
			playerBilgiOku();
		}
		while(puanGoruntu!='p');
	
	}
