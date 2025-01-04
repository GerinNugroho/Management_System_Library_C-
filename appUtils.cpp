#include "./include/appUtils.h"

// fitur untuk admin
void app::tampilkanDataBuku(int ukuranPage, int indexPage)
{
    int startIndex = indexPage * ukuranPage;
    int endIndex = startIndex + ukuranPage;
    if (!Data.size())
    {
        std::cout << "Tambahkan Data Terlebih dahulu!" << std::endl;
        return;
    };

    if (startIndex >= Data.size())
    {
        std::cout << "Halaman tidak valid" << std::endl;
        return;
    }

    for (int i = startIndex; i < endIndex && i < Data.size(); i++)
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Buku " << i + 1 << "\nJudul: " << Data[i].judul << "\nPenulis: " << Data[i].penulis << "\nTahun Terbit: " << Data[i].tahunTerbit << "\nPenerbit: " << Data[i].penerbit << "\nISBN: " << Data[i].isbn << "\nStock: " << Data[i].stock << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
};
bool app::cariDataBuku(std::string input)
{
    bool find = false;
    bool penulis, judul, isbn;
    std::cout << "Data Yang Ditemukan" << std::endl;
    for (auto it : Data)
    {
        penulis = textFormat(it.penulis, "low") == textFormat(input, "low");
        judul = textFormat(it.judul, "low") == textFormat(input, "low");
        isbn = it.isbn == input;

        if (penulis || judul || isbn)
        {
            std::cout << "\nJudul: " << it.judul << "\nPenulis: " << it.penulis << "\nTahun Terbit: " << it.tahunTerbit << "\nPenerbit: " << it.penerbit << "\nISBN: " << it.isbn << "\nStock: " << it.stock << std::endl;
            find = true;
        }
    }
    return find;
}
bool app::tambahDataBuku(std::string judul, std::string penulis, std::string tahunTerbit, std::string penerbit, std::string ISBN, int stock = 0)
{
    int beforeAdd = Data.size();
    std::string frmtJudul = textFormat(judul, "cap"), frmtPenulis = textFormat(penulis, "cap"), frmtPenerbit = textFormat(penerbit, "cap");

    Data.push_back({frmtJudul, frmtPenulis, tahunTerbit, frmtPenerbit, ISBN, stock});

    if (Data.size() == beforeAdd)
    {
        return false;
    }
    simpanDataBuku();
    return true;
}
bool app::hapusDataBuku(std::string Judul)
{
    int beforeErase = Data.size(), index = 0;
    std::string frmtJudul = textFormat(Judul, "low");
    for (auto it : Data)
    {
        if (textFormat(it.judul, "low") == frmtJudul)
        {
            Data.erase(Data.begin() + index);
        };
        index++;
    }
    if (Data.size() == beforeErase)
    {
        return false;
    }
    simpanDataBuku();
    return true;
}
void app::exportDataBuku()
{

    std::remove("./buku.xls");

    std::ofstream data("./buku.xls", std::ios::app);

    data << "<?xml version=\"1.0\"?><?mso-application progid=\"Excel.Sheet\"?><Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:o=\"urn:schemas-microsoft-com:office:office\" xmlns:x=\"urn:schemas-microsoft-com:office:excel\" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:html=\"http://www.w3.org/TR/REC-html40\">";

    data << "<Styles><Style ss:ID=\"s63\"><Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Bottom\"/><Borders><Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/></Borders></Style>";

    data << "<Style ss:ID=\"s64\"><Borders><Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/></Borders></Style></Styles>";

    data << "<Worksheet ss:Name=\"Sheet1\"><Table><Column ss:Index=\"2\" ss:AutoFitWidth=\"0\" ss:Width=\"100\" ss:Span=\"1\"/>";
    data << "<Row ss:Index=\"2\"> <Cell ss:Index=\"2\" ss:StyleID=\"s63\"><Data ss:Type=\"String\">Judul</Data></Cell>";
    data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Penulis</Data></Cell>";
    data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Tahun Terbit</Data></Cell>";
    data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Penerbit</Data></Cell>";
    data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">ISBN</Data></Cell>";
    data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Stock</Data></Cell>";
    data << " </Row>";

    for (auto it : Data)
    {
        data << "<Row>";
        data << "<Cell ss:Index=\"2\" ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.judul << "</Data></Cell>";
        data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.penulis << "</Data></Cell>";
        data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.tahunTerbit << "</Data></Cell>";
        data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.penerbit << "</Data></Cell>";
        data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.isbn << "</Data></Cell>";
        data << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"Number\">" << it.stock << "</Data></Cell>";
        data << "</Row>";
    };

    data << "</Table></Worksheet></Workbook>";

    data.close();
};
void app::exportDataMember()
{

    std::remove("./member.xls");

    std::ofstream memberFile("./member.xls", std::ios::app);

    memberFile << "<?xml version=\"1.0\"?><?mso-application progid=\"Excel.Sheet\"?><Workbook xmlns=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:o=\"urn:schemas-microsoft-com:office:office\" xmlns:x=\"urn:schemas-microsoft-com:office:excel\" xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\" xmlns:html=\"http://www.w3.org/TR/REC-html40\">";

    memberFile << "<Styles><Style ss:ID=\"s63\"><Alignment ss:Horizontal=\"Center\" ss:Vertical=\"Bottom\"/><Borders><Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/></Borders></Style>";

    memberFile << "<Style ss:ID=\"s64\"><Borders><Border ss:Position=\"Bottom\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Left\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Right\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/><Border ss:Position=\"Top\" ss:LineStyle=\"Continuous\" ss:Weight=\"1\"/></Borders></Style></Styles>";

    memberFile << "<Worksheet ss:Name=\"Sheet1\"><Table><Column ss:Index=\"2\" ss:AutoFitWidth=\"0\" ss:Width=\"100\" ss:Span=\"1\"/>";
    memberFile << "<Row ss:Index=\"2\"> <Cell ss:Index=\"2\" ss:StyleID=\"s63\"><Data ss:Type=\"String\">ID Member</Data></Cell>";
    memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Nama Lengkap</Data></Cell>";
    memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Username</Data></Cell>";
    memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Password</Data></Cell>";
    memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Status Peminjaman</Data></Cell>";
    memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">Judul</Data></Cell>";
    memberFile << " </Row>";

    for (auto it : DataMember)
    {
        std::string judul1 = it.judul1;
        std::string judul2 = it.judul2;
        std::string judul3 = it.judul3;
        memberFile << "<Row>";
        memberFile << "<Cell ss:Index=\"2\" ss:StyleID=\"s63\"><Data ss:Type=\"Number\">" << it.id << "</Data></Cell>";
        memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.fullname << "</Data></Cell>";
        memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.username << "</Data></Cell>";
        memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.password << "</Data></Cell>";
        memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << it.status << "</Data></Cell>";
        memberFile << " <Cell ss:StyleID=\"s63\"><Data ss:Type=\"String\">" << judul1 << ", " << judul2 << ", " << judul3 << "</Data></Cell>";
        memberFile << "</Row>";
    };

    memberFile << "</Table></Worksheet></Workbook>";

    memberFile.close();
};
void app::buatDatabase()
{

    std::remove("./library.sql");

    std::ofstream sql("./library.sql", std::ios::app);

    int list = 1;

    sql << "CREATE TABLE `buku`(`ID_BUKU` varchar(10) NOT NULL,`BUKU` varchar(150) DEFAULT NULL,`PENULIS` varchar(150) DEFAULT NULL,`TAHUN_TERBIT` char(4) DEFAULT NULL,`PENERBIT` varchar(150) DEFAULT NULL,`ISBN` char(50) DEFAULT NULL,`STOCK` char(4) DEFAULT NULL)ENGINE=InnoDB DEFAULT CHARSET=latin1;INSERT INTO `buku`(`ID_BUKU`, `BUKU`, `PENULIS`, `TAHUN_TERBIT`, `PENERBIT`, `ISBN`, `STOCK`) VALUES";

    for (auto it : Data)
    {
        if (list == Data.size())
        {
            sql << "(\'BK" << list << "\',\'" << it.judul << "\',\'" << it.penulis << "\',\'" << it.tahunTerbit << "\',\'" << it.penerbit << "\',\'" << it.isbn << "\',\'" << it.stock << "\');";
        }
        else
        {
            sql << "(\'BK" << list << "\',\'" << it.judul << "\',\'" << it.penulis << "\',\'" << it.tahunTerbit << "\',\'" << it.penerbit << "\',\'" << it.isbn << "\',\'" << it.stock << "\'),";
        }
        list++;
    }

    sql << "CREATE TABLE `member`(`ID_MEMBER` varchar(10) NOT NULL,`NAMA_LENGKAP` varchar(150) DEFAULT NULL,`USERNAME` varchar(150) DEFAULT NULL,`PASSWORD` varchar(150) DEFAULT NULL,`STATUS` varchar(150) DEFAULT NULL,`JUDUL` varchar(150) DEFAULT NULL)ENGINE=InnoDB DEFAULT CHARSET=latin1;INSERT INTO `member`(`ID_MEMBER`, `NAMA_LENGKAP`, `USERNAME`, `PASSWORD`, `STATUS`, `JUDUL`) VALUES";

    list = 1;

    for (auto itMember : DataMember)
    {
        std::string buffer = itMember.judul1 + ", " + itMember.judul2 + ", " + itMember.judul3;
        if (list == DataMember.size())
        {
            sql << "(\'M" << list << "\',\'" << itMember.fullname << "\',\'" << itMember.username << "\',\'" << itMember.password << "\',\'" << itMember.status << "\',\'" << buffer << "\');";
        }
        else
        {
            sql << "(\'M" << list << "\',\'" << itMember.fullname << "\',\'" << itMember.username << "\',\'" << itMember.password << "\',\'" << itMember.status << "\',\'" << buffer << "\'),";
        }
        list++;
    }

    sql << "ALTER TABLE `buku` ADD PRIMARY KEY (`ID_BUKU`);ALTER TABLE `member` ADD PRIMARY KEY (`ID_MEMBER`); COMMIT;";
    sql.close();
}
bool app::editDataBuku(std::string input)
{
    bool edited = false;
    int index = 0;
    for (auto it : Data)
    {
        if (textFormat(it.judul, "low") == textFormat(input, "low") || it.isbn == input)
        {
            std::cout << "\nData yang akan diedit" << std::endl;
            std::cout << std::endl;
            std::cout << "Judul: " << it.judul << "\nPenulis: " << it.penulis << "\nTahun Terbit: " << it.tahunTerbit << "\nPenerbit: " << it.penerbit << "\nISBN: " << it.isbn << "\nStock: " << it.stock << std::endl;

            std::string judul, penulis, tahunTerbit, penerbit, ISBN, stock;
            std::cout << "\nMasukkan data baru" << std::endl;
            std::cout << "Silahkan diisi \'-\' jika tidak ingin mengubah datanya" << std::endl;
            std::cout << std::endl;
            std::cout << "Judul: ";
            getline(std::cin, judul);
            std::cout << "Penulis: ";
            getline(std::cin, penulis);
            std::cout << "Tahun Terbit: ";
            getline(std::cin, tahunTerbit);
            std::cout << "Penerbit: ";
            getline(std::cin, penerbit);
            std::cout << "ISBN: ";
            getline(std::cin, ISBN);
            std::cout << "Stock: ";
            getline(std::cin, stock);

            stock = stock == "-" ? std::to_string(it.stock) : stock;
            Data[index] = {
                judul == "-" ? it.judul : textFormat(judul, "cap"),
                penulis == "-" ? it.penulis : textFormat(penulis, "cap"),
                tahunTerbit == "-" ? it.tahunTerbit : tahunTerbit,
                penerbit == "-" ? it.penerbit : textFormat(penerbit, "cap"),
                ISBN == "-" ? it.isbn : ISBN,
                std::stoi(stock)};
            simpanDataBuku();
            return edited = true;
        }
        index++;
    }
    return edited;
}
void app::sortirDataBuku(char input)
{
    auto compareAlfabet = [&](structureData &b, structureData &e)
    {
        return b.judul < e.judul;
    };

    auto compareStock = [&](structureData &b, structureData &e)
    {
        return b.stock < e.stock;
    };

    if (input == '1')
    {
        std::sort(Data.begin(), Data.end(), compareAlfabet);
    }
    else if (input == '2')
    {
        std::sort(Data.begin(), Data.end(), compareStock);
    }
};
bool app::inisialiasiAdmin()
{
    std::ifstream adminFile("./datas/admin.txt");
    bool status = false;

    if (adminFile.is_open())
    {
        char buffer[1];
        adminFile.getline(buffer, 2);
        if (adminFile.gcount() > 0)
        {
            status = true;
        }
    }
    adminFile.close();
    return status;
}
void app::buatAdmin(std::string username, std::string password)
{
    nameAdmin = username;
    passAdmin = password;
    std::ofstream adminFile("./datas/admin.txt");

    std::replace(username.begin(), username.end(), ' ', '_');
    std::replace(password.begin(), password.end(), ' ', '_');
    adminFile << username << " " << password;

    adminFile.close();
}
bool app::authentikasiAdmin(std::string username, std::string password)
{
    ambilDataAdmin();
    if (username == nameAdmin && password == passAdmin)
    {
        return true;
    }
    return false;
}
void app::tampilkanDataMember(int ukuranPage, int indexPage)
{
    int startIndex = indexPage * ukuranPage;
    int endIndex = startIndex + ukuranPage;
    if (!DataMember.size())
    {
        std::cout << "Tidak ada data member!" << std::endl;
    }

    if (startIndex >= DataMember.size())
    {
        std::cout << "Halaman Tidak Valid!" << std::endl;
        return;
    }

    for (int i = startIndex; i < endIndex && i < DataMember.size(); i++)
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "Nama Lengkap: " << DataMember[i].fullname << "\nUsername: " << DataMember[i].username << "\nPassword: " << DataMember[i].password << "\nStatus: " << DataMember[i].status << "\nJudul: " << DataMember[i].judul1 << ", " << DataMember[i].judul2 << ", " << DataMember[i].judul3 << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
}
void app::hapusDataMember(std::string username)
{
    int index = 0;
    for (auto it : DataMember)
    {
        if (it.username == username)
        {
            DataMember.erase(DataMember.begin() + index);
            std::cout << "Nama Lengkap: " << it.fullname << "\nUsername: " << it.username << "\nStatus: " << it.status << std::endl;
            std::cout << std::endl;
            std::cout << "Data berhasil di hapus!" << std::endl;
            simpanDataMember();
            return;
        }
        index++;
    }
    std::cout << "Data gagal dihapus!" << std::endl;
}
void app::cariFilterDataMember(std::string input)
{
    bool find = false;
    for (auto it : DataMember)
    {
        if (it.username == input && it.status != input)
        {
            std::cout << "Nama Lengkap: " << it.fullname << "\nUsername: " << it.username << "\nPassword: " << it.password << "\nStatus: " << it.status << "\nJudul: " << it.judul1 << ", " << it.judul2 << ", " << it.judul3 << std::endl;
            return;
        }
        else if (it.username != input && it.status == input)
        {
            std::cout << "Nama Lengkap: " << it.fullname << "\nUsername: " << it.username << "\nPassword: " << it.password << "\nStatus: " << it.status << "\nJudul: " << it.judul1 << ", " << it.judul2 << ", " << it.judul3 << std::endl;
            find = true;
        }
    }
    if (!find)
    {
        std::cout << "Data tidak ditemukan!" << std::endl;
    }
};

