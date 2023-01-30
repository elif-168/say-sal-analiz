#include<stdio.h>
#include<math.h>
#define MAX 30
//aþaðýda printflerle yazýlý olan sayýsal analiz yöntemlerinin kodlanmasý   

void fonksiyon_al(double* p, int n );
double fonksiyon_deger(double*p, double deger, int N);
int aralik(double u, double a);
int hata_iterasyon(double b, double a, int i, double hata );
void matris_al(double p[][MAX], int n);
void birim_matris(int n, double matris[][MAX]);
void satiri_bol(double matris[][MAX], int i, double bolen, int n);
void denklem_matrisi(double p[][MAX], int n);
void denklem_deger(double mat[][MAX], int N, double degisken[]);
void mutlak_siralama(double mat[][MAX], int n);
double seidal_deger(double mat[][MAX], int degisken_no, int n, double* degiskenler);
double ileri_geri_fark(double u, double a, double h);
double turev(double*poli, int N, double deger);
int hata_karsilastirmali(double a, double b, double epsilon);

 

int main (){
	int secim, N, M, i, j, k, m, q, tmp, iterasyon=1, aralik_kontrol=0, sutun, satir;
	int kok, kontrol=0, devam_kontrol=1, satir_kont=0;
	double HATA, u, a, c, ust_deger, alt_deger, orta_deger, h, ileri_deger, geri_deger, deger, x, sonuc1, sonuc2, sonuc3, carpim;
	double polinom[MAX], degiskenler[MAX]={0};
	double matris[MAX][MAX]={{0}}, ters_matris[MAX][MAX]={{0}};
	double yeni_deger;
	
	
	while(devam_kontrol==1){
	
	for(i=0;i<MAX;i++){
		degiskenler[i]=0;
	}
	

	kontrol=0, satir_kont=0, aralik_kontrol=0, iterasyon=1;
	
	printf("1-Bisection Yontemi\n");
	printf("2-Regula-Falsi Yontemi\n");
	printf("3-Newton-Raphson Yontemi\n");
	printf("4-NxN'lik Matrisin Tersi\n");
	printf("5-Gauss Eleminasyon Yontemi\n");
	printf("6-Gauss Seidal Yontemi\n");
	printf("7-Sayisal Turev\n");
	printf("8-Simpson Yontemi\n");
	printf("9-Trapez Yontemi\n");
	printf("10-Degisken Donusumsuz Gregory Newton Enterpolasyonu\n");
	printf("sececeginiz yontemin numarasini giriniz:\n");
	scanf("%d", &secim);
	
	if(secim==1){
		//bisection 
		printf("polinomun derecesini girniz:\n");
		scanf("%d", &N);
		fonksiyon_al(polinom, N);
		printf("hata payini giriniz:\n");
		scanf("%lf", &HATA);
		
		aralik_kontrol=0;

		do {
			if(aralik_kontrol==0){
			printf("ust ve alt sinirlari sirasiyla giriniz:\n");
			}
			else{
				printf("girdiginiz aralikta ara deger teoremine gore kok yoktur.\nust ve alt sinirlari sirasiyla tekrar giriniz:\n");
			}

		scanf("%lf", &u);
		scanf("%lf", &a);
		ust_deger=fonksiyon_deger(polinom, u, N);
		alt_deger=fonksiyon_deger(polinom, a, N);
		kok=aralik(ust_deger, alt_deger);
		aralik_kontrol=1;
		}
		while (kok==1);//kok 1 iken çarpýmlarý pozitif demek 
		while(kontrol==0){
		c=(u+a)/2;
		ust_deger=fonksiyon_deger(polinom, u, N);
		alt_deger=fonksiyon_deger(polinom, a, N);
		orta_deger=fonksiyon_deger(polinom, c, N);
		if(aralik(ust_deger, orta_deger)==0){
			a=c;
			kontrol= hata_iterasyon(u, a, iterasyon, HATA);
		}
		else{
			u=c;
			kontrol= hata_iterasyon(u, a, iterasyon, HATA);
		}
		
		
		
		iterasyon++;
	}
	
		printf("\n%lf hata payina gore polinomun koku: %lf\n",HATA, c );
	}
	else if (secim==2){
	// regula-falsi 
		printf("polinomun derecesini girniz:\n");
		scanf("%d", &N);
		fonksiyon_al(polinom, N);
		aralik_kontrol=0;
		printf("hata payini giriniz:\n");
		scanf("%lf", &HATA);
		
		do {
			if(aralik_kontrol==0){
			printf("ust ve alt sinirlari sirasiyla giriniz:\n");
			}
			else{
				printf("girdiginiz aralikta ara deger teoremine gore kok yoktur.\nust ve alt sinirlari sirasiyla tekrar giriniz:\n");
			}
		scanf("%lf", &u);
		scanf("%lf", &a);
		ust_deger=fonksiyon_deger(polinom, u, N);
		alt_deger=fonksiyon_deger(polinom, a, N);
		kok=aralik(ust_deger, alt_deger);
		aralik_kontrol=1;
		}
		while (kok==1);
		
		while(kontrol==0){
		c=(((u*alt_deger)-(a*ust_deger))/(alt_deger-ust_deger));
	
		ust_deger=fonksiyon_deger(polinom, u, N);
		alt_deger=fonksiyon_deger(polinom, a, N);
		orta_deger=fonksiyon_deger(polinom, c, N);
		if(aralik(ust_deger, orta_deger)==0){
			a=c;
			kontrol= hata_iterasyon(u, a, iterasyon, HATA);
		}
		else{
			u=c;
			kontrol= hata_iterasyon(u, a, iterasyon, HATA);
		}
		
		iterasyon++;

	}
	printf("\ngirilen %lf hata payina gore polinomun koku: %lf\n", HATA, c );	
	}
	else if(secim==3){
		//newton-raphson yöntemi 
		printf("polinomun derecesini girniz:\n");
		scanf("%d", &N);
		fonksiyon_al(polinom, N);
		aralik_kontrol=0;
		printf("hata payini giriniz:\n");
		scanf("%lf", &HATA);
		
		do {
			if(aralik_kontrol==0){
			printf("ust ve alt sinirlari sirasiyla giriniz:\n");
			}
			else{
				printf("girdiginiz aralikta ara deger teoremine gore kok yoktur.\nust ve alt sinirlari sirasiyla tekrar giriniz:\n");
			}
		scanf("%lf", &u);
		scanf("%lf", &a);
		ust_deger=fonksiyon_deger(polinom, u, N);
		alt_deger=fonksiyon_deger(polinom, a, N);
		kok=aralik(ust_deger, alt_deger);
		aralik_kontrol=1;
		}
		while (kok==1);
		
		alt_deger=0;
		
		while(kontrol==0){
		
		m=turev(polinom, N, a);
		c=a-(fonksiyon_deger(polinom, a, N)/turev(polinom, N, a));
		
		alt_deger=fonksiyon_deger(polinom, a, N);
		ust_deger=fonksiyon_deger(polinom, c, N);
		

		kontrol=hata_karsilastirmali(ust_deger, alt_deger, HATA);
		a=c;

	}
	printf("\ngirilen %lf hata payina gore polinomun koku: %lf\n", HATA, c );	
		
		
		
	}
	else if(secim==4){
		//NxN lik matrisin tersi 
			for (i=0;i<N;i++){
	 			for(j=0;j<N;j++){
	 			ters_matris[i][j]=0;
			 	} //birden fazla kez programý çalýþtýrýrsa ters matrisi sýfýrlamak için
			}
		
		
		
		printf("karesel matrisin satir ya da sutun sayisini giriniz:\n");
		scanf("%d",&N);
	    matris_al(matris, N);
	    printf("alinan matris\n");
		for (i=0;i<N;i++){
 			for(j=0;j<N;j++){
 			printf("%lf \t",matris[i][j]);
		 	} printf("\n");
		 }
		
		 
		 birim_matris(N,ters_matris);
		


		for(j=0; j<N; j++){
			satiri_bol(ters_matris, j, matris[j][j], N);
				satiri_bol(matris, j, matris[j][j], N);
		        for(i=0; i<N; i++)
		        {
		            if(i!=j)
		            {
		                c=matris[i][j];
		                for(k=0; k<N; k++)
		                {
		                	ters_matris[i][k]=ters_matris[i][k]-c*ters_matris[j][k];
		                    matris[i][k]=matris[i][k]-c*matris[j][k];
		                }
		            }
		        }
		    }
		
	
		   printf("matrisin tersi:\n");
			for (i=0;i<N;i++){
	 			for(j=0;j<N;j++){
	 			printf("%lf \t",ters_matris[i][j]);
			 	} 
			 	printf("\n");
		 }
		
 	
		}
		else if(secim==5){
			//gauss eliminasyon yöntemi
			printf("denklem sayisini giriniz:\n");
			scanf("%d", &N);

			denklem_matrisi(matris, N);
			
			printf("alinan matris\n");
		for (i=0;i<N;i++){
 			for(j=0;j<N+1;j++){
 			printf("%lf \t",matris[i][j]);
		 	} printf("\n");
		 }
		 printf("\n");
	
			for(j=0; j<N; j++){
				satiri_bol(matris, j, matris[j][j], N+1);
		        for(i=0; i<N; i++)
		        {
		            if(i>j)
		            {
		                c=matris[i][j];
		                for(k=0; k<N+1; k++)
		                {
		                    matris[i][k]=matris[i][k]-c*matris[j][k];
		                }
		            }
		        }
		    }
    
			
			printf("ust ucgensel matris:\n");
				for (i=0;i<N;i++){
		 			for(j=0;j<N+1;j++){
		 			printf("%lf \t",matris[i][j]);
				 	} 
			 	printf("\n");
		 		}
		 		
		 		denklem_deger(matris, N, degiskenler);
		 		
		 		
		 		for (i=0;i<N;i++){
		 			printf("%d. degisken: %lf\n", i+1, degiskenler[i]);
				 }
		}
		else if(secim==6){
			//gauss-seidal 
			
			printf("denklem sayisini giriniz:\n");
			scanf("%d", &N);
			for(i=1;i<=N;i++){
				printf("%d. degiskenin baslangic degerini giriniz:\n", i);
				scanf("%lf", &degiskenler[i-1]);
			}
			denklem_matrisi(matris, N);
			
			mutlak_siralama(matris, N);
			printf("hata payini giriniz:\n");
		scanf("%lf", &HATA);
			
			
			
			while(kontrol<N){
				kontrol=0;
				for(i=0;i<N;i++){
					yeni_deger=seidal_deger(matris, i, N, degiskenler);
					if(abs(yeni_deger-degiskenler[i])<HATA){
						kontrol=kontrol+1;
					}
					degiskenler[i]=yeni_deger;
				
				}	
				
			}
			
			
			
			for (i=0;i<N;i++){
		 			for(j=0;j<N+1;j++){
		 			printf("%lf \t",matris[i][j]);
				 	} 
			 	printf("\n");
		 		}
		 		
		 		for (i=0;i<N;i++){
		 			printf("%d. degisken: %lf\n", i, degiskenler[i]);
				 }
		 		
			
			
		}
		else if(secim==7){
			//sayýsal türev 
			printf("polinomun derecesini girniz:\n");
			scanf("%d", &N);
			fonksiyon_al(polinom, N);
			
			printf("adim araligini(h) giriniz:\n");
			scanf("%lf", &h);
			
			printf("turevin hesaplanacagi noktayi giriniz:\n ");
			scanf("%lf", &x);
			
			
			ileri_deger=fonksiyon_deger(polinom, x+h, N);
			geri_deger=fonksiyon_deger(polinom, x-h, N);
			deger=fonksiyon_deger(polinom, x, N);
			
			
			
			sonuc1=ileri_geri_fark( ileri_deger, deger, h);
			sonuc2=ileri_geri_fark(deger, geri_deger, h);
			sonuc3=ileri_geri_fark(ileri_deger, geri_deger, 2*h);
			
			printf("ileri fark ile sayisal turev: %lf\n", sonuc1);
			printf("geri fark ile sayisal turev: %lf\n", sonuc2);
			printf("merkezi fark ile sayisal turev: %lf\n", sonuc3);
			
		}
		else if(secim==8){
			//simpson yöntemi
			printf("polinomun derecesini girniz:\n");
			scanf("%d", &N);
			fonksiyon_al(polinom, N);
			printf("integralin alinacagi araligin ust ve alt sinirlarini sirasiyla giriniz:\n");
			scanf("%lf", &u);
			scanf("%lf", &a);
			
			printf("aralik sayisini giriniz(cift sayi olmalidir):\n");
			scanf("%d", &m);
			//1/3 kuralý 
			h=(u-a)/m;
			
			sonuc1=fonksiyon_deger(polinom, u, N)+fonksiyon_deger(polinom, a, N);
			
			for(i=1;i<m;i++){
				if(i%2!=0){
					//tek ise
					sonuc1=sonuc1+(4*fonksiyon_deger(polinom, a+i*h, N));
				}
				else{
					//çift ise
					sonuc1=sonuc1+(2*fonksiyon_deger(polinom, a+i*h, N));
				}
			}
			
			sonuc1=(h/3)*sonuc1;
			sonuc2=0;
			//3/8 kuralý
			for(i=0;i<m;i++){
				sonuc2=sonuc2+fonksiyon_deger(polinom, a, N);
				sonuc2=sonuc2+3*fonksiyon_deger(polinom, a+h/3, N);
				sonuc2=sonuc2+3*fonksiyon_deger(polinom, a+2*h/3, N);
				sonuc2=sonuc2+fonksiyon_deger(polinom, a+h, N);
				a=a+h;
			}
			sonuc2=(sonuc2*3)/8;
			
			printf("simpson 1/3 yontemi ile fonksiyonun integrali: %lf\n", sonuc1);
			printf("simpson 3/8 yontemi ile fonksiyonun integrali: %lf\n", sonuc2);
			
			
		}
		else if(secim==9){
			//trapez yöntemi
			printf("polinomun derecesini girniz:\n");
			scanf("%d", &N);
			fonksiyon_al(polinom, N);
			printf("integralin alinacagi araligin ust ve alt sinirlarini sirasiyla giriniz:\n");
			scanf("%lf", &u);
			scanf("%lf", &a);
			
			printf("aralik sayisini giriniz:\n");
			scanf("%d", &m);
			h=(u-a)/m;
			sonuc1=(fonksiyon_deger(polinom, a, N)+fonksiyon_deger(polinom, u, N))/2;
			
			for(i=1;i<m;i++){
				sonuc1=sonuc1+fonksiyon_deger(polinom, a+i*h, N);
				
			}
			
			
		sonuc1=sonuc1*h;
		
		printf("trapez yontemi ile fonksiyonun integrali: %lf\n", sonuc1);
		
		}
		else if(secim==10){
			//gregory newton enterpolasyonu deðiþken dönüþümsüz
			printf("gireceginiz x degerleri sayisini girniz:\n");
			scanf("%d", &N);
			for(i=0;i<N;i++){
				printf("%d. x degerini giriniz:\n", i+1);
				scanf("%lf", &matris[i][0]);
				printf("%d. y degerini giriniz:\n", i+1);
				scanf("%lf", &matris[i][1]);
			}
			printf("sonucunu bulmak istediginiz noktayi giriniz:\n");
			scanf("%lf",&x);
			i=2;
			h=matris[1][0]-matris[0][0];
			kontrol=0;
			tmp=N;
			while(kontrol<N){
				
				for(k=0;k<tmp-i+1;k++){
					matris[k+i-1][i]=matris[k+i-1][i-1]-matris[k+i-2][i-1];
					
					a=matris[k+i-1][i-1]-matris[k+i-2][i-1];
				
				}
				kontrol=0;
				for(j=0;j<N;j++){
					if(matris[j][i]==matris[i-1][i]){
						kontrol=kontrol+1;
					}
				}
				
				
				i++;
			}
			printf("farklar tablosu:\n");
			for (m=0;m<N;m++){
		 			for(j=0;j<i;j++){
		 			printf("%lf \t",matris[m][j]);
				 	} 
			 	printf("\n");
		 		}
		 		
		 		 
		 		sonuc1=matris[0][1];
		 		printf("enterpolasyon denklemi:\n");
				 printf("F(x)=f(0)");
		 	for(k=0;k<i-2;k++){
		 		printf(" +");
		 		for(j=0;j<=k;j++){
		 			printf("(x-%lf)", matris[j][0]);
				 }
		 		printf("*(1/%lf^%d)*(1/%d!)*%lf", h, j, k, matris[k][k+1]);
			 }	
			 printf("\n");
			 carpim=1;
			 sonuc1=matris[0][1];
			for(k=0;k<i-2;k++){
		 		carpim=1;
		 		m=1;
		 		for(j=0;j<=k;j++){
		 			carpim=carpim*(x-matris[j][0])*(1/h);
		 			m=m*(j+1);
				 }
		 		carpim=(carpim*matris[k+1][k+2])/m;
	
		 		sonuc1=sonuc1+carpim;
			 }
			 printf("%lf noktasindaki degeri= %lf\n", x, sonuc1);	
			
			
			
		}
		
		
		


	printf("programi tekrar calistirmak istiyorsaniz 1, cikis yapmak istiyorsaniz 0 giriniz:\n");
	scanf("%d", &devam_kontrol);
	
	}


	
	return 0;
}
void fonksiyon_al(double* p, int n ){
int i;

	for (i=0;i<=n;i++){
		printf("%d dereceli terimin katsayisini giriniz:\n",i);
		scanf("%lf", &p[i]);
	}


}

