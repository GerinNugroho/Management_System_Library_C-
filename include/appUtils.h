#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstdio>

struct stuctureData {
    std::string judul;
    std::string penulis;
    std::string tahunTerbit;
    std::string penerbit;
    std::string isbn;
    int stock;
};

class app {
private:
    std::vector<stuctureData> database;
public:
    void tampilkanSemuaBuku(int ukuran, int index);
    int ambilJumlahData();
    void cariBuku(std::string Penulis);
    void tambahBuku(std::string judul, std::string Penulis, std::string TahunTerbit, std::string Penerbit, std::string ISBN, int stock);
    void hapusBuku(std::string Judul);
    void exportDataBuku();
    void exportDataBukuSql();
    void simpanDataBuku();
    void ambilDataBuku();
    void inisialiasiUser();
    bool editDataBuku(std::string input);
    bool validasiAdmin(std::string username, std::string password);
    void test();
};