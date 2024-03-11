#ifndef UNBIGINT_HPP
#define UNBIGINT_HPP

#include <stdlib.h>
#include <vector>
#include <iostream>

class UnBigInt
{
private:
    std::vector<unsigned char> data; //
    
public:
    UnBigInt() {}

    ~UnBigInt() { ClearInt(); }

    void InitRand(int len) {
        ClearInt();
        if (len == 0) {
            data.push_back(0);
            return;
        }
        else if (len < 0) {
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < len; ++i) {
            unsigned char ch = rand() % 10; // 0..9
            data.push_back(ch);
        }
        if (len > 0) {
            this->CheckInt();
        }
    }

    void ClearInt() {
        data.clear();
    }

private:
    //检查合法性
    void CheckInt() {
        while (data[data.size() - 1] == 0 && data.size() > 1) {
            data.pop_back();
        }
    }

    //检查大小(是否满足减法或除法)
    bool CheckSize(const UnBigInt &bt2) const {
        if (data.size() > bt2.data.size()) {
            return true;
        }
        else if (data.size() == bt2.data.size()) {
            if (data.size() == 0) {
                return false;
            }
            for (int i = data.size() - 1; i >= 0; i--) {
                if ((int)data[i] > (int)bt2.data[i]) {
                    return true;
                }
                else if ((int)data[i] == (int)bt2.data[i]) {
                    continue;
                }
                else {
                    return false;
                }
            }
            return true;
        }
        else {
            return false;
        }
    }

public:
    UnBigInt operator=(const UnBigInt &bt) {
        this->ClearInt();
        for (int i = 0; i < bt.data.size(); i++) {
            this->data.push_back(bt.data[i]);
        }
        this->CheckInt();
        return *this;
    }

    bool operator==(const UnBigInt &bt) const {
        if (this->data.size() != 0 && bt.data.size() != 0) {
            if (this->data.size() == bt.data.size()) {
                for (int i = 0; i < bt.data.size(); i++) {
                    if (this->data[i] != bt.data[i]) {
                        return false;
                    }
                }
                return true;
            }
            else {
                return false;
            }
        }
        return false;
    }

    //大数相加++++++++++++++++++++++
    UnBigInt operator+(const UnBigInt &bt) const {
        if (bt.data.size() == 0 && data.size() == 0) {
            UnBigInt bs;
            bs.InitRand(0);
            return bs;
        }
        if (bt.data.size() == 0) {
            return *this;
        }
        if (data.size() == 0) {
            return bt;
        }
        UnBigInt sum;
        int sumx = 0;//求和
        int tmp = 0;//进位
        int i = 0;
        if (data.size() <= bt.data.size()) {
            for (i = 0; i < data.size();i++) {
                sumx = (int)data[i] + (int)bt.data[i] + tmp;
                sum.data.push_back(sumx % 10);
                tmp = sumx / 10;
            }
            for (i = data.size(); i < bt.data.size(); i++) {
                sumx = (int)bt.data[i] + tmp;
                sum.data.push_back(sumx % 10);
                tmp = sumx / 10;
            }
            if (tmp != 0) {
                sum.data.push_back(tmp);
            }
        }
        else {
            for (i = 0; i < bt.data.size(); i++) {
                sumx = (int)data[i] + (int)bt.data[i] + tmp;
                sum.data.push_back(sumx % 10);
                tmp = sumx / 10;
            }
            for (i = bt.data.size(); i < data.size(); i++) {
                sumx = (int)data[i] + tmp;
                sum.data.push_back(sumx % 10);
                tmp = sumx / 10;
            }
            if (tmp != 0) {
                sum.data.push_back(tmp);
            }
        }
        sum.CheckInt();

        return sum;
    }

    UnBigInt& operator+=(const UnBigInt &bt) {
        (*this) = (*this) + bt;
        return *this;
    }

