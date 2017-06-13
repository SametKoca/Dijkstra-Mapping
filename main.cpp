/**
   Samet KOCA 140202037

   Internetten yararlandigim kod parçasi :

   http://www.zafercomert.com/Medya/2015_05_11_2_121_69f9a888.pdf

   PDF dosyasindaki 3. ve 4. sayfalardadir.

   Dikkat edilmesi gerekenler :

   1 - Kullanilacak txt dosyalarinin isimleri "sehir kod.txt" ve "sehir mesafe.txt"
   olmasi gerekir. Aksi takdirde txt den okuma yapamaz.

   2 - Haritanin düzgün bir sekilde calismasi için sehir isimlerinin uygun formatta olmasi gerek.
   Sehirlerin bas harfleri büyük diger hafleri ise küçük olarak yazilacakdir.

   3 - "sehir kod.txt" dosyasindaki sehirlerin isimleri ile "sehir mesafe.txt" dosyasindaki sehir
   isimleri birbirinden farkli olamaz.
   Örnegin birinde "Afyon" digerinde "Afyonkarahisar" yazamaz. Yoksa düzgün sonuç alinamaz.

   4- Harita asamasinda sorun yasamamak için sehir isimleri türkce harflerle yazilacakdir.
   Örnegin "Nigde" yerine "Niğde" yazilmasi lazim. Yumusak g kullanilmazsa haritada o sehiri bulamaz.

   5 - Bazi sehirlerin iki farkli ismi vardir. Bazi sehirlerde kisaltilarak kullanilabilir.
   Bu yüzden harita kullaniminda sorun olmamasi için bunlarin bir kural içinde yazilmasi gerek.

   "Afyonkarahisar" yerine "Afyon" yazilicak.
   "Antep" yerine "Gaziantep" yazilicak.
   "Maras" yerine "Kahramanmaras" yazilicak.
   "Urfa" yerine "Sanliurfa" yazilicak.
   "Icel" yerine "Mersin" yazilicak.
   "Izmit" yerine "Kocaeli" yazilicak.
   "Adapazari" yerine "Sakarya" yazilicak.
   "Antakya" yerine "Hatay" yazilicak.

   Klasör içinde "Harita.txt" adinda bir dosya daha olusturuldu. Bu dosya program tarafindan çekilip
   haritada sehir isimlerine göre kordinatlarini tutar. Böylece program içinde bütün sehirleri tanimlamak
   yerine txt üzerinde 81 il ve kodlari program içindeki struct a atiliyor.

*/

#include <stdio.h>
#include <locale.h> /// Türkçe karakter kullanmak için
#include <string.h>
#include <graphics.h>
#include <stdlib.h>

///"sehir kod.txt" dosyasini attigimiz bagli liste
struct dugum{

    char Sehir[50];
    int Sehirkod;
    struct dugum *sonraki;
    struct dugum *onceki;
};

///"sehir mesafe.txt" dosyasini attigimiz bagli liste
struct dugum2{

    char Sehir1[50];
    char Sehir2[50];
    int Uzaklik;
    struct dugum2 *sonraki;
    struct dugum2 *onceki;
};

///"Harita.txt" dosyasini attigimiz bagli liste
struct dugum3{

   char Sehir[50];
   int x;
   int y;
   struct dugum3 *sonraki;
   struct dugum3 *onceki;
};

///"sehir kod.txt" dosyasindakileri bagli listeye ekleme islemini yapiyor.
void Ekle1(struct dugum **bas,struct dugum **son,char Sehir[],int Sehirkod)
{
    struct dugum *yeni = (struct dugum*) malloc(sizeof(struct dugum));

    strcpy(yeni->Sehir,Sehir);
    yeni->Sehirkod = Sehirkod;

    if(Sehirkod != 0)  /// txt dosyasinda ilk satirda sehrin kodunun olmasi  gereken yerde
    {                  /// "Kod" yaziyor. Bunu atoi() ile almak istedigimizde 0 dönüyor.
       if(*bas == NULL)/// Böylece ilk satiri bagli listeye almiyoruz.
       {
           yeni->sonraki = NULL;
           yeni->onceki = NULL;
           *bas = *son = yeni;
       }
       else
       {
           yeni->sonraki = NULL;
           yeni->onceki = *son;
           (*son)->sonraki = yeni;
           *son = yeni;
       }
    }
}

