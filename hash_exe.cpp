#include <iostream>
#include <fstream>
#include <string>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>

using namespace CryptoPP;

std::string sha256(const std::string& filename) {
    SHA256 hash;
    std::string digest;
    FileSource file(filename.c_str(), true, new HashFilter(hash, new HexEncoder(new StringSink(digest))));
    return digest;
}

int main() {
    const std::string filename = "file.txt";
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "Ошибка: Не удалось открыть файл " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::cout << "Содержимое файла " << filename << ":\n";
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    file.close();

    try {
        std::string hash = sha256(filename);
        std::cout << "Хэширование методом SHA256: " << hash << std::endl;
    } catch (const Exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