    //大数相减---------------------
    UnBigInt operator-(const UnBigInt &bt) const {
        if ( this->CheckSize(bt) ) {
            UnBigInt sub;
            int subx = 0;//差
            int tmp = 0;//借位
            int i = 0;
            if (data.size() > bt.data.size()) {
                if (bt.data.size() == 0) {
                    return *this;
                }
                //计算
                for (i = 0; i < bt.data.size(); i++) {
                    if ((int)data[i] - tmp >= (int)bt.data[i]) {
                        subx = (int)data[i] - tmp - (int)bt.data[i];
                        tmp = 0;
                        sub.data.push_back(subx);
                    }
                    else {
                        subx = (int)data[i] - tmp + 10 - (int)bt.data[i];
                        tmp = 1;
                        sub.data.push_back(subx);
                    }
                }
                for (i = bt.data.size(); i < data.size(); i++) {
                    if (tmp == 1) {
                        if ((int)data[i] - tmp >= 0) {
                            sub.data.push_back((int)data[i] - tmp);
                            tmp = 0;
                        }
                        else {
                            sub.data.push_back((int)data[i] - tmp + 10);
                            tmp = 1;
                        }
                    }
                    else {
                        sub.data.push_back((int)data[i] - tmp);
                    }
                }
            }
            else {
                for (i = 0; i < bt.data.size(); i++) {
                    if ((int)data[i] - tmp >= (int)bt.data[i]) {
                        subx = (int)data[i] - tmp - (int)bt.data[i];
                        tmp = 0;
                        sub.data.push_back(subx);
                    }
                    else {
                        subx = (int)data[i] - tmp + 10 - (int)bt.data[i];
                        tmp = 1;
                        sub.data.push_back(subx);
                    }
                }
            }
            sub.CheckInt();
            return sub;
        }
        //减不过，数据不合法，都返回0
        UnBigInt aaa;
        aaa.InitRand(0);
        return aaa;
    }

    //大数乘个位数****************************
    UnBigInt Mul(int a) const {
        if (this->data.size() > 0 && a >= 0 && a < 10) {
            UnBigInt mul;
            int mulx = 0;
            int tmp = 0;
            for (int i = 0; i < this->data.size(); i++) {
                int mulx = ((int)(data[i]) * a) + tmp;
                tmp = mulx / 10;
                mul.data.push_back(mulx % 10);
            }
            if (tmp != 0) {
                mul.data.push_back(tmp);
            }
            mul.CheckInt();
            return mul;
        }
        else if (a == 10) {
            UnBigInt mul;
            mul.data.push_back(0);
            for (int i = 0; i < this->data.size(); i++) {
                mul.data.push_back((int)data[i]);
            }
            mul.CheckInt();
            return mul;
        }
        UnBigInt tmp_a;
        tmp_a.InitRand(0);
        return tmp_a;
    }

    //大数相乘******************************
    UnBigInt operator*(const UnBigInt &bt) const {
        if (this->data.size() == 0 || bt.data.size() == 0) {
            exit(1);
        }
        if ((this->data.size() == 1 && (int)(this->data[0]) == 0) || (bt.data.size() == 1 && (int)(bt.data[0]) == 0)) {
            UnBigInt mul;
            mul.InitRand(0);
            return mul;
        }
        else if (this->data.size() == 1 && (int)(this->data[0]) == 1) {
            UnBigInt mul;
            for (int i = 0; i < bt.data.size(); i++) {
                mul.data.push_back(bt.data[i]);
            }
            mul.CheckInt();
            return mul;
        }
        else if (bt.data.size() == 1 && (int)(bt.data[0]) == 1) {
            UnBigInt mul;
            for (int i = 0; i < this->data.size(); i++) {
                mul.data.push_back(this->data[i]);
            }
            mul.CheckInt();
            return mul;
        }
        else {
            size_t big_size, small_size;
            if (this->data.size() >= bt.data.size()) {
                big_size = this->data.size();
                small_size = bt.data.size();

                std::vector<UnBigInt> nums_group;
                for (int i = 0; i < small_size; i++) {
                    UnBigInt mul_d, mul_x;
                    int g = i;
                    while (g--) {
                        mul_x.data.push_back(0);
                    }
                    mul_d = this->Mul((int)bt.data[i]);
                    for (int j = 0; j < mul_d.data.size(); j++) {
                        mul_x.data.push_back((int)(mul_d.data[j]));
                    }
                    nums_group.push_back(mul_x);
                }
                UnBigInt mul;
                for (int x = 0; x < nums_group.size(); x++) {
                    mul = mul + nums_group[x];
                }
                mul.CheckInt();
                return mul;
            }
            else {
                big_size = bt.data.size();
                small_size = this->data.size();

                std::vector<UnBigInt> nums_group;
                for (int i = 0; i < small_size; i++) {
                    UnBigInt mul_d, mul_x;
                    int g = i;
                    while (g--) {
                        mul_x.data.push_back(0);
                    }
                    mul_d = this->Mul((int)this->data[i]);
                    for (int j = 0; j < mul_d.data.size(); j++) {
                        mul_x.data.push_back((int)(mul_d.data[j]));
                    }
                    nums_group.push_back(mul_x);
                }
                UnBigInt mul;
                for (int x = 0; x < nums_group.size(); x++) {
                    mul = mul + nums_group[x];
                }
                mul.CheckInt();
                return mul;
            }
        }
    }

