#include <cryptopp/aes.h>    // для алгоритма AES
#include <cryptopp/modes.h>    // для режимов шифрования (CBC)
#include <cryptopp/files.h>    // для работы с файлами
#include <cryptopp/osrng.h>    // для генерации случайных чисел
#include <cryptopp/pwdbased.h> // для вывода ключа из пароля (PBKDF2)
#include <cryptopp/sha.h>    // для хеш-функции SHA256
#include <iostream>
#include <fstream>

void processFile(const std::string& inFile, const std::string& outFile, const std::string& psw, bool encrypt) {
    using namespace CryptoPP;

    // Создание генератора случайных чисел для вектора инициализации (IV)
    AutoSeededRandomPool prng;
    // Массив для ключа AES
    byte key[AES::DEFAULT_KEYLENGTH];
    // Массив для вектора инициализации
    byte iv[AES::BLOCKSIZE];

    // Объект для вывода ключа из пароля
    PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    // Вывод ключа. на 500 итераций
    pbkdf.DeriveKey(key, sizeof(key), 0, (const byte*)psw.data(), psw.size(), nullptr, 0, 500);

    std::ifstream inputFile(inFile, std::ios::binary);
    std::ofstream outputFile(outFile, std::ios::binary);

    if (!inputFile || !outputFile) {
        std::cerr << "Ошибка открытия файлов" << std::endl;
        return;
    }

    // Если режим шифрования
    if (encrypt) {
        // Генерируется случайный IV
        prng.GenerateBlock(iv, sizeof(iv));
        outputFile.write(reinterpret_cast<const char*>(iv), sizeof(iv));
    } else {
        inputFile.read(reinterpret_cast<char*>(iv), sizeof(iv));
    }

    try {
        if (encrypt) {
            CBC_Mode<AES>::Encryption encryptor(key, sizeof(key), iv);
            // Создается поток для зашифрования, перенаправляющий данные в выходной файл
            StreamTransformationFilter stfEncryptor(encryptor, new FileSink(outputFile));
            // Чтение данных из входного файла и зашифрование
            FileSource(inputFile, true, new Redirector(stfEncryptor));
        } else {
            CBC_Mode<AES>::Decryption decryptor(key, sizeof(key), iv);
            StreamTransformationFilter stfDecryptor(decryptor, new FileSink(outputFile));
            FileSource(inputFile, true, new Redirector(stfDecryptor));
        }
    } catch (const Exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
}

int main() {
    std::string inFile, outFile, password;
    int opt;
    std::cout << "Выберите режим (1 - зашифрование, 2 - расшифрование): ";
    std::cin >> opt;
    std::cout << "Введите путь к входному файлу: ";
    std::cin >> inFile;
    std::cout << "Введите путь к выходному файлу: ";
    std::cin >> outFile;
    std::cout << "Введите пароль: ";
    std::cin >> password;

    processFile(inFile, outFile, password, opt == 1);
    return 0;
}
