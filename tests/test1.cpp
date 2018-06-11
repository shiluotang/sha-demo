#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <ostream>
#include <stdexcept>
#include <algorithm>

#include "../src/sha.hpp"
#include "../src/envvars.hpp"

int main(int argc, char* argv[]) {
    using namespace std;
    using namespace org::sqg;

    bytes b;

    map<string, checksum*> checksumers;
    checksumers["sha"] = new sha();
    checksumers["sha1"] = new sha1();
    checksumers["sha224"] = new sha224();
    checksumers["sha256"] = new sha256();
    checksumers["sha384"] = new sha384();
    checksumers["sha512"] = new sha512();

    string const filename = envvars::var("srcdir") + "/tests/data/data.dat";
    ifstream infile(filename);
    if (!infile) {
        cerr << filename << " can't be open for read!" << endl;
        return EXIT_FAILURE;
    }
    for (map<string, checksum*>::const_iterator it = checksumers.begin();
            it != checksumers.end(); ++it)
        it->second->reset();
    std::vector<char> buffer(0xff);
    do {
        infile.read(&buffer[0], buffer.size());
        for (map<string, checksum*>::const_iterator it = checksumers.begin();
                it != checksumers.end(); ++it)
            it->second->update(&buffer[0], infile.gcount());
    } while (infile);
    for (map<string, checksum*>::const_iterator it = checksumers.begin();
            it != checksumers.end(); ++it) {
        it->second->finish(b);
        cout << std::setw(8) << std::left << it->first << "\t" << b << endl;
    }

    for (map<string, checksum*>::const_iterator it = checksumers.begin();
            it != checksumers.end(); ++it) {
        delete it->second;
    }
    checksumers.clear();

    return EXIT_SUCCESS;
}
