#include <fstream>
#include "blowfish.h"

using namespace std;

int main()
{
    // Read the 3D object file
    ifstream input_file("object.obj", ios::binary);
    input_file.seekg(0, ios::end);
    size_t file_size = input_file.tellg();
    input_file.seekg(0, ios::beg);
    char* buffer = new char[file_size];
    input_file.read(buffer, file_size);
    input_file.close();

    // Create a key for encryption
    const char* key = "my_secret_key";
    unsigned int key_len = strlen(key);
    CBLOWFISH blowfish(key, key_len);

    // Encrypt the data
    blowfish.Encrypt(buffer, file_size);

    // Save the encrypted data to a file
    ofstream output_file("object_encrypted.obj", ios::binary);
    output_file.write(buffer, file_size);
    output_file.close();

    // Read the encrypted data from a file
    input_file.open("object_encrypted.obj", ios::binary);
    input_file.seekg(0, ios::end);
    file_size = input_file.tellg();
    input_file.seekg(0, ios::beg);
    buffer = new char[file_size];
    input_file.read(buffer, file_size);
    input_file.close();

    // Decrypt the data
    blowfish.Decrypt(buffer, file_size);

    // Save the decrypted data to a file
    output_file.open("object_decrypted.obj", ios::binary);
    output_file.write(buffer, file_size);
    output_file.close();

    return 0;
}
