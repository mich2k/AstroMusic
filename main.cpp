#include <iostream>  // Basic I/O
#include <windows.h> // Beep (Hz), consoleT, CColor Min: 1080, Max: 1920
#include <string> // Gestione Stringhe C++
#include <fstream> //Gestione File
#include <ctype.h> // Toupper
#include <conio.h> // kbhit()
#include <sstream> // stringsteam
#include <mmsystem.h> // Gestione Audio
#define MAX 30 // Default: 30, Array Define
#define _MAX 50 // Default: 50, Matrix Define
#define NMAX 18
#define BUFF cin.clear(); cin.ignore(999, '\n'); // Macro Buffer

using namespace std; // Namespace std::

/*
* Progetto Fisica (Muoni)
* Anno 2016 / 2017
* Liceo P.S. Mancini Avellino (AV)
* Scritto da Michele Giarletta 3^ASA ed Eduardo Gaudiosi 3^E
 */

int inputcheck ( string str ) // Completed
{
    /*
    * Semplice ma efficace funzione che si occupa
    * del controllo e del trasformare tutti i caratteri
    * dati in input in maiuscolo se serve, così da avere
    * un output più curato ed omogeneo.
    */
    unsigned int ret = 0;
    for ( unsigned int j = 0; j < str.length(); j++)
    {
        str[j] = toupper(str[j]);
        switch(str[j])
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            ret+=1;
            break;
        default:
            break;
        }
    }
    if ( ret == str.length() )
        return TRUE;
    else
        return FALSE;
}

void hexch ( string &str, int n )
{
    /*
    * hexcharge, alias hexch è la funzione che
    * carica i due array iniziali in hex, formati
    * da 30 elementi l'uno
    */
    int j = 0, ret = 0;
    do // input check
    {
        ret = 0;
        if ( j > 0 )
            cout << "\n Rilevato valore non valido, reinserire la " << n << " strip nuovamente! " << endl;
        else
            cout << "\n Inserire " << n << " strip (hex): ";
        cin >> str;
        for ( unsigned int i = 0; i < str.size(); ++i ) // rendo tutto maiuscolo per non avere errori negli switch
        {
            str[i]=toupper(str[i]);
            if ( inputcheck(str) != TRUE )
            {
                ret++;
                break;
            }
        }
        j++;
    }
    while ( ret != 0 );
    cout << "\n " << n << " array Acquisito" << endl;
    Sleep(500);
    return;
}

int fout ( string hex_1[MAX], string bin_1[MAX], string matrix_1[_MAX], string hex_2 [MAX], string bin_2 [MAX], string matrix_2 [MAX] )
{
    /*
    * La funzione fout si occupa della stampa di >> tutti >> gli
    * output del codice su file .txt, essa stamperà cinque file:
    * - out: File con nome chiesto all' utente in input, il file di testo principale con tutte le info e commenti.
    * - rawoutbin: Stampa valori bin "raw".
    * - rawouthex: Stampa valori hex "raw".
    * - bin_mtx: Matrice binaria con grazie.
    * - raw_mtx: Matrice binaria "raw".
    */
    unsigned int i = 0, j = 0, chk = 0;
    string filename;
    cout << "\n\n Inizio fase stampa su file...\n" << endl;
    cout << " Inserire nome file: ";
    cin >> filename;
    filename += ".txt";
    ofstream out(filename.c_str(), ios::ate);
    ofstream rawoutbin("RawDataBin.txt", ios::ate);
    ofstream rawouthex("RawDataHex.txt", ios::ate);
    ofstream bin_mtx("Matrix_Bin.txt", ios::ate);
    ofstream raw_mtx("RawDataMtx.txt", ios::ate);
    if (!out || !rawoutbin || !rawouthex || !bin_mtx || !raw_mtx)
    {
        cout << " File non creato, riavvio funzione... " << endl;
        Sleep(1750);
        return FALSE;
    }
    else
    {
        for ( int n = 1; n <= 2; ++n )
        {
            i = 0, j = 0;
            out << "\n-------------------------------------------------\n\t     Output Triplette 2017\n-------------------------------------------------\n" << endl;
            out << " Stampa " << n << " matrice: " << endl;
            rawoutbin << endl << " --- Inizio fase stampa " << n << " array numeri bin --- " << endl << endl;
            rawouthex << endl <<  "\t --- Inizio fase stampa " << n << " strip numeri hex --- " << endl << endl << endl << endl;
            raw_mtx << endl <<  " --- Inizio fase stampa " << n << " matrice --- " << endl << endl;
            for ( i = 0; i < MAX; ++i )
            {
                if ( i % 3 == 0)
                {
                    out << "\n " << n << " matrice tripletta n: " << j + 1 << endl << "\n";
                    j++;
                }
                if ( n == 1 )
                {
                    out << "\tPosizione " << i + 1 << " vettore: " << hex_1[i] << " (HEX) = " << bin_1[i] << " (BIN)" << endl;
                    rawoutbin << " " << bin_1[i] << endl;
                    rawouthex << hex_1[i];
                }
                else
                {
                    out << "\tPosizione " << i + 1 << " vettore: " << hex_2[i] << " (HEX) = " << bin_2[i] << " (BIN)" << endl;
                    rawoutbin << " " << bin_2[i] << endl;
                    rawouthex << hex_2[i];
                }
            }
            bin_mtx << endl << endl <<  " --- Inizio fase stampa " << n << " matrice --- " << endl;
            for ( i = 0; i < MAX / 3; ++i )
            {
                bin_mtx << " Matrice " << n << ", strip numero " << i + 1 << ":";
                for ( j = 0; j < 10; ++j )
                {
                    if ( n == 1 )
                    {
                        bin_mtx << " " << matrix_1[i][j];
                        raw_mtx << " " << matrix_1[i][j];
                    }
                    else
                    {
                        bin_mtx << " " << matrix_2[i][j];
                        raw_mtx << " " << matrix_2[i][j];
                    }
                    chk++;
                }
                bin_mtx << endl;
                raw_mtx << endl;
            }
        }
    }
    out.close();
    rawoutbin.close();
    rawouthex.close();
    bin_mtx.close();
    raw_mtx.close();
    cout << "\n Fase stampa su file terminata!" << endl;
    return TRUE;
}

