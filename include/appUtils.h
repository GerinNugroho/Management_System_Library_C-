#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdio>

struct structureData
{
    std::string judul;
    std::string penulis;
    std::string tahunTerbit;
    std::string penerbit;
    std::string isbn;
    int stock;
};

struct structureMember
{
    int id;
    std::string fullname;
    std::string username;
    std::string password;
    std::string status;
    std::string judul1;
    std::string judul2;
    std::string judul3;
};

class app
{
private:
    std::vector<structureData> Data;
    std::vector<structureMember> DataMember;
    std::string nameAdmin;
    std::string passAdmin;
    int idActiveMember;

public:
    // fitur untuk admin
    void tampilkanDataBuku(int ukuranPage, int indexPage);
    bool hapusDataBuku(std::string judul);
    bool cariDataBuku(std::string input);
    bool editDataBuku(std::string input);
    bool tambahDataBuku(std::string judul, std::string penulis, std::string tahunTerbit, std::string penerbit, std::string ISBN, int stock);
    void exportDataBuku();
    void exportDataMember();
    void buatDatabase();
    void sortirDataBuku(char input);
    bool inisialiasiAdmin();
    void buatAdmin(std::string username, std::string password);
    bool authentikasiAdmin(std::string username, std::string password);
    void tampilkanDataMember(int ukuranPage, int indexPage);
    void hapusDataMember(std::string username);
    void cariFilterDataMember(std::string input);

    // fitur untuk member
    void daftarDataMember(std::string fullname, std::string username, std::string password);
    bool masukMember(std::string username, std::string password);
    void tampilkanDataBukuMember(int ukuranPage, int indexPage);
    void cariBukuMember(std::string input);
    void pinjamBukuMember(std::string judul, std::string activeMember, int id);
    void kembalikanBukuMember(std::string activeMember, int id);
    void tampilkanBukuMember(std::string activeMember, int id);

    // storage system
    void simpanDataBuku();
    void ambilDataBuku();
    void ambilDataMember();
    void simpanDataMember();
    void ambilDataAdmin();

    // fungsi pendukung
    int ambilJumlahData();
    std::string textFormat(std::string input, std::string form);
    int ambilIdMemberActive();
    int ambilJumlahDataMember();
    void errorcheck();
};