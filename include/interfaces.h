#pragma once
#include "appUtils.h"
#include <iostream>
#include <string>
#include <stdlib.h>

class interfaces
{
private:
    app utils;
    std::string input, judul, penulis, tahunterbit, penerbit, ISBN, stock;
    std::string username, password, fullname;
    char choose;
    int ukuranPage = 5, indexPage, jumlahData;

public:
    interfaces()
    {
        utils.ambilDataBuku();
        utils.ambilDataMember();
    };

    char loginSelection()
    {
        system("cls");
        std::cout << "========== Masuk Sebagai ==========" << std::endl;
        std::cout << "1. Member" << std::endl;
        std::cout << "2. Admin" << std::endl;
        std::cout << "3. Keluar Program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        system("cls");
        return choose;
    }

    // interfaces untuk admin
    void initAdmin()
    {
        if (!utils.inisialiasiAdmin())
        {
            std::cout << "========== Inisialisasi Admin ==========" << std::endl;
            std::cout << "Buat username: ";
            std::cin.ignore();
            getline(std::cin, username);
            std::cout << "Buat password: ";
            getline(std::cin, password);
            utils.buatAdmin(username, password);
            system("cls");
        }
    }
    bool authentikasiAdmin()
    {
        std::cout << "========== Authentikasi Admin ==========" << std::endl;
        std::cout << "Masukkan Username: ";
        std::cin.ignore();
        getline(std::cin, username);
        std::cout << "Masukkan Password: ";
        getline(std::cin, password);

        if (!utils.authentikasiAdmin(username, password))
        {
            system("cls");
            return false;
        };
        system("cls");
        return true;
    }
    char menuAdmin()
    {
        indexPage = 0;
        jumlahData = utils.ambilJumlahData();
        system("cls");
        std::cout << "========== System Management Data Perpustakaan ==========" << std::endl;
        std::cout << "1. Tambah data buku" << std::endl;
        std::cout << "2. Hapus data buku" << std::endl;
        std::cout << "3. Edit data buku" << std::endl;
        std::cout << "4. Sort data buku" << std::endl;
        std::cout << "5. Cari data buku" << std::endl;
        std::cout << "6. Tampilkan data buku" << std::endl;
        std::cout << "7. Export data buku" << std::endl;
        std::cout << "8. Buat database sql" << std::endl;
        std::cout << "9. keluar program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        system("cls");
        return choose;
    }
    void tambahDataBuku()
    {
        std::cout << "========== Tambah Data Buku ==========" << std::endl;
        std::cout << "Masukkan Judul Buku: ";
        std::cin.ignore();
        getline(std::cin, judul);
        std::cout << "Masukkan Penulis Buku: ";
        getline(std::cin, penulis);
        std::cout << "Masukkan Tahun Terbit: ";
        getline(std::cin, tahunterbit);
        std::cout << "Masukkan Penerbit Buku: ";
        getline(std::cin, penerbit);
        std::cout << "Masukkan ISBN Buku: ";
        getline(std::cin, ISBN);
        std::cout << "Masukkan Jumlah Buku: ";
        getline(std::cin, stock);

        if (utils.tambahDataBuku(judul, penulis, tahunterbit, penerbit, ISBN, stoi(stock)))
        {
            std::cout << "Data berhasil ditambahkan" << std::endl;
        }
        else
        {
            std::cout << "Data gagal ditambahkan" << std::endl;
        }

        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }
    void hapusDataBuku()
    {
        do
        {
            system("cls");
            std::cout << "========== Hapus Data Buku ==========" << std::endl;
            utils.tampilkanDataBuku(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan perintah: ";
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
        std::cout << "Masukkan Judul Buku: ";
        std::cin.ignore();
        getline(std::cin, judul);

        if (utils.hapusDataBuku(judul))
        {
            std::cout << "Data berhasil dihapus" << std::endl;
        }
        else
        {
            std::cout << "Data gagal di hapus" << std::endl;
        }
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }
    void editDataBuku()
    {
        do
        {
            system("cls");
            std::cout << "========== Edit Data Buku ==========" << std::endl;
            utils.tampilkanDataBuku(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk preveious, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan perintah: ";
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
        std::cout << "Masukkan Judul/ISBN buku: ";
        std::cin.ignore();
        getline(std::cin, input);
        if (!utils.editDataBuku(input))
        {
            std::cout << "Buku tidak ditemukan!" << std::endl;
        }
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }
    void cariDataBuku()
    {
        system("cls");
        std::cout << "========== Cari Data Buku ==========" << std::endl;
        std::cout << "Masukkan judul/penulis/ISBN: ";
        std::cin.ignore();
        getline(std::cin, input);
        if (!utils.cariDataBuku(input))
        {
            std::cout << "Buku tidak ditemukan!" << std::endl;
        };
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }
    void sortirDataBuku()
    {
        system("cls");
        std::cout << "========== Sortir Data Buku ==========" << std::endl;
        utils.simpanDataBuku();
        std::cout << "Silahkan pilih metode sortir" << std::endl;
        std::cout << "1. Alfabet" << std::endl;
        std::cout << "2. Stock" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        utils.sortirDataBuku(choose);
        std::cout << "\nList Data Hasil Sorting\n"<< std::endl;
        do{
            utils.tampilkanDataBuku(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk preveious, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan perintah: ";
            std::cin >> choose;
            if(choose == 'n') 
            { 
                if((indexPage + 1) * ukuranPage < jumlahData) {
                    indexPage++;
                }else {
                    std::cin.ignore();
                    std::cout << "Halaman terakhir ";
                    std::cin.get();
                }
            }else if (choose == 'p')
            {
                if(indexPage > 0) {
                    indexPage--;
                }else {
                    std::cin.ignore();
                    std::cout << "Halaman pertama ";
                    std::cin.get();
                }
            }
        }while(choose == 'n' || choose == 'p');
        std::cout << "Apakah anda yakin dengan list ini(y/n): ";
        std::cin >> choose;

        if (choose == 'y')
        {
            std::cout << "Data hasil sortir disimpan" << std::endl;
        }
        else if (choose == 'n')
        {
            std::cout << "Data hasil sortir dibatalkan" << std::endl;
            utils.ambilDataBuku();
        }
        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan";
        std::cin.get();
        system("cls");
    }
    void tampilkanDataBuku()
    {
        do
        {
            system("cls");
            std::cout << "========== Tampilkan Data Buku ==========" << std::endl;
            utils.tampilkanDataBuku(ukuranPage, indexPage);
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
        utils.buatDatabase();
        std::cout << "Database telah berhasil di buat" << std::endl;
        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }
    void simpanDataBuku()
    {
        utils.simpanDataBuku();
    };

    // interfaces untuk member
    char menuMasukMember()
    {
        system("cls");
        std::cout << "========== Selamat Datang ==========" << std::endl;
        std::cout << "1. Daftar Member" << std::endl;
        std::cout << "2. Masuk Member" << std::endl;
        std::cout << "3. Kembali " << std::endl;
        std::cout << "4. Keluar Program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        system("cls");
        return choose;
    }
    void signMember()
    {
        system("cls");
        std::cin.ignore();
        std::cout << "========== Daftar Member ==========" << std::endl;
        std::cout << "Masukkan nama lengkap: ";
        getline(std::cin, fullname);
        std::cout << "Masukkan username: ";
        getline(std::cin, username);
        std::cout << "Masukkan password: ";
        getline(std::cin, password);
        utils.simpanDataMember(fullname, username, password);
        std::cout << "Anda sekarang member" << std::endl;
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }
    bool loginMember()
    {
        bool status = true;
        system("cls");
        std::cout << "========== Masuk Member ==========" << std::endl;
        std::cout << "Masukkan username: ";
        std::cin.ignore();
        getline(std::cin, username);
        std::cout << "Masukkan password: ";
        getline(std::cin, password);
        if (!utils.masukMember(username, password))
        {
            std::cout << "Gagal masuk kombinasi username dan password anda salah" << std::endl;
            status = false;
        }
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
        return status;
    }
    char menuMember()
    {
        system("cls");
        indexPage = 0;
        jumlahData = utils.ambilJumlahData();
        std::cout << "========== Selamat Datang di perpustakaan ==========" << std::endl;
        std::cout << "1. Lihat buku yang tersedia" << std::endl;
        std::cout << "2. Cari Buku" << std::endl;
        std::cout << "3. Pinjam Buku" << std::endl;
        std::cout << "4. Kembalikan Buku" << std::endl;
        std::cout << "5. keluar" << std::endl;
        std::cout << "6. keluar Program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        system("cls");
        return choose;
    }
    void tampilkanBukuMember()
    {
        do
        {
            system("cls");
            std::cout << "========== Buku yang tersedia ==========" << std::endl;
            utils.tampilkanBukuMember(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan input: ";
            std::cin >> choose;

            if (choose == 'n')
            {
                if ((indexPage + 1) * ukuranPage < ukuranPage)
                {
                    indexPage++;
                }
                else
                {
                    std::cin.ignore();
                    std::cout << "halaman terakhir ";
                    std::cin.get();
                }
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
            }
        } while (choose == 'n' || choose == 'p');

        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }
    void cariBukuMember()
    {
        system("cls");
        std::cout << "========== Cari Buku ==========" << std::endl;
        std::cout << "Masukkan Judul/Penulis buku: ";
        std::cin.ignore();
        getline(std::cin, judul);
        utils.cariBukuMember(judul);
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    };
    void pinjamBukuMember()
    {
        do
        {
            system("cls");
            std::cout << "========== Peminjaman Buku ==========" << std::endl;
            utils.tampilkanBukuMember(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan input: ";
            std::cin >> choose;

            if (choose == 'n')
            {
                if ((indexPage + 1) * ukuranPage < ukuranPage)
                {
                    indexPage++;
                }
                else
                {
                    std::cin.ignore();
                    std::cout << "halaman terakhir ";
                    std::cin.get();
                    system("cls");
                }
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
                    system("cls");
                }
            }
        } while (choose == 'n' || choose == 'p');
        std::cout << "Masukkan judul buku: " << std::endl;
        std::cin.ignore();
        getline(std::cin, judul);
        utils.pinjamBukuMember(judul);
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }
};