// fitur untuk member
void app::daftarDataMember(std::string fullname, std::string username, std::string password)
{
    std::string frmtFullname = textFormat(fullname, "cap"), status = "Tidak Meminjam";
    int id = DataMember.size() + 1;
    idActiveMember = id;

    DataMember.push_back({id, frmtFullname, username, password, status});

    std::ofstream memberFile("./datas/member.txt", std::ios::app);

    std::replace(frmtFullname.begin(), frmtFullname.end(), ' ', '_');
    std::replace(username.begin(), username.end(), ' ', '_');
    std::replace(status.begin(), status.end(), ' ', '_');
    memberFile << id << " " << frmtFullname << " " << username << " " << password << " " << status << std::endl;

    memberFile.close();
};
bool app::masukMember(std::string username, std::string password)
{
    for (auto it : DataMember)
    {
        if (it.username == username && it.password == password)
        {
            idActiveMember = it.id;
            return true;
        }
    }
    return false;
}
void app::tampilkanDataBukuMember(int ukuranPage, int indexPage)
{
    int startIndex = indexPage * ukuranPage;
    int endIndex = startIndex + ukuranPage;
    if (!Data.size())
    {
        std::cout << "Tidak ada buku yang tersedia" << std::endl;
        return;
    };

    if (startIndex >= Data.size())
    {
        std::cout << "Halaman tidak valid" << std::endl;
        return;
    }

    for (int i = startIndex; i < endIndex && i < Data.size(); i++)
    {
        std::cout << "-------------------------------" << std::endl;
        std::cout << "\nBuku " << i + 1 << "\nJudul: " << Data[i].judul << "\nPenulis: " << Data[i].penulis << "\nPenerbit: " << Data[i].penerbit << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }
}
void app::cariBukuMember(std::string input)
{
    bool find = false;
    bool judul, penulis;
    int index = 1;
    for (auto it : Data)
    {
        judul = textFormat(it.judul, "low") == textFormat(input, "low");
        penulis = textFormat(it.penulis, "low") == textFormat(input, "low");
        if (judul || penulis)
        {
            std::cout << "-------------------------------" << std::endl;
            std::cout << "Buku " << index << "\nJudul: " << it.judul << "\nPenulis: " << it.penulis << "\nPenerbit: " << it.penerbit << std::endl;
            std::cout << "-------------------------------" << std::endl;
            find = true;
        }
        index++;
    }
    if (!find)
    {
        std::cout << "Buku tidak ditemukan!" << std::endl;
    }
}
void app::pinjamBukuMember(std::string judul, std::string activeMember, int id)
{
    int index = 0;
    for (auto it : DataMember)
    {
        if (it.username == activeMember)
        {
            for (int i = 0; i < Data.size(); i++)
            {
                if (textFormat(Data[i].judul, "low") == textFormat(judul, "low"))
                {
                    textFormat(Data[i].judul, "cap");
                    if (it.judul1.empty())
                    {
                        DataMember[index].judul1 = Data[i].judul;
                    }
                    else if (it.judul2.empty())
                    {
                        DataMember[index].judul2 = Data[i].judul;
                    }
                    else if (it.judul3.empty())
                    {
                        DataMember[index].judul3 = Data[i].judul;
                    }
                    else
                    {
                        std::cout << "Hanya dapat meminjam 3 buku" << std::endl;
                        return;
                    }
                    Data[i].stock -= 1;
                    DataMember[index].status = "Meminjam";
                    std::cout << "Peminjaman berhasil dilakukan dengan judul " << Data[i].judul << std::endl;
                    simpanDataBuku();
                    simpanDataMember();
                    return;
                }
            }
        }
        index++;
    }
    std::cout << "Buku yang dipinjam tidak ada" << std::endl;
}
void app::kembalikanBukuMember(std::string activeMember, int id)
{
    int index = 0;
    for (auto it : DataMember)
    {
        if (it.username == activeMember && it.id == id)
        {
            if (it.judul1.empty())
            {
                std::cout << "Anda belum melakukan peminjaman!" << std::endl;
                return;
            };
            std::cout << "1. " << it.judul1 << std::endl;
            std::cout << "2. " << it.judul2 << std::endl;
            std::cout << "3. " << it.judul3 << std::endl;

            for (int i = 0; i < Data.size(); i++)
            {
                if (Data[i].judul == it.judul1)
                {
                    Data[i].stock += 1;
                }
                else if (Data[i].judul == it.judul2)
                {
                    Data[i].stock += 1;
                }
                else if (Data[i].judul == it.judul3)
                {
                    Data[i].stock += 1;
                }
            }
            DataMember[index].judul1.clear();
            DataMember[index].judul2.clear();
            DataMember[index].judul3.clear();
            DataMember[index].status = "Tidak Meminjam";
            simpanDataBuku();
            simpanDataMember();
            std::cout << "Buku berhasil dikembalikan!" << std::endl;
            return;
        }
        index++;
    }
};
void app::tampilkanBukuMember(std::string activeMember, int id)
{
    for (auto it : DataMember)
    {
        if (it.username == activeMember && it.id == id)
        {
            if (it.judul1.empty())
            {
                std::cout << "Anda belum meminjam buku" << std::endl;
                return;
            }
            std::cout << "-------------------------------" << std::endl;
            std::cout << it.fullname << "\nJudul1: " << it.judul1 << "\nJudul2: " << it.judul2 << "\nJudul3: " << it.judul3 << std::endl;
            std::cout << "-------------------------------" << std::endl;
            return;
        }
    }
}

