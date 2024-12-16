#include "./include/appUtils.h"

using std::ofstream;
using std::fstream;
using std::ifstream;

void app::tampilkanSemuaBuku(int ukuran, int index) {
    int startIndex = index * ukuran;
    int endIndex = startIndex + ukuran;
    if(!database.size()) {
        std::cout << "Tambahkan Data Terlebih dahulu!" << std::endl;
        return;
    };

    if(startIndex >= database.size()) {
        std::cout << "Halaman tidak valid" << std::endl;
        return;
    }

    for(int i = startIndex; i < endIndex && i < database.size(); i++) {
        std::cout << "Buku "<< i + 1 << "\nJudul: "<< database[i].judul << "\nPenulis: " << database[i].penulis << "\nTahun Terbit: " << database[i].tahunTerbit << "\nPenerbit: " << database[i].penerbit << "\nISBN: " << database[i].isbn << "\nStock: " << database[i].stock << "\n" << std::endl;
    }
};

void app::cariBuku(std::string input) {
    bool find = false;
    for(auto it : database) {
        if(it.penulis == input || it.judul == input || it.isbn == input) {
            std::cout << "\nJudul: " << it.judul <<"\nPenulis: " << it.penulis << "\nTahun Terbit: " << it.tahunTerbit << "\nPenerbit: " << it.penerbit << "\nISBN: " << it.isbn <<"\nStock: " << it.stock << std::endl;
            find = true;
        }
    }
    if(!find) {
        std::cout << "Buku tidak ditemukan!" << std::endl;
    }
}

void app::tambahBuku(std::string Judul, std::string Penulis, std::string TahunTerbit, std::string Penerbit, std::string ISBN, int Stock = 0) {
    database.push_back({Judul, Penulis, TahunTerbit, Penerbit, ISBN, Stock});
    std::cout << "Buku berhasil di tambahkan!" << std::endl;
}

void app::hapusBuku(std::string Judul) {
    int sizeData = database.size();

    for(int i = 0; i < sizeData; i++) {
        if(database[i].judul == Judul) {
            database.erase(database.begin() + i);
        };
    }
    if(database.size() == sizeData) {
        std::cout << "Buku tidak ada di list!" << std::endl;
        return;
    }
    std::cout << "Buku berhasil di hapus" << std::endl;
}

void app::exportDataBuku() {
    ofstream data("./library.txt");

    std::string bufferData;
    int list = 1;

    for (auto it : database) {
        bufferData += "Data " + std::to_string(list) + "\n" + "Judul: " + it.judul + "\nPenulis: " + it.penulis + "\nTahun Terbit: " + it.tahunTerbit + "\nPenerbit: " + it.penerbit + "\nISBN: " + it.isbn + "\nStock: " + std::to_string(it.stock) + "\n";
        list++;
    }

    data << bufferData;

    data.close();
};

void app::exportDataBukuSql() {

    std::remove("./library.sql");

    ofstream sql("./library.sql", std::ios::app);

    int list = 1;
 
    sql << "CREATE TABLE `buku`(`ID_BUKU` varchar(10) NOT NULL,`BUKU` varchar(150) DEFAULT NULL,`PENULIS` varchar(150) DEFAULT NULL,`TAHUN_TERBIT` char(4) DEFAULT NULL,`PENERBIT` varchar(150) DEFAULT NULL,`ISBN` char(50) DEFAULT NULL,`STOCK` char(4) DEFAULT NULL)ENGINE=InnoDB DEFAULT CHARSET=latin1;INSERT INTO `buku`(`ID_BUKU`, `BUKU`, `PENULIS`, `TAHUN_TERBIT`, `PENERBIT`, `ISBN`, `STOCK`) VALUES";

    for(auto it : database) {
        if(list == database.size()) {
            sql << "(\'BK" << list << "\',\'" << it.judul << "\',\'" << it.penulis << "\',\'" << it.tahunTerbit<< "\',\'" << it.penerbit << "\',\'" << it.isbn << "\',\'" << it.stock << "\');";
        }else {
            sql << "(\'BK" << list << "\',\'" << it.judul << "\',\'" << it.penulis << "\',\'" << it.tahunTerbit<< "\',\'" << it.penerbit << "\',\'" << it.isbn << "\',\'" << it.stock << "\'),";
        }
        list++;
    }

    sql << "ALTER TABLE `buku` ADD PRIMARY KEY (`ID_BUKU`); COMMIT;";
    sql.close();
}

