#include "./include/interfaces.h"
using namespace std;

int main()
{
    interfaces interface;

loginSelection:
    char callback = interface.loginSelection();

    if (callback == '1')
    {
        bool member;
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
        callback = interface.menuMember();
        switch (callback)
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
            goto menuMember;
            break;
        case '4':
            interface.kembalikanBukuMember();
            goto menuMember;
            break;
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
    else if (callback == '2')
    {
        interface.initAdmin();

    loginAdmin:
        if (!interface.authentikasiAdmin())
        {
            goto loginAdmin;
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
            interface.simpanDataBuku();
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
    }
    else
    {
        cin.ignore();
        cout << "Masukkan angka yang benar!";
        cin.get();
        system("cls");
        goto loginSelection;
    };
    cout << "Terima kasih sudah menggunakan program kami!";
    cin.get();
    return 0;
}