/*Furkan BALCI
  02200201076
  2. sinif normal ogretim

	Kodun calisma sekli : Gramer dogru isliyorsa kodu gelen verilere gore yazmaya baslar. 
	Eger ki hata algiladiysa hatali olan kelimeyi ekrana yazip kullaniciya gosterdikten sonra hatanin ne oldugu yazar.
	Hata eksikliklikten kaynaklýysa doðru olan kýsmý yine yazar ve eksik olan kelimeyi verir.(Bazen iki hata birden verebiliyor ilk verdiði hata doðru kabul edilir.)

  	NOT : Noktali virgul gramere dahil edilmemistir.*/
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
	//terminal fonksiyonu
bool terminal(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' || ch == '=')

		return (true);
	return (false);
}

//noktalama iþaretleri
bool noktalama(char ch)
{
	if (ch == ';' || ch == '"' || ch == '(' || ch == ')' || ch == '[' || ch == ']' ||
		ch == '{' || ch == '}' || ch == '!' || ch == '&' || ch == '|' || ch == '?')

		return (true);
	return (false);
}

//rakamlar
bool rakam(char ch)
{
	if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' ||
		ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9')

		return (true);
	return (false);
}

//harfler
bool harf(char ch)
{
	if (ch == 'a' || ch == 'b' || ch == 'c' || ch == 'd' || ch == 'e' || ch == 'f')

		return (true);
	return (false);
}

//operand
bool operand(char ch)
{
	if (ch == '<' || ch == '>' || ch == '=')

		return (true);
	return (false);
}

//gramerdeki cumlenin elemanlarý 
bool operat(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' || ch == '/')

		return (true);
	return (false);
}

//hata fonksiyonu
void hata()
{
	printf(" -DOSYA HATALIDIR!!!");
}

//-------------------------------------------------------------------------------------
//gramerde sayi gelme durumunu kontrol eder istenen sartlar saglanirsa true degeri doner

