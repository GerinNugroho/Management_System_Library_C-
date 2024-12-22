#include "./include/appUtils.h"

using std::fstream;
using std::ifstream;
using std::ofstream;

// fitur utama
void app::tampilkanSemuaBuku(int ukuran, int index)
{
    int startIndex = index * ukuran;
    int endIndex = startIndex + ukuran;
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
bool app::cariBuku(std::string input)
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
bool app::tambahBuku(std::string Judul, std::string Penulis, std::string TahunTerbit, std::string Penerbit, std::string ISBN, int Stock = 0)
{
    int beforeAdd = Data.size();
    std::string frmtJudul = capitalize(Judul), frmtPenulis = capitalize(Penulis), frmtPenerbit = capitalize(Penerbit);

    Data.push_back({frmtJudul, frmtPenulis, TahunTerbit, frmtPenerbit, ISBN, Stock});

    if (Data.size() == beforeAdd)
    {
        return false;
    }
    return true;
}
bool app::hapusBuku(std::string Judul)
{
    int sizeData = Data.size();
    std::string frmtJudul = capitalize(Judul);
    for (int i = 0; i < sizeData; i++)
    {
        if (Data[i].judul == frmtJudul)
        {
            Data.erase(Data.begin() + i);
        };
    }
    if (Data.size() == sizeData)
    {
        return false;
    }
    return true;
}
void app::exportDataBuku()
{

    std::remove("./library.xls");

    ofstream data("./library.xls", std::ios::app);
    int list = 1;

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
void app::exportDataBukuSql()
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
    for (int i = 0; i < Data.size(); i++)
    {
        if (Data[i].judul == capitalize(input) || Data[i].isbn == input)
        {
            std::cout << "\nData yang akan diedit" << std::endl;
            std::cout << "Judul: " << Data[i].judul << "\nPenulis: " << Data[i].penulis << "\nTahun Terbit: " << Data[i].tahunTerbit << "\nPenerbit: " << Data[i].penerbit << "\nISBN: " << Data[i].isbn << "\nStock: " << Data[i].stock << std::endl;

            std::string bfrJudul, bfrPenulis, bfrTahunTerbit, bfrPenerbit, bfrISBN, bfrStock;
            std::cout << "\nMasukkan data baru" << std::endl;
            std::cout << "NOTE: Silahkan diisi \"-\" jika tidak ingin mengubah datanya!" << std::endl;
            std::cout << "Judul: ";
            getline(std::cin, bfrJudul);
            std::cout << "Penulis: ";
            getline(std::cin, bfrPenulis);
            std::cout << "Tahun Terbit: ";
            getline(std::cin, bfrTahunTerbit);
            std::cout << "Penerbit: ";
            getline(std::cin, bfrPenerbit);
            std::cout << "ISBN: ";
            getline(std::cin, bfrISBN);
            std::cout << "Stock: ";
            getline(std::cin, bfrStock);

            bfrStock = bfrStock == "-" ? std::to_string(Data[i].stock) : bfrStock;
            Data[i] = {
                bfrJudul == "-" ? Data[i].judul : capitalize(bfrJudul),
                bfrPenulis == "-" ? Data[i].penulis : capitalize(bfrPenulis),
                bfrTahunTerbit == "-" ? Data[i].tahunTerbit : bfrTahunTerbit,
                bfrPenerbit == "-" ? Data[i].penerbit : capitalize(bfrPenerbit),
                bfrISBN == "-" ? Data[i].isbn : bfrISBN,
                std::stoi(bfrStock)};
            std::cout << "Data berhasil di edit" << std::endl;
            return edited = true;
        }
    }
    return edited;
}
void app::sortingDataBuku(char input)
{
    auto compareAlfabet = [&](structureData &b, structureData &e)
    {
        return b.judul < e.judul;
    };

    auto compareStock = [&](structureData &b, structureData &e)
    {
        return b.stock < e.stock;
    };

    if(input == '1') {
        std::sort(Data.begin(), Data.end(), compareAlfabet);
    }else if(input == '2') {
        std::sort(Data.begin(), Data.end(), compareStock);
    }
};

// storage system
void app::simpanDataBuku()
{
    ofstream datas("./datas/datas.txt");
    std::string bufferData;
    for (auto it : Data)
    {
        std::replace(it.judul.begin(), it.judul.end(), ' ', '_');
        std::replace(it.penulis.begin(), it.penulis.end(), ' ', '_');
        std::replace(it.penerbit.begin(), it.penerbit.end(), ' ', '_');
        bufferData += it.judul + " " + it.penulis + " " + it.tahunTerbit + " " + it.penerbit + " " + it.isbn + " " + std::to_string(it.stock) + "\n";
    }

    datas << bufferData;
    datas.close();
}
void app::ambilDataBuku()
{
    fstream datas("./datas/datas.txt");
    Data.clear();
    std::string line;
    while (getline(datas, line))
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
        tambahBuku(judul, penulis, tahunterbit, penerbit, isbn, stock);
    };

    datas.close();
};

// fitur sampingan
bool app::inisialiasiUser()
{
    ifstream pengguna("./datas/pengguna.txt");

    if (pengguna.is_open())
    {
        char buffer[1];
        pengguna.getline(buffer, 2);
        if (pengguna.gcount() > 0)
        {
            return true;
        }
    }
    return false;
    pengguna.close();
}
void app::createUser(std::string username, std::string password)
{
    ofstream writePengguna("./datas/pengguna.txt");

    std::replace(username.begin(), username.end(), ' ', '_');
    std::replace(password.begin(), password.end(), ' ', '_');
    writePengguna << username << " " << password;

    writePengguna.close();
}
bool app::validasiAdmin(std::string inptusername, std::string inptpassword)
{
    fstream pengguna("./datas/pengguna.txt");

    std::string line;
    bool validate = false;

    while (getline(pengguna, line))
    {
        std::istringstream iss(line);
        std::string username, password, data;
        int index = 0;
        while (iss >> data)
        {
            std::replace(data.begin(), data.end(), '_', ' ');
            if (index == 0)
            {
                username = data;
            }
            else if (index == 1)
            {
                password = data;
            }
            index++;
        }

        if (username == inptusername && password == inptpassword)
        {
            return validate = true;
        }
    }
    pengguna.close();
    return validate;
}
int app::ambilJumlahData()
{
    return Data.size();
}
std::string app::capitalize (std::string input) 
{
    int inputSize = input.size();
    for(int i = 0; i < inputSize; i++) {
        if(i == 0 || input[i - 1] == ' ') {
            input[i] = toupper(input[i]);
        }
    }
    return input;
}