// storage system
void app::simpanDataBuku()
{
    std::ofstream saveDataFile("./datas/datas.txt");
    std::string bufferData;
    for (auto it : Data)
    {
        std::replace(it.judul.begin(), it.judul.end(), ' ', '_');
        std::replace(it.penulis.begin(), it.penulis.end(), ' ', '_');
        std::replace(it.penerbit.begin(), it.penerbit.end(), ' ', '_');
        bufferData += it.judul + " " + it.penulis + " " + it.tahunTerbit + " " + it.penerbit + " " + it.isbn + " " + std::to_string(it.stock) + "\n";
    }

    saveDataFile << bufferData;
    saveDataFile.close();
}
void app::ambilDataBuku()
{
    std::ifstream loadDataFile("./datas/datas.txt");
    Data.clear();
    std::string line;
    while (getline(loadDataFile, line))
    {
        std::istringstream iss(line);
        std::string data, judul, penulis, tahunterbit, penerbit, isbn;
        int index = 0, stock;
        while (iss >> data)
        {
            if (index == 0)
            {
                std::replace(data.begin(), data.end(), '_', ' ');
                judul = data;
            }
            else if (index == 1)
            {
                std::replace(data.begin(), data.end(), '_', ' ');
                penulis = data;
            }
            else if (index == 2)
            {
                tahunterbit = data;
            }
            else if (index == 3)
            {
                std::replace(data.begin(), data.end(), '_', ' ');
                penerbit = data;
            }
            else if (index == 4)
            {
                isbn = data;
            }
            else if (index == 5)
            {
                stock = std::stoi(data);
            }
            index++;
        }
        tambahDataBuku(judul, penulis, tahunterbit, penerbit, isbn, stock);
    };

    loadDataFile.close();
};
void app::ambilDataMember()
{
    std::ifstream loadMemberFile("./datas/member.txt");

    std::string line, word, fullname, username, password, status, judul1, judul2, judul3;
    int id, index;

    while (getline(loadMemberFile, line))
    {
        index = 0;
        std::istringstream frmtLine(line);
        while (frmtLine >> word)
        {
            if (index == 0)
            {
                id = std::stoi(word);
            }
            else if (index == 1)
            {
                std::replace(word.begin(), word.end(), '_', ' ');
                fullname = word;
            }
            else if (index == 2)
            {
                std::replace(word.begin(), word.end(), '_', ' ');
                username = word;
            }
            else if (index == 3)
            {
                password = word;
            }
            else if (index == 4)
            {
                std::replace(word.begin(), word.end(), '_', ' ');
                status = word;
            }
            else if (index == 5)
            {
                std::replace(word.begin(), word.end(), '_', ' ');
                judul1 = word;
            }
            else if (index == 6)
            {
                std::replace(word.begin(), word.end(), '_', ' ');
                judul2 = word;
            }
            else if (index == 7)
            {
                std::replace(word.begin(), word.end(), '_', ' ');
                judul3 = word;
            }
            index++;
        }
        DataMember.push_back({id, fullname, username, password, status, judul1, judul2, judul3});
        judul1.clear();
        judul2.clear();
        judul3.clear();
    }
    loadMemberFile.close();
}
void app::simpanDataMember()
{
    std::remove("./datas/member.txt");
    std::ofstream saveMemberFile("./datas/member.txt", std::ios::app);

    for (auto it : DataMember)
    {
        std::replace(it.status.begin(), it.status.end(), ' ', '_');
        std::replace(it.fullname.begin(), it.fullname.end(), ' ', '_');
        std::replace(it.username.begin(), it.username.end(), ' ', '_');
        std::replace(it.judul1.begin(), it.judul1.end(), ' ', '_');
        std::replace(it.judul2.begin(), it.judul2.end(), ' ', '_');
        std::replace(it.judul3.begin(), it.judul3.end(), ' ', '_');
        saveMemberFile << it.id << " " << it.fullname + " " << it.username << " " << it.password << " " << it.status << " " << it.judul1 << " " << it.judul2 << " " << it.judul3 << std::endl;
    }
    saveMemberFile.close();
}
void app::ambilDataAdmin()
{
    std::ifstream adminFile("./datas/admin.txt");

    std::string word;
    int index = 0;
    while (adminFile >> word)
    {
        std::replace(word.begin(), word.end(), '_', ' ');
        if (index == 0)
        {
            nameAdmin = word;
        }
        else if (index == 1)
        {
            passAdmin = word;
        }
        index++;
    }
    adminFile.close();
}

// fungsi pendukung
int app::ambilJumlahData()
{
    return Data.size();
}
std::string app::textFormat(std::string input, std::string form)
{
    int inputSize = input.size();
    for (int i = 0; i < inputSize; i++)
    {
        if ((i == 0 || input[i - 1] == ' ') && form == "cap")
        {
            input[i] = toupper(input[i]);
        }
        else if ((true) && form == "low")
        {
            input[i] = tolower(input[i]);
        }
    }
    return input;
}
int app::ambilIdMemberActive()
{
    return idActiveMember;
}
int app::ambilJumlahDataMember()
{
    return DataMember.size();
}
void app::errorcheck()
{
    for (auto it : DataMember)
    {
        std::cout << it.status << " " << it.judul1 << " " << it.judul2 << " " << it.judul3 << " " << std::endl;
    }
}