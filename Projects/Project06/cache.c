#include <stdio.h>

// THE CACHE
struct LINE{
    char valid;
    int tag;
    char data[32];
};

struct SET{
    struct LINE line[1];
};

struct CACHE {
    struct SET set[8];
} cache;

// GLOBALDATA
// increment these in your function
unsigned hit_count  = 0;
unsigned miss_count = 0;
unsigned read_data_count = 0;

// SYSTEM BUS 
// call Read_Data_From_Ram to update this
char system_bus[32];



// READ DATA FROM RAM
// this function copies 32 character from the text file to
// the system_bus array aligned with the system bus
// (we will not test this with input larger than the text file)
void Read_Data_From_Ram(unsigned address) {
    address >>= 5; address <<= 5; // get align the data
    read_data_count++;
    FILE *file;
    file = fopen("alice_in_wonderland.txt", "r");
    fseek(file, address, SEEK_SET);
    for (int i = 0; i<32; i++) system_bus[i] = fgetc(file);
    return;
}


// COMPLETE THE FOLLOWING FUNCTION 
//
// this code should check to see if the data in the cache is valid and the tag matches
// if so it should return the char matching the address and increment the hit count
//
// if not it should read the data from the system bus copy it into the cache and 
// increment the miss count and return the char matching the address
// 
char Read_Data_From_Cache(unsigned address){
    int dataIndex;
    int setIndex;
    int tag;
    unsigned copyAddress = address;

    dataIndex = address <<= 27;
    dataIndex = address >>= 27;
    address = copyAddress;

    setIndex = address >>= 5;
    setIndex = address <<= 29;
    setIndex = address >>= 29;
    address = copyAddress;

    tag = address >>= 8;
    address = copyAddress;

    char returnChar;

    if (cache.set[setIndex].line[0].valid == 1 && cache.set[setIndex].line[0].tag == tag) {
        returnChar = cache.set[setIndex].line[0].data[dataIndex];
        hit_count++;
    } else {
        Read_Data_From_Ram(address);
        cache.set[setIndex].line[0].tag = tag;
        cache.set[setIndex].line[0].valid = 1;
        for (int i = 0; i < 32; i++) {
            cache.set[setIndex].line[0].data[i] = system_bus[i];
        }
        miss_count++;
        returnChar = cache.set[setIndex].line[0].data[dataIndex];
    }

    return returnChar;
    }


int main() {
    // INITIALIZE CACHE
    for (int i = 0; i<8; i++) cache.set[i].line[0].valid = 0;
    
    // READ SOME DATA
    char c;

    printf("Reading charcter starting at index 0 to 50 with an interval of 1\n");
    
    c = Read_Data_From_Cache(0); printf("Reading character at index 0    : data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(10); printf("Reading character at index 10   : data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(20); printf("Reading character at index 20   : data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(30); printf("Reading character at index 30   : data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    c = Read_Data_From_Cache(40); printf("Reading character at index 40   : data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
   

    // WRITE A LOT MORE TESTS

    return 0;
}

