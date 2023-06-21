#include <stdio.h>
#define heshTblBoyutu 10


typedef struct strcOgrenciVerisi
{
	int Numara;
	char Ad[20];
	int Not;
}Ogrenci;


Ogrenci veri_liste[heshTblBoyutu]; 

int hash_tablo[heshTblBoyutu][2];	


void HeshTblOlustur()
{
	int i = 0;
	for (i=0; i < heshTblBoyutu; i++)
	{
		hash_tablo[i][0] = -1;
		hash_tablo[i][1] = -1;
	}
}

int HeshIndexFonksiyonu(int key)
{
	return key % heshTblBoyutu;
}

int BosIndex()
{
	int indx = -1;
	int i = 0;
	for (i = 0; i < heshTblBoyutu; i++)
	{
		if (hash_tablo[i][0] == -1)
		{
			indx = i;
			break;
		}
	}
	return indx; 
}

int OgrenciEkle(Ogrenci ogrVeri)
{
	int heshIndex = HeshIndexFonksiyonu(ogrVeri.Not); 
	
	if (hash_tablo[heshIndex][0] == -1)	
	{
		hash_tablo[heshIndex][0] = ogrVeri.Not;	
		veri_liste[heshIndex] = ogrVeri;	
	}
	else
	{
		while (hash_tablo[heshIndex][1]!=-1) 
		{
			heshIndex = hash_tablo[heshIndex][1];
		}
		
		hash_tablo[heshIndex][1] = BosIndex();	
		heshIndex = hash_tablo[heshIndex][1];
		
		if (heshIndex != -1)	
		{
			hash_tablo[heshIndex][0] = ogrVeri.Not;
			veri_liste[heshIndex] = ogrVeri;			
		}
	}
	return heshIndex; 
}

void DosyadanEkle()
{
	FILE* fp;
	
	if ((fp = fopen("Veri.txt", "r")) == NULL) {
		printf("Dosya açýlamadý");
	}
	else
	{
		Ogrenci ogrv = { 0,"",0 };	
		int adet = 0;
		
		while (fscanf(fp, "%d%s%d",&ogrv.Numara,ogrv.Ad,&ogrv.Not) != EOF) 
		{
			printf(" %d %s %d\n",  ogrv.Numara, ogrv.Ad, ogrv.Not); 
			
			if (OgrenciEkle(ogrv) == -1)
			{
				printf("< HesH tablosu doldu >");
				break;
			}
			adet++;
		}
		fclose(fp);
		printf("Dosyadan Eklenen Kayit :%d\n",adet);
	}

}

int Ara(int key)
{
	int heshIndex = HeshIndexFonksiyonu(key); 
	int adim = 0;
	
	do
	{
		if (hash_tablo[heshIndex][0] == key)
		{
			adim++;
			printf("%d Adimda bulundu ->  %d %s %d\n", adim, veri_liste[heshIndex].Numara, veri_liste[heshIndex].Ad, veri_liste[heshIndex].Not);
			break;
		}
		else
		{
			if (hash_tablo[heshIndex][1] == -1)
			{
				adim = -1;
				printf("Kayit bulunamadi....!\n");
				break;
			}
			else
			{
				heshIndex = hash_tablo[heshIndex][1];
				adim++;
			}
		}
	} while (adim< heshTblBoyutu);
	
	return adim;
}


void HeshTblListele()
{
	int i = 0;
	for (i = 0; i < heshTblBoyutu; i++)
	{
		printf("%d <> %d <> %d         %d %s %d\n",i, hash_tablo[i][0], hash_tablo[i][1], veri_liste[i].Numara, veri_liste[i].Ad, veri_liste[i].Not);
	}
}

void main()
{
	
	HeshTblOlustur();
	int sec = 0;
	int notlar = 0;
	Ogrenci ogrv = { 0,"",0 };
	
	do
	{
		printf("\n\n1- Kayit Ekle\n");
		printf("2- Dosyadan Kayit Ekle(Veri.txt)\n");
		printf("3- Ara\n");
		printf("4- Hesh tablosunu ve verileri listele\n");
		printf("5- Cikis\n\n");
		printf("    Seciminiz ..:");
		scanf("%d", &sec);
		switch (sec)
		{
		case 1:
			printf("\n   Numara .:"); scanf("%d", &ogrv.Numara);
			printf("   Adi ....:"); scanf("%s", ogrv.Ad);
			printf("   Notu ...:"); scanf("%d", &ogrv.Not);
			if (OgrenciEkle(ogrv) == -1)
			{
				printf("Hesh tablosu dolu oldugu icin kayit eklenemedi!......\n");
			}
			else
			{
				printf("Kayit eklendi\n");
			}
			break;
		case 2:
			DosyadanEkle();
			break;
		case 3:
			printf("   Aranan Not ...:"); scanf("%d", &notlar);
			Ara(notlar);
			break;
		case 4:
			HeshTblListele();
			break;
		}


	} while (sec != 5);
	printf("   !....... Hoscakal .......!\n\n");
}
