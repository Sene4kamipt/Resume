#include <stdint.h>

typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31 
} float_class_t;

int get_bit(double *x, int pos){
	void *vpx = x;
	uint64_t *ipx = vpx;
	return 1 & (*ipx >> pos);
}

int get_sign(double *x){
	return get_bit(x, 8*(sizeof(double)) - 1);
}

extern float_class_t classify(double *value_ptr){
    int mantissa_zero =1;
    for(int i = 0; i < 52; ++i){
		if (get_bit(value_ptr, i) ^ 0){
            mantissa_zero = 0;
        }
	}
   // int mantissa_one = 1;
   // for(int i = 0; i < 52; ++i){
   //     if (get_bit(value_ptr, i) ^ 1){
   //         mantissa_one = 0;
   //     }
   // }
    int exponent_zero =1;
    for(int i = 52; i < 63; ++i){
        if (get_bit(value_ptr, i) ^ 0){
            exponent_zero = 0;
        }
    }
    int exponent_one =1;
    for(int i = 52; i < 63; ++i){
        if (get_bit(value_ptr, i) ^ 1){
            exponent_one = 0;
         }
    }
    if (mantissa_zero==1){
        if (exponent_zero==1){
            if (get_sign(value_ptr)){
                return MinusZero;
            }
            else{
                return PlusZero;
            }
        }
        else{
            if (exponent_one==1){
                if (get_sign(value_ptr)){
                    return MinusInf;
                }
                else{
                    return PlusInf;
                }
            }
        }
        if (get_sign(value_ptr)){
            return MinusRegular;
        }
        else{
            return PlusRegular;
        }

    }
    else{
        if (exponent_one==1){
            if(get_bit(value_ptr, 51))
                {return QuietNaN;}
            else{  return   SignalingNaN;}
        }
        else{
            if (exponent_zero==1){
                if (get_sign(value_ptr)){
                    return MinusDenormal;
                }
                else{
                    return PlusDenormal;
                }
            }
        }
    }
    if (get_sign(value_ptr)){
        return MinusRegular;
    }
    else{
        return PlusRegular;
    }

}
