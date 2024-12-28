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
    std::string username, password, fullname, activeMember;
    char choose;
    int ukuranPage = 3, indexPage, jumlahData, jumlahDataMember, idMember;

public:
    interfaces()
    {
        utils.ambilDataBuku();
        utils.ambilDataMember();
    };

    char loginSelection()
    {
        system("cls");
        activeMember.clear();
        idMember = 0;
        std::cout << "========== Masuk Sebagai ==========" << std::endl;
        std::cout << "1. Member" << std::endl;
        std::cout << "2. Admin" << std::endl;
        std::cout << "3. Keluar Program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        std::cin.ignore();
        return choose;
    }

    // interfaces untuk admin
    bool initAdmin()
    {
        if (!utils.inisialiasiAdmin())
        {
            system("cls");
            std::cout << "========== Inisialisasi Admin ==========" << std::endl;
            std::cout << "Buat username: ";
            getline(std::cin, username);
            std::cout << "Buat password: ";
            getline(std::cin, password);
            utils.buatAdmin(username, password);
            std::cout << "Inisialisai admin selesai! " << std::endl;
            std::cout << "Tekan enter untuk lanjut ";
            std::cin.get();
            system("cls");
            return true;
        }
    }
    bool authentikasiAdmin()
    {
        system("cls");
        std::cout << "========== Authentikasi Admin ==========" << std::endl;
        std::cout << "Masukkan Username: ";
        getline(std::cin, username);
        std::cout << "Masukkan Password: ";
        getline(std::cin, password);

        if (!utils.authentikasiAdmin(username, password))
        {
            std::cout << "username dan password tidak cocok! ";
            std::cin.get();
            system("cls");
            return false;
        };
        system("cls");
        return true;
    }
    std::string menuAdmin(char index)
    {
        indexPage = 0;
        jumlahData = utils.ambilJumlahData();
        jumlahDataMember = utils.ambilJumlahDataMember();
        if (index == '0')
        {
            system("cls");
            std::cout << "========== System Management Data Perpustakaan ==========" << std::endl;
            std::cout << "1. Tambah data buku" << std::endl;
            std::cout << "2. Hapus data buku" << std::endl;
            std::cout << "3. Edit data buku" << std::endl;
            std::cout << "4. Sort data buku" << std::endl;
            std::cout << "5. Cari data buku" << std::endl;
            std::cout << "6. Tampilkan data buku" << std::endl;
            std::cout << "7. Tampilkan data member" << std::endl;
            std::cout << "8. Hapus data Member" << std::endl;
            std::cout << "9. Cari & Filter data member" << std::endl;
        }
        else if (index == '1')
        {
            system("cls");
            std::cout << "========== System Management Data Perpustakaan ==========" << std::endl;
            std::cout << "10. Export data buku" << std::endl;
            std::cout << "11. Buat database sql" << std::endl;
            std::cout << "12. Kembali" << std::endl;
            std::cout << "13. Keluar program" << std::endl;
        }
        std::cout << "NOTE: Silahkan isi \'n\' untuk next dan \'p\' untuk previous" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> input;;
        return input;
    }
    void tambahDataBuku()
    {
        system("cls");
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

            std::cin.ignore();
            switch (choose)
            {
            case 'n':
                if((indexPage + 1) * ukuranPage  < jumlahData) {
                    indexPage++;
                    system("cls");
                }else {
                    std::cout << "Halaman Terakhir ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'p':
                if(indexPage > 0) {
                    indexPage--;
                    system("cls");
                }else {
                    std::cout << "Halaman Pertama ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'q':
                break;
            default:
                std::cout << "Silahkan isi \'q\' untuk lanjut! ";
                choose = 'n';
                std::cin.get();
                system("cls");
                break;
            }
        } while (choose == 'n' || choose == 'p');
        std::cout << "Masukkan Judul Buku: ";
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

            std::cin.ignore();
            switch (choose)
            {
            case 'n':
                if((indexPage + 1) * ukuranPage  < jumlahData) {
                    indexPage++;
                    system("cls");
                }else {
                    std::cout << "Halaman Terakhir ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'p':
                if(indexPage > 0) {
                    indexPage--;
                    system("cls");
                }else {
                    std::cout << "Halaman Pertama ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'q':
                break;
            default:
                std::cout << "Silahkan isi \'q\' untuk lanjut! ";
                choose = 'n';
                std::cin.get();
                system("cls");
                break;
            }
        } while (choose == 'n' || choose == 'p');
        std::cout << "Masukkan Judul/ISBN buku: ";
        getline(std::cin, input);
        if (!utils.editDataBuku(input))
        {
            std::cout << "Gagal mengedit data buku!" << std::endl;
        }else {
            std::cout << "Berhasil mengedit data buku!" << std::endl;
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
        do
        {
            utils.tampilkanDataBuku(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk preveious, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan perintah: ";
            std::cin >> choose;

            switch (choose)
            {
            case 'n':
                if((indexPage + 1) * ukuranPage  < jumlahData) {
                    indexPage++;
                }else {
                    std::cout << "Halaman Terakhir ";
                    std::cin.get();
                }
                break;
            case 'p':
                if(indexPage > 0) {
                    indexPage--;
                }else {
                    std::cout << "Halaman Pertama ";
                    std::cin.get();
                }
                break;
            case 'q':
                break;
            default:
                std::cout << "Silahkan isi \'q\' untuk lanjut! ";
                choose = 'n';
                std::cin.get();
                break;
            }
        } while (choose == 'n' || choose == 'p');
        std::cout << "Apakah anda yakin dengan list ini(y/n): ";
        std::cin >> choose;

        if (choose == 'y')
        {
            std::cout << "Data hasil sortir disimpan" << std::endl;
            utils.simpanDataBuku();
        }
        else if (choose == 'n')
        {
            std::cout << "Data hasil sortir dibatalkan" << std::endl;
            utils.ambilDataBuku();
        }
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
            std::cout << "Masukkan perintah: ";
            std::cin >> choose;

            std::cin.ignore();
            switch (choose)
            {
            case 'n':
                if((indexPage + 1) * ukuranPage  < jumlahData) {
                    indexPage++;
                    system("cls");
                }else {
                    std::cout << "Halaman Terakhir ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'p':
                if(indexPage > 0) {
                    indexPage--;
                    system("cls");
                }else {
                    std::cout << "Halaman Pertama ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'q':
                break;
            default:
                std::cout << "Silahkan isi \'q\' untuk lanjut! ";
                choose = 'n';
                std::cin.get();
                system("cls");
                break;
            }
        } while (choose == 'n' || choose == 'p');
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }
    void exportData()
    {
        utils.exportDataBuku();
        utils.exportDataMember();
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
    void simpanData()
    {
        utils.simpanDataBuku();
        utils.simpanDataMember();
    };
    void tampilkanDataMember()
    {
        do{
            system("cls");
            std::cout << "========== Tampilkan Data Buku ==========" << std::endl;
            utils.tampilkanDataMember(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, dan \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan perintah: ";
            std::cin >> choose;

            std::cin.ignore();
            switch (choose)
            {
            case 'n':
                if((indexPage + 1) * ukuranPage < jumlahDataMember) 
                {
                    indexPage++;
                }else {
                    std::cout << "Halaman Terakhir ";
                    std::cin.get();
                }
                break;
            case 'p':
                if(indexPage > 0) {
                    indexPage--;
                }else {
                    std::cout << "Halaman Pertama ";
                    std::cin.get();
                }
                break;
            case 'q':
                break;
            default:
                std::cout << "Silahkan isi \'q\' untuk lanjut! ";
                choose = 'n';
                std::cin.get();
                break;
            }
        }while(choose == 'n' || choose == 'p');
        std::cout << "Tekan enter untuk lanjut! ";
        std::cin.get();
        system("cls");
    }
    void hapusDataMember()
    {
        system("cls");
        std::cout << "========== Hapus Data Member ==========" << std::endl;
        std::cout << "Masukkan username member: " << std::endl;
        std::cin.ignore();
        getline(std::cin, input);
        utils.hapusDataMember(input);
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }
    void cariFilterDataMember()
    {
        system("cls");
        std::cout << "========== Cari & Filter Data Member ==========" << std::endl;
        std::cout << "Masukkan username/status: ";
        std::cin.ignore();
        getline(std::cin, input);
        utils.cariFilterDataMember(input);
        std::cout << "Tekan enter untuk lanjut! ";
        std::cin.get();
        system("cls");
    }

    // interfaces untuk member
    char menuMasukMember()
    {
        activeMember = " ";
        system("cls");
        std::cout << "========== Selamat Datang ==========" << std::endl;
        std::cout << "1. Daftar Member" << std::endl;
        std::cout << "2. Masuk Member" << std::endl;
        std::cout << "3. kembali" << std::endl;
        std::cout << "4. Keluar Program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
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
        activeMember = username;
        std::cout << "Masukkan password: ";
        getline(std::cin, password);
        utils.daftarDataMember(fullname, username, password);
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
        activeMember = username;
        if (!utils.masukMember(username, password))
        {
            std::cout << "Gagal masuk kombinasi username dan password anda salah" << std::endl;
            status = false;
        }
        idMember = utils.ambilIdMemberActive();
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
        std::cout << "5. Tampilkan Buku Member" << std::endl;
        std::cout << "6. kembali" << std::endl;
        std::cout << "7. keluar Program" << std::endl;
        std::cout << "Pilih dari menu: ";
        std::cin >> choose;
        return choose;
    }
    void tampilkanDataBukuMember()
    {
        do
        {
            system("cls");
            std::cout << "========== Buku yang tersedia ==========" << std::endl;
            utils.tampilkanDataBukuMember(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan perintah: ";
            std::cin >> choose;

            std::cin.ignore();
            switch (choose)
            {
            case 'n':
                if((indexPage + 1) * ukuranPage  < jumlahData) {
                    indexPage++;
                    system("cls");
                }else {
                    std::cout << "Halaman Terakhir ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'p':
                if(indexPage > 0) {
                    indexPage--;
                    system("cls");
                }else {
                    std::cout << "Halaman Pertama ";
                    std::cin.get();
                    system("cls");
                }
                break;
            case 'q':
                break;
            default:
                std::cout << "Silahkan isi \'q\' untuk lanjut! ";
                choose = 'n';
                std::cin.get();
                system("cls");
                break;
            }
        } while (choose == 'n' || choose == 'p');
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
            utils.tampilkanDataBukuMember(ukuranPage, indexPage);
            std::cout << "NOTE: \'n\' untuk next, \'p\' untuk previous, \'q\' untuk lanjut" << std::endl;
            std::cout << "Masukkan perintah: ";
            std::cin >> choose;

            std::cin.ignore();
            switch (choose)
            {
            case 'n':
                if((indexPage + 1) * ukuranPage  < jumlahData) {
                    indexPage++;
                }else {
                    std::cout << "Halaman Terakhir ";
                    std::cin.get();
                }
                break;
            case 'p':
                if(indexPage > 0) {
                    indexPage--;
                }else {
                    std::cout << "Halaman Pertama ";
                    std::cin.get();
                }
                break;
            case 'q':
                break;
            default:
                std::cout << "Silahkan isi \'q\' untuk lanjut! ";
                choose = 'n';
                std::cin.get();
                break;
            }
        } while (choose == 'n' || choose == 'p');
        std::cout << "Masukkan judul buku: ";
        getline(std::cin, judul);
        utils.pinjamBukuMember(judul, activeMember, idMember);
        std::cout << "Tekan enter untuk melanjutkan!";
        std::cin.get();
        system("cls");
    }
    void kembalikanBukuMember()
    {
        system("cls");
        std::cout << "========== Pengembalian Buku ==========" << std::endl;
        utils.kembalikanBukuMember(activeMember, idMember);
        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }
    void tampilkanBukuMember()
    {
        system("cls");
        std::cout << "========== Buku Yang Dipinjam ==========" << std::endl;
        utils.tampilkanBukuMember(activeMember, idMember);
        std::cin.ignore();
        std::cout << "Tekan enter untuk melanjutkan! ";
        std::cin.get();
        system("cls");
    }
};