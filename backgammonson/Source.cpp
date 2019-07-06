//kýrýlma noktalarýna taþ gelmesini engelle
//onceki yerdeki taþý azalt
//kýrýlma þeyine bak onda hata var
//foto yüklemede sýkýntý var
//toplama kýsmýna da bir bak
#include <allegro.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
void Baslat();
void Bitir();
int tavla[28] = { 0, 2, 0, 0, 0, 0, -5, 0, 0, -3, 0, 0, 0, 5, -5, 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, -2, 0 };
int tavlabastan[28] = { 0, 2, 0, 0, 0, 0, -5, 0, 0, -3, 0, 0, 0, 5, -5, 0, 0, 0, 3, 0, 0, 5, 0, 0, 0, 0, -2, 0 };
int zar[6] = { 1, 2, 3, 4, 5, 6 };
int gelen_zar[4] = { 0, 0, 0, 0 };
int elde = 0, konum = 0, onceki = 0;//elde elimizdeki tas//önceki da belirlenen konum oluyo //konum tası koyacagimiz veya aldıgımız yer
int x, y;
int k = 0;
int scor[2] = { 0, 0 };
int yazi_x = 600, yazi_y = 0;
int dur = 0;
BITMAP *Tavla, *siyah, *beyaz, *a1, *a2, *a3, *a4, *a5, *a6, *siyahinsirasi, *beyazinsirasi, *tavlabaslangic, *scorbeyaz, *scorsiyah, *AraKatman;
void Mesaj(char yazi[])
{
	yazi_y += 10;
	textprintf_ex(screen, font, yazi_x, yazi_y, makecol(255, 0, 0), -1, yazi);
	rest(300);
}
void degerdon()
{

	int i;
	int d = 5;
	for (i = 0; i < 28; i++)
	{
		textprintf_ex(screen, font, d, 485, makecol(255, 0, 0), -1, "%d    ", tavla[i]);
		d += 20;
	}



}
void scorkontrol()
{
	int i;
	if (tavla[0] == -15)
	{
		scor[1]++;
		for (i = 0; i < 28; i++)
			tavla[i] = tavlabastan[i];
		elde = 0;
		onceki = 0;
		konum = 0;


	}
	else if (tavla[27] == 15)
	{
		scor[0]++;
		for (i = 0; i < 28; i++)
			tavla[i] = tavlabastan[i];
		elde = 0;
		onceki = 0;
		konum = 0;

	}


}
bool sirakontrol()//durum true ise sýra diðerine gececek bu da nasýl oluyo k++ oluyo biz k ya göre yapacaz..
{
	int i;

	bool drm = false;
	for (i = 0; i < 4; i++)
	{
		if (gelen_zar[i] != 0)
			return drm;
	}
	drm = true;
	k++; //sýra diðerine geciyor

	/*clear_bitmap(Tavla);
	blit(Tavla, screen, 0, 0, 0, 0, 900, 500);
	Tavla = load_bitmap("sungam.bmp", NULL);*/

	return drm;
}
void kirilmakontrol()
{

	//kýrýk taþ var 
	//ikisinin de kýrýk taþý olabilir. sýranýn kimde olduðu önemli
	//if (k % 2 == 0)// eðer beyazýn sýrasý ise//k mýz sýramýz oluyo
	//{
	//       if (tavla[20] != 0)//kýrýk var mý kontrol ediyo
	//       {
	//               elde = 1;
	//               onceki = 0;
	//               tavla[7]--;
	//       }

	//}
	//else//deðirles siyahýn sýrasýdýr
	//{
	//       if (tavla[7] != 0)//yine kontrol ediyo kýrýk var mý diye
	//       {
	//               elde = -1;
	//               onceki = 27;
	//               tavla[20]++;
	//       }

	//}
}
void tavla_diz()//sýkýntý yok//a tavla b beyaz c siyah
{



	int i, j, x = 504, y = 8, k = -38, l = 38;
	for (i = 0; i < 28; i++)
	{
		if (i == 14)
		{
			k = 38;
			y = 402;
			l = -38;
			x += k;
		}
		if (tavla[i] > 0)//beyaz taþlarý dizecek
		{
			for (j = 0; j < tavla[i]; j++)
			{
				blit(beyaz, Tavla, 0, 0, x, y, 129, 126);//burda taþý çizdirecez
				y += l;
			}
			y = y - (l*tavla[i]);//geri gitme
		}
		else if (tavla[i] < 0)//siyah taþýmýz var
		{
			for (j = tavla[i]; j < 0; j++)
			{
				blit(siyah, Tavla, 0, 0, x, y, 129, 126);//burda taþý çizdirecez
				y += l;
			}
			y = y + (l*tavla[i]);
		}
		x += k;

	}
}
bool kontrol()
{
	int i;
	bool durum = false;
	int k = konum - onceki;//beyaz için
	int l = onceki - konum;//siyah için
	if (k == 0 || l == 0)//ayný yere koyuyoo
	{
		elde = 0;
		//return durum;
	}
	//if (konum == 7 || konum == 20)
	//{
	//return durum;
	//}
	if (elde > 0)//beyaz taþ
	{
		if (k > 0)//doðru ilerliyo
		{
			if ((onceki < 7 && konum>7) || (onceki < 21 && konum > 21))
				k--;

			for (i = 0; i < 4; i++)
			{
				if ((k) == gelen_zar[i])
				{
					gelen_zar[i] = 0;
					durum = true;
					break;
				}
			}
		}
	}
	else if (elde < 0)//siyah taþ
	{
		if (l > 0)//doðru ilerliyo
		{
			if ((onceki > 7 && konum < 7) || (onceki > 20 && konum < 20))
				l--;//?
			for (i = 0; i < 4; i++)
			{
				if ((l) == gelen_zar[i])
				{
					gelen_zar[i] = 0;
					durum = true;
					break;
				}

			}

		}

	}

	else
	{
		elde = 0;
	}
	//degerdon(k);

	return durum;
}
void OynamaKontrol(){


	//kiþinin oynayacak hamlesi varmý kontrol edilir.
	if (k % 2 == 0)//beyaz
	{
		if (tavla[20] > 0)//kýrýlmýþ taþý var
		{

			for (int i = 0; i < 4; i++){
				int gelen = gelen_zar[i];
				if (gelen > 0 && tavla[26 - gelen] >= -1)//1 taþ vardýr veya beyazvardýr yada boþtur
				{
					return; //gelebilir sýrayý atlatma
				}
			}
		}
	}
	else//siyahýn sýrasý
	{
		if (tavla[7] < 0)//kýrýlmýþ taþý var
		{
			for (int i = 0; i < 4; i++){
				int gelen = gelen_zar[i];
				if (gelen > 0 && tavla[gelen] <= 1)//1 taþ vardýr veya beyazvardýr yada boþtur
				{
					return;//oynayabilir sýrayý atlatma
				}
			}
		}

		for (int i = 1; i <= 26; i++)
		{
			if (k % 2 == 0)//sýra beyazdaysa
			{

				if (tavla[i] > 0)//taþ beyazsa
				{
					for (int j = 0; j < 4; j++)
					{
						int gelen = gelen_zar[j];
						int karsi = gelen + i;
						if (i < 7 && karsi>7 || i < 20 && karsi>20)
						{
							karsi++;
						}

						if (gelen > 0 && karsi <= 26 && tavla[karsi] >= -1)//1 tas vardır veya 
						{
							return;//oynayabilir sirayı atlatma
						}
					}
				}
			}
			else //sira siyahta
			{
				if (tavla[i] < 0) //tas beyaz
				{
					for (int j = 0; j < 4; j++)
					{
						int gelen = gelen_zar[j];
						int karsi = i - gelen;
						if (i > 7 && karsi < 7 || i > 20 && karsi < 20)
						{
							karsi--;
						}

						if (gelen > 0 && karsi >= 1 && tavla[karsi] <= 1){
							return;
						}
					}

				}

			}

		}
	}
	//sira karşıya gececek
	//zarları sıfırla
	for (int i = 0; i < 4; i++)
	{
		//gelen_zar[i] = 0;
	}
	//sırayı karşıya ver
	//k++;


}


