
#include <iostream> 
#include <cstdint> 
#include <cmath>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <climits>

std::string operator+(const std::string s1, const std::string s2) { 
    int idx = 0;
    std::string res(s1.length() + s2.length(), '\0');

    for (int i =0; i < s1.length(); i++) res[idx++] = s1[i];
    for (int i = 0; i < s2.length(); i++) res[idx++] = s2[i];

    return res;
}

class MemoryManagementUnit {
private:
    int _ISABitRep;
    int _bytes;
    long long _pageCount;
    long long _pageTableSize;

    long long calculateRep(std::string s) { 
        if(s.empty()) return -1;

        std::string numStr = "";
        int multiplier = 1;

        int idx = 0;
        while(std::isdigit(s[idx])) {
            numStr += s[idx]; idx++;
        }
    
        switch(s[idx]) {
            case 'K':
                multiplier = std::pow(2,10);
                break;
            case 'M':
                multiplier = std::pow(2, 20);
                break;
            case 'G':
                multiplier = std::pow(2, 30);
        }

        return multiplier * std::stoi(numStr);
    }


    std::string strRep(long long bytes) {
        int iters = 0;
        while(bytes > 1000) {
            bytes /= std::pow(2,10); 
            iters++;
        }
        
        std::string rep; 
        switch(iters) {
            case 0:
                rep = "B";
                break;
            case 1:
                rep = "KB";
                break;
            case 2:
                rep = "MB";
                break;
            case 3:
                rep = "GB";
                break;
            default :
                rep = "?";
        }
        return std::to_string(bytes) + rep;
    }

    long long calculatePageTableSize(std::string computerAddressSpace, std::string pageSize) {
        int bitRep = std::stoi(computerAddressSpace); 
        int bytes = std::ceil(bitRep/8);
        
        long long pageSizeActual = calculateRep(pageSize);

        long long pages = std::pow(2,bitRep) / pageSizeActual;
        std::printf("bitRep is %d and bytes are %d.\npageSize is %lld and so there are %lld pages\n", bitRep, bytes, pageSizeActual, pages);
        
        return pages * bytes;
    }

public:
    MemoryManagementUnit(std::string computerAddressSpace, std::string pageSize) {
        _ISABitRep = std::stoi(computerAddressSpace);
        _bytes = std::ceil(_ISABitRep/8);

        long long pageSizeActual = calculateRep(pageSize);

        long long pages = std::pow(2,_ISABitRep) / pageSizeActual;
        std::printf("bitRep is %d and bytes are %d.\npageSize is %lld and so there are %11d pages\n", _ISABitRep, _bytes, pageSizeActual, pages);
        _pageCount = pages;
        _pageTableSize = pages * _bytes;

        std::printf("physical address size of the page table is %lld, or %s\n", _pageTableSize, strRep(_pageTableSize).c_str());
    }

    long retrievePage (long logicalAddress) {
        return logicalAddress;
    }

};


void runSimulation (MemoryManagementUnit& mmu) {
    std::vector<int> p1(64), p2(64), p3(64), p4(64); // Initialize 4 vectors with 64 elements each
    // Random number generator setup
    std::random_device rd; // Seed for random number generator
    std::mt19937 gen(rd()); // Mersenne Twister random number generator
    std::uniform_int_distribution<int> dist(0, INT_MAX); // Range: 0 to 2^32 - 1
    // Fill each vector with random numbers
    for (int i = 0; i < 64; i++) {
        p1[i]  = dist(gen);
        p2[i]  = dist(gen);
        p3[i]  = dist(gen);
        p4[i]  = dist(gen);
    }
    std::vector<std::vector<int>> processes = {p1, p2, p3, p4};
    std::uniform_int_distribution<int> processSelector(0,3); 
    std::uniform_int_distribution<int> pageSelector(0,63); 
    for(int i = 0; i < 100000; i++) {
        long virtualAddress = processes [processSelector(gen)] [pageSelector(gen)]; 
        std::cout << "Retrieving physical address for logical/virtual address# " << virtualAddress << '\n';
        std::cout << "Physical address: " <<mmu.retrievePage(virtualAddress) << '\n';
    }
}


int main() {
    std::vector<std::string> lines;
    std::string line;

    while(std::getline(std::cin,line)) {
        lines.push_back(line);
        if(lines.size() == 2) break;
    }

    std::printf("logical adddress space is %s-bits, page size is %s\n", lines[0].c_str(), lines[1].c_str()); 
    MemoryManagementUnit mmu (lines[0], lines[1]);
    
    //runSimulation(mmu);

    return 0;

}