void app::simpanDataBuku() {
    ofstream datas("./datas/datas.txt");
    std::string bufferData;
    for (auto it : database) {
        std::replace(it.judul.begin(), it.judul.end(), ' ', '_');
        std::replace(it.penulis.begin(), it.penulis.end(), ' ', '_');
        std::replace(it.penerbit.begin(), it.penerbit.end(), ' ', '_');
        bufferData += it.judul + " " + it.penulis + " " + it.tahunTerbit + " " + it.penerbit+ " " + it.isbn + " " + std::to_string(it.stock) + "\n"; 
    }

    datas << bufferData;
    datas.close();
}

void app::ambilDataBuku() {
    fstream datas("./datas/datas.txt");
    std::string line;
    while(getline(datas, line)) {
        std::istringstream iss(line);
        std::string data, judul, penulis, tahunterbit, penerbit, isbn;
        int index = 0, stock;
        while(iss >> data) {
            if(index == 0) {
                std::replace(data.begin(), data.end(), '_', ' ');
                judul = data;
            }else if(index == 1) {
                std::replace(data.begin(), data.end(), '_', ' ');
                penulis = data;
            }else if(index == 2) {
                tahunterbit = data;
            }else if(index == 3) {
                std::replace(data.begin(), data.end(), '_', ' ');
                penerbit = data;
            }else if(index == 4) {
                isbn = data;
            }else if(index == 5) {
                stock = std::stoi(data);
            }
            index++;
        }
        database.push_back({judul, penulis, tahunterbit, penerbit, isbn, stock});
    };

    datas.close();
};

void app::inisialiasiUser () {
    std::string username, password;
    ifstream pengguna("./datas/pengguna.txt");

    if(pengguna.is_open()) {
        char buffer[1];
        pengguna.getline(buffer, 2);
        if(pengguna.gcount() == 1) {
            return;
        }
    }

    ofstream writePengguna("./datas/pengguna.txt");
    std::cout << "========== Inisialisasi Pengguna ==========" << std::endl;
    std::cout <<"Buat username: ";
    getline(std::cin, username);
    std::cout << "Buat password: ";
    getline(std::cin, password);

    std::replace(username.begin(), username.end(), ' ', '_');
    std::replace(password.begin(), password.end(), ' ', '_');
    writePengguna << username << " " << password;

    pengguna.close();
    writePengguna.close();
}

bool app::editDataBuku(std::string input) {
    bool find = false;
    for(int i = 0; i < database.size(); i++) {
        if(database[i].judul == input || database[i].isbn == input) {
            std::cout << "\nData yang akan diedit" << std::endl;
            std::cout << "Judul: " << database[i].judul << "\nPenulis: " << database[i].penulis << "\nTahun Terbit: " << database[i].tahunTerbit << "\nPenerbit: " << database[i].penerbit << "\nISBN: " << database[i].isbn << "\nStock: " << database[i].stock << std::endl;

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

            bfrStock = bfrStock == "-" ? std::to_string(database[i].stock) : bfrStock;
            database[i] = {
                bfrJudul == "-" ? database[i].judul : bfrJudul,
                bfrPenulis == "-" ? database[i].penulis : bfrPenulis,
                bfrTahunTerbit == "-" ? database[i].tahunTerbit : bfrTahunTerbit, 
                bfrPenerbit == "-" ? database[i].penerbit : bfrPenerbit, 
                bfrISBN == "-" ? database[i].isbn : bfrISBN, 
                std::stoi(bfrStock)
            };
            std::cout << "Data berhasil di edit" << std::endl;
            return find = true;
        }
    }
    return find;
}

bool app::validasiAdmin (std::string inptusername, std::string inptpassword) {
    fstream pengguna("./datas/pengguna.txt");

    std::string line;
    bool validate = false;

    while(getline(pengguna, line)) {
        std::istringstream iss(line);
        std::string username, password, data;
        int index = 0;
        while(iss >> data) {
            std::replace(data.begin(), data.end(),'_', ' ');
            if(index == 0) {
                username = data;
            }else if(index == 1) {
                password = data;
            }
            index++;
        }

        if(username == inptusername && password == inptpassword) {
            return validate = true;
        }
    }
    pengguna.close();
    return validate;
}

int app::ambilJumlahData () {
    return database.size();
}