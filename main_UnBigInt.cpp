#include <iostream>
#include "../UnBigInt.hpp"

int main() {
    /*
    UnBigInt bt1;
    UnBigInt bt2;
    bt1.InitRand(50);
    bt2.InitRand(40);
    std::cout << bt1 << std::endl;
    std::cout << bt2 << std::endl;
    std::cout << bt1 + bt2 << std::endl;
    UnBigInt bt3;
    UnBigInt bt4;
    bt3.InitRand(8);
    bt4.InitRand(3);
    std::cout << bt3 << std::endl;
    std::cout << bt4 << std::endl;
    UnBigInt bt5;
    bt5 = bt3 - bt4;
    std::cout << bt5 << std::endl;
    */

    UnBigInt bt6;
    bt6.InitRand(1000);
    std::cout << bt6 << std::endl;
    UnBigInt bt7;
    bt7.InitRand(500);
    std::cout << bt7 << std::endl;
    UnBigInt bt8;
    bt8 = bt6 + bt7;
    std::cout << bt8 << std::endl;
    
    // bt8 = bt6 * bt7;
    // std::cout << "bt6 * bt7 = " << bt8 << std::endl;
    //bt8 = bt6 / bt7;
    //std::cout << "bt6 / bt7 = " << bt8 << std::endl;
    // bt8 = bt6 % bt7;
    // std::cout << "bt6 % bt7 = " << bt8 << std::endl;
    
    /*
    UnBigInt bt9;
    bt9.InitRand(3);
    std::cout << bt9 << std::endl;
    UnBigInt bt10;
    bt10.InitRand(3);
    std::cout << bt10 << std::endl;
    bt9+=bt10;
    std::cout << bt9 << std::endl;
    */
    
}




