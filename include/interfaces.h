#pragma once
#include "appUtils.h"
#include <iostream>
#include <string>
#include <stdlib.h>

class interfaces
{
private:
    app utils;
    std::string inptJudul, inptPenulis, inptTahunTerbit, inptPenerbit, inptISBN, inptStock;
    std::string username, password;
    char choose;
    int ukuranPage = 5, indexPage, jumlahData;

public:
    interfaces()
    {
        utils.ambilDataBuku();
    };
    void initUser()
    {
        utils.inisialiasiUser();
        if (!utils.inisialiasiUser())
        {
            std::cout << "========== Inisialisasi Pengguna ==========" << std::endl;
            std::cout << "Buat username: ";
            getline(std::cin, username);
            std::cout << "Buat password: ";
            getline(std::cin, password);
            utils.createUser(username, password);
        }
    }

    bool loginUser()
    {
        std::cout << "========== Autentikasi Pengguna ==========" << std::endl;
        std::cout << "Masukkan Username: ";
        getline(std::cin, username);
        std::cout << "Masukkan Password: ";
        getline(std::cin, password);

        if (!utils.validasiAdmin(username, password))
        {
            return false;
            system("cls");
        };
        system("cls");
        return true;
    }

    char menu()
    {
        indexPage = 0;
        std::cout << "========== Library System ==========" << std::endl;
        std::cout << "1. Tambah data buku" << std::endl;
        std::cout << "2. Hapus data buku" << std::endl;
        std::cout << "3. Edit data buku" << std::endl;
        std::cout << "4. Cari data buku" << std::endl;
        std::cout << "5. Tampilkan data buku" << std::endl;
        std::cout << "6. Export data buku" << std::endl;
        std::cout << "7. Buat database sql" << std::endl;
        std::cout << "8. keluar program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        return choose;
    }

    void tambahData()
    {
        std::cin.ignore();
        std::cout << "========== Tambah Data Buku ==========" << std::endl;
        std::cout << "Masukkan Judul Buku: ";
        getline(std::cin, inptJudul);
        std::cout << "Masukkan Penulis Buku: ";
        getline(std::cin, inptPenulis);
        std::cout << "Masukkan Tahun Terbit: ";
        getline(std::cin, inptTahunTerbit);
        std::cout << "Masukkan Penerbit Buku: ";
        getline(std::cin, inptPenerbit);
        std::cout << "Masukkan ISBN Buku: ";
        getline(std::cin, inptISBN);
        std::cout << "Masukkan Jumlah Buku: ";
        getline(std::cin, inptStock);

        utils.tambahBuku(inptJudul, inptPenulis, inptTahunTerbit, inptPenerbit, inptISBN, stoi(inptStock));

        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }

    void hapusData()
    {
    page:
        jumlahData = utils.ambilJumlahData();
        system("cls");
        std::cout << "========== Hapus Data Buku ==========" << std::endl;
        utils.tampilkanSemuaBuku(ukuranPage, indexPage);
        std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << std::endl;
        std::cout << "Masukkan input: ";
        std::cin >> choose;

        if (choose == 'n')
        {
            if ((indexPage + 1) * ukuranPage < jumlahData)
            {
                indexPage++;
            }
            else
            {
                std::cin.ignore();
                std::cout << "Halaman terakhir ";
                std::cin.get();
            }
            system("cls");
            goto page;
        }
        else if (choose == 'p')
        {
            if (indexPage > 0)
            {
                indexPage--;
            }
            else
            {
                std::cin.ignore();
                std::cout << "Halaman pertama ";
                std::cin.get();
            }
            system("cls");
            goto page;
        }

        std::cin.ignore();
        std::cout << "Masukkan Judul Buku: ";
        getline(std::cin, inptJudul);

        utils.hapusBuku(inptJudul);

        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }

    void editData()
    {
        do
        {
            jumlahData = utils.ambilJumlahData();
            system("cls");
            std::cout << "========== Edit Data Buku ==========" << std::endl;
            utils.tampilkanSemuaBuku(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk preveious, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan input: ";
            std::cin >> choose;

            if (choose == 'n')
            {
                if ((indexPage + 1) * ukuranPage < jumlahData)
                {
                    indexPage++;
                }
                else
                {
                    std::cin.ignore();
                    std::cout << "Halaman terakhir ";
                    std::cin.get();
                }
                system("cls");
            }
            else if (choose == 'p')
            {
                if (indexPage > 0)
                {
                    indexPage--;
                }
                else
                {
                    std::cin.ignore();
                    std::cout << "Halaman pertama ";
                    std::cin.get();
                }
                system("cls");
            }
        } while (choose == 'n' || choose == 'p');
        std::cin.ignore();
        std::cout << "Masukkan Judul/ISBN buku: ";
        getline(std::cin, inptJudul);
        if (!utils.editDataBuku(inptJudul))
        {
            std::cout << "Buku tidak ditemukan!" << std::endl;
        }
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }

    void cariData()
    {
        system("cls");
        std::cout << "========== Cari Data Buku ==========" << std::endl;
        std::cin.ignore();
        std::cout << "Masukkan judul/penulis/ISBN: ";
        getline(std::cin, inptPenulis);
        utils.cariBuku(inptPenulis);
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }

    void tampilkanData()
    {
        do
        {
            jumlahData = utils.ambilJumlahData();
            system("cls");
            std::cout << "========== Tampilkan Data Buku ==========" << std::endl;
            utils.tampilkanSemuaBuku(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan input: ";
            std::cin >> choose;

            if (choose == 'n')
            {
                if ((indexPage + 1) * ukuranPage < jumlahData)
                {
                    indexPage++;
                }
                else
                {
                    std::cin.ignore();
                    std::cout << "halaman terakhir ";
                    std::cin.get();
                }
                system("cls");
            }
            else if (choose == 'p')
            {
                if (indexPage > 0)
                {
                    indexPage--;
                }
                else
                {
                    std::cin.ignore();
                    std::cout << "halaman pertama ";
                    std::cin.get();
                }
                system("cls");
            }
        } while (choose == 'n' || choose == 'p');

        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }

    void exportData()
    {
        utils.exportDataBuku();
        std::cout << "Data telah berhasil di export" << std::endl;
        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }

    void buatDatabaseSql()
    {
        utils.exportDataBukuSql();
        std::cout << "Database telah berhasil di buat" << std::endl;
        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
    }

    void saveData()
    {
        utils.simpanDataBuku();
    };
};