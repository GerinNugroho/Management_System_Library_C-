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
};

class app
{
private:
    std::vector<structureData> Data;
    std::vector<structureMember> DataMember;

public:
    // fitur untuk admin
    void tampilkanDataBuku(int ukuranPage, int indexPage);
    bool hapusDataBuku(std::string judul);
    bool cariDataBuku(std::string input);
    bool editDataBuku(std::string input);
    bool tambahDataBuku(std::string judul, std::string penulis, std::string tahunTerbit, std::string penerbit, std::string ISBN, int stock);
    void exportDataBuku();
    void buatDatabase();
    void sortirDataBuku(char input);
    bool inisialiasiAdmin();
    void buatAdmin(std::string username, std::string password);
    bool authentikasiAdmin(std::string username, std::string password);
    
    // fitur untuk member
    void simpanDataMember (std::string fullname, std::string username, std::string password);
    bool masukMember(std::string username, std::string password);
    void tampilkanBukuMember(int ukuranPage, int indexPage);
    void cariBukuMember(std::string input);
    void pinjamBukuMember(std::string judul);

    // storage system
    void simpanDataBuku();
    void ambilDataBuku();
    void ambilDataMember ();

    // fungsi pendukung
    int ambilJumlahData();
    std::string capitalize(std::string input);
};