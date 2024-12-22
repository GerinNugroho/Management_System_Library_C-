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

class app
{
private:
    std::vector<structureData> Data;

public:
    // fitur utama
    void tampilkanSemuaBuku(int ukuran, int index);
    bool hapusBuku(std::string Judul);
    bool cariBuku(std::string input);
    bool editDataBuku(std::string input);
    bool tambahBuku(std::string judul, std::string Penulis, std::string TahunTerbit, std::string Penerbit, std::string ISBN, int stock);
    void exportDataBuku();
    void exportDataBukuSql();
    void sortingDataBuku(char input);

    // storage system
    void simpanDataBuku();
    void ambilDataBuku();

    // fitur sampingan
    int ambilJumlahData();
    bool inisialiasiUser();
    void createUser(std::string username, std::string password);
    bool validasiAdmin(std::string username, std::string password);
    std::string capitalize(std::string input);
};