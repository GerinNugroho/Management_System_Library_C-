#include "./include/appUtils.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main () {
    app utils;
    utils.ambilDataBuku();
    string inptJudul, inptPenulis, inptTahunTerbit, inptPenerbit, inptISBN, inptStock;
    string username, password;

    char choose;
    int ukuranPage = 5, indexPage = 0, jumlahData;

    utils.inisialiasiUser();
    system("cls");

    login:
    cout << "========== Autentikasi Pengguna ==========" << endl;
    cout << "Masukkan Username: ";
    getline(cin, username);
    cout << "Masukkan Password: ";
    getline(cin, password);

    if(!utils.validasiAdmin(username, password)) {
        cout << "Anda bukan admin ";
        cin.get();
        system("cls");
        goto login;
        return 0;
    };

    system("cls");
    
    menu:
    jumlahData = utils.ambilJumlahData();
    menuAdmin();
    cout << "Pilih dari menu: ";
    cin >> choose;
    switch (choose)
    {
    case '1':
        system("cls");
        cout << "========== Tambah Data Buku ==========" << endl;
        cin.ignore();
        cout << "Masukkan Judul Buku: ";
        getline(cin, inptJudul);
        cout << "Masukkan Penulis Buku: ";
        getline(cin, inptPenulis);
        cout << "Masukkan Tahun Terbit: ";
        cin >> inptTahunTerbit;
        cin.ignore();
        cout << "Masukkan Penerbit Buku: ";
        getline(cin, inptPenerbit);
        cout << "Masukkan ISBN Buku: ";
        cin >> inptISBN;
        cout << "Masukkan Jumlah Buku: ";
        cin >> inptStock;
        utils.tambahBuku(inptJudul, inptPenulis, inptTahunTerbit, inptPenerbit, inptISBN, stoi(inptStock));
        cin.ignore();
        cout << "Tekan enter untuk melanjutkan!";
        cin.get();
        system("cls");
        goto menu;
        break;
    case '2':
        page:
        system("cls");
        cout << "========== Hapus Data Buku ==========" << endl;
        utils.tampilkanSemuaBuku(ukuranPage, indexPage);
        cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << endl;
        cout << "Masukkan input: ";
        cin >> choose;

        if(choose == 'n') {
            if((indexPage + 1) * ukuranPage < jumlahData) {
                indexPage++;
            }else {
                cin.ignore();
                cout << "Halaman terakhir ";
                cin.get();
            }
            system("cls");
            goto page;
        }else if (choose == 'p') {
            if(indexPage > 0) {
                indexPage--;
            }else {
                cin.ignore();
                cout << "Halaman pertama ";
                cin.get();
            }
            system("cls");
            goto page;
        }

        cin.ignore();
        cout << "Masukkan Judul Buku: ";
        getline(cin, inptJudul);
        utils.hapusBuku(inptJudul);
        cout << "Tekan enter untuk melanjutkan! ";
        cin.get();
        system("cls");
        goto menu;
        break;
    case '3':
        do{
            system("cls");
            cout << "========== Edit Data Buku ==========" << endl;
            utils.tampilkanSemuaBuku(ukuranPage, indexPage);
            cout << "NOTE: \'n\' untuk next, \'p\' untuk preveious, \'q\' untuk lanjut" << endl;
            cout << "Masukkan input: ";
            cin >> choose;

            if(choose == 'n') {
                if((indexPage + 1) * ukuranPage < jumlahData) {
                    indexPage++;
                }else {
                    cin.ignore();
                    cout << "Halaman terakhir ";
                    cin.get();
                }
                system("cls");
            }else if(choose == 'p') {
                if(indexPage > 0) {
                    indexPage--;
                }else {
                    cin.ignore();
                    cout << "Halaman pertama ";
                    cin.get();
                }
                system("cls");
            }
        }while(choose == 'n' || choose == 'p');
        cin.ignore();
        cout << "Masukkan Judul/ISBN buku: ";
        getline(cin, inptJudul);
        if(!utils.editDataBuku(inptJudul)) {
            cout << "Buku tidak ditemukan!" << endl;
        }
        cout << "Tekan enter untuk melanjutkan! ";
        cin.get();
        system("cls");
        goto menu;
        break;
    case '4':
        system("cls");
        cout << "========== Cari Data Buku ==========" << endl;
        cin.ignore();
        cout << "Masukkan judul/penulis/ISBN: ";
        getline(cin, inptPenulis);
        utils.cariBuku(inptPenulis);
        cout << "Tekan enter untuk melanjutkan!";
        cin.get();
        system("cls");
        goto menu;
        break;
    case '5':
        do{
            system("cls");
            cout << "========== Tampilkan Data Buku ==========" << endl;
            utils.tampilkanSemuaBuku(ukuranPage, indexPage);
            cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << endl;
            cout << "Masukkan input: ";
            cin >> choose;

            if(choose == 'n') {
                if((indexPage + 1) * ukuranPage < jumlahData) {
                    indexPage++;
                }else {
                    cin.ignore();
                    cout << "halaman terakhir ";
                    cin.get();
                }
                system("cls");
            }else if(choose == 'p') {
                if(indexPage > 0) {
                    indexPage--;
                }else {
                    cin.ignore();
                    cout << "halaman pertama ";
                    cin.get();
                }
                system("cls");
            }
        }while (choose == 'n' || choose == 'p');
        
        cin.ignore();
        cout << "Tekan enter untuk melanjutkan!";
        cin.get();
        system("cls");
        goto menu;
        break;
    case '6':
        utils.exportDataBuku();
        cout << "Data telah berhasil di export" << endl;
        cin.ignore();
        cout << "Tekan enter untuk melanjutkan! ";
        cin.get();
        system("cls");
        goto menu;
        break;
    case '7':
        utils.exportDataBukuSql();
        cout << "Database telah berhasil di buat" << endl;
        cin.ignore();
        cout << "Tekan enter untuk melanjutkan! ";
        cin.get();
        goto menu;
        break;
    case '8':
        utils.simpanDataBuku();
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