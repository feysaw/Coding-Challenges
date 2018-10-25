#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include "isbn.h"

uint8_t isValidISBN10(uint8_t* isbn) {
    uint32_t result = 0;
    
    for (uint8_t i = 0; i < 9; i++) {
        result += (uint32_t) (isbn[i] * (1 + i));
    }
    
    uint8_t check_digit = (uint8_t) (result % 11);
    
    if (isbn[9] == check_digit) {
        return 1;
    }
    
    return 0;
}

uint8_t isValidISBN13(uint8_t* isbn) {
    uint32_t result = 0;
    
    for (uint8_t i = 0; i < 12; i++) {
        result += (uint32_t) (isbn[i] * ((i % 2) ? 3 : 1));
    }
    
    uint8_t check_digit = (uint8_t) (10 - (result % 10));
    
    if (check_digit == 10) {
        check_digit = 0;
    }
    
    if (check_digit == isbn[12]) {
        return 1;
    }
    
    return 0;
}

uint8_t normalizeISBN(const char* isbn, uint8_t* normalized, uint8_t* normal_len) {
    uint8_t len = strlen(isbn);
    
    for (uint8_t i = 0; i < len && *normal_len <= 12; i++) {
        uint8_t val = isbn[i] - '0';
        
        if (val > 9) {
            if (val == 40) {
                if (*normal_len != 9) {
                    return 0;
                }
                
                val = 10;
            }
            
            continue;
        }
        
        normalized[(*normal_len)++] = val;
        
        if (*normal_len == 10 && val == 10) {
            break;
        }
    }
    
    if (*normal_len == 10 || *normal_len == 13) {
        return 1;
    }
    
    return 0;
}

uint8_t isValidISBN(const char* isbn) {
    int len = strlen(isbn);
    
    if (len < 10 || len > 17) {
        return 0;
    }
    
    uint8_t normalized[13];
    uint8_t normal_len = 0;
    
    if (!normalizeISBN(isbn, normalized, &normal_len)) {
        return 0;
    }
    
    if (normal_len == 10) {
        return isValidISBN10(normalized);
    }
    
    return isValidISBN13(normalized);
}