#ifndef ISBN_H
#define ISBN_H

uint8_t isValidISBN10(uint8_t* isbn);
uint8_t isValidISBN13(uint8_t* isbn);
uint8_t normalizedISBN(const char* isbn, uint8_t* normalized, uint8_t* normal_len);
uint8_t isValidISBN(const char* isbn);

#endif