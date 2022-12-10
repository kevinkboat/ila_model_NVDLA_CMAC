

// Returns true if bit in specified index is 1, false if 0
bool _SelectBit(const ExprRef& bv, const int& idx){
    auto b = Ite(SelectBit(bv, idx) == BvConst(1,1), BvConst(1,1), BvConst(1,2));
    return b.bit_width() == 1;
}

int _BvToInt(const ExprRef& bv){
    auto len = bv.bit_width();      // should be limited to the max size of an int
    int num = 0;
    for (int i = 0; i < len; i++){
        // Binary to Decimal conversion
        if (_SelectBit(bv, i)){
            num += static_cast<int>(std::pow(2, i));
        }
    }
    return num;
}