void hareketettir()
{
	int i;
	//kirilmakontrol();
	if (elde == 0)//elimizde taþ yoktu onu oluþturduuuk//
	{


		if (((tavla[7]<0 && konum == 7) || (tavla[7] == 0 && tavla[konum] < 0)) && k % 2 == 1)
		{
			elde = -1;
			//tavla[konum]++;
			if (konum == 7)
			{
				onceki = 27;
			}
			else
			{
				onceki = konum;
			}

		}


		else if ((tavla[20]>0 && konum == 20) || (tavla[20] == 0 && tavla[konum]>0) && k % 2 == 0)// beyazsa elde taş yoksa tıklanan
		{
			elde = 1;
			//tavla[konum]--;
			if (konum == 20)
			{
				onceki = 0;
			}
			else
			{
				onceki = konum;
			}


		}

	}
	else if (elde != 0)//eðer elimizde taþ varsa onu býracak yer arýyoruz..
	{
		//if (konum == onceki)
		//elde = 0;
		if (konum == onceki)
		{
			elde = 0;
			onceki = 0;

		}
		else if ((tavla[konum] < 0 && elde < 0) || (tavla[konum] > 0 && elde > 0) || tavla[konum] == 0)
		{
			if (kontrol())
			{

				Mesaj("Tas ayni renkti veya bos yere kondu");

				tavla[konum] += elde;

				if (tavla[7]<0 && onceki == 27) //kırılan siyah  taşı koymuş
				{
					tavla[7]++;
				}
				else if (tavla[20]>0 && onceki == 0)//kırılan beyaz taşı koymuş
				{
					tavla[20]--;
				}
				else
				{
					tavla[onceki] -= elde;
				}

				elde = 0;
				onceki = 0;

			}

		}
		else//tas ayni degil veya kýrýlabilir
		{
			if (kontrol())
				//{
				//Mesaj("Taþ Konulabilir");

				if (abs(tavla[konum]) > 1) //taþ 1 den fazla iþlem yok
				{
				//Mesaj("gözde birden fazla taþ vardýr hamle yapýlamaz");
				}
				else if (abs(tavla[konum]) == 1) //tek taþ vardýr kýrýlma ihtimali var
				{
					//Mesaj("Tek Taþ var kýrýlabilir");

					if (tavla[7]<0 && onceki == 27) //kırılan siyah  taşı koymuş
					{
						tavla[7]++;
					}
					else if (tavla[20]>0 && onceki == 0)//kırılan beyaz taşı koymuş
					{
						tavla[20]--;
					}
					else
					{
						tavla[onceki] -= elde;
					}

					if (elde < 0 && tavla[konum]>0) //eldeki taþ siyah yerdeki taþ beyazsa
					{
						//Mesaj("Eldeki Taþ Siyah Yerdeki Beyazdý. Taþ Kýrýldý");
						tavla[20] += tavla[konum];
						tavla[konum] = elde;
						elde = 0;
						onceki = 0;

					}
					else if (elde > 0 && tavla[konum] < 0)//eldeki taþ beyaz yerdeki taþ siyahsa
					{
						//Mesaj("Eldeki Taþ Beyaz Yerdeki Taþ Siyahtý Taþ Kýrýldý");
						tavla[7] += tavla[konum];
						tavla[konum] = elde;
						elde = 0;
						onceki = 0;

					}
				}

		}//if kontrol()

	}

	sirakontrol();
	OynamaKontrol();//kalan zarlarla oynayabiliyormu
}
int yer_belirle(int x, int y)//sýkýntý yok
{
	int nokta;
	if (x > 362 && x < 470 && y>210 && y < 248)
	{
		nokta = 0;
	}
	else if (y < 220)
	{
		nokta = ceil(((double)x - 20) / 38);
		nokta = 14 - nokta;
	}
	else
	{
		nokta = ceil(((double)x - 20) / 38);
		nokta = 13 + nokta;
	}
	return nokta;
}
void tiklama()
{
	int k1, k2;
	if (gelen_zar[0] == 0 && gelen_zar[1] == 0 && gelen_zar[2] == 0 && gelen_zar[3] == 0)
	{
		if (x > 362 && x < 470 && y>210 && y < 248)
		{
			k1 = rand() % 6;
			switch (k1)
			{
			case 0:blit(a1, Tavla, 0, 0, 362, 210, 38, 38); break;
			case 1:blit(a2, Tavla, 0, 0, 362, 210, 38, 38); break;
			case 2:blit(a3, Tavla, 0, 0, 362, 210, 38, 38); break;
			case 3:blit(a4, Tavla, 0, 0, 362, 210, 38, 38); break;
			case 4:blit(a5, Tavla, 0, 0, 362, 210, 38, 38); break;
			case 5:blit(a6, Tavla, 0, 0, 362, 210, 38, 38); break;
			}
			gelen_zar[0] = zar[k1];
			k2 = rand() % 6;
			switch (k2)
			{
			case 0:blit(a1, Tavla, 0, 0, 412, 210, 38, 38); break;
			case 1:blit(a2, Tavla, 0, 0, 412, 210, 38, 38); break;
			case 2:blit(a3, Tavla, 0, 0, 412, 210, 38, 38); break;
			case 3:blit(a4, Tavla, 0, 0, 412, 210, 38, 38); break;
			case 4:blit(a5, Tavla, 0, 0, 412, 210, 38, 38); break;
			case 5:blit(a6, Tavla, 0, 0, 412, 210, 38, 38); break;
			}
			gelen_zar[1] = zar[k2];
			if (k1 == k2)
			{
				gelen_zar[2] = zar[k1];
				gelen_zar[3] = zar[k1];
			}
		}

		OynamaKontrol();// her zarı attığında bakıyo oynanabiliyo mu
	}
	else
	{
		hareketettir();


	}

}

