#include <iostream>
using namespace std;

const uint64_t CARD_PUBLIC_KEY = 13135480;
const uint64_t DOOR_PUBLIC_KEY = 8821721;

void transform(uint64_t subject, uint64_t &value) {
    value *= subject;
    value %= 20201227;
}

int main() {
    
    int loopSize = 0;
    uint64_t value = 1;
    uint64_t subject = 7;

    while (value != CARD_PUBLIC_KEY) {
        loopSize++;
        transform(subject, value);
    }

    cout << "The card's loop size is " << loopSize << endl;

    uint64_t key = 1;
    for (int i=0; i<loopSize; i++) {
        transform(DOOR_PUBLIC_KEY, key);
    }

    cout << "The encryption key is " << key << endl;

    return 0;
}