    //大数相除//////////////////////////////////
    /*
    UnBigInt operator/(const UnBigInt &bt) const {
        if (this->CheckSize(bt)) {
            //无法判断除数为0
            if (1) {
                UnBigInt bt_fx, bt_dev, bt_one;
                bt_fx = *this;
                bt_dev.data.push_back(0);
                bt_one.data.push_back(1);
                while (1) {
                    if (bt_fx.CheckSize(bt)) {
                        bt_fx = bt_fx - bt;
                        bt_dev = bt_dev + bt_one;
                        if (bt_fx.data.size() == 1 && (int)bt_fx.data[0] == 0) {
                            bt_dev.CheckInt();
                            return bt_dev;
                        }
                    }
                    else {
                        bt_dev.CheckInt();
                        return bt_dev;
                    }
                }
            }
        }
        UnBigInt btx;
        btx.data.push_back(0);
        return btx;
    }
    */

    //扩大bt
    UnBigInt Expand( const UnBigInt& bt, const UnBigInt &target) {
        int i = 0;
        UnBigInt bt_r= bt;
        while ( target.CheckSize( bt_r.Mul(10) ) ) {
            bt_r = bt_r.Mul(10);
            i++;
        }
        bt_r.CheckInt();
        return bt_r;
    }

    //获取扩大的数
    int ExpandSize(const UnBigInt &bt, const UnBigInt &target) {
        //
        int i = 0;
        UnBigInt bt_r = bt;
        while (target.CheckSize(bt_r.Mul(10))) {
            bt_r = bt_r.Mul(10);
            i++;
        }
        return i;
    }

    UnBigInt operator/(const UnBigInt &bt) {
        if (this->CheckSize(bt)) {
            UnBigInt bt_fx, bt_sx, bt_dev, bt_one, bt_zero;
            bt_fx = *this;
            bt_dev.data.push_back(0);
            bt_one.data.push_back(1);
            bt_zero.data.push_back(0);
            int n = 0;

            while (bt_fx.CheckSize(bt)) {
                bt_sx = Expand(bt, bt_fx);
                n = ExpandSize(bt, bt_fx);
                UnBigInt x;
                x = bt_zero;
                while (bt_fx.CheckSize(bt_sx)) {
                    if ((bt_fx - bt_sx).CheckSize(bt_zero)) {
                        x = x + bt_one;
                        bt_fx = bt_fx - bt_sx;
                    }
                    else {
                        break;
                    }
                }
                while (n--) {
                    x = x.Mul(10);
                }
                bt_dev = bt_dev + x;
            }
            bt_dev.CheckInt();
            return bt_dev;
        }
        UnBigInt btx;
        btx.data.push_back(0);
        return btx;
    }

    /*
    // 大数取余
    UnBigInt operator%(const UnBigInt &bt) const {
        if (this->CheckSize(bt)) {
            UnBigInt bt_fx;
            bt_fx = *this;
            while (1) {
                if (bt_fx.CheckSize(bt)) {
                    bt_fx = bt_fx - bt;
                    if (bt_fx.data.size() == 1 && (int)bt_fx.data[0] == 0) {
                        bt_fx.CheckInt();
                        return bt_fx;
                    }
                }
                else {
                    bt_fx.CheckInt();
                    return bt_fx;
                }
            }
        }
        UnBigInt btx;
        btx.data.push_back(0);
        return btx;
    }
    */
    
    std::ostream &operator<<(std::ostream &out) const {
        if (data.size() == 0) {
            out << '0';
        }
        else {
            for (int i = data.size() - 1; i >= 0; --i) {
                out << ((int)data[i]);
            }
        }
        
        return out;
    }

    /*
    void MoveSumADD(UnBigInt& bta, int pos, UnBigInt& btb) {
        UnBigInt btc;
        while (pos--) {
            btc.data.push_back(0);
        }
        for (int i = 0; i < btb.data.size(); i++) {
            btc.data.push_back(btb.data[i]);
        }
        btc.CheckInt();
        bta = bta + btc;
        bta.CheckInt();
    }
    */
    
};

std::ostream &operator<<(std::ostream &out, const UnBigInt &it) {
    return it << out;
}

#endif