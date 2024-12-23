#include "./include/appUtils.h"

using std::fstream;
using std::ifstream;
using std::ofstream;

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
        std::cout << "Buku " << i + 1 << "\nJudul: " << Data[i].judul << "\nPenulis: " << Data[i].penulis << "\nTahun Terbit: " << Data[i].tahunTerbit << "\nPenerbit: " << Data[i].penerbit << "\nISBN: " << Data[i].isbn << "\nStock: " << Data[i].stock << "\n"
                  << std::endl;
    }
};
bool app::cariDataBuku(std::string input)
{
    bool find = false;
    for (auto it : Data)
    {
        if (it.penulis == input || it.judul == input || it.isbn == input)
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
    std::string frmtJudul = capitalize(judul), frmtPenulis = capitalize(penulis), frmtPenerbit = capitalize(penerbit);

    Data.push_back({frmtJudul, frmtPenulis, tahunTerbit, frmtPenerbit, ISBN, stock});

    if (Data.size() == beforeAdd)
    {
        return false;
    }
    return true;
}
bool app::hapusDataBuku(std::string Judul)
{
    int beforeErase = Data.size(), index = 0;
    std::string frmtJudul = capitalize(Judul);
    for (auto it : Data)
    {
        if (it.judul == frmtJudul)
        {
            Data.erase(Data.begin() + index);
        };
        index++;
    }
    if (Data.size() == beforeErase)
    {
        return false;
    }
    return true;
}
void app::exportDataBuku()
{

    std::remove("./library.xls");

    ofstream data("./library.xls", std::ios::app);

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
void app::buatDatabase()
{

    std::remove("./library.sql");

    ofstream sql("./library.sql", std::ios::app);

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

    sql << "ALTER TABLE `buku` ADD PRIMARY KEY (`ID_BUKU`); COMMIT;";
    sql.close();
}
bool app::editDataBuku(std::string input)
{
    bool edited = false;
    int index = 0;
    for (auto it : Data)
    {
        if (it.judul == capitalize(input) || it.isbn == input)
        {
            std::cout << "\nData yang akan diedit" << std::endl;
            std::cout << "Judul: " << it.judul << "\nPenulis: " << it.penulis << "\nTahun Terbit: " << it.tahunTerbit << "\nPenerbit: " << it.penerbit << "\nISBN: " << it.isbn << "\nStock: " << it.stock << std::endl;

            std::string judul, penulis, tahunTerbit, penerbit, ISBN, stock;
            std::cout << "\nMasukkan data baru" << std::endl;
            std::cout << "NOTE: Silahkan diisi \"-\" jika tidak ingin mengubah datanya!" << std::endl;
            std::cout << "Judul: ";
            std::cin.ignore();
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
                judul == "-" ? it.judul : capitalize(judul),
                penulis == "-" ? it.penulis : capitalize(penulis),
                tahunTerbit == "-" ? it.tahunTerbit : tahunTerbit,
                penerbit == "-" ? it.penerbit : capitalize(penerbit),
                ISBN == "-" ? it.isbn : ISBN,
                std::stoi(stock)};
            std::cout << "Data berhasil di edit" << std::endl;
            return edited = true;
        }
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
    ifstream adminFile("./datas/admin.txt");
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
    ofstream adminFile("./datas/admin.txt");

    std::replace(username.begin(), username.end(), ' ', '_');
    std::replace(password.begin(), password.end(), ' ', '_');
    adminFile << username << " " << password;

    adminFile.close();
}
bool app::authentikasiAdmin(std::string username, std::string password)
{
    fstream adminFile("./datas/admin.txt");

    std::string line;
    bool validate = false;

    while (getline(adminFile, line))
    {
        std::istringstream iss(line);
        std::string Fusername, Fpassword, word;
        int index = 0;
        while (iss >> word)
        {
            std::replace(word.begin(), word.end(), '_', ' ');
            if (index == 0)
            {
                Fusername = word;
            }
            else if (index == 1)
            {
                Fpassword = word;
            }
            index++;
        }

        if (Fusername == username && Fpassword == password)
        {
            validate = true;
        }
    }
    adminFile.close();
    return validate;
}

// fitur untuk member 
void app::simpanDataMember(std::string fullname, std::string username, std::string password)
{
    std::string frmtFullname = capitalize(fullname), status = "Tidak Meminjam";
    int id = DataMember.size() + 1;

    DataMember.push_back({id, frmtFullname, username, password, status});

    ofstream memberFile("./datas/member.txt", std::ios::app);

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
            return true;
        }
    }
    return false;
}
void app::tampilkanBukuMember(int ukuranPage, int indexPage)
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
        std::cout << "\nBuku " << i + 1 << "\nJudul: " << Data[i].judul << "\nPenulis: " << Data[i].penulis << "\nPenerbit: " << Data[i].penerbit << std::endl;
    }
}
void app::cariBukuMember(std::string input)
{
    bool find = false;
    int index = 1;
    for (auto it : Data)
    {
        if (it.judul == input || it.penulis == input)
        {
            std::cout << "\nBuku " << index << "\nJudul: " << it.judul
                      << "\nPenulis: " << it.penulis << "\nPenerbit: " << it.penerbit << std::endl;
            find = true;
        }
        index++;
    }
    if (!find)
    {
        std::cout << "Buku tidak ditemukan!" << std::endl;
    }
}
void app::pinjamBukuMember(std::string judul)
{
    bool find = false;
    int index = 0;
    for (auto it : Data)
    {
        if (it.judul == judul)
        {
            Data[index].stock -= 1;
            find = true;
        }
        index++;
    }
    if (!find)
    {
        std::cout << "Buku gagal dipinjam karna tidak ada!" << std::endl;
        return;
    }

    std::cout << "Buku berhasil dipinjam!" << std::endl;
    simpanDataBuku();
}

// storage system
void app::simpanDataBuku()
{
    ofstream datasFile("./datas/datas.txt");
    std::string bufferData;
    for (auto it : Data)
    {
        std::replace(it.judul.begin(), it.judul.end(), ' ', '_');
        std::replace(it.penulis.begin(), it.penulis.end(), ' ', '_');
        std::replace(it.penerbit.begin(), it.penerbit.end(), ' ', '_');
        bufferData += it.judul + " " + it.penulis + " " + it.tahunTerbit + " " + it.penerbit + " " + it.isbn + " " + std::to_string(it.stock) + "\n";
    }

    datasFile << bufferData;
    datasFile.close();
}
void app::ambilDataBuku()
{
    fstream datasFile("./datas/datas.txt");
    Data.clear();
    std::string line;
    while (getline(datasFile, line))
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

    datasFile.close();
};
void app::ambilDataMember()
{
    fstream memberFile("./datas/member.txt");

    std::string line, word, fullname, username, password, status;
    int id, index;

    while (getline(memberFile, line))
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
            index++;
        }
        DataMember.push_back({id, fullname, username, password, status});
    }
    memberFile.close();
}

// fungsi pendukung
int app::ambilJumlahData()
{
    return Data.size();
}
std::string app::capitalize(std::string input)
{
    int inputSize = input.size();
    for (int i = 0; i < inputSize; i++)
    {
        if (i == 0 || input[i - 1] == ' ')
        {
            input[i] = toupper(input[i]);
        }
    }
    return input;
}
