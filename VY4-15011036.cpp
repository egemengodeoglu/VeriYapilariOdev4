#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void yazdir(int size,char**maze){								//Yazdýr fonksiyonu matrisi formatlý þekilde ekrana yazdýrýyor
	static int sayac=0;											//Sayac kaçýncý adýmda olduðunu gösteriyor Static tanýmlandýðý için deðer fonksiyonun içinde deðiþiyor
		printf("%d. adim\n",sayac);								//Adým ekrana yazdýrýlýyor
	int i,j;
		for(i=0;i<size;i++){									//Matirisin satýr indisi
		for(j=0;j<size;j++){									//Matrisin sutun indisi
			if(i%2==0){											//Matrisin çift satýrlarýnda - yada + yazýyor
				if(j%2==0)										//Eðer sutun çiftse + koyuyor
				printf("+ ");
				else if(maze[i][j]=='0')						//Eðer sutun tekse ve 0 ise - koyuyor
				printf("- ");
				else											//Eðer sutun tekse ve 1 ise yolu boþ býrakýyor
				printf("  ");	
			}else{												//Eðer satýr tek ise
				if(maze[i][j]=='0')								//Eðer 0 ise yolu kapatýyor | 
				printf("| ");
				else if(i==1 && j==1)							//Eðer ilk satýr ve sütunsa * koyuyor			
				printf("* ");
				else if(maze[i][j]=='V' && j==(size-2))			//Eðer son satýrdaysa sona ulasmýþtýr ve X koyuyor
				printf("X ");
				else if(maze[i][j]=='V')						//Eðer nokta visited edilmiþse I koyuyor
				printf("I ");
				else											//Eðer daha önce visited edilmemiþse yolu boþ býrakýyor
				printf("  ");
			}
		}
		printf("\n");
	}
	sayac++;													//Adým sayýsý için sayac 1 arttýrýlýyor
	printf("\n");
}
void DFS(int size,int i,int j,char**maze){						//Depth First Search yapan fonksiyor

	yazdir(size,maze);											//Her adýmýn baþýnda ekrana durumu yazdýrýyor
	maze[i][j]='V';												//Bulunduðu düðümü ziyaret edilmiþ(Visited) yapýyor
	static int exit=0;											//Sona ulaþýldýðýnda çýkmak için exit tanýmlanýyor
	if(j==size-2){
		exit=1;
	}	
	if(maze[i+1][j]=='1' && maze[i+2][j]=='B' && exit==0)		//Eðer aþaðý tarafa yol açýksa ve ziyaret edilmemiþse aþaðý gidiyor
		DFS(size,i+2,j,maze);	
	if(maze[i][j+1]=='1' && maze[i][j+2]=='B' && exit==0)		//Eðer sað tarafa yol açýksa ve ziyaret edilmemiþse saða gidiyor
		DFS(size,i,j+2,maze);
	if(maze[i-1][j]=='1' && maze[i-2][j]=='B' && exit==0)		//Eðer yukarý tarafa yol açýksa ve ziyaret edilmemiþse yukarý gidiyor
		DFS(size,i-2,j,maze);
	if(maze[i][j-1]=='1' && maze[i][j-2]=='B' && exit==0)		//Eðer sol tarafa yol açýksa ve ziyaret edilmemiþse sola gidiyor
		DFS(size,i,j-2,maze);
	
}

int main(){			
	int i,j,size;
	char** maze,*line,*ptr;									
	
	printf("Matrisin boyutunu giriniz=");						//Matrisin boyutu kullanýcýdan alýnýyor
	scanf("%d",&size);
	
	
	maze=(char**)calloc(size,sizeof(char*));					//Labirent için dinamic memory ile yer açýlýyor
	for(i=0;i<size;i++)												
		maze[i]=(char*)calloc(size,sizeof(char));				
		
	line=(char*)calloc(50,sizeof(char));						//Her okunan satýrý tutmak için dinamic memory ile yer açýlýyor
	i=0;
	FILE *fp;													//Dosya pointer'ý açýlýyor
	fp=fopen("Yeni Metin Belgesi (2).txt","r");					//Dosya okuma iþlemleri için açýlýyor
	while(!feof(fp)){											//Dosyanýn sonuna kadar okuma iþlemleri devam ediyor
		fgets(line,50,fp);										//fgets fonksiyonu ile satýrlar line'ýn içine atýlýyor
		ptr=strtok(line,", ");									//strtok fonksiyonu ile satýrdan boþluk ve virgüller siliniyor
		maze[i][0]=ptr[0];										//Silindikten sonra labirentin ilk sütununa yerleþtiriliyor
		
		for(j=1;j<size;j++){									//Geriye kalan satýrlarda boþluk ve virgüllerden temizlenip
			ptr=strtok(NULL,", ");								//labirentin içine atýlýyor
			maze[i][j]=ptr[0];
		}
		i++;
	}	
	fclose(fp);													//Dosya pointer'ý kapatýlýyor
	
	DFS(size,1,1,maze);											//DFS fonksiyonu çaðýrýlýyor
	
	yazdir(size,maze);											//yazdir fonksiyonu çaðýrýlýyor

	return 0;
}