int hata_iterasyon(double b, double a, int i, double hata ){
	if((b-a)/pow(2,i)<=hata){
		return 1;
	}
	else {
		return 0;
	}
}

int hata_karsilastirmali(double a, double b, double epsilon){
	if(abs(a-b)<epsilon){
		return 1;
	}
	else{
		return 0;
	}
}
	
	

int aralik(double u, double a){

	if(u*a<=0){
		return 0;
	}
	else{
		return 1;
	}
}

double fonksiyon_deger(double*p, double deger, int N){
	int i;
	double sayi=0;
	for (i=0;i<=N;i++){
		sayi=sayi+(p[i]*pow(deger,i));
		
	}
	return sayi;
}
 void matris_al(double p[][MAX], int n){
 	
 	int i, j;
 	
 	printf("matrisin elemanlarini soldan saga dogru giriniz:\n");
 	for (i=0;i<n;i++){
 		for(j=0;j<n;j++){
 			scanf("%lf",&p[i][j]);
		 }
	 }
 	
 	
 }
 
void birim_matris(int n, double matris[][MAX]){
	int i;
	for(i=0;i<n;i++){
		matris[i][i]=1;
	}
}
void satiri_bol(double matris[][MAX], int i, double bolen, int n){
	// i burda bölünecek elemanýn satýr numarasý
	int k;
	for(k=0;k<n;k++){
		matris[i][k]=matris[i][k]/bolen;
	}
	
}


 void denklem_matrisi(double p[][MAX], int n){
 	
 	int i, j;
 
 	printf("denklemleri istenilen sekilde giriniz:\n\n");
 	for (i=1;i<=n;i++){
 		
 		for(j=1;j<=n;j++){
 			printf("%d. denklemin %d. degiskeninin katsayisini giriniz:\n", i, j);
 			scanf("%lf",&p[i-1][j-1]);
 			
		 }
		 printf("%d. denklemin sonucunu giriniz:\n", i);
		 scanf("%lf",&p[i-1][n]);
	 }
 	
 	
 }

