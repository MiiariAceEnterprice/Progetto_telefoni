/*
Mattiuz Marco, Miatello Alessandro, Shera Shefik 3DII
Data inizio: 9/5/2021
Data fine: @/5/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <cstdlib>
#include <time.h>
using namespace std;
const int SIZE_ACCOUNT=30;
const int SIZE_ARRAY=50;
const int SUPER_SIZE_ARRAY=500;
const int SIZE_PASSWORD = 10;



//   ---------STRUCT------------
typedef struct{
    int x;
    int y;
}Coordinate;

typedef struct{
    int batteria;
    int pollici_schermo;
    int memoria;
    int codice_modello;
    float prezzo_vendita;
    float costo_produzione;
}Modello;

struct Utente;

typedef struct{
    char codice_seriale[6];    //casuale
    Coordinate puntatore_posizione;
    Modello* puntatore_modello;
    struct Utente* puntatore_aquisto;
    int data_acquisto;
}Smartphone;

typedef struct Utente _utente;


struct Utente{
    char email[SIZE_ACCOUNT];       //da fare funzione inserimento mail
    char nickname[SIZE_ACCOUNT];    //è quello che differenzia gli account
    char password[SIZE_PASSWORD];
    Smartphone* puntatore_telefono[SIZE_ARRAY];
};

typedef struct{
   Modello modelli[SIZE_ARRAY];
   int nModelli;
   _utente utenti[SIZE_ARRAY];
   int nUtenti;
   Smartphone smartphones[SIZE_ARRAY];
   int nSmartphones;
}Mondo;
///////////////////////////////////////////////////////



////funzioni di bellezza///////////////////////////////
void SetColor(short Color)
{ 
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCon,Color);
	/*
	1 = Blue 2 = Green 3 = Light Blue 4 = Red 5 = Purple 
	6 = Orange/Brown 7 = White 8 = Grey 9 = Blue 
	10 = Green 11 = Light Blue 12 = Pink/Red 13 = Purple
	14 = Yellow 15 = While
	*/
}
void cls()
{
    
	DWORD n;
	DWORD size;
	COORD coord = {0};
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	GetConsoleScreenBufferInfo ( h, &csbi );
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter ( h, TEXT ( ' ' ), size, coord, &n );
	GetConsoleScreenBufferInfo ( h, &csbi );
	FillConsoleOutputAttribute ( h, csbi.wAttributes, size, coord, &n );
	SetConsoleCursorPosition ( h, coord );
}
//////////////////////////////////////////////////////



//////////////// FUNZIONI GENERALI /////////////////////
void preparaGeneratore()
{
	srand(time(0));
}
int sorteggiaNumero(int min, int max)
{
	int width = max-min+1;
	int ris = rand() % width;	
	ris += min;
	return ris;
}

void f_codiceTelefono(char codice[],int n){
	preparaGeneratore();
		codice[0]=sorteggiaNumero('A','Z');
		codice[1]=sorteggiaNumero('A','Z');
		codice[2]=sorteggiaNumero('0','9');
		codice[3]=sorteggiaNumero('0','9');
		codice[4]=sorteggiaNumero('0','9');
		codice[5]=sorteggiaNumero('0','9');
		codice[6]='\0';
		//fare funzione ricerca codice all'interno dell'array Telefoni
}

void f_verificapassword(char x[],char confronto[],int colore_scritte){
    
    
    SetColor(colore_scritte);
    cout << "Inserisci la password: ";
    cin >> x;
        int i = 0;
        
        while(strcmp(x, confronto) != 0){	
        	SetColor(4);
            cout << "\n======\nErrore\n======\n";
            SetColor(colore_scritte);
            cout << "Inserisci la password: ";
            cin >> x;
        }
        
    cout << "Passwod inserita con successo";
}

int f_codicemodello(Modello Arr[],int n){
	preparaGeneratore();
	int cod= sorteggiaNumero(1000,9999);
	for(int i=0;i<n;i++){
		preparaGeneratore();
	while(cod==Arr[i].codice_modello){
		cod= sorteggiaNumero(1000,9999);
	}	
	}
	return cod;
}
////////////////////////////////////////////////////////



////SEZIONE ADMIN////////////////////////////////////////

