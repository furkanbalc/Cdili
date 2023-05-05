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
//noktalama iþaretleri
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
	//dosyaya ulaþmak için FILE tipinde tanýmlama ve diðer dizi ve deðiþken tanýmlamalarý
	FILE *dosya;
	char veri[9999], veriyedek[9999]; //dosya elemanlarý için
	char txt[99];					  //adres için
	char karakter;					  //diziye eleman atmaya yardýmcý deðiþken
	int i = 0, j, flag;

	//dosyaya eriþme iþlemi
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
		i++; // boþluk karakterleri dahil eleman sayýsýný tutuyor
	}

	int k = 0;
	/*veri dizisinden boþluklarý eleyerek veriyedek dizisine geçildi
	eðer veri dizisinde boþluk, tab ve enter karakteri varsa bir sonraki elemana geç*/
	for (j = 0; j < i - 1; j++)
	{
		if (veri[j] != toascii(32) && veri[j] != toascii(10) && veri[j] != toascii(9))
		{
			veriyedek[k] = veri[j];
			//printf("%c,", veriyedek[k]); // harf harf yazdýrma
			k++; //boþluklar hariç karakter sayisini tutuyor
		}
	}
	printf("\n");

	printf("*****KAYNAK KOD*****\n");
	//dosyanýn kendisini yazdýrma yani kaynak kod
	for (j = 0; j < i; j++)
	{
		printf("%c", veri[j]);
	}
	printf("\n*****KELIMELESTIRME*****\n");
	printf("\n{ "); //yazdýrma iþlemi baþlarken a. parantez

	//tokenizer iþlemi
	for (j = 0; j < k; j++)
	{
		if (terminal(veriyedek[j]) == 1)
		{
			//burda ++ -- <= >= != == && || çiftli durumlarý kontrol ediliyor
			if (veriyedek[j] == '+' && veriyedek[j + 1] == '+' || veriyedek[j] == '-' && veriyedek[j + 1] == '-' 
			 || veriyedek[j] == '=' && veriyedek[j + 1] == '=' || veriyedek[j] == '<' && veriyedek[j + 1] == '=' 
			 || veriyedek[j] == '>' && veriyedek[j + 1] == '=' || veriyedek[j] == '=' && veriyedek[j + 1] == '=' 
			 || veriyedek[j] == '+' && veriyedek[j + 1] == '=' || veriyedek[j] == '-' && veriyedek[j + 1] == '=')
			{
				//veriyedek[j] ve veriyedek[j+1] þarlarý saðlýyorsa yaz
				printf("%c", veriyedek[j]);
				printf("%c,", veriyedek[j + 1]);

				j += 1;
			}
			else
			{
				printf("%c,", veriyedek[j]); //ikili operatör deðilse terminal fonksiyonu elemanýný yaz
			}
		}
		else if (noktalama(veriyedek[j]) == 1)
		{
			//çiftli durumlar kontrolü
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
				//flag kontrolü iki çift arasýný tek token almak için yapýldý
				//flag 1 se gir çift týrnaða gelene kadar yaz flag = 0 yap ve whiledan çýk
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
				printf("%c,", veriyedek[j]); //çift durum ve týrnak deðilse noktalama fonskiyonu elemanýný yaz
			}
		}
		else
		{
			//terminal ve noktalama elemanlarý hariç diðer karakterlerin gelme durumu
			printf("%c", veriyedek[j]);

			//veriyedek[j+1] noktalama ve terminal fonksiyonu elemaný deðilse yaz sonra noktalama ve terminal elemaný gelene kadar j yi arttýrarak devam et
			while (noktalama(veriyedek[j + 1]) != 1 && terminal(veriyedek[j + 1]) != 1)
			{
				printf("%c", veriyedek[j + 1]);
				j += 1;
			}
			//while döngüsü bittikten sonra virgül koy çünkü bir cümle yada sayý yazmýþ olacak veya harf
			printf(",");
		}
	}

	printf(" }");  //yazdýrma iþlemi bittiksen sonra kapa parantez
	fclose(dosya); //dosyayý kapat
	return 0;
}