/// "sehir mesafe.txt" dosyasindakileri bagli listeye ekleme islemini yapiyor.
void Ekle2(struct dugum2 **bas2,struct dugum2 **son2,char Sehir1[],char Sehir2[],int Uzaklik)
{
    struct dugum2 *yeni = (struct dugum2*) malloc(sizeof(struct dugum2));

    strcpy(yeni->Sehir1,Sehir1);
    strcpy(yeni->Sehir2,Sehir2);
    yeni->Uzaklik = Uzaklik;

    if(Uzaklik != 0)     /// txt dosyasinda ilk satirda sehrin mesafesi olmasi gereken yerde
    {                    /// "Mesafe" yaziyor. Bunu atoi() ile almak istedigimizde 0 dönüyor.
       if(*bas2 == NULL) /// Böylece ilk satiri bagli listeye almiyoruz.
       {
           yeni->sonraki = NULL;
           yeni->onceki = NULL;
           *bas2 = *son2 = yeni;
       }
       else
       {
           yeni->sonraki = NULL;
           yeni->onceki = *son2;
           (*son2)->sonraki = yeni;
           *son2 = yeni;
       }
    }
}

/// "Harita.txt" dosyasindakileri bagli listeye ekleme islemini yapiyor.
void Ekle3(struct dugum3 **bas3,struct dugum3 **son3,char Sehir[],int x,int y)
{
    struct dugum3 *yeni = (struct dugum3*) malloc(sizeof(struct dugum3));

    strcpy(yeni->Sehir,Sehir);
    yeni->x = x;
    yeni->y = y;
    if(x != 0)           /// txt dosyasindaki ilk satirda sehrin  x kordinati olmasi gereken yerde
    {                    /// "Kodx" yaziyor. Bunu atoi() ile almak istedigimizde 0 dönüyor.
       if(*bas3 == NULL) /// Böylece ilk satiri bagli listeye almiyoruz.
       {
           yeni->sonraki = NULL;
           yeni->onceki = NULL;
           *bas3 = *son3 = yeni;
       }
       else
       {
           yeni->sonraki = NULL;
           yeni->onceki = *son3;
           (*son3)->sonraki = yeni;
           *son3 = yeni;
       }
    }
}