bool sayi(char d[][20], int p)
{
	if (rakam(d[p][0]) == 1)
	{
		int tmp = 1;
		while (rakam(d[p][tmp]) == 1)
		{
			tmp++;
		}

		if (d[p][tmp] == '\0')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//gramerde operand gelme durumunu kontrol eder istenen sartlar saglanirsa true degeri doner
bool op(char d[][20], int p)
{
	if (operand(d[p][0]) == 1)
	{
		if (d[p][0] == '=')
		{
			if (d[p][1] == '=' && d[p][2] == '\0')
			{
				printf("%s", d[p]);
				return true;
			}
			else
			{
				printf("%s", d[p]);
				printf("(Hatali operand)");
				return false;
			}
		}
		else
		{
			if (d[p][0] == '<' && d[p][1] == '\0' || d[p][0] == '>' && d[p][1] == '\0' || d[p][0] == '<' && d[p][1] == '=' && d[p][2] == '\0' || d[p][0] == '>' && d[p][1] == '=' && d[p][2] == '\0')
			{
				printf("%s", d[p]);
				return true;
			}
			else
			{
				printf("%s", d[p]);
				printf("(Hatali operand)");
				return false;
			}
		}
	}
	else
	{
		printf("%s", d[p]);
		printf("(Operand gelmeli)");
		return false;
	}
}

//<id> degiskeninin durumunu kontrol eder istenen sartlar saglanirsa true degeri doner
bool idKontrol(char d[][20], int p)
{
	if (harf(d[p][0]) == 1 && d[p][1] == '\0')
	{
		printf("%s", d[p]);
		p++;

		return true;
	}
	else if (sayi(d, p) == 1)
	{
		printf("%s", d[p]);
		p++;
		return true;
	}
	else
	{
		printf("%s", d[p]);
		printf("(Gecersiz id)");

		return false;
		
	}
}

//<cumle> gramerinin kontrolunü saðlar istenen sartlar saglanirsa true degeri doner
bool cumle(char d[][20], int p)
{
	/*<id> kontrolu eger<id> varsa bir sonrasi operat fonk elemanlarýndan biriyse bir sonrasi<id> mi sart saglanir ise 
	bir sonrasý kapali parantezse<cumle> gramerindeki {<id> =<id>} sarti saglanmis olur.
	eger<id><id> den sonra kapali parantez gelmiyorsa bir sonrasi erand ve onun bir sonrasi<id> mi diye bakýlýr 
	sartlar saglanirsa {<id> =<id> +|*|-|/<id> sartlarindan biri saglanmis olur ve gramer saglanir. 
	*/
	if (idKontrol(d, p) == 1)
	{
		p++;
		if (d[p][0] == '=' && d[p][1] == '\0')
		{
			printf("%c", d[p][0]);
			p++;
			if (idKontrol(d, p) == 1)
			{
				p++;
				if (d[p][0] == '}' && d[p][1] == '\0')
				{
					printf("%s", d[p]);
					return true;
				}
				else if (operat(d[p][0]) == 1 && d[p][1] == '\0')
				{
					printf("%s", d[p]);
					p++;
					if (idKontrol(d, p) == 1)
					{
						p++;
						if (d[p][0] == '}' && d[p][1] == '\0')
						{
							printf("%s", d[p]);
							return true;
						}
						else
						{
							printf("%s", d[p]);
							printf("('}' gelmeli)");

							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					printf("('}' gelmeli veya dogru operator kullandiginizdan emin olun.)");

					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			printf("(sadece '=' kullanilabilir)");
			//hata();
			return false;
		}
	}
	else
	{
		return false;
	}
}

//if icerisindeki<sart> degiskenini kontrol eder istenen sartlar saglanirsa true degeri doner
bool sart(char d[][20], int p)
{
	//<id> harf mi ? harfse ve tek baþýnaysa bir sonraki<op> mu bu da doðruysa tekrar<id> mi id ise harf mi deðilse sayý mý ikiside deðilse hata 
	if (harf(d[p][0]) == 1 && d[p][1] == '\0')
	{
		printf("%s", d[p]);
		p++;

		if (op(d, p) == 1)
		{
			p++;
			if (harf(d[p][0]) == 1 && d[p][1] == '\0')
			{
				printf("%s", d[p]);
				p++;
				return true;
			}
			else if (sayi(d, p) == 1)
			{
				printf("%s", d[p]);
				return true;
			}
			else
			{
				printf("%s", d[p]);
				printf("(Gecersiz id)");

				return false;
			}
		}
		else
		{
			return false;
		}
	}

	//<id> sayi mi ? sayýysa bir sonraki<op> mu bu da doðruysa tekrar<id> harf mi deðilse sayý mý ikiside deðilse hata
	else if (sayi(d, p) == 1)
	{
		printf("%s", d[p]);
		p++;
		if (op(d, p) == 1)
		{
			p++;
			if (harf(d[p][0]) == 1 && d[p][1] == '\0')
			{
				printf("%s", d[p]);
				p++;
				return true;
			}
			else if (sayi(d, p) == 1)
			{
				printf("%s", d[p]);
				return true;
			}
			else
			{
				printf("%s", d[p]);
				printf("(Gecersiz id)");

				return false;
			}
		}
		else
		{
			return false;
		}
	}

	//<id> sayi da harf de degilse hata ver
	else
	{
		printf("%s", d[p]);
		printf("(Gecersiz id)");

		return false;
	}
}

//else ifin gelme durumunu kontrol eder þartlarý saðlýyorsa true donderir
bool elseIf(char d[][20], int p)
{
	int j;
	if (d[p][0] == 'e' && d[p][1] == 'l' && d[p][2] == 's' && d[p][3] == 'e' &&
		d[p][4] == 'i' && d[p][5] == 'f' && d[p][6] == '\0')
	{
		printf("%s", d[p]);
		p++;
		if (d[p][0] == '(')
		{
			printf("%s", d[p]);
			p++;
			if (d[p][0] != ')')
			{
				if (sart(d, p) == 1)
				{
					p += 3;
					if (d[p][0] == ')')
					{
						printf("%s", d[p]);
						p++;
						if (d[p][0] == '{')
						{
							printf("%s", d[p]);
							p++;
							if (cumle(d, p) == 1)
							{
								return true;
							}
							else
							{
								return false;

							}
						}
						else
						{
							printf("%s", d[p]);
							printf("('{' gelmeli)");
							hata();
							return false;
						}
					}
					else
					{
						printf("%s", d[p]);
						printf("(<sart> grameri saglandiysa kapa parantez gelmeli)");
						hata();
						return false;
					}
				}
				else
				{
					hata();
					return false;
				}
			}
			else
			{
				printf("%s", d[p]);
				printf("(Elseifin ici bos kalamaz)");
				hata();

				return false;

			}
		}
		else
		{
			printf("%s", d[p]);
			printf("(Ac parantez hatasi)");
			hata();
			return false;
		}
	}
	else
	{
		return false;
	}
}

int main()
{
	//dosyaya ulaþmak için FILE tipinde tanýmlama ve diðer dizi ve deðiþken tanýmlamalarý
	FILE * dosya;
	char veri[9999], veriyedek[9999];	//dosya elemanlarý için
	char parse[999][20];
	char txt[99];	//adres için
	char karakter;	//diziye eleman atmaya yardýmcý deðiþken
	int i = 0, j, flag, b1 = 0, //iki boyutlu parser dizisinin ilk boyunutu tutuyor
					    b2 = 0, //iki boyutlu parser dizisinin ikinci boyutunu tutuyor
						p = 0, //parser iþleminde satýr numarasýný tutuyor
						temp = 0;

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
		i++;	// boþluk karakterleri dahil eleman sayýsýný tutuyor
	}

	int k = 0;
	/*veri dizisinden boþluklarý eleyerek veriyedek dizisine geçildi
	eðer veri dizisinde boþluk, tab ve enter karakteri varsa bir sonraki elemana geç*/
	for (j = 0; j < i - 1; j++)
	{
		if (veri[j] != toascii(32) && veri[j] != toascii(10) && veri[j] != toascii(9))
		{
			veriyedek[k] = veri[j];
			//printf("%c,", veriyedek[k]);	// harf harf yazdýrma
			k++;	//boþluklar hariç karakter sayisini tutuyor
		}
	}

	printf("\n");

	printf("******************************** KAYNAK KOD  ********************************\n\n");
	//dosyanýn kendisini yazdýrma yani kaynak kod
	for (j = 0; j < i; j++)
	{
		printf("%c", veri[j]);
	}

	printf("\n******************************** TOKENIZER  ********************************\n");
	printf("\n{ ");	//yazdýrma iþlemi baþlarken aç parantez

	//tokenizer iþlemi
	for (j = 0; j < k; j++)
	{
		if (terminal(veriyedek[j]) == 1)
		{
			//burda ++ -- <= >= != == && || çiftli durumlarý kontrol ediliyor
			if (veriyedek[j] == '+' && veriyedek[j + 1] == '+' || veriyedek[j] == '-' && veriyedek[j + 1] == '-' ||
				veriyedek[j] == '=' && veriyedek[j + 1] == '=' || veriyedek[j] == '<' && veriyedek[j + 1] == '=' ||
				veriyedek[j] == '>' && veriyedek[j + 1] == '=' || veriyedek[j] == '=' && veriyedek[j + 1] == '=' ||
				veriyedek[j] == '+' && veriyedek[j + 1] == '=' || veriyedek[j] == '-' && veriyedek[j + 1] == '=' ||
				veriyedek[j] == '=' && veriyedek[j + 1] == '<' || veriyedek[j] == '=' && veriyedek[j + 1] == '>'
				//			 || veriyedek[j] == '=' && terminal(veriyedek[j + 1]) != 1 && harf(veriyedek[j + 1]) != 1
				//			 || terminal(veriyedek[j]) == 1 && terminal(veriyedek[j + 1]) == 1
				||
				(veriyedek[j]) != 1 && operand(veriyedek[j + 1]) == 1

		)
			{
				//veriyedek[j] ve veriyedek[j+1] þarlarý saðlýyorsa dizye at

				parse[b1][b2] = veriyedek[j];
				parse[b1][++b2] = veriyedek[j + 1];
				b1++;
				b2 = 0;
				j += 1;
			}
			else
			{
				//ikili operatör deðilse terminal fonksiyonu elemanýný diziye at
				parse[b1][b2] = veriyedek[j];
				b1++;
				b2 = 0;
			}
		}
		else if (noktalama(veriyedek[j]) == 1)
		{
			//çiftli durumlar kontrolü
			if (veriyedek[j] == '!' && veriyedek[j + 1] == '=' ||
				veriyedek[j] == '&' && veriyedek[j + 1] == '&' ||
				veriyedek[j] == '|' && veriyedek[j + 1] == '|')
			{
				parse[b1][b2] = veriyedek[j];
				parse[b1][++b2] = veriyedek[j + 1];
				b1++;
				b2 = 0;

				j = j + 1;
			}
			else if ((veriyedek[j]) == '"')
			{
				parse[b1][b2] = veriyedek[j];
				b1++;
				b2 = 0;
				//flag kontrolü iki çift arasýný tek token almak için yapýldý
				//flag 1 se gir çift týrnaða gelene kadar yaz flag = 0 yap ve whiledan çýk
				flag = 1;
				while (flag == 1)
				{
					if (veriyedek[j + 1] != '"')
					{
						parse[b1][b2] = veriyedek[j + 1];
						b2++;

						j += 1;
					}
					else
					{
						b1++;
						b2 = 0;

						parse[b1][b2] = veriyedek[j + 1];
						b1++;
						b2 = 0;
						j += 1;
						flag = 0;
					}
				}
			}
			else
			{
				//çift durum ve týrnak deðilse noktalama fonskiyonu elemanýný diziye at
				parse[b1][b2] = veriyedek[j];
				b1++;
				b2 = 0;
			}
		}
		else
		{
			//terminal ve noktalama elemanlarý hariç diðer karakterlerin gelme durumu

			parse[b1][b2] = veriyedek[j];

			//veriyedek[j+1] noktalama ve terminal fonksiyonu elemaný deðilse yaz sonra noktalama ve terminal elemaný gelene kadar j yi arttýrarak devam et
			while (noktalama(veriyedek[j + 1]) != 1 && terminal(veriyedek[j + 1]) != 1)
			{
				if (veriyedek[j + 1] == 'e' && veriyedek[j + 2] == 'l' && veriyedek[j + 3] == 's' && veriyedek[j + 4] == 'e' && veriyedek[j + 5] == 'i' && veriyedek[j + 6] == 'f')
				{
					b1++;
					b2 = 0;
					parse[b1][b2] = veriyedek[j + 1];
					parse[b1][++b2] = veriyedek[j + 2];
					parse[b1][++b2] = veriyedek[j + 3];
					parse[b1][++b2] = veriyedek[j + 4];
					parse[b1][++b2] = veriyedek[j + 5];
					parse[b1][++b2] = veriyedek[j + 6];
					b1++;
					b2 = 0;
					j += 6;
				}
				else if (veriyedek[j + 1] == 'e' && veriyedek[j + 2] == 'l' && veriyedek[j + 3] == 's' && veriyedek[j + 4] == 'e')
				{
					b1++;
					b2 = 0;
					parse[b1][b2] = veriyedek[j + 1];
					parse[b1][++b2] = veriyedek[j + 2];
					parse[b1][++b2] = veriyedek[j + 3];
					parse[b1][++b2] = veriyedek[j + 4];
					b1++;
					b2 = 0;
					j += 4;
				}
				else
				{
					parse[b1][++b2] = veriyedek[j + 1];
					j += 1;
				}
			}

			b1++;
			b2 = 0;

		}
	}

	//tokenizer yazdýrma kýsmý
	for (j = 0; j < b1; j++)
	{
		printf("%s,", parse[j]);
	}

	printf("}\n");	//yazdýrma iþlemi bittiksen sonra kapa parantez

	printf("\n********************************  PARSER  ********************************\n");

	//parser yazdýrma kýsmý
	for (j = 0; j < b1; j++)
	{
		printf("%s\n", parse[j]);
	}
	printf("\n********************************  HATA KISMI  ********************************");
	printf("\n\n");
	//Parser iþlemiminde satýrlara ne gelmesi gerektiði örnek
	/*
	0 - if
	1 - (
	2 - id
	3 - op
	4 - id
	5 -)
	6 - {
	7 - id
	8 - =
	9 - id
	10 - +|-|/|*|} 
	11 - id 
	12 - }

	13 - else if | else
	14 - (
	15 - id
	16 - op
	17 - id
	18 -)
	.
	.
	.
	.
	.

	*/
	// parse dizisinin ilk elemaný if se  (<id><op> < id>) kýsmý konrol edilir sonra doðruysa {cumle} kýsmý kontrol edilir. Hata varsa gerekli uyarýlar yapýlýr ve else, elseif kontrolüne geçilir
	if (parse[p][0] == 'i' && parse[p][1] == 'f' && parse[p][2] == '\0')
	{
		printf("%s", parse[p]);
		p++;
		if (parse[p][0] == '(')
		{
			printf("%s", parse[p]);
			p++;
			if (parse[p][0] != ')')
			{
				if (sart(parse, p) == 1)
				{
					p = 5;
					if (parse[p][0] == ')')
					{
						printf("%s", parse[p]);
						p++;
						if (parse[p][0] == '{' && parse[p][1] == '\0')
						{
							printf("%s", parse[p]);
							p++;
							if (cumle(parse, p) == 1)
							{
								j = 0;
								while (parse[j][0] != '}')
								{
									j++;
								}

								int suslusulu = j;

								//kapalý parantez cumle fonksiyonu icerisinde sart saglandiysa yazildi.
								p = suslusulu;
								p++;
								// else  ise  {cumle} kýsmý kontrol edilir. Hata varsa gerekli uyarýlar yapýlýr ve elseif kontrolüne geçilir
								if (parse[p][0] == 'e' && parse[p][1] == 'l' && parse[p][2] == 's' && parse[p][3] == 'e' && parse[p][4] == '\0')
								{
									printf("%s", parse[p]);
									p++;
									if (parse[p][0] == '{' && parse[p][1] == '\0')
									{
										printf("%s", parse[p]);
										p++;
										if (cumle(parse, p) == 1)
										{
											while (parse[p][0] != '}')
											{
												p++;
											}

											//kapalý parantez cumle fonksiyonu icerisinde sart saglandiysa yazildi.

											p++;
											if (parse[p][0] == '\0')
											{
												printf("\nKODUNUZ GRAMERE UYGUN (DOSYA DOGRU)");
											}
											else
											{
												printf("%s", parse[p]);
												printf("(Elseden sonra bisey gelemez)");
												hata();
											}
										}
										else
										{
											hata();
										}
									}
									else
									{
										printf("%s", parse[p]);
										printf("('{' gelmeli)");
										hata();
									}
								}

								//elseif se  (<id><op> < id>) kýsmý konrol edilir sonra doðruysa {cumle} kýsmý kontrol edilir. Hata varsa gerekli uyarýlar yapýlýr ve else, elseif kontrolüne geçilir
								else if (elseIf(parse, p) == 1)
								{
									while (parse[p][0] != '}')
									{
										p++;
									}

									//kapalý parantez cumle fonksiyonu icerisinde sart saglandiysa yazildi.

									p++;
									bool bir = false;
									//elseif in birden fazla gelme durumunda (<id><op> < id>) kýsmý konrol edilir sonra doðruysa {cumle} kýsmý kontrol edilir. 
									//Hata varsa gerekli uyarýlar yapýlýr ve else kontrolüne geçilir
									while (elseIf(parse, p) == 1)
									{
										bir = true;
										while (parse[p][0] != '}')
										{
											p++;
										}

										//kapalý parantez cumle fonksiyonu icerisinde sart saglandiysa yazildi.

										p++;

									}

									// else  ise  {cumle} kýsmý kontrol edilir. Hata varsa gerekli uyarýlar yapýlýr.
									if (parse[p][0] == 'e' && parse[p][1] == 'l' && parse[p][2] == 's' && parse[p][3] == 'e' && parse[p][4] == '\0')
									{
										printf("%s", parse[p]);
										p++;
										if (parse[p][0] == '{' && parse[p][1] == '\0')
										{
											printf("%s", parse[p]);
											p++;
											if (cumle(parse, p) == 1)
											{
												while (parse[p][0] != '}')
												{
													p++;
												}

												//kapalý parantez cumle fonksiyonu icerisinde sart saglandiysa yazildi.

												p++;
												//sonrasý boþsa
												if (parse[p][0] == '\0')
												{
													printf("\nKODUNUZ GRAMERE UYGUN (DOSYA DOGRU)");
												}
												else
												{
													printf("%s", parse[p]);
													printf("(Elseden sonra bisey gelemez)");
													hata();
												}
											}
											else
											{
												hata();
											}
										}
										else
										{
											printf("%s", parse[p]);
											printf("('{' gelmeli)");
											hata();
										}
									}
									else
									{
										//sonrasý boþsa
										if (parse[p][0] == '\0')
										{
											printf("\nKODUNUZ GRAMERE UYGUN (DOSYA DOGRU)");
										}
										else
										{
											if (bir == false)
											{
												printf("%s", parse[p]);
												printf("(Elseiften sonra sadece elseif veya else gelebilir)");
												hata();
											}
											else
											{
												printf("%s", parse[p]);
												printf("(Elseiften sonra sadece elseif veya else gelebilir)");
												hata();
											}
										}
									}
								}
								else
								{
									//sonrasý boþsa
									if (parse[p][0] == '\0')
									{
										printf("\nKODUNUZ GRAMERE UYGUN (DOSYA DOGRU)");
									}
									else
									{
										printf("%s", parse[p]);
										printf("(iften sonra sadece elseif veya else gelebilir)");
										hata();

									}
								}
							}
							else
							{
								hata();
							}
						}
						else
						{
							printf("%s", parse[p]);
							printf("('{' gelmeli)");
							hata();
						}
					}
					else
					{
						printf("%s", parse[p]);
						printf("(<sart> grameri saglandiysa kapa parantez gelmeli)");
						hata();
					}
				}
				else
				{
					hata();
				}
			}
			else
			{
				printf("%s", parse[p]);
				printf("(ifin ici bos kalamaz)");
				hata();
			}
		}
		else
		{
			printf("%s", parse[p]);
			printf("(Ac parantez hatasi)");
			hata();
		}
	}
	else
	{
		printf("%s", parse[p]);
		printf("(Hatali if yazimi veya ac parantez hatasi)");
		hata();
	}

	fclose(dosya);	//dosyayý kapat

	return 0;

}
