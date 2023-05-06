#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

struct OGRENCI {
    char adSoyad[100];
    int okulNo;
    int sifre;
    int parola;
    int anahtar;
    FILE* dosya;
}ogrenciBilgi;

bool sifrele(char* ogrenci, int anahtar, FILE* dosya);

int asalCapranýBul();

void sifrecoz(char* ogrenci, int anahtar, FILE* dosya);

bool dosyaYaz(char* bilgi);

char* dosyaOku();

bool dosyaSil();


int main(void)
{
    ogrenciBilgi.anahtar = 8; //202802068
    ogrenciBilgi.dosya = fopen("SezarSifreleme.txt", "w+");
    secimgiris:
    printf("          SEZAR SIFRELEME UYGULAMASI          \n\n\n");

    printf("       BILGI GIRISI YAPMAK ICIN 1       \n");
    printf("       ASAL CARPANI BULMAK ICIN 2       \n");
    printf("       SIFRE COZMEK ICIN 3       \n");
    printf("       DOSYAYI SILMEK ICIN 4       \n");

    int secim;
    scanf("%d", &secim);

    switch (secim)
    {
    case 1:
        printf("\n\n       BILGILERI DOLDURUNUZ       \n\n");

        printf("Ogrencinin Adi Soyadi: ");
        gets(ogrenciBilgi.adSoyad, sizeof(ogrenciBilgi.adSoyad), stdin);


        printf("\nOgrencinin Numarasi: ");
        scanf("%d", &ogrenciBilgi.okulNo);
         

        printf("\nSifre Gir: ");
        scanf("%d", &ogrenciBilgi.sifre);

        if ((sifrele(ogrenciBilgi.adSoyad, ogrenciBilgi.anahtar, ogrenciBilgi.dosya)) == true)
        {
            printf("\nSIFRELEME BASARILI\n");
        }
        else
        {
            printf("\nSIFRELEME BASARISIZ\n");
        }
        break;
    case 2:
        printf("\n       PAROLA COZUM ISLEMI     \n\n");

        printf("Ogrenci Numaraniz Nedir?\n");
        scanf("%d", &ogrenciBilgi.okulNo);

        printf("Ogrenci Parolaniz : %d",asalCapranýBul());
        break;
    case 3:
        printf("\n\n       SIFRE COZME ISLEMI     \n\n");
    parolagiris:
        printf("Ogrenci Numaranizin En Buyuk Asal Carpani Nedir?\n");
        scanf("%d", &ogrenciBilgi.parola);

        if (ogrenciBilgi.parola == 1)
        {
            printf("PAROLA : ");
            scanf("%d", &ogrenciBilgi.parola);
            if (ogrenciBilgi.parola == asalCapranýBul(ogrenciBilgi.okulNo))//Kullanicidan alinan deger metot ciktisina esit ise
            {
                sifrecoz(ogrenciBilgi.adSoyad, ogrenciBilgi.anahtar, ogrenciBilgi.dosya);//Sifre cozumleme metotu calisiyor

                fclose(ogrenciBilgi.dosya);//Acik dosya kapatiliyor
                remove("OgrenciSifreleri.txt");//Dosya bilgisayardan siliniyor
            }
            else
            {
                printf("\n**Hatali parola girdiniz!");
                goto parolagiris;
            }
        }
        else
        {
            printf("HATALI KODLAMA, program sonlandiriliyor...");

            if (dosyaSil())
            {
                exit(1);
            }
            else
            {
                printf("DOSYA SILINEMEDI");
            }

        }
        break;
    case 4:
        if (dosyaSil())
        {
            exit(1);
        }
        else
        {
            printf("DOSYA SILINEMEDI");
        }
        break;
    default:
        printf("HATALI GIRIS YAPTINIZ!");
        goto secimgiris;
        break;
    }

    
}

bool dosyaYaz(char* ogrenci)
{
    fputs(ogrenci, ogrenciBilgi.dosya);
    return true;
}

char* dosyaOku() {

    return fgets(ogrenciBilgi.adSoyad, sizeof(ogrenciBilgi.adSoyad), ogrenciBilgi.dosya);
}

bool sifrele(char* ogrenci, int anahtar, FILE* dosya)
{
    char* p = ogrenci;
    bool durum = false;
    while (*p != '\0')
    {
        if (isupper(*p))
        {
            *p = ((*p - 65 + anahtar) % 26) + 65;
        }
        else if (islower(*p))
        {
            *p = ((*p - 97 + anahtar) % 26) + 97;
        }
        p++;
    }
    durum = dosyaYaz(ogrenci);
    fputs(ogrenci, dosya);
    rewind(dosya);
    return durum;
}

int asalCapranýBul(okulNo)
{
    int x = 0, i = 2;

    while (ogrenciBilgi.okulNo > 1)
    {
        while (ogrenciBilgi.okulNo % i == 0)
        {
            if (i > x)
            {
                x = i;
            }
            ogrenciBilgi.okulNo = ogrenciBilgi.okulNo / i;
        }
        i++;
    }
    return x;
}

void sifrecoz(char* ogrenci, int anahtar, FILE* dosya)
{
    char* temp = ogrenci;
    while (*temp != '\0')
    {
        if (isupper(*temp))
        {
            *temp = ((*temp - 65 + (26 - anahtar)) % 26) + 65;
        }
        else if (islower(*temp))
        {
            *temp = ((*temp - 97 + (26 - anahtar)) % 26) + 97;
        }
        temp++;
    }
    printf(ogrenciBilgi.adSoyad, " adli ogrencinin Sifresi: %s\n", ogrenci);//Sifresi cozulmus metin ekrana yaziliyor
}

bool dosyaSil() {
    fclose(ogrenciBilgi.dosya);
    remove("OgrenciSifreleri.txt");
    return true;
}