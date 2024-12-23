#include "./include/interfaces.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    interfaces interface;

loginSelection:
    char login = interface.loginSelection();

    if (login == '1')
    {
        bool member;
    menuMasukMember:
        login = interface.menuMasukMember();

        if (login == '1')
        {
            interface.signMember();
        }
        else if (login == '2')
        {
            if(!interface.loginMember()) {
                goto menuMasukMember;
            }
        }
        else if (login == '3')
        {
            goto loginSelection;
        }
        else if (login == '4')
        {
            cin.ignore();
            cout << "Terima kasih sudah menggunakan program kami!";
            cin.get();
            return 0;
        }
        else
        {
            cin.ignore();
            cout << "Masukkan angka yang benar!";
            cin.get();
            system("cls");
            goto menuMasukMember;
        }

    menuMember:
        switch (interface.menuMember())
        {
        case '1':
            interface.tampilkanBukuMember();
            goto menuMember;
            break;
        case '2':
            interface.cariBukuMember();
            goto menuMember;
            break;
        case '3':
            interface.pinjamBukuMember();
            break;
        case '4':
            break;
        case '5':
            goto menuMasukMember;
            break;
        case '6':
            break;
        default:
            break;
        }
    }
    else if (login == '2')
    {
        interface.initAdmin();

    loginAdmin:
        if (!interface.authentikasiAdmin())
        {
            goto loginAdmin;
        }

    menuAdmin:
        switch (interface.menuAdmin())
        {
        case '1':
            interface.tambahDataBuku();
            goto menuAdmin;
            break;
        case '2':
            interface.hapusDataBuku();
            goto menuAdmin;
            break;
        case '3':
            interface.editDataBuku();
            goto menuAdmin;
            break;
        case '4':
            interface.sortirDataBuku();
            goto menuAdmin;
            break;
        case '5':
            interface.cariDataBuku();
            goto menuAdmin;
            break;
        case '6':
            interface.tampilkanDataBuku();
            goto menuAdmin;
            break;
        case '7':
            interface.exportData();
            goto menuAdmin;
            break;
        case '8':
            interface.buatDatabaseSql();
            goto menuAdmin;
            break;
        case '9':
            interface.simpanDataBuku();
            break;
        default:
            cin.ignore();
            cout << "Masukkan angka yang benar!";
            cin.get();
            system("cls");
            goto menuAdmin;
            break;
        };
    }
    else if (login == '3')
    {
    }
    else
    {
        cin.ignore();
        cout << "Masukkan angka yang benar!";
        cin.get();
        system("cls");
        goto loginSelection;
    };
    cin.ignore();
    cout << "Terima kasih sudah menggunakan program kami!";
    cin.get();
    return 0;
}