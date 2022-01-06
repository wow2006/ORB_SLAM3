#include <chrono>
#include <iostream>
#include "ORBVocabulary.h"

using namespace std::literals;

bool load_as_text(ORB_SLAM3::ORBVocabulary *voc, const std::string infile)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    bool res = voc->loadFromTextFile(infile);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Loading from text took: " << (t2 - t1).count() << "ns\n";
    return res;
}

void save_as_text(ORB_SLAM3::ORBVocabulary* voc, const std::string outfile)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    voc->saveToTextFile(outfile);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Saving to text took: " << (t2 - t1).count() << "ns\n";
}

void load_as_binary(ORB_SLAM3::ORBVocabulary *voc, const std::string infile)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    voc->loadFromBinaryFile(infile);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Loading from binary took: " << (t2 - t1).count() << "ns\n";
}

void save_as_binary(ORB_SLAM3::ORBVocabulary *voc, const std::string outfile)
{
    auto t1 = std::chrono::high_resolution_clock::now();
    voc->saveToBinaryFile(outfile);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Saving to binary took: " << (t2 - t1).count() << "ns\n";
}

int main(int argc, char **argv)
{
    cout << "BoW load/save benchmark" << endl;
    ORB_SLAM3::ORBVocabulary *voc = new ORB_SLAM3::ORBVocabulary();

    load_as_text(voc, "Vocabulary/ORBvoc.txt");
    save_as_binary(voc, "Vocabulary/ORBvoc.bin");

    return 0;
}