int hexconf ( string hex_1[MAX], string bin_1[MAX], string hex_2[MAX], string bin_2[MAX], int conf )
{
    /*
    * La funzione hexconf si occupa della fase di stampa
    * e conferma dell' input, lato necessario per avere
    * un algoritmo completo e curato sotto ogni punto di vista.
    */
    char check;
    int i, j = 0, k = 0;
    while ( k < 2 )
    {
        k++;
        j = 0;
        cout << "\n\t --- Inizio fase stampa " << k << " strip ---" << endl;
        for ( i = 0; i < MAX; ++i )
        {
            if ( i % 3 == 0)
            {
                cout << "\n " << k << " strip, tripletta n: " << j + 1 << endl << "\n"; // L' utente vedrà sempre valori che partono da 1
                j++;
            }
            if ( k == 1 )
                cout << "\tPosizione " << i + 1 << " vettore: " << hex_1[i] << " (HEX) = " << bin_1[i] << " (BIN)" << endl; //L'utente vedrà posizioni partendo da 1
            else
                cout << "\tPosizione " << i + 1 << " vettore: " << hex_2[i] << " (HEX) = " << bin_2[i] << " (BIN)" << endl;
        }
    }
    if ( conf != 1 )
    {
        cout << "\n Confermare questi valori (s/n)? ";
        cin >> check;
        if ( check == 's' ||check == 'S' )
            return TRUE;
        else
        {
            cout << " Verra\' riavviata la procedura di input..." << endl;
            Sleep(1750);
            return FALSE;
        }
    }
    return 3;
}

string binconv ( string str) // hex >> switch  >> bin
{
    /*
    * Funzione che si occupa della conversione da esadecimale
    * a binario non matematicamente, bensì utilizzando uno
    * switch con associazione "meccanica" dei valori binari
    * ai decimali, la funzione torna la stringa binaria "ret"
    */
    string ret = ""; //Azzero Stringa
    for (unsigned int j = 0; j < str.length(); ++j)
    {
        switch (str[j])
        {
        case '0':
            ret.append ("0000");
            break;
        case '1':
            ret.append ("0001");
            break;
        case '2':
            ret.append ("0010");
            break;
        case '3':
            ret.append ("0011");
            break;
        case '4':
            ret.append ("0100");
            break;
        case '5':
            ret.append ("0101");
            break;
        case '6':
            ret.append ("0110");
            break;
        case '7':
            ret.append ("0111");
            break;
        case '8':
            ret.append ("1000");
            break;
        case '9':
            ret.append ("1001");
            break;
        case 'A':
            ret.append ("1010");
            break;
        case 'B':
            ret.append ("1011");
            break;
        case 'C':
            ret.append ("1100");
            break;
        case 'D':
            ret.append ("1101");
            break;
        case 'E':
            ret.append ("1110");
            break;
        case 'F':
            ret.append ("1111");
            break;
            // default: break; Input già controllato
        }
    }
    return ret;
}