void f_nuovoModello(Modello Arr[],Modello& x, int i, float capitale){
    int n_dispositivi;
    cout << "\n======================================\n";
    cout << "Stai inserendo il Modello n." << i << "\n";
    cout << "======================================\n";
    cout << "Inserisci la capacita' della batteria del modello(mA): ";
    cin >> x.batteria;
    cout << "Inserisci la grandezza dello schermo(in pollici): ";
    cin >> x.pollici_schermo;
    cout << "Inserisci la memoria del dispositivo(GB): ";
    cin >> x.memoria;
    cout << "Inserisci il prezzo di vendita del dispositivo: ";
    cin >> x.prezzo_vendita;
    cout << "Inserisci il costo di produzione del dispositivo: ";
    cin >> x.costo_produzione;
    cout << "Inserisci quanti dispositivi vuoi produrre: ";
    cin >> n_dispositivi;
    ////generatore del codice modello (4 cifre)
    x.codice_modello = f_codicemodello(Arr,i);
    

}

void f_viewModello(Modello& x, int j){
	
	SetColor(9);
	cout << "\n------Modello n."<< j << "------";
	cout << "\ncodice modello: " << x.codice_modello;
	cout << "\nCosto di produzione: " << x.costo_produzione << "\n";
	cout << "Prezzo di vendita: " << x.prezzo_vendita << "\n";
	cout << "-------------------\n";
    cout << "Batteria: " << x.batteria << "mA\n";
    cout << "Memoria: " << x.memoria << "GB\n";
    cout << "Pollici: " << x.pollici_schermo << "\n";
    cout << "-----------------------\n";
    
    
}

// cosa fa questa funzione?
/*
void f_inserisciCapitale(bool primavolta, float capitale){
    cout << "Inserisci il capitale in euro di cui disponi: ";
    cin >> capitale;
}
*/

void f_menuAdmin(Modello x[], int i, float capitale){
    int menu;
    do
    {
    	cout << "\n====================Menu'====================\n";
        cout << "1-Inerisci modello\n";
        cout << "2-Stampa modelli\n";
        cout << "3-Cancellazione modello;\n";
        cout << "4-Visualizza capitale;\n";
        cout << "5-Visualizza i modelli piu' venduti;\n";
        cout << "6-Visualizza telefono e account associato;\n";
        cout << "0-Termina sessione;\n";
         cout << "\n=============================================\n";
        cout << "-->";
        cin >> menu;
       
        switch (menu){
            case 1:
                cls();
                f_nuovoModello(x,x[i], i,capitale);
                i++;
                    break;
                case 2:
                cls();
                if(i == 0){
                    cls();
                    cout << "Devi prima inserire un modello!\n";
                    f_nuovoModello(x,x[i], i, capitale);
                    i++;
                }else{
                    for(int j=0;j<i;j++){
                    f_viewModello(x[j],j);	
					}
                    
                }
                break;
            case 3:
            cout << "Inserisci l'identificativo del modello che vuoi cancellare: ";
            //generatore 4 numeri per identificativo modello --> da fare prima con preparageneratore e tutte quelle robe li 
                break;
            case 4:

                break;
        }
    } while (menu != 0);
}
/////////////////////////////////////////////



////SEZIONE UTENTE/////////////////////////
int f_trovaNick(char tmp_Nick[],_utente Arr[],int n_Arr)   //questo da in OUTPUT la posizione dell'utente nell'array degli utenti
{
    int pos=-1;
    for(int i=0;i<n_Arr;i++){
        if(strcmp(tmp_Nick, Arr[i].nickname)==0){
            pos=i;
        }
    }
    return pos;
}

/*
typedef struct{
    int batteria;
    int pollici_schermo;
    int memoria;
    int codice_modello;
    float prezzo_vendita;
    float costo_produzione;
}Modello;
*/

void f_stampaModelli(Modello Arr[],int n){
	for(int i=0;i<n;i++){
		cout << "\n-----Modello " << i << "-----"; 
		cout << "\nCodice modello: " << Arr[i].codice_modello;
		cout << "\nPrezzo modello: " << Arr[i].prezzo_vendita;
		cout << "\n-------------------";
	}
}


/////////////////////////////////////////




