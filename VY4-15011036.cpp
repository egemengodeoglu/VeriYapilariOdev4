#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void yazdir(int size,char**maze){								//Yazd�r fonksiyonu matrisi formatl� �ekilde ekrana yazd�r�yor
	static int sayac=0;											//Sayac ka��nc� ad�mda oldu�unu g�steriyor Static tan�mland��� i�in de�er fonksiyonun i�inde de�i�iyor
		printf("%d. adim\n",sayac);								//Ad�m ekrana yazd�r�l�yor
	int i,j;
		for(i=0;i<size;i++){									//Matirisin sat�r indisi
		for(j=0;j<size;j++){									//Matrisin sutun indisi
			if(i%2==0){											//Matrisin �ift sat�rlar�nda - yada + yaz�yor
				if(j%2==0)										//E�er sutun �iftse + koyuyor
				printf("+ ");
				else if(maze[i][j]=='0')						//E�er sutun tekse ve 0 ise - koyuyor
				printf("- ");
				else											//E�er sutun tekse ve 1 ise yolu bo� b�rak�yor
				printf("  ");	
			}else{												//E�er sat�r tek ise
				if(maze[i][j]=='0')								//E�er 0 ise yolu kapat�yor | 
				printf("| ");
				else if(i==1 && j==1)							//E�er ilk sat�r ve s�tunsa * koyuyor			
				printf("* ");
				else if(maze[i][j]=='V' && j==(size-2))			//E�er son sat�rdaysa sona ulasm��t�r ve X koyuyor
				printf("X ");
				else if(maze[i][j]=='V')						//E�er nokta visited edilmi�se I koyuyor
				printf("I ");
				else											//E�er daha �nce visited edilmemi�se yolu bo� b�rak�yor
				printf("  ");
			}
		}
		printf("\n");
	}
	sayac++;													//Ad�m say�s� i�in sayac 1 artt�r�l�yor
	printf("\n");
}
void DFS(int size,int i,int j,char**maze){						//Depth First Search yapan fonksiyor

	yazdir(size,maze);											//Her ad�m�n ba��nda ekrana durumu yazd�r�yor
	maze[i][j]='V';												//Bulundu�u d���m� ziyaret edilmi�(Visited) yap�yor
	static int exit=0;											//Sona ula��ld���nda ��kmak i�in exit tan�mlan�yor
	if(j==size-2){
		exit=1;
	}	
	if(maze[i+1][j]=='1' && maze[i+2][j]=='B' && exit==0)		//E�er a�a�� tarafa yol a��ksa ve ziyaret edilmemi�se a�a�� gidiyor
		DFS(size,i+2,j,maze);	
	if(maze[i][j+1]=='1' && maze[i][j+2]=='B' && exit==0)		//E�er sa� tarafa yol a��ksa ve ziyaret edilmemi�se sa�a gidiyor
		DFS(size,i,j+2,maze);
	if(maze[i-1][j]=='1' && maze[i-2][j]=='B' && exit==0)		//E�er yukar� tarafa yol a��ksa ve ziyaret edilmemi�se yukar� gidiyor
		DFS(size,i-2,j,maze);
	if(maze[i][j-1]=='1' && maze[i][j-2]=='B' && exit==0)		//E�er sol tarafa yol a��ksa ve ziyaret edilmemi�se sola gidiyor
		DFS(size,i,j-2,maze);
	
}

int main(){			
	int i,j,size;
	char** maze,*line,*ptr;									
	
	printf("Matrisin boyutunu giriniz=");						//Matrisin boyutu kullan�c�dan al�n�yor
	scanf("%d",&size);
	
	
	maze=(char**)calloc(size,sizeof(char*));					//Labirent i�in dinamic memory ile yer a��l�yor
	for(i=0;i<size;i++)												
		maze[i]=(char*)calloc(size,sizeof(char));				
		
	line=(char*)calloc(50,sizeof(char));						//Her okunan sat�r� tutmak i�in dinamic memory ile yer a��l�yor
	i=0;
	FILE *fp;													//Dosya pointer'� a��l�yor
	fp=fopen("Yeni Metin Belgesi (2).txt","r");					//Dosya okuma i�lemleri i�in a��l�yor
	while(!feof(fp)){											//Dosyan�n sonuna kadar okuma i�lemleri devam ediyor
		fgets(line,50,fp);										//fgets fonksiyonu ile sat�rlar line'�n i�ine at�l�yor
		ptr=strtok(line,", ");									//strtok fonksiyonu ile sat�rdan bo�luk ve virg�ller siliniyor
		maze[i][0]=ptr[0];										//Silindikten sonra labirentin ilk s�tununa yerle�tiriliyor
		
		for(j=1;j<size;j++){									//Geriye kalan sat�rlarda bo�luk ve virg�llerden temizlenip
			ptr=strtok(NULL,", ");								//labirentin i�ine at�l�yor
			maze[i][j]=ptr[0];
		}
		i++;
	}	
	fclose(fp);													//Dosya pointer'� kapat�l�yor
	
	DFS(size,1,1,maze);											//DFS fonksiyonu �a��r�l�yor
	
	yazdir(size,maze);											//yazdir fonksiyonu �a��r�l�yor

	return 0;
}

