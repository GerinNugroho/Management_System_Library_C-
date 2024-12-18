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
    int ukuranPage = 5, indexPage = 0, jumlahData;

public:
    interfaces()
    {
        utils.ambilDataBuku();
    };
    void initUser();
    bool loginUser();
    char menu();
    void tambahData();
    void hapusData();
    void editData();
    void cariData();
    void tampilkanData();
    void exportData();
    void buatDatabaseSql();
    void saveData();
};