void mgen ( string matrix [_MAX], string binstr [MAX] )
{
    /*
    * Formazione Matrice 10x10 da due strip hex convertite in bin;
    * così da formare 10 strip ed eliminazione delle prime due cifre binarie
    * di ogni strip, essendo queste sicuramente "00" ergo non necessarie
    * e non da elaborare secondo la traccia data.
    *  << questa funzione comprende l'invertire la matrice, caratteristica richiesta
    * dalla traccia. <<
    * Matrice 30
    */
    int j = 9;
    for ( int i = 0; i < MAX; ++i )
    {
        if ( i % 3 == 0) //Taglio Valori
        {
            matrix[j] = binstr[i].erase(2);
            matrix[j].append(binstr[i+1]);
            matrix[j].append(binstr[i+2]);
            j--;
            /*matrix[i][0] = binstr[i][2];
            matrix[i][1] = binstr[i][3];
            matrix[i].append(binstr[i+1]);
            matrix[i].append(binstr[i+2]);*/
        }
    }
    return;
}

void m_print ( string matrix [_MAX], int n )
{
    /*
    *
    Funzione specifica per stampare una matrice di dimensione _MAX, n passa l'identificatore della matrice
    *
    */
    unsigned int i, j;
    cout << "\n\t - inizio stampa " << n << " matrice - \n" << endl;
    for ( i = 0; i < MAX / 3; ++i )
    {
        cout << " Strip numero " << i + 1 << ":";
        for ( j = 0; j < matrix[i].length() + 1; ++j )
        {
            cout << " " << matrix[i][j];
        }
        cout << endl;
    }
    if ( n > 1 )
        cout << "\n\t - termine stampa  matrici - \n" << endl;
}

