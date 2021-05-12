#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include <cstdlib>
using namespace std;
const int SIZE_PASSWORD = 11;
const int SIZE_ARRAY=50;
const char passwordefault[SIZE_PASSWORD] = "adminpwd";
const int cap = 10;

typedef struct{
    int batteria;
    int pollici_schermo;
    int memoria;
    float prezzo_vendita;
    float costo_produzione;
}Modello;


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

/*int raddoppio(int cap, float* arr){
    cout << "cap iniziale:" << cap << "\n";
    cap = cap*2;
    float* temp = (float*)malloc(sizeof(float)*cap);
    for(int i = 0; i < (cap/2); i++){
        temp[i] = arr[i];
    }
    free(arr);
    cout << "cap finale: " << cap << "\n";
    arr = temp;

    return cap;
}*/


void f_verificapassword(){
    int err = 0;
    int guess = 0;
    bool controllo = false;
    char passwordin[SIZE_PASSWORD];
    
    cout << "Inserisci la password: ";
    cin >> passwordin;
    do{
        int i = 0;
        if(strcmp(passwordin, passwordefault) == 0){
            guess++;
            controllo  = true;
        }else{
            err++;
            guess = 0;
            controllo = false;
            cout << "\nErrore ";
            cout << "Inserisci la password: ";
            cin >> passwordin;
        }
    }while(err < 3 && guess != 10);
    cout << "Passwod corretta!";
}

void f_nuovoModello(Modello& x, int i){
    cout << "Modello n." << i << "\n\n";
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
}

void f_viewModello(Modello& x){
    cout << "Batteria: " << x.batteria << "mA\n";
    cout << "Memoria: " << x.memoria << "GB\n";
    cout << "Pollici: " << x.pollici_schermo << "\n";
    cout << "Prezzo di vendita: " << x.prezzo_vendita << "€";
    cout << "Costo di produzione" << x.costo_produzione << "€";
}

void f_menuAdmin(Modello x[], int i){
    int menu;
    int idmodello;
    do
    {
        cout << "1-Inerisci modello\n";
        cout << "2-Visualizza modello\n";
        cout << "4-Cancellazione modello;\n";
        cout << "5-Visualizza capitale;\n";
        cout << "6-Visualizza i modelli piu' venduti;\n";
        cout << "7-;\n";
        cout << "0-Termina sessione;\n\n";
        cin >> menu;
        switch (menu){
            case 1:
                cls();
                f_nuovoModello(x[i], i);
                i++;
                    break;
                case 2:
                cls();
                if(i == 0){
                    cls();
                    cout << "Devi prima inserire un modello!\n";
                    f_nuovoModello(x[i], i);
                    i++;
                }else{
                    for(int j = 0; j <= i; j++){
                        cout << "id = " << j << "\n";
                    }
                    cout << "Inserisci l'identificativo del modello: ";
                    cin >> idmodello;
                    f_viewModello(x[idmodello]);
                }
                break;
            case 3:
            
                break;
        }
    } while (menu != 0);
}
int main(){
    int m;
    int i = 0;//puntatore per il conteggio dei modelli creati
    Modello x[SIZE_ARRAY];
    cout << "Login as:\n";
    cout << "1 - Admin\n";
    cout << "2 - User\n";
    cin >> m;
    switch(m){
        case 1:
        cls();
        f_verificapassword();
        cls();
        f_menuAdmin(x, i);
        cls();
            break;
        case 2:
            break;
    }
}