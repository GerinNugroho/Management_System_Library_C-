#include "./include/interfaces.h"
using namespace std;

int main()
{
    interfaces interface;

loginSelection:
    char callback = interface.loginSelection();

    if (callback == '1')
    {
    menuMasukMember:
        callback = interface.menuMasukMember();

        if (callback == '1')
        {
            interface.signMember();
        }
        else if (callback == '2')
        {
            if (!interface.loginMember())
            {
                goto menuMasukMember;
            }
        }
        else if (callback == '3')
        {
            goto loginSelection;
        }
        else if (callback == '4')
        {
            interface.simpanData();
            cin.ignore();
            cout << "Anda telah keluar dari program! ";
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
        callback = interface.menuMember();
        switch (callback)
        {
        case '1':
            interface.tampilkanDataBukuMember();
            goto menuMember;
            break;
        case '2':
            interface.cariBukuMember();
            goto menuMember;
            break;
        case '3':
            interface.pinjamBukuMember();
            goto menuMember;
            break;
        case '4':
            interface.kembalikanBukuMember();
            goto menuMember;
            break;
        case '5':
            interface.tampilkanBukuMember();
            goto menuMember;
            break;
        case '6':
            goto menuMasukMember;
            break;
        case '7':
            interface.simpanData();
            cin.ignore();
            cout << "Anda telah keluar dari program! ";
            cin.get();
            return 0;
        default:
            cin.ignore();
            cout << "Masukkan angka yang benar!";
            cin.get();
            system("cls");
            goto menuMember;
            break;
        }
    }
    else if (callback == '2')
    {
        interface.initAdmin();

        if (!interface.authentikasiAdmin())
        {
            goto loginSelection;
        }

        char indexPage = '0';
    menuAdmin:
        string chooseAdmin = interface.menuAdmin(indexPage);
        if (chooseAdmin == "1")
        {
            interface.tambahDataBuku();
            goto menuAdmin;
        }
        else if (chooseAdmin == "2")
        {
            interface.hapusDataBuku();
            goto menuAdmin;
        }
        else if (chooseAdmin == "3")
        {
            interface.editDataBuku();
            goto menuAdmin;
        }
        else if (chooseAdmin == "4")
        {
            interface.sortirDataBuku();
            goto menuAdmin;
        }
        else if (chooseAdmin == "5")
        {
            interface.cariDataBuku();
            goto menuAdmin;
        }
        else if (chooseAdmin == "6")
        {
            interface.tampilkanDataBuku();
            goto menuAdmin;
        }
        else if (chooseAdmin == "7")
        {
            interface.tampilkanDataMember();
            goto menuAdmin;
        }
        else if (chooseAdmin == "8")
        {
            interface.hapusDataMember();
            goto menuAdmin;
        }
        else if (chooseAdmin == "9")
        {
            interface.cariFilterDataMember();
            goto menuAdmin;
        }
        else if (chooseAdmin == "10")
        {
            interface.exportData();
            goto menuAdmin;
        }
        else if (chooseAdmin == "11")
        {
            interface.buatDatabaseSql();
            goto menuAdmin;
        }
        else if (chooseAdmin == "12")
        {
            goto loginSelection;
        }
        else if (chooseAdmin == "13")
        {
            interface.simpanData();
            cin.ignore();
            cout << endl;
            cout << "Anda telah keluar dari program! ";
            cin.get();
            return 0;
        }
        else if (chooseAdmin == "n")
        {
            indexPage = '1';
            goto menuAdmin;
        }
        else if (chooseAdmin == "p")
        {
            indexPage = '0';
            goto menuAdmin;
        }
        else
        {
            cin.ignore();
            cout << "Masukkan angka yang benar!";
            cin.get();
            system("cls");
            goto menuAdmin;
        }
    }
    else if (callback == '3')
    {
        interface.simpanData();
        cout << "Anda telah keluar dari program! ";
        cin.get();
        return 0;
    }
    else
    {
        cin.ignore();
        cout << "Masukkan angka yang benar!";
        cin.get();
        system("cls");
        goto loginSelection;
    };
    return 0;
}