int main()
{
	
	//dichiarazione variabili
	char passwordefault[SIZE_PASSWORD] = "adminpwd"; 
    float capitale;
    _utente CEO;
    bool firsTime = true;
    ///////////////////////////
    //_utente Arr_utenti[SUPER_SIZE_ARRAY];
    //int n_utente=0;
    cout << "\nACCOUNT PRE-INSERITI\n";
    _utente Arr_utenti[]{
		{"marco@gmail.com","marco","marcopwd"},
		{"shera@gmail.com","shera","sherapwd"},
		{"ace@gmail.com","ace","acepwd"}
	};
    int n_utente=3;
    for(int i=0;i<n_utente;i++){
    	cout << Arr_utenti[i].email << " " <<  Arr_utenti[i].nickname << " " << Arr_utenti[i].password;
    	cout << "\n";
	}
    //////////////////////////
    int cap_telefoni=1;
    int n_telefoni=0;
    Smartphone* Arr_telefoni = (Smartphone*) malloc(cap_telefoni*sizeof(Smartphone)); 
    //////////////////////////
    //int n_modelli=0;
    //Modello Arr_modelli[SIZE_ARRAY];
    cout << "\n MODELLI PRE-INSERITI\n";
    
    Modello Arr_modelli[]{
		{2500,4,256,1352,600,340},
		{3600,5,128,1423,300,150},
		{1800,7,512,1234,890.99,400},
		{5000,6,256,1567,1200.90,630},
	};
	int n_modelli=4;
	for(int i=0;i<n_modelli;i++){
    	cout << Arr_modelli[i].batteria << " " <<  Arr_modelli[i].pollici_schermo << " " << Arr_modelli[i].memoria << " " << Arr_modelli[i].codice_modello << " " << Arr_modelli[i].prezzo_vendita << " " << Arr_modelli[i].costo_produzione;
    	cout << "\n";
	}
	
    ////////////////////////////////

	// ---INIZIO--- //
	SetColor(2);
	int menu;
    cout << "=====Login=====\n";
    cout << "1-Admin\n";
    cout << "2-Utente\n";
    cout << "===============\n";
    cout << "--> ";
    cin >> menu;
    cls();
    switch(menu)
    {
    	////////ADMIN/////////////
        case 1: 
        	SetColor(3);
        	cout << "=============\nSezione Admin\n=============\n";
        	char tmp_passwordAD[SIZE_PASSWORD];
        	f_verificapassword(tmp_passwordAD,passwordefault,3);
            cls();
            if(firsTime == true){
                //f_inserisciCapitale(firsTime, capitale);
                firsTime = false;
                cls();
                f_menuAdmin(Arr_modelli, n_modelli, capitale);
            }else{
            f_menuAdmin(Arr_modelli, n_modelli, capitale);
            }
            break;
       ////////UTENTE/////////////
        case 2: 
			int scelta_utente;
            SetColor(2);
            cout << "\nPossiedi gia' un dispositivo?";
            cout << "\n1-SI";
            cout << "\n2-No";
            cout << "\n0-esci";
            cout << "-->";
            cin >> scelta_utente;
            switch(scelta_utente){
                case 1:
                    char tmp_nickname[SIZE_ARRAY];
                    cout << "\n========================\nLOGIN\n========================= ";
                    cout << "\nInserisci il Nickname: ";
                    cin >> tmp_nickname;
                    while(f_trovaNick(tmp_nickname,Arr_utenti,n_utente)==-1){
                    	SetColor(4);
                    	cout << "\nHai inserito un nickname non valido";
                    	SetColor(2);
                    	cout << "\nReinserisci: ";
                    	cin >> tmp_nickname;
					}
					// inserimento/verifica password utente 
					char tmp_pwdUtente[SIZE_ARRAY];
                    f_verificapassword(tmp_pwdUtente,Arr_utenti[f_trovaNick(tmp_nickname,Arr_utenti,n_utente)].password,2);
                    break;
                case 2:
                	int tmp_codice;
                	cout << "\n=====================\nCompra dispositivo\n=====================";
                	//stampa catalogo modelli (e numero di smartphone per modello)
                	f_stampaModelli(Arr_modelli,n_modelli);
                	cout << "\nInserisci codice del modello: ";
                	cin >> tmp_codice;
                	//ricerca codice modello;
                	//stampa caratteristiche modello 
                	
                    break;
            }
            break;
    }
}
