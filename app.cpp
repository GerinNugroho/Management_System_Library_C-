#include "./include/interfaces.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    interfaces interface;

    interface.initUser();

login:
    if (!interface.loginUser())
    {
        goto login;
    }

menu:
    switch (interface.menu())
    {
    case '1':
        interface.tambahData();
        goto menu;
        break;
    case '2':
        interface.hapusData();
        goto menu;
        break;
    case '3':
        interface.editData();
        goto menu;
        break;
    case '4':
        interface.sortDataBuku();
        cin.ignore();
        cout << "Tekan enter untuk melanjutkan";
        cin.get();
        system("cls");
        goto menu;
        break;
    case '5':
        interface.cariData();
        goto menu;
        break;
    case '6':
        interface.tampilkanData();
        goto menu;
        break;
    case '7':
        interface.exportData();
        goto menu;
        break;
    case '8':
        interface.buatDatabaseSql();
        goto menu;
        break;
    case '9':
        interface.saveData();
        break;
    default:
        cin.ignore();
        cout << "Masukkan angka yang benar!";
        cin.get();
        system("cls");
        goto menu;
        break;
    };
    cout << "Terima kasih sudah menggunakan program kami!";
    return 0;
}