int main()
{
    /// Kodlarin oldugu dügüm
    struct dugum *bas = NULL;
    struct dugum *son = NULL;

    /// Mesafelerin oldugu dügüm
    struct dugum2 *bas2 = NULL;
    struct dugum2 *son2 = NULL;

    /// Kordinatlarin oldugu dügüm
    struct dugum3 *bas3 = NULL;
    struct dugum3 *son3 = NULL;

    setlocale(LC_ALL,"Turkish"); /// Türkçe karakter kullanmak için

    FILE *dosya; /// txt dosyalarini açmak için tanimladik
    int SONSUZ = 99999; ///Ulasamadigimiz yerlere sonsuz atiyicaz
    char kelime[50]; /// Satiri parçalamak için kelimeye aticaz
    char *kelime2;   /// Parçalanan string
    char *sehir,*sehir1,*sehir2; /// Kod için *sehir 'e mesafeler için *sehir1 ve *sehir2 ihtiyacimiz var.
    int sayi;  ///Parçaladigimiz kodu sayiya atarak Ekle fonksiyonuna atiyoruz.
    int Mesafe;    ///Masafe degerlerini atiyoruz.
    int sayac = 0; ///Sehir sayisini atiyoruz.
    int num1=0,num2=0,Check1,Check2;  ///Komsuluk matrisini olustururken kullanilan degiskenler
    int sec=0,SehirS,secx;  ///sec = Kullanicinin seçtigi sehrin kodu,SehirS = Þehir sayisi,secx = sec islemde degisecegi için sec i tutar.
    int i,j,k; ///For döngüleri için kullanildi.
    int EK; ///En küçük deger. Ilk etapda buna sonsuz atanicak.
    int Kodx,Kody,Koda,Kodb; ///Kordinatlari tutan degiskenler.
    int Dugumx,Dugumy,sec2=0; /// Kullanicinin ilk seçtigi sehrin kordinatlarini tutar. sec2 = Kullanicinin seçtigi ikinci sehir.
    int Dugum2x,Dugum2y;   /// Kullanicinin ikinci seçtigi(seçerse) sehrin kordinatlarini tutar.

    dosya = fopen("sehir kod.txt","r"); /// Dosya açildi.

    if(dosya == NULL)
    {
        printf("Dosya Bulunamadi.");
    }
    else
    {
        while(!feof(dosya))
        {
            fscanf(dosya,"%s",&kelime); /// String okundu.
            kelime2 = strtok(kelime,"-"); /// "-" isaretine göre parçalandi.
            while(kelime2!=NULL) /// String bitine kadar.
            {
                sehir = kelime2; /// Ilk parça sehir.
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi.
                sayi = atoi(kelime2); /// Ikinci parça kodu.
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi.
                Ekle1(&bas,&son,sehir,sayi); ///Birinci bagli listeye eklendi.

            }
        }
    }

    fclose(dosya); /// Dosya kapandi.

    struct dugum *e;
    i=0;
    for(e = bas;e!=NULL;e=e->sonraki) /// Kullanici için sehir ve kodlari ekrana yazildi.
    {
        i++;
        printf("%s     \t",e->Sehir);
        printf("%5d \t",e->Sehirkod);
           if(i%3==0) ///Her 3 sehir yazinca bir alt satira geç.
            printf("\n");

    }

    printf("\n");

    dosya = fopen("sehir mesafe.txt","r"); ///Dosya açildi.

    if(dosya == NULL)
    {
        printf("Dosya Bulunamadi.");
    }
    else
    {
        while(!feof(dosya))
        {
            fscanf(dosya,"%s",&kelime); ///String okundu.
            kelime2 = strtok(kelime,"-"); /// "-" isaretine göre parçalandi.
            while(kelime2!=NULL) /// String bitine kadar.
            {
                sehir1 = kelime2; /// Birinci sehir
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi
                sehir2 = kelime2; /// Ikinci sehir
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi
                Mesafe = atoi(kelime2); /// Aralarindaki mesafe
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi
                Ekle2(&bas2,&son2,sehir1,sehir2,Mesafe); /// Ikinci bagli listeye eklendi.
            }
        }
    }

    fclose(dosya); /// Dosya kapandi.

    dosya = fopen("Harita.txt","r"); /// Dosya açildi.

    if(dosya == NULL)
    {
        printf("Dosya Bulunamadi.");
    }
    else
    {
        while(!feof(dosya))
        {
            fscanf(dosya,"%s",&kelime); /// String okundu.
            kelime2 = strtok(kelime,"-"); /// "-" isaretine göre parçalandi.
            while(kelime2!=NULL) /// String bitene kadar
            {
                sehir = kelime2; /// Sehir
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi
                Kodx = atoi(kelime2); /// X kodu
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi
                Kody = atoi(kelime2); /// Y kodu
                kelime2 = strtok(NULL,"-"); /// Parçalama islemi
                Ekle3(&bas3,&son3,sehir,Kodx,Kody); /// Üçüncü bagli listeye eklendi.
            }
        }
    }

    fclose(dosya); /// Dosya kapandi.

    struct dugum *e2; /// Sehir sayisi bulundu.
    for(e2 = bas;e2!=NULL;e2=e2->sonraki)
       sayac++;

    SehirS = sayac; /// Sehir sayisini SehirS degiskenine atadik.

    int KM[SehirS][SehirS]; /// Komsuluk Matrisi
    int YOOL[SehirS][SehirS]; /// Her sehrin geçtigi illeri tuttugumuz matris
    int Maliyet[SehirS];  /// En kisa yoldan gidis maliyetlerinin tutuldugu dizi
    int Gidilen[SehirS]; /// Bir sehire tekrar gitmemek için gittigimiz sehirleri tutuyoruz.
    int Secim; /// Ilk 2 seçenekden seçtigimiz seçim. 1 yada 2 olabilir yoksa islem yapmaz.
    int HATA = 0; /// Hata kontrolü yapar. Hata varsa bu geger 1 olucak.

    for(i=0;i<SehirS;i++) /// En basta hiç bir sehire gidilmedi. Hepsi 0.
        Gidilen[i] = 0;


    for(i=0;i<SehirS;i++) /// Komsuluk matrisine önce -1 atiliyor. KM olustugunda mesaflerin oldugu yerlere mesafe yazilicak.
    {                     /// Mesafe yoksa yani ulasilamiyorsa -1 olarak kalicak.
        for(j=0;j<SehirS;j++)
        {
            KM[i][j] = -1;
        }
    }

    struct dugum2 *q;
    struct dugum *w;

    Check1 = 0;
    Check2 = 0;

    for(q = bas2;q!=NULL;q=q->sonraki)
    {
        for(w = bas;w!=NULL;w=w->sonraki)
        {
            if(!strcmp(q->Sehir1,w->Sehir))
            {
                num1 = w->Sehirkod;
                Check1 = 1; /// Sehir1 in kodu alindi.
            }

            if(!strcmp(q->Sehir2,w->Sehir))
            {
                num2 = w->Sehirkod;
                Check2 = 1; /// Sehir2 nin kodu alindi.
            }

            if(Check1 == 1 && Check2 == 1) /// Komusuk matrisine atildi.
            {
                KM[num1-1][num2-1] = q->Uzaklik;
                KM[num2-1][num1-1] = q->Uzaklik; ///Simetrisine de ayni mesafe atandi. Yani KM[1][2] ve KM[2][1] ayni sayidir.
                Check1 = 0;
                Check2 = 0;
            }
        }
    }


    printf("\n1 - BIR SEHRIN DIGER SEHIRLERE UZAKLIGI \n");
    printf("\n2 - BIR SEHRIN BASKA BIR SEHIRE UZAKLIGI \n");
    printf("\nSECIM : "); scanf("%d",&Secim);
    printf("\n");

    if(Secim == 1)
    {
        printf("ISTEDIGINIZ SEHRIN KODUNU GIRINIZ : "); scanf("%d",&sec);

        if(sec < 0 || sec > SehirS) /// Hata Kontrolü
        {
            printf("\nBOYLE BIR SEHIR YOK!");
            HATA = 1;
        }

    }

    else if(Secim == 2)
    {
        printf("BIRINCI SEHRIN KODUNU GIRINIZ : "); scanf("%d",&sec);

        if(sec < 0 || sec > SehirS) /// Hata Kontrolü
        {
            printf("\nBOYLE BIR SEHIR YOK!");
            HATA = 1;
        }

        if(HATA != 1) /// Ilk sehir de hata varsa ikinci sehiri isteme
        {
            printf("IKINCI SEHRIN KODUNU GIRINIZ : "); scanf("%d",&sec2);
        }

        if((sec2 < 0 || sec > SehirS) && HATA != 1) /// Hata Kontrolü
        {
            printf("\nBOYLE BIR SEHIR YOK!");
            HATA = 1;
        }
    }
    else
    {
        printf("\nHATALI SECIM\n"); /// Kullanici 1 yada 2 yi seçmelidir.
    }

    secx=sec; /// sec döngü içinde degisecegi için ve kullanicinin seçtigi sehri unutmamak için secx de tutuldu.
    sec=sec-1; /// Her sehrin matrisdeki yeri kendi kodundan 1 eksigidir. Ankara nin kodu 1 ise matrisde 0. satirdir.
    sec2=sec2-1; ///Ikinci sehirde de ayni islemler yapilir. Ikinci sehir bidaha tutulmaz çünkü üstünde degisme olmayacak.

    for(i=0;i<SehirS;i++) ///Bütün sehirlerin gittigi yollara önce -1 atiyoruz. -1 o sehire gitmedigini gösterir.
    {
        for(j=0;j<SehirS;j++)
        {
            YOOL[i][j] = -1;
        }
    }

    Maliyet[sec]=0; /// Seçtigimiz sehre gidis maliyeti 0 olmalidir.

    for(i=0;i<SehirS;i++) /// Sectigimiz sehir hariç diger sehrilere basta sonsuz uzaklikta.
    {
        if(i != sec)
        {
            Maliyet[i]=SONSUZ; /// Önceki maliyet kontrolü yapildigi için en büyük deger yani sonsuz atanmasi gerek.
        }

    }

    for(i=0;i<SehirS;i++)
    {
        for(j=0;j<SehirS;j++)
        {
            if(Gidilen[j] == 0 && KM[sec][j] != -1) /// O sehire gidilmediyse ve komsuluk varsa
            {
                    if(Maliyet[j] > KM[sec][j] + Maliyet[sec]) /// Maliyet önceki maliyetten daha azsa.
                    {
                        Maliyet[j] = KM[sec][j] + Maliyet[sec]; /// O sehrin yeni maliyeti

                        for(k=0;k<SehirS;k++)
                        {
                            YOOL[j][k] = YOOL[sec][k]; /// Maliyet degistigine göre o sehre gidilmis demektir.
                        }          /// Önceki sehrin gidis yollarini yeni sehrin gidis yollarina kopyaliyoruz.

                        k=0;
                        while(1)
                        {
                            if(YOOL[j][k] == -1)
                            {
                                YOOL[j][k] = sec+1; /// O sehre gidildigine göre YOOL matrisindeki bir sonraki -1 e
                                break;              ///sehrin kodunu at. Bidahaki -1 e atmamasi için break ile çik.
                            }
                            k++;
                        }
                    }
            }
        }

        EK = SONSUZ; ///En kisa yol basta sonsuz.
        for(j=0;j<SehirS;j++)
        {
            if(Gidilen[j] == 0 && Maliyet[j] < EK) /// Gidilmemisse ve Maliyeti sonsuzdan azsa
            {
                EK = Maliyet[j]; /// En az gittigi maliyet ek olarak degisecek
                sec = j; /// Bir sonraki gittigi sehir j olucak
            }
        }

        Gidilen[sec] = 1 ; /// O sehire gidildigi için onun indisine -1 atanicak.
    }



    struct dugum *es;

    if(Secim == 1 && HATA != 1) /// Kullanici 1 i seçtiyse
    {
        for(k=0;k<SehirS;k++)
        {
            for(e=bas;e!=NULL;e=e->sonraki)
            {
                if(e->Sehirkod == k+1)      /// Sehiler yazildi
                   printf("%s    ",e->Sehir);
            }

            if(Maliyet[k]==0 && k==secx-1) /// sEçilen sehirse
            {
                printf("\t=   SECTIGINIZ SEHIR");
            }

            else if(Maliyet[k]==0 && k!=secx-1) /// O sehire gidilemiyorsa
            {
                printf("\t=   YOL YOK!");
            }

            else
            {
                printf("\t= %5d    ",Maliyet[k]); /// Maliyetleri yaz
            }

            for(i=0;i<SehirS;i++)
            {
                if(YOOL[k][i] != -1)
                {
                    for(es=bas;es!=NULL;es=es->sonraki)  /// Geçtigi sehrileri yaz
                    {
                        if(es->Sehirkod == YOOL[k][i])
                        {
                            printf("%s   ",es->Sehir);
                        }
                    }
                }
            }
            printf("\n");
        }
    }

    if(Secim == 2 && HATA != 1) /// Secim 2 ise
    {
        for(k=0;k<SehirS;k++)
        {
            if(k==sec2) /// Sadece ulasmak istedigi sehri yaz
            {
                for(e=bas;e!=NULL;e=e->sonraki)
                {
                    if(e->Sehirkod == secx)
                       printf("%s ILE ",e->Sehir);
                }

                for(e=bas;e!=NULL;e=e->sonraki)
                {
                    if(e->Sehirkod == sec2+1)
                       printf("%s ARASI TOPLAM",e->Sehir);
                }

                printf(" = %d KMDIR.\n",Maliyet[k]);
                printf("\nGECILEN SEHIRLER : \n");

                for(i=0;i<SehirS;i++)
                {
                    if(YOOL[k][i] != -1)
                    {
                        for(es=bas;es!=NULL;es=es->sonraki)
                        {
                            if(es->Sehirkod == YOOL[k][i])  /// O sehire giderken geçtigi sehirler
                               printf("%s   ",es->Sehir);
                        }
                    }
                }
            }
        }
    }

    struct dugum  *e1;
    struct dugum3 *e3;
    for(e1=bas;e1!=NULL;e1=e1->sonraki)
    {
        if(e1->Sehirkod == secx)
        {
            for(e3=bas3;e3!=NULL;e3=e3->sonraki)
            {
               if(strcmp(e1->Sehir,e3->Sehir)==0) /// Seçtigimiz ilk sehrin kordinatlari aliniyor.
               {
                   Dugumx = e3->x;
                   Dugumy = e3->y;
               }
            }
        }
    }

    for(e1=bas;e1!=NULL;e1=e1->sonraki)
    {
        if(e1->Sehirkod == sec2+1)
        {
            for(e3=bas3;e3!=NULL;e3=e3->sonraki)
            {
               if(strcmp(e1->Sehir,e3->Sehir)==0) /// Seçtigimiz ikinci sehrin(seçildiyse) kordinatlarini aliyor.
               {
                   Dugum2x = e3->x;
                   Dugum2y = e3->y;
               }
            }
        }
    }

    if((Secim == 1 || Secim == 2) && HATA != 1)
    {
        initwindow(1499,777,"Turkiye Haritasi"); /// Grafik ekranini açiyor
        readimagefile("Turkiye.bmp",0,0,1499,797); /// "Turkiye.bmp" dosyasini açiyor

        setlinestyle(0,1,3); /// Çizgi kalinligini ayarliyor

        setcolor(0); /// Renk siyah seçildi


        for(i=0;i<SehirS;i++)
        {
            for(j=0;j<SehirS;j++)
            {
                if(YOOL[i][j] != -1) /// Yol oldugu sürece
                {
                    for(e1=bas;e1!=NULL;e1=e1->sonraki)
                    {
                        if(YOOL[i][j+1] == -1) /// O sehirden sonra baska bir yere gitmediyse
                        {
                            if(i+1 == e1->Sehirkod) /// Birinci sehir aliniyor
                               sehir1 = e1->Sehir;

                            if(YOOL[i][j] == e1->Sehirkod) /// Ikinci sehir aliniyor
                               sehir2 = e1->Sehir;
                        }

                        else
                        {
                            if(YOOL[i][j+1] == e1->Sehirkod) /// Birinci sehir aliniyor
                               sehir1 = e1->Sehir;

                            if(YOOL[i][j] == e1->Sehirkod) /// Ikinci sehir aliniyor
                               sehir2 = e1->Sehir;
                        }
                    }

                    for(e3=bas3;e3!=NULL;e3=e3->sonraki)
                    {
                        if(strcmp(e3->Sehir,sehir1)==0) /// Birinci sehrin kodlarini ariyip aliyor
                        {
                            Kodx = e3->x;
                            Kody = e3->y;
                        }
                        if(strcmp(e3->Sehir,sehir2)==0) /// Ikinci sehrin kodlarini ariyip aliyor
                        {
                            Koda = e3->x;
                            Kodb = e3->y;
                        }
                    }

                    if(Secim == 1) /// Secim 1 ise hepsini ekrana çizdir
                    {
                        line(Kodx,Kody,Koda,Kodb); ///Çizdirme fonksiyonu

                        for(k=0;k<=10;k++)
                           circle(Kodx,Kody,k); ///Içi dolu çember yerine iç iç farkli yariçapli çemberler çizer
                    }

                    if(Secim == 2) /// Seçim 2 ise sadece ikinci sehir ile baglantisini çizdir
                    {
                        if(i == sec2)
                        {
                            line(Kodx,Kody,Koda,Kodb); /// Çizdirme fonksiyonu

                        for(k=0;k<=10;k++)
                           circle(Kodx,Kody,k); /// Içi dolu daire olusturur
                        }
                    }
                }
            }
        }

        setcolor(4); /// Kirmizi rengi seçtik. Çünkü seçilen sehirler kirmizi olucak.

        for(k=0;k<=10;k++)
            circle(Dugumx,Dugumy,k); /// Kirmizi daire çiziliyor ilk seçtigimiz sehire

        setcolor(0); ///Ikinci sehir yoksa tekrar renk siyah olucak

        if(Secim == 2)
        {
            setcolor(4);

            for(k=0;k<=10;k++)
               circle(Dugum2x,Dugum2y,k); /// Kirmizi daire çiziliyor ikinci seçtigimiz sehire

        }

        while(1){} /// Haritanin ekranda kalmasi için

        closegraph(); /// Grafik kapatma fonksiyonu
    }

    return 0;
}