string hz ( int pos )
{
    /*
    * Funzione che riceve un parametro intero, questo parametro
    * si posizionerà in un range definito secondo il quale verrà
    * riprodotta una nota / file audio preimpostato.
    */
    unsigned int i, k;
    string noteArray[NMAX];
    string noteNames[NMAX] = {"DO", "DO#", "RE", "RE#", "MI", "FA", "FA#", "SOL", "SOL#", "LA", "LA#", "SI", "DO_A", "DO_A#", "RE_A", "RE_A#", "MI_A", "FA_A"};
    string temp_noteArray[NMAX] = {"do", "dodie", "re", "redie", "mi", "fa", "fadie", "sol", "soldie", "la", "ladie", "si", "doA", "doAdie", "reA", "reAdie", "miA", "faA"};
    for ( i = 0; i < NMAX; ++i )
    {
        noteArray[i] = "./note/";
        noteArray[i] += temp_noteArray[i];
        noteArray[i] += ".wav";
    }
    if ( pos >= 1 && pos < 5 )
        k = 0;
    else
    {
        if ( pos >= 5 && pos < 11 )
            k = 1;
        else
        {
            if ( pos > 11 && pos < 19 )
                k = 2;
            else
            {
                if ( pos > 19 && pos    < 29 )
                    k = 3;
                else
                {
                    if ( pos > 29 && pos  < 37 )
                        k = 4;
                    else
                    {
                        if ( pos > 37 && pos  < 47 )
                            k = 5;
                        else
                        {
                            if ( pos > 47 && pos  < 53 )
                                k = 6;
                            else
                            {
                                if ( pos > 53 && pos < 59 )
                                    k = 7;
                                else
                                {
                                    if ( pos > 59 && pos <= 63 )
                                        k = 8;
                                    else
                                    {
                                        if ( pos > 63 && pos <= 67 )
                                            k = 9;
                                        else
                                        {
                                            if ( pos > 67 && pos < 71 )
                                                k = 10;
                                            else
                                            {
                                                if( pos > 71 && pos <= 77 )
                                                    k = 11;
                                                else
                                                {
                                                    if ( pos > 77 && pos <= 80 )
                                                        k = 12;
                                                    else
                                                    {
                                                        if ( pos > 80 && pos <= 86 )
                                                            k = 13;
                                                        else
                                                        {
                                                            if ( pos  > 86 && pos <= 91 )
                                                                k = 14;
                                                            else
                                                            {
                                                                if ( pos > 91 && pos <= 94 )
                                                                    k = 15;
                                                                else
                                                                {
                                                                    if ( pos > 94 && pos <= 97 )
                                                                        k = 16;
                                                                    else
                                                                    {
                                                                        if ( pos > 97 && pos <= 100 )
                                                                            k = 17;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    PlaySound(TEXT(noteArray[k].c_str()), NULL, SND_SYNC);
    return noteNames[k];
}

void hz2 ( string matrix [_MAX], string matrix_ [_MAX], int pos[110], int delay )
{
    /*
    * L'ultima funzione a scopo matematico del programma
    * Si occupa del calcolo del valore "pos", gestito da
    * 3 cicli for e due if, mettendo in relazione
    * due matrici bidimensionali, secondo le richieste
    * il valore pos equivale al prodotto tra j e k in scala di i
    * solo in presenza del valore binario "1" in entrambe le posizioni.
    */
    cout << endl << endl;
    int x, y, i = 0;
    string temp, temp2, snd;
    for ( x = 0; x < 10; x++ )
    {
        for ( y = 0; y < 10; y++ )
        {
            temp = matrix[x][y];
            //cout << temp2 << endl << matrix[x][y] << endl;
            if ( temp == "1" )
            {
                for ( int k = 0; k < 10; k++ )
                {
                    temp2 = matrix_[x][k];
                    if ( temp2 == "1" )
                    {
                        pos[i] = (y+1) * (k+1);
                        cout << " xy = (" << x + 1 << "; " << y + 1 << ") \\ xk = (" << x + 1 << "; " << k + 1 << "), pos = " << pos[i];
                        cout << ", nota: " << hz(pos[i]) << endl;
                        Sleep(delay);
                        i++;
                    }
                }
            }
        }
    }
    if ( i == 0 )
        cout << " Non e\' stato trovato nessun valore compatibile per queste due strip " << endl;
}

void getint_input ( int *x, int _min, int _max, string ask )
{
    /*
    * Funzione per ricevere un input x
    * compreso tra un _min ed un _max
    * con output 'ask'
    */
    unsigned int i = 0;
    do
    {
        if ( i > 0 )
        {
            if ( cin.fail() )
                BUFF;
            cout << endl << " Valore inserito non valido!\n (E\' compreso tra " << _min << " e " << _max << "?)" << "\n Riprovare..." << endl;
        }
        cout << endl << ask << " compreso tra " << _min << " e " << _max << " : ";
        ++i;
    }
    while( !(cin >> *x) || *x > _max || *x <_min );
    return;
}

int main( void )
{
    /*
    * Funzione principale del programma
    * dove è possibile vedere la mappa
    * logica dell'algoritmo e la gestione
    * generale delle funzioni.
    */
    SetConsoleTitle("Progetto Fisica");
    system("color f0");
    char check;
    int conf = 0, pos[110], delay;
    cout << " Progetto Fisica Muoni, Liceo P.S. Mancini Avellino \n" << endl;
    string hexstr_1, bin_1[MAX], hexstr_2, bin_2[MAX], hex_1[MAX], hex_2[MAX];
    getint_input ( &delay, 10, 1000, " Inserire delay tra note (default: 190/195) "); // WARN: Questo può variare da computer a computer in alcuni casi
    system("cls");
    cout << " E\' stato impostato un delay di " << delay << "." << endl;
    do
    {
        hexch ( hexstr_1, 1);
        hexch ( hexstr_2, 2);
        for ( int i = 0; i < MAX; ++i )
        {
            // Conversione binaria
            // cout << hexstr_1 << hexstr_2;
            hex_1 [i] = hexstr_1 [i];
            hex_2 [i] = hexstr_2 [i];
            bin_1 [i] = binconv(hex_1 [i]);
            bin_2 [i] = binconv(hex_2 [i]);
        }
    }
    while( hexconf( hex_1, bin_1, hex_2, bin_2, 2 ) != TRUE );
    system("cls");
    cout << " --- Generazione matrice binaria e rimozione cifre --- \n" << endl;
    string binmatrix_1[_MAX], binmatrix_2[_MAX];
    mgen ( binmatrix_1, bin_1 );
    mgen ( binmatrix_2, bin_2 );
    m_print(binmatrix_1, 1);
    m_print(binmatrix_2, 2);
    /*for ( int i = 0; i < _MAX; i++ )
        cout << binmatrix_1[i] << endl << binmatrix_1 [i][2] << endl;*/

    hz2 (binmatrix_1, binmatrix_2, pos, delay);
    cout << " \n\nStampare a triplette su un file (s/n)? ";
    cin >> check;
    if ( check == 's' || check == 'S' )
    {
        do
        {
            if ( fout(hex_1, bin_1, binmatrix_1, hex_2, bin_2, binmatrix_2) == TRUE)
                conf = TRUE;
            else
                conf = FALSE;
        }
        while (conf != TRUE);
    }
    cout << "\n" << endl;
    return EXIT_SUCCESS;
    kbhit();
    getch();
}