void denklem_deger(double mat[][MAX], int N, double degisken[]){
	
	int i, j, k=1;
	double toplam=0;
	degisken[N-1]=mat[N-1][N];
	
	for(i=N-2;i>=0;i--){
		toplam=0;
		for(j=N-1;j>=N-k;j--){
		toplam=toplam+degisken[j]*mat[i][j];
		
		}
		degisken[i]=mat[i][N]-toplam;
	k++;
	}
	
}

void mutlak_siralama(double mat[][MAX], int n){
	int i, j, k;
	double tmp;
	for(j=0;j<n;j++){
		for(i=0;i<n;i++){
			if(abs(mat[j][j])<abs(mat[i][j])){
				for(k=0;k<n+1;k++){
					tmp=mat[j][k];
					mat[j][k]=mat[i][k];
					mat[i][k]=tmp;
				}
			}
		}
	}
}
	
double seidal_deger(double mat[][MAX], int degisken_no, int n, double* degiskenler){
	int i;
	double toplam=0;
	for(i=0;i<n+1;i++){
		if(i!=degisken_no){
			toplam=toplam+(mat[degisken_no][i]*degiskenler[i]);
		}
	}
	toplam=(mat[degisken_no][n]-toplam)/mat[degisken_no][degisken_no];
	
	
	return toplam;
}	

double ileri_geri_fark(double u, double a, double h){
	double sonuc;
	sonuc=(u-a)/h;
	return sonuc;	
}
double turev(double*poli, int N, double deger){
	double sonuc=0;
	int i;
	for(i=1;i<=N;i++){
		sonuc=sonuc+i*poli[i]*pow(deger,i-1);
	}
	return sonuc; 
	
}




