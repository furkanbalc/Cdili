#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int chartoint(char sayi)
{
	int i;
	for (i = 48; i <= 57; i++)
	{
		if (toascii(i) == sayi)
		{
			return i - 48;
		}
	}

	return 0;
}

//rakamlar
bool rakam(char ch)
{
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
		ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')

		return (true);
	return (false);
}

int main()
{
	//dosyaya ulaþmak için FILE tipinde tanýmlama ve diðer dizi ve deðiþken tanýmlamalarý
	FILE * dosya;
	char veri[9999], veriyedek[9999];
	char txt[99];	//adres için
	char karakter;
	int i, j, k = 0, bsayisi = 0, n = 0, sayi = 0, bdeger = 1, bellek = 0;
	short int ram[2047];
	unsigned short int AX = 0, BX = 0, CX = 0, DX = 0;

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
		veri[n] = karakter;
		n++;	// boþluk karakterleri dahil eleman sayýsýný tutuyor

	}

	for (j = 0; j < n - 1; j++)
	{
		if (veri[j] != toascii(32) && veri[j] != toascii(10) && veri[j] != toascii(9))
		{
			veriyedek[k] = veri[j];
			printf("%c,", veriyedek[k]);	// harf harf yazdýrma
			k++;	//boþluklar hariç karakter sayisini tutuyor
		}
	}

	printf("\n");
	printf("**KAYNAK KOD**\n");
	//dosyanýn kendisini yazdýrma yani kaynak kod
	for (j = 0; j < n; j++)
	{
		printf("%c", veri[j]);
	}

	printf("\n");

	for (i = 0; i < k - 1; i++)
	{	
		//HRK gelme durumu
		if (veriyedek[i] == 'H')
		{
			i = i + 3;
			//HRK den sonra AX,BX,CX,DX,BELLEK veya SABÝT gelme durumu
			if (veriyedek[i] == 'A')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					AX = AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					AX = BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					AX = CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					AX = DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;
					}

					AX = ram[sayi];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					AX = sayi;
					i = i + bsayisi - 1;

				}
			}
			else if (veriyedek[i] == 'B')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					BX = AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					BX = BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					BX = CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					BX = DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					BX = ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					BX = sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'C')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					CX = AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					CX = BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					CX = CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					CX = DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					CX = ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					CX = sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'D')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					DX = DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = sayi;
					i = i + bsayisi - 1;
				}
			}
			//BELLEK DURUMU
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				i = i + bsayisi + 2;

				if (veriyedek[i] == 'A')
				{
					ram[bellek] = AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					ram[bellek] = BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					ram[bellek] = CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					ram[bellek] = DX;
					i = i + 1;
				}
				else
				{
					//SABIT DURUMU

					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					ram[bellek] = sayi;
					i = i + bsayisi - 1;

				}
			}
			else
			{
				// SABIT DURUMU

			}
		}
		else if (veriyedek[i] == 'T')
		{
			i = i + 3;
			if (veriyedek[i] == 'A')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					AX = AX + AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					AX = AX + BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					AX = AX + CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					AX = AX + DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;
					}

					AX = AX + ram[sayi];
					i = i + bsayisi;

				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					AX = AX + sayi;
					i = i + bsayisi - 1;

				}
			}
			else if (veriyedek[i] == 'B')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					BX = BX + AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					BX = BX + BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					BX = BX + CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					BX = BX + DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					BX = BX + ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					BX = BX + sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'C')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					CX = CX + AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					CX = CX + BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					CX = CX + CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					CX = CX + DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					CX = CX + ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					CX = CX + sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'D')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = DX + AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = DX + BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = DX + CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					DX = DX + DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = DX + ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = DX + sayi;
					i = i + bsayisi - 1;
				}
			}
			//BELLEK DURUMU
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				i = i + bsayisi + 2;

				if (veriyedek[i] == 'A')
				{
					ram[bellek] = ram[bellek] + AX;

					i = i + 1;	//////////////////////////////////////////////////

				}
				else if (veriyedek[i] == 'B')
				{
					ram[bellek] = ram[bellek] + BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					ram[bellek] = ram[bellek] + CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					ram[bellek] = ram[bellek] + DX;
					i = i + 1;
				}
				else
				{
					//SABIT DURUMU

					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					ram[bellek] = ram[bellek] + sayi;
					i = i + bsayisi - 1;

				}
			}
			else
			{
				// SABIT DURUMU

			}
		}
		else if (veriyedek[i] == 'C' && veriyedek[i + 1] == 'I')
		{
			i = i + 3;
			if (veriyedek[i] == 'A')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					AX = AX - AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					AX = AX - BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					AX = AX - CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					AX = AX - DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;
					}

					AX = AX - ram[sayi];
					i = i + bsayisi;
					printf("i = %d ", i);
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					AX = AX - sayi;
					i = i + bsayisi - 1;

				}
			}
			else if (veriyedek[i] == 'B')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					BX = BX - AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					BX = BX - BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					BX = BX - CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					BX = BX - DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					BX = BX - ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					BX = BX - sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'C')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					CX = CX - AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					CX = CX - BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					CX = CX - CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					CX = CX - DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					CX = CX - ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					CX = CX - sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'D')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = DX - AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = DX - BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = DX - CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					DX = DX - DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = DX - ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = DX - sayi;
					i = i + bsayisi - 1;
				}
			}
			//BELLEK DURUMU
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				i = i + bsayisi + 2;

				if (veriyedek[i] == 'A')
				{
					ram[bellek] = ram[bellek] - AX;

					i = i + 1;

				}
				else if (veriyedek[i] == 'B')
				{
					ram[bellek] = ram[bellek] - BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					ram[bellek] = ram[bellek] - CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					ram[bellek] = ram[bellek] - DX;
					i = i + 1;
				}
				else
				{
					//SABIT DURUMU

					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					ram[bellek] = ram[bellek] - sayi;
					i = i + bsayisi - 1;

				}
			}
			else
			{
				

			}
		}
		else if (veriyedek[i] == 'C' && veriyedek[i + 1] == 'R')
		{
			i = i + 3;
			if (veriyedek[i] == 'A')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					AX = AX * AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					AX = AX * BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					AX = AX * CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					AX = AX * DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;
					}

					AX = AX *ram[sayi];
					i = i + bsayisi;

				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					AX = AX * sayi;
					i = i + bsayisi - 1;

				}
			}
			else if (veriyedek[i] == 'B')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					BX = BX * AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					BX = BX * BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					BX = BX * CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					BX = BX * DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					BX = BX *ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					BX = BX * sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'C')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					CX = CX * AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					CX = CX * BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					CX = CX * CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					CX = CX * DX;
					i = i + 1;
				}//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					CX = CX *ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					CX = CX * sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'D')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = DX * AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = DX * BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = DX * CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					DX = DX * DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = DX *ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = DX * sayi;
					i = i + bsayisi - 1;
				}
			}
			//BELLEK DURUMU
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				i = i + bsayisi + 2;

				if (veriyedek[i] == 'A')
				{
					ram[bellek] = ram[bellek] *AX;

					i = i + 1;

				}
				else if (veriyedek[i] == 'B')
				{
					ram[bellek] = ram[bellek] *BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					ram[bellek] = ram[bellek] *CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					ram[bellek] = ram[bellek] *DX;
					i = i + 1;
				}
				else
				{
					//SABIT DURUMU

					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					ram[bellek] = ram[bellek] *sayi;
					i = i + bsayisi - 1;

				}
			}
			else
			{
				
				

			}
		}
		else if (veriyedek[i] == 'B')
		{
			i = i + 3;
			if (veriyedek[i] == 'A')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = AX % AX;
					AX = AX / AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = AX % BX;
					AX = AX / BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = AX % CX;
					AX = AX / CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					int tmp = DX;
					DX = AX % DX;
					AX = AX / tmp;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;
					}

					DX = AX % ram[sayi];
					AX = AX / ram[sayi];
					i = i + bsayisi;

				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = AX % sayi;
					AX = AX / sayi;
					i = i + bsayisi - 1;

				}
			}
			else if (veriyedek[i] == 'B')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = BX % AX;
					BX = BX / AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = BX % BX;
					BX = BX / BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = BX % CX;
					BX = BX / CX;

					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					int tmp = DX;
					DX = BX % DX;
					BX = BX / tmp;

					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = BX % ram[bellek];
					BX = BX / ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = BX % sayi;
					BX = BX / sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'C')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = CX % AX;
					CX = CX / AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = CX % BX;
					CX = CX / BX;

					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = CX % CX;
					CX = CX / CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					int tmp = DX;
					DX = CX % DX;
					CX = CX / tmp;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = CX % ram[bellek];
					CX = CX / ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = CX % sayi;
					CX = CX / sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'D')
			{
				int tmp = DX;
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = DX % AX;
					DX = tmp/AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = DX % BX;
					DX = tmp / BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = DX % CX;
					DX = tmp / CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					DX = DX % DX;
					DX = tmp / DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = DX % ram[bellek];
					DX = tmp / ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = DX % sayi;
					DX = tmp / sayi;
					i = i + bsayisi - 1;
				}
			}
			//BELLEK DURUMU
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				i = i + bsayisi + 2;

				if (veriyedek[i] == 'A')
				{
					DX = ram[bellek] % AX;
					ram[bellek] = ram[bellek] / AX;

					i = i + 1;

				}
				else if (veriyedek[i] == 'B')
				{
					DX = ram[bellek] % BX;
					ram[bellek] = ram[bellek] / BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = ram[bellek] % CX;
					ram[bellek] = ram[bellek] / CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					int tmp = DX;
					DX = ram[bellek] % DX;
					ram[bellek] = ram[bellek] / tmp;
					i = i + 1;
				}
				else
				{
					//SABIT DURUMU

					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = ram[bellek] % sayi;
					ram[bellek] = ram[bellek] / sayi;
					i = i + bsayisi - 1;

				}
			}
			else
			{
				

			}
		}
		else if (veriyedek[i] == 'V' && veriyedek[i + 1] == 'E' && veriyedek[i + 2] == 'Y')
		{
			i = i + 4;
			if (veriyedek[i] == 'A')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					AX = AX | AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					AX = AX | BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					AX = AX | CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					AX = AX | DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;
					}

					AX = AX | ram[sayi];
					i = i + bsayisi;

				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					AX = AX | sayi;
					i = i + bsayisi - 1;

				}
			}
			else if (veriyedek[i] == 'B')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					BX = BX | AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					BX = BX | BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					BX = BX | CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					BX = BX | DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					BX = BX | ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					BX = BX | sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'C')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					CX = CX | AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					CX = CX | BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					CX = CX | CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					CX = CX | DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					CX = CX | ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					CX = CX | sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'D')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = DX | AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = DX | BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = DX | CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					DX = DX | DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = DX | ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = DX | sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				i = i + bsayisi + 2;

				if (veriyedek[i] == 'A')
				{
					ram[bellek] = ram[bellek] | AX;

					i = i + 1;

				}
				else if (veriyedek[i] == 'B')
				{
					ram[bellek] = ram[bellek] | BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					ram[bellek] = ram[bellek] | CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					ram[bellek] = ram[bellek] | DX;
					i = i + 1;
				}
				else
				{
					//SABIT DURUMU

					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					ram[bellek] = ram[bellek] | sayi;
					i = i + bsayisi - 1;

				}
			}
			else
			{
				// SABIT DURUMU

			}
		}
		else if (veriyedek[i] == 'V' && veriyedek[i + 1] == 'E')
		{
			i = i + 2;
			if (veriyedek[i] == 'A')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					AX = AX &AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					AX = AX &BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					AX = AX &CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					AX = AX &DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;
					}

					AX = AX &ram[sayi];
					i = i + bsayisi;

				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					AX = AX &sayi;
					i = i + bsayisi - 1;

				}
			}
			else if (veriyedek[i] == 'B')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					BX = BX &AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					BX = BX &BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					BX = BX &CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					BX = BX &DX;
					i = i + 1;
				}//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					BX = BX &ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					BX = BX &sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'C')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					CX = CX &AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					CX = CX &BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					CX = CX &CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					CX = CX &DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					CX = CX &ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					CX = CX &sayi;
					i = i + bsayisi - 1;
				}
			}
			else if (veriyedek[i] == 'D')
			{
				i = i + 3;
				if (veriyedek[i] == 'A')
				{
					DX = DX &AX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'B')
				{
					DX = DX &BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					DX = DX &CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					DX = DX &DX;
					i = i + 1;
				}
				//BELLEK DURUMU
				else if (veriyedek[i] == '[')
				{
					bdeger = 1;
					bsayisi = 0;
					bellek = 0;
					i = i + 1;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						bellek = chartoint(veriyedek[i]) *bdeger + bellek;
						bdeger = bdeger * 10;
					}

					DX = DX &ram[bellek];
					i = i + bsayisi;
				}
				else
				{
					// SABIT DURUMU
					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					DX = DX &sayi;
					i = i + bsayisi - 1;
				}
			}
			//BELLEK DURUMU
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				i = i + bsayisi + 2;

				if (veriyedek[i] == 'A')
				{
					ram[bellek] = ram[bellek] &AX;

					i = i + 1;

				}
				else if (veriyedek[i] == 'B')
				{
					ram[bellek] = ram[bellek] &BX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'C')
				{
					ram[bellek] = ram[bellek] &CX;
					i = i + 1;
				}
				else if (veriyedek[i] == 'D')
				{
					ram[bellek] = ram[bellek] &DX;
					i = i + 1;
				}
				else
				{
					//SABIT DURUMU

					bdeger = 1;
					bsayisi = 0;
					sayi = 0;
					while (rakam(veriyedek[i]) == 1)
					{
						i++;
						bsayisi++;
					}

					for (j = bsayisi; j >= 1; j--)
					{
						i--;
						sayi = chartoint(veriyedek[i]) *bdeger + sayi;
						bdeger = bdeger * 10;

					}

					ram[bellek] = ram[bellek] &sayi;
					i = i + bsayisi - 1;

				}
			}
			else
			{

			}
		}
		else if (veriyedek[i] == 'D')
		{
			i = i + 3;
			if (veriyedek[i] == 'A')
			{
				AX = ~AX;
				i = i + 1;
			}
			else if (veriyedek[i] == 'B')
			{
				BX = ~BX;
				i = i + 1;

			}
			else if (veriyedek[i] == 'C')
			{
				CX = ~CX;
				i = i + 1;

			}
			else if (veriyedek[i] == 'D')
			{
				DX = ~DX;
				i = i + 1;

			}
			//BELLEK DURUMU
			else if (veriyedek[i] == '[')
			{
				bdeger = 1;
				bsayisi = 0;
				bellek = 0;
				i = i + 1;
				while (rakam(veriyedek[i]) == 1)
				{
					i++;
					bsayisi++;
				}

				for (j = bsayisi; j >= 1; j--)
				{
					i--;
					bellek = chartoint(veriyedek[i]) *bdeger + bellek;
					bdeger = bdeger * 10;
				}

				ram[bellek] = ~ram[bellek];
				i = i + bsayisi - 1;

			}
			else
			{
				// SABIT DURUMU

			}
		}
	}
	//önemli sekiz biti maskelemek için yapýldý
	AX = AX &255;
	BX = BX &255;
	CX = CX &255;
	DX = DX &255;

	printf("AX = %d\n", AX);
	printf("BX = %d\n", BX);
	printf("CX = %d\n", CX);
	printf("DX = %d", DX);

}