int main()
{
	Baslat();

	Tavla = load_bitmap("sungam.bmp", NULL);
	siyah = load_bitmap("siyah.bmp", NULL);
	beyaz = load_bitmap("tas.bmp", NULL);
	a1 = load_bitmap("1.bmp", NULL);
	a2 = load_bitmap("2.bmp", NULL);
	a3 = load_bitmap("3.bmp", NULL);
	a4 = load_bitmap("4.bmp", NULL);
	a5 = load_bitmap("5.bmp", NULL);
	a6 = load_bitmap("6.bmp", NULL);
	siyahinsirasi = load_bitmap("siyahinsirasi.bmp", NULL);
	beyazinsirasi = load_bitmap("beyazinsirasi.bmp", NULL);
	tavlabaslangic = load_bitmap("tavlabaslangic.bmp", NULL);
	scorbeyaz = load_bitmap("scorbeyazz.bmp", NULL);
	scorsiyah = load_bitmap("scorsiyahh.bmp", NULL);
	srand(time(NULL));
	while (!key[KEY_ENTER])
	{
		blit(tavlabaslangic, screen, 0, 0, 0, 0, 900, 500);
		textprintf_ex(tavlabaslangic, font, 50, 35, makecol(255, 255, 255), -1, "2 Kisilik Tavla Oyununa Hosgeldiniz.. Baslamak icin ENTER e basiniz");
	}
	clear_bitmap(screen);
	tavla_diz();
	blit(Tavla, screen, 0, 0, 20, 20, 544, 440);

	while (!key[KEY_ESC])
	{


		show_mouse(screen);
		scorkontrol();

		blit(scorbeyaz, screen, 0, 0, 590, 170, 120, 21);
		blit(scorsiyah, screen, 0, 0, 740, 170, 120, 21);
		textprintf_ex(screen, font, 590, 195, makecol(255, 255, 255), -1, "       %d                  %d   ",scor[0],scor[1]);
		textprintf_ex(screen, font, 568, 300, makecol(255, 255, 255), -1, "Oyundan cikmak icin ESC tusuna basiniz.");
		if (k % 2 == 0)
			blit(beyazinsirasi, screen, 0, 0, 570, 40, 312, 70);
		else
			blit(siyahinsirasi, screen, 0, 0, 570, 40, 312, 70);

		if (mouse_b)
		{

			x = mouse_x;
			y = mouse_y;
			konum = yer_belirle(x, y);

			clear_bitmap(Tavla);
			Tavla = load_bitmap("sungam.bmp", NULL);
			tiklama();
			tavla_diz();

			//clear_bitmap(screen);
			degerdon();
			mouse_b = false;

			blit(Tavla, screen, 0, 0, 20, 20, 544, 440);

		}


	}

	Bitir();
	return 0;
}
END_OF_MAIN()

void Baslat() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 900, 500, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	install_timer();
	install_keyboard();
	install_mouse();

}
void Bitir() {
	clear_keybuf();

}