/*Furkan BALCI
  02200201076
  2. sinif normal ogretim*/

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
//terminal fonksiyonu
bool terminal(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' 
	 || ch == '/' || ch == '>' || ch == '<' || ch == '=')

		return (true);
	return (false);
}
//noktalama i�aretleri
bool noktalama(char ch)
{
	if (ch == ';' || ch == ',' || ch == '"' || ch == '(' 
	 || ch == ')' || ch == '[' || ch == ']' || ch == '{' 
   	 || ch == '}' || ch == '!' || ch == '&' || ch == '|')

		return (true);
	return (false);
}
int main()
{
	//dosyaya ula�mak i�in FILE tipinde tan�mlama ve di�er dizi ve de�i�ken tan�mlamalar�
	FILE *dosya;
	char veri[9999], veriyedek[9999]; //dosya elemanlar� i�in
	char txt[99];					  //adres i�in
	char karakter;					  //diziye eleman atmaya yard�mc� de�i�ken
	int i = 0, j, flag;

	//dosyaya eri�me i�lemi
dongu:
	printf("Dosyanizin adresini giriniz >> ");
	scanf("%s", &txt);

	if ((dosya = fopen(txt, "r")) == NULL)
	{
		printf("Dosya acilamadi.\n");
		goto dongu;
	}

	//dosyadaki verileri diziye atma
	while (!feof(dosya))
	{
		karakter = fgetc(dosya);
		veri[i] = karakter;
		i++; // bo�luk karakterleri dahil eleman say�s�n� tutuyor
	}

	int k = 0;
	/*veri dizisinden bo�luklar� eleyerek veriyedek dizisine ge�ildi
	e�er veri dizisinde bo�luk, tab ve enter karakteri varsa bir sonraki elemana ge�*/
	for (j = 0; j < i - 1; j++)
	{
		if (veri[j] != toascii(32) && veri[j] != toascii(10) && veri[j] != toascii(9))
		{
			veriyedek[k] = veri[j];
			//printf("%c,", veriyedek[k]); // harf harf yazd�rma
			k++; //bo�luklar hari� karakter sayisini tutuyor
		}
	}
	printf("\n");

	printf("*****KAYNAK KOD*****\n");
	//dosyan�n kendisini yazd�rma yani kaynak kod
	for (j = 0; j < i; j++)
	{
		printf("%c", veri[j]);
	}
	printf("\n*****KELIMELESTIRME*****\n");
	printf("\n{ "); //yazd�rma i�lemi ba�larken a. parantez

	//tokenizer i�lemi
	for (j = 0; j < k; j++)
	{
		if (terminal(veriyedek[j]) == 1)
		{
			//burda ++ -- <= >= != == && || �iftli durumlar� kontrol ediliyor
			if (veriyedek[j] == '+' && veriyedek[j + 1] == '+' || veriyedek[j] == '-' && veriyedek[j + 1] == '-' 
			 || veriyedek[j] == '=' && veriyedek[j + 1] == '=' || veriyedek[j] == '<' && veriyedek[j + 1] == '=' 
			 || veriyedek[j] == '>' && veriyedek[j + 1] == '=' || veriyedek[j] == '=' && veriyedek[j + 1] == '=' 
			 || veriyedek[j] == '+' && veriyedek[j + 1] == '=' || veriyedek[j] == '-' && veriyedek[j + 1] == '=')
			{
				//veriyedek[j] ve veriyedek[j+1] �arlar� sa�l�yorsa yaz
				printf("%c", veriyedek[j]);
				printf("%c,", veriyedek[j + 1]);

				j += 1;
			}
			else
			{
				printf("%c,", veriyedek[j]); //ikili operat�r de�ilse terminal fonksiyonu eleman�n� yaz
			}
		}
		else if (noktalama(veriyedek[j]) == 1)
		{
			//�iftli durumlar kontrol�
			if (veriyedek[j] == '!' && veriyedek[j + 1] == '=' 
			 || veriyedek[j] == '&' && veriyedek[j + 1] == '&' 
			 || veriyedek[j] == '|' && veriyedek[j + 1] == '|')
			{
				printf("%c", veriyedek[j]);
				printf("%c,", veriyedek[j + 1]);

				j = j + 1;
			}

			else if ((veriyedek[j]) == '"')
			{
				printf("%c,", veriyedek[j]);
				//flag kontrol� iki �ift aras�n� tek token almak i�in yap�ld�
				//flag 1 se gir �ift t�rna�a gelene kadar yaz flag = 0 yap ve whiledan ��k
				flag = 1;
				while (flag == 1)
				{
					if (veriyedek[j + 1] != '"')
					{
						printf("%c", veriyedek[j + 1]);
						j += 1;
					}
					else
					{
						printf(",%c,", veriyedek[j + 1]);
						j += 1;
						flag = 0;
					}
				}
			}
			else
			{
				printf("%c,", veriyedek[j]); //�ift durum ve t�rnak de�ilse noktalama fonskiyonu eleman�n� yaz
			}
		}
		else
		{
			//terminal ve noktalama elemanlar� hari� di�er karakterlerin gelme durumu
			printf("%c", veriyedek[j]);

			//veriyedek[j+1] noktalama ve terminal fonksiyonu eleman� de�ilse yaz sonra noktalama ve terminal eleman� gelene kadar j yi artt�rarak devam et
			while (noktalama(veriyedek[j + 1]) != 1 && terminal(veriyedek[j + 1]) != 1)
			{
				printf("%c", veriyedek[j + 1]);
				j += 1;
			}
			//while d�ng�s� bittikten sonra virg�l koy ��nk� bir c�mle yada say� yazm�� olacak veya harf
			printf(",");
		}
	}

	printf(" }");  //yazd�rma i�lemi bittiksen sonra kapa parantez
	fclose(dosya); //dosyay� kapat
	return 0;
}
