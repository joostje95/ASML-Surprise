#ifndef BITMAP_H
#define BITMAP_H

#include <Arduino.h>
#include <avr/pgmspace.h>

const PROGMEM byte asmlLogo[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x0f,
    0x00, 0xc0, 0x7f, 0x00, 0xff, 0x03, 0xfc, 0x07, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0x00, 0xfe, 0x0f, 0x00, 0xf8, 0xff, 0x01, 0xff, 0x03, 0xfc, 0x07,
    0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x1f, 0x00, 0xfc, 0xff, 0x01,
    0xff, 0x03, 0xfe, 0x0f, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x1f,
    0x00, 0xfe, 0xff, 0x01, 0xff, 0x07, 0xfe, 0x0f, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0x00, 0xff, 0x1f, 0x00, 0xff, 0xff, 0x01, 0xff, 0x07, 0xfe, 0x0f,
    0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3f, 0x80, 0xff, 0xff, 0x01,
    0xff, 0x07, 0xfe, 0x0f, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x00, 0xff, 0x3f,
    0x80, 0x81, 0xc0, 0x01, 0xff, 0x0f, 0xff, 0x0f, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0x80, 0xbf, 0x3f, 0x80, 0x60, 0x00, 0x81, 0xff, 0x0f, 0xff, 0x0f,
    0xf8, 0x07, 0x00, 0x00, 0x00, 0x80, 0xbf, 0x7f, 0x00, 0x70, 0x00, 0x80,
    0xff, 0x0f, 0xff, 0x0f, 0xf8, 0x07, 0x00, 0x00, 0x00, 0x80, 0x3f, 0x7f,
    0x00, 0xf0, 0x00, 0x80, 0xff, 0x8f, 0xff, 0x1f, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0xc0, 0x3f, 0x7f, 0x00, 0xf0, 0x03, 0x80, 0xff, 0x8f, 0xff, 0x1f,
    0xf8, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x3f, 0xff, 0x00, 0xf0, 0x1f, 0x80,
    0xff, 0x9f, 0xff, 0x1f, 0xf8, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x1f, 0xff,
    0x00, 0xf0, 0x7f, 0x80, 0xbf, 0x9f, 0xff, 0x1f, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0xe0, 0x1f, 0xff, 0x00, 0xf0, 0xff, 0x81, 0xbf, 0x9f, 0xef, 0x1f,
    0xf8, 0x07, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xfe, 0x01, 0xe0, 0xff, 0x83,
    0xbf, 0xdf, 0xef, 0x1f, 0xf8, 0x07, 0x00, 0x00, 0x00, 0xe0, 0x1f, 0xfe,
    0x01, 0xc0, 0xff, 0x83, 0x3f, 0xff, 0xef, 0x1f, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0xe0, 0x1f, 0xfe, 0x01, 0x00, 0xff, 0x87, 0x3f, 0xff, 0xef, 0x3f,
    0xf8, 0x07, 0x00, 0x00, 0x00, 0xf0, 0x1f, 0xfe, 0x01, 0x00, 0xfc, 0x87,
    0x3f, 0xff, 0xcf, 0x3f, 0xf8, 0x07, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff,
    0x03, 0x00, 0xf8, 0x87, 0x3f, 0xff, 0xc7, 0x3f, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0xf0, 0xff, 0xff, 0x03, 0x00, 0xf8, 0x8f, 0x3f, 0xff, 0xc7, 0x3f,
    0xf8, 0x07, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0x83, 0x00, 0xf8, 0x8f,
    0x3f, 0xfe, 0xc7, 0x3f, 0xf8, 0x07, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff,
    0x87, 0x03, 0xfc, 0x87, 0x3f, 0xfe, 0xc7, 0x3f, 0xf8, 0x07, 0x00, 0x00,
    0x00, 0xf8, 0x07, 0xfc, 0x87, 0xff, 0xff, 0xc3, 0x3f, 0xfe, 0xc3, 0x3f,
    0xf8, 0xff, 0x3f, 0x00, 0x00, 0xfc, 0x07, 0xf8, 0x87, 0xff, 0xff, 0xc3,
    0x3f, 0xfc, 0xc3, 0x7f, 0xf8, 0xff, 0x3f, 0x00, 0x00, 0xfc, 0x07, 0xf8,
    0x8f, 0xff, 0xff, 0xc1, 0x3f, 0xfc, 0xc3, 0x7f, 0xf8, 0xff, 0x3f, 0x00,
    0x00, 0xfc, 0x07, 0xf8, 0x8f, 0xff, 0xff, 0xc0, 0x1f, 0xfc, 0xc3, 0x7f,
    0xf8, 0xff, 0x3f, 0x00, 0x00, 0xfe, 0x03, 0xf8, 0x0f, 0xfe, 0x3f, 0xc0,
    0x1f, 0xfc, 0xc3, 0x7f, 0xf8, 0xff, 0x3f, 0x00, 0x00, 0xfe, 0x03, 0xf0,
    0x1f, 0xe0, 0x07, 0xc0, 0x1f, 0xfc, 0xc1, 0x7f, 0xf0, 0xff, 0x3f, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

const PROGMEM byte waferBitmapArray[][350] =
    {
        {0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xde, 0xff, 0x03,
         0x00, 0x00, 0x00, 0x80, 0xdf, 0xff, 0x0f, 0x00, 0x00, 0x00, 0xb0, 0xdf,
         0xff, 0x2f, 0x00, 0x00, 0x00, 0xb8, 0xdf, 0xff, 0xef, 0x00, 0x00, 0x00,
         0xbc, 0xdf, 0xff, 0xef, 0x01, 0x00, 0x00, 0xbe, 0xdf, 0xff, 0xef, 0x01,
         0x00, 0x80, 0xbf, 0xdf, 0xff, 0xef, 0x07, 0x00, 0x80, 0xbf, 0xdf, 0xff,
         0xef, 0x07, 0x00, 0xc0, 0xbf, 0xdf, 0xff, 0xef, 0x17, 0x00, 0xe0, 0xbf,
         0xdf, 0xff, 0xef, 0x37, 0x00, 0xf0, 0xbf, 0xdf, 0xff, 0xef, 0x77, 0x00,
         0xf8, 0xbf, 0xdf, 0xff, 0xef, 0x77, 0x00, 0xf8, 0xbf, 0xdf, 0xff, 0xef,
         0xf7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xbf, 0xdf,
         0xff, 0xef, 0xf7, 0x00, 0xfc, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x01, 0xfe,
         0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x01, 0xfe, 0xbf, 0xdf, 0xff, 0xef, 0xf7,
         0x03, 0xfe, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x03, 0xfe, 0xbf, 0xdf, 0xff,
         0xef, 0xf7, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xbf,
         0xdf, 0xff, 0xef, 0xf7, 0x03, 0xff, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x03,
         0xff, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x03, 0xff, 0xbf, 0xdf, 0xff, 0xef,
         0xf7, 0x03, 0xff, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x03, 0xff, 0xbf, 0xdf,
         0xff, 0xef, 0xf7, 0x03, 0x7f, 0xbf, 0xdf, 0xcf, 0xef, 0xf7, 0x03, 0xfe,
         0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x03, 0xfe, 0xbf, 0xdf, 0xff, 0xef, 0xf7,
         0x03, 0xfe, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x03, 0xfe, 0xbf, 0xdf, 0xff,
         0xef, 0xf7, 0x03, 0xfc, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x01, 0xfc, 0xbf,
         0xdf, 0xff, 0xef, 0xf7, 0x01, 0xf8, 0xbf, 0xdf, 0xff, 0xef, 0xf7, 0x00,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xbf, 0xdf, 0xff, 0xef,
         0xf7, 0x00, 0xf0, 0xbf, 0xdf, 0xff, 0xef, 0x77, 0x00, 0xf0, 0xbf, 0xdf,
         0xff, 0xef, 0x37, 0x00, 0xe0, 0xbf, 0xdf, 0xff, 0xef, 0x17, 0x00, 0x80,
         0xbf, 0xdf, 0xff, 0xef, 0x07, 0x00, 0x80, 0xbf, 0xdf, 0xff, 0xef, 0x07,
         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0xdf, 0xff,
         0xef, 0x01, 0x00, 0x00, 0xbc, 0xdf, 0xff, 0xef, 0x00, 0x00, 0x00, 0xb8,
         0xdf, 0xff, 0x6f, 0x00, 0x00, 0x00, 0xa0, 0xdf, 0xff, 0x2f, 0x00, 0x00,
         0x00, 0x00, 0xdf, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xdc, 0xff, 0x01,
         0x00, 0x00},
        {0x00, 0x00, 0x60, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x3f, 0x01,
         0x00, 0x00, 0x00, 0x80, 0x3f, 0x3f, 0x07, 0x00, 0x00, 0x00, 0xc0, 0x3f,
         0x9f, 0x3f, 0x00, 0x00, 0x00, 0xf8, 0x9f, 0x9f, 0x3f, 0x00, 0x00, 0x00,
         0xfc, 0x9f, 0xdf, 0xff, 0x00, 0x00, 0x00, 0xfc, 0xdf, 0xcf, 0xff, 0x03,
         0x00, 0x00, 0xe1, 0xcf, 0xcf, 0xff, 0x03, 0x00, 0x80, 0x87, 0xef, 0xe7,
         0xff, 0x0f, 0x00, 0xc0, 0x1f, 0xe6, 0xe7, 0xff, 0x07, 0x00, 0xe0, 0xff,
         0xe0, 0xf3, 0xff, 0x07, 0x00, 0xe0, 0xff, 0xc3, 0xf3, 0xff, 0x33, 0x00,
         0x80, 0xff, 0x03, 0xfb, 0xff, 0x73, 0x00, 0x18, 0xfe, 0x7b, 0xf8, 0xff,
         0x79, 0x00, 0x78, 0xf8, 0xf9, 0xe1, 0xff, 0x79, 0x00, 0xfc, 0xc1, 0xf9,
         0x04, 0xff, 0xfd, 0x00, 0xfc, 0x0f, 0xfc, 0x3c, 0xfc, 0xfc, 0x00, 0xfe,
         0x3f, 0x7c, 0xfe, 0xf0, 0x7c, 0x00, 0xfe, 0x7f, 0x60, 0xfe, 0x03, 0x7e,
         0x00, 0xfe, 0x7f, 0x06, 0xff, 0x1f, 0x7e, 0x03, 0xfe, 0x7f, 0x1f, 0xfe,
         0x3f, 0x38, 0x03, 0x7e, 0x3f, 0x3f, 0xf0, 0x3f, 0x83, 0x03, 0xff, 0x3f,
         0x9f, 0xc3, 0xbf, 0x0f, 0x03, 0xfe, 0x9f, 0x9f, 0x0f, 0x9e, 0x1f, 0x00,
         0xfe, 0x9f, 0xdf, 0x7f, 0x98, 0xcf, 0x01, 0xfe, 0xcf, 0xcf, 0xff, 0xc1,
         0xcf, 0x03, 0xfe, 0xcf, 0xef, 0xff, 0x07, 0xef, 0x03, 0xf0, 0xef, 0xe7,
         0xff, 0x2f, 0xe4, 0x03, 0xc3, 0xe7, 0xe7, 0xff, 0xe7, 0xe0, 0x03, 0x0e,
         0xe7, 0xf3, 0xf3, 0xf7, 0x83, 0x03, 0x3f, 0xf0, 0xf3, 0xf7, 0xf3, 0x13,
         0x00, 0xfe, 0xe1, 0xfb, 0xff, 0xf3, 0x79, 0x00, 0xfc, 0x83, 0xf9, 0xff,
         0xf9, 0xf9, 0x01, 0xfc, 0x39, 0xf8, 0xff, 0xf9, 0xfd, 0x00, 0xfc, 0xfd,
         0xf0, 0xff, 0xfd, 0xfc, 0x00, 0xf0, 0xfc, 0xc0, 0xff, 0xfc, 0x7c, 0x00,
         0x80, 0x7c, 0x1e, 0xfe, 0x7e, 0x7e, 0x00, 0x18, 0x7e, 0x7e, 0x78, 0x7e,
         0x7e, 0x00, 0x70, 0x70, 0xff, 0x61, 0x3e, 0x3f, 0x00, 0x70, 0x03, 0xff,
         0x0f, 0x3f, 0x3f, 0x00, 0x20, 0x0f, 0xff, 0x3f, 0xbc, 0x1f, 0x00, 0x80,
         0x1f, 0xf8, 0xbf, 0x90, 0x1f, 0x00, 0x00, 0x9f, 0xe1, 0x9f, 0x87, 0x07,
         0x00, 0x00, 0xcf, 0x87, 0x9f, 0x0f, 0x02, 0x00, 0x00, 0xce, 0x3f, 0xcc,
         0x4f, 0x00, 0x00, 0x00, 0xec, 0xff, 0xc0, 0xef, 0x00, 0x00, 0x00, 0xe0,
         0xff, 0xc3, 0x27, 0x00, 0x00, 0x00, 0x80, 0xff, 0x07, 0x06, 0x00, 0x00,
         0x00, 0x00, 0xfe, 0x77, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x73, 0x00,
         0x00, 0x00},
        {0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0x00,
         0x00, 0x00, 0x00, 0x80, 0xfc, 0xff, 0x04, 0x00, 0x00, 0x00, 0xe0, 0xf9,
         0x7f, 0x1e, 0x00, 0x00, 0x00, 0xf0, 0xf3, 0x3f, 0x3f, 0x00, 0x00, 0x00,
         0xf0, 0xe7, 0x9f, 0x3f, 0x00, 0x00, 0x00, 0xe2, 0xcf, 0xcf, 0x1f, 0x01,
         0x00, 0x00, 0xc7, 0x9f, 0xe7, 0x8f, 0x03, 0x00, 0x80, 0x8f, 0x3f, 0xf3,
         0xc7, 0x07, 0x00, 0xc0, 0x1f, 0x7f, 0xf8, 0xe3, 0x0f, 0x00, 0xe0, 0x3f,
         0xfe, 0xfc, 0xf1, 0x1f, 0x00, 0xe0, 0x7f, 0x7c, 0xf8, 0xf8, 0x1f, 0x00,
         0xf0, 0xff, 0x38, 0x73, 0xfc, 0x3f, 0x00, 0xf8, 0xff, 0x91, 0x27, 0xfe,
         0x7f, 0x00, 0xf8, 0xfb, 0xc3, 0x0f, 0xff, 0xff, 0x00, 0xfc, 0xf9, 0xc7,
         0x8f, 0xff, 0xff, 0x00, 0xfc, 0xff, 0x83, 0x07, 0xff, 0xff, 0x00, 0xfc,
         0xff, 0x19, 0x63, 0xfe, 0xff, 0x00, 0xf8, 0xff, 0x3c, 0xf0, 0xfc, 0x7f,
         0x00, 0xf2, 0x7f, 0x7e, 0xf8, 0xf9, 0x3f, 0x01, 0xe7, 0x3f, 0x7f, 0xf8,
         0xf3, 0x9f, 0x03, 0xcf, 0x9f, 0x3f, 0xf0, 0xe7, 0xcf, 0x03, 0x9f, 0xcf,
         0x1f, 0xe3, 0xcf, 0xe7, 0x03, 0x3e, 0xe7, 0x8f, 0xc7, 0x9f, 0xf3, 0x01,
         0x7f, 0xf0, 0xc7, 0x8f, 0x3f, 0xf8, 0x03, 0xff, 0xf8, 0xe3, 0x1f, 0x7f,
         0xfc, 0x03, 0xfe, 0xf8, 0xf1, 0x3f, 0x7e, 0xfc, 0x01, 0x7c, 0xf2, 0xf8,
         0x7f, 0x3c, 0xf9, 0x00, 0x39, 0x67, 0xfc, 0xff, 0x98, 0x73, 0x02, 0x83,
         0x0f, 0xfe, 0xfc, 0xc1, 0x07, 0x03, 0xc7, 0x1f, 0xff, 0xfc, 0xe3, 0x8f,
         0x03, 0xc6, 0x0f, 0xff, 0xff, 0xc3, 0x8f, 0x01, 0x92, 0x47, 0xfe, 0xff,
         0x89, 0x27, 0x01, 0x38, 0xe3, 0xfc, 0xff, 0x1c, 0x73, 0x00, 0x7c, 0xf0,
         0xf9, 0x7f, 0x3e, 0xf8, 0x00, 0xfc, 0xf8, 0xf3, 0x3f, 0x7f, 0xfc, 0x00,
         0x78, 0xf8, 0xe7, 0x9f, 0x7f, 0x78, 0x00, 0x38, 0xf2, 0xcf, 0xcf, 0x3f,
         0x71, 0x00, 0x10, 0xe7, 0x9f, 0xe7, 0x9f, 0x23, 0x00, 0x80, 0xcf, 0x3f,
         0xf3, 0xcf, 0x07, 0x00, 0xc0, 0x9f, 0x7f, 0xf8, 0xe7, 0x0f, 0x00, 0x80,
         0x3f, 0xff, 0xfc, 0xf3, 0x07, 0x00, 0x00, 0x7f, 0x7e, 0xf8, 0xf9, 0x03,
         0x00, 0x00, 0xfe, 0x3c, 0xf3, 0xfc, 0x01, 0x00, 0x00, 0xfc, 0x99, 0x67,
         0xfe, 0x00, 0x00, 0x00, 0xf8, 0xc3, 0x0f, 0x7f, 0x00, 0x00, 0x00, 0xf0,
         0xe7, 0x9f, 0x3f, 0x00, 0x00, 0x00, 0xe0, 0xc3, 0x0f, 0x1f, 0x00, 0x00,
         0x00, 0x00, 0x98, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0xf3, 0x00,
         0x00, 0x00},
        {0x00, 0x00, 0x40, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf2, 0x7b, 0x00,
         0x00, 0x00, 0x00, 0x80, 0xf3, 0xf3, 0x07, 0x00, 0x00, 0x00, 0xf0, 0xe7,
         0xf3, 0x0f, 0x00, 0x00, 0x00, 0xf0, 0xe7, 0xe7, 0x7f, 0x00, 0x00, 0x00,
         0xfc, 0xef, 0xe7, 0xff, 0x00, 0x00, 0x00, 0xfe, 0xcf, 0xef, 0xff, 0x00,
         0x00, 0x00, 0xff, 0xcf, 0xcf, 0x1f, 0x02, 0x00, 0x80, 0xff, 0x9f, 0xdf,
         0x87, 0x07, 0x00, 0x80, 0xff, 0x9f, 0x9f, 0xe1, 0x0f, 0x00, 0x80, 0x3f,
         0x3f, 0x1f, 0xfc, 0x1f, 0x00, 0x30, 0xff, 0x3f, 0x0f, 0xff, 0x1f, 0x00,
         0x38, 0xff, 0x7f, 0x03, 0xff, 0x07, 0x00, 0x78, 0xfe, 0x7f, 0x78, 0xff,
         0x61, 0x00, 0x78, 0xfe, 0x1f, 0x7e, 0x7e, 0x78, 0x00, 0xfc, 0xfe, 0x83,
         0x7c, 0x0e, 0xfe, 0x00, 0xfc, 0xfc, 0xf0, 0xfc, 0xc0, 0xff, 0x00, 0xf8,
         0x3c, 0xfc, 0xf9, 0xf0, 0xff, 0x01, 0xf8, 0x01, 0xff, 0x19, 0xf8, 0xff,
         0x01, 0xfb, 0xe1, 0xff, 0x83, 0xf9, 0xff, 0x01, 0x73, 0xf0, 0xff, 0xe1,
         0xfb, 0xff, 0x01, 0x07, 0xf3, 0x3f, 0xf0, 0xf3, 0xff, 0x01, 0xc3, 0xf7,
         0x0f, 0xe7, 0xf3, 0xff, 0x03, 0xe0, 0xe7, 0xc1, 0xe7, 0xe7, 0xff, 0x03,
         0xce, 0x67, 0xf8, 0xef, 0xe7, 0xff, 0x03, 0xcf, 0x0f, 0xfe, 0xcf, 0xcf,
         0xff, 0x03, 0xdf, 0x83, 0xff, 0xdf, 0xcf, 0xff, 0x01, 0x9f, 0xd0, 0xff,
         0x9f, 0xdf, 0x3f, 0x00, 0x1f, 0x9c, 0xff, 0x9f, 0x9f, 0x0f, 0x03, 0x07,
         0xbf, 0x3f, 0x3f, 0x9f, 0xc3, 0x01, 0x20, 0x3f, 0x7f, 0x3f, 0x3f, 0xf0,
         0x03, 0x78, 0x3e, 0xff, 0x7f, 0x1f, 0xfe, 0x01, 0x7e, 0x7e, 0xfe, 0x7f,
         0x06, 0xff, 0x00, 0xfc, 0x7e, 0xfe, 0x7f, 0x70, 0xfe, 0x00, 0xfc, 0xfc,
         0xfe, 0x3f, 0xfc, 0xfe, 0x00, 0xf8, 0xfc, 0xfc, 0x0f, 0xfc, 0x3c, 0x00,
         0xf8, 0xf9, 0xfd, 0xe1, 0xf9, 0x04, 0x00, 0xf8, 0xf9, 0x79, 0xf8, 0xf9,
         0x61, 0x00, 0xf0, 0xf3, 0x19, 0xfe, 0x3b, 0x38, 0x00, 0xf0, 0xf3, 0xc3,
         0xff, 0x03, 0x3b, 0x00, 0xe0, 0xf7, 0xf0, 0xff, 0xc3, 0x13, 0x00, 0xe0,
         0x27, 0xf4, 0x7f, 0xe0, 0x07, 0x00, 0x80, 0x87, 0xe7, 0x1f, 0xe6, 0x03,
         0x00, 0x00, 0xc1, 0xe7, 0x87, 0xcf, 0x03, 0x00, 0x00, 0xc8, 0xcf, 0xf0,
         0xcf, 0x01, 0x00, 0x00, 0xdc, 0x0f, 0xfc, 0xdf, 0x00, 0x00, 0x00, 0x90,
         0x0f, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x80, 0x81, 0xff, 0x07, 0x00, 0x00,
         0x00, 0x00, 0xb8, 0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0x38, 0x3f, 0x00,
         0x00, 0x00}};

const PROGMEM byte doneCheckMark[] = {
   0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x07, 0x00, 0x00, 0xf8,
   0xff, 0x1f, 0x00, 0x00, 0xfe, 0xff, 0x7f, 0x00, 0x00, 0xff, 0xff, 0xff,
   0x00, 0x80, 0xff, 0x81, 0xff, 0x03, 0xc0, 0x3f, 0x00, 0xfc, 0x07, 0xe0,
   0x0f, 0x00, 0xf0, 0x07, 0xf0, 0x07, 0x00, 0xe0, 0x0f, 0xf8, 0x03, 0x00,
   0xc0, 0x1f, 0xf8, 0x01, 0x00, 0x80, 0x1f, 0xfc, 0x00, 0x00, 0x00, 0x3f,
   0x7c, 0x00, 0x00, 0x00, 0x3e, 0x7e, 0x00, 0x00, 0x1c, 0x7e, 0x3e, 0x00,
   0x00, 0x3e, 0x7c, 0x3e, 0x00, 0x00, 0x3f, 0x7c, 0x3f, 0x00, 0xc0, 0x1f,
   0xf8, 0x1f, 0x00, 0xe0, 0x0f, 0xf8, 0x1f, 0x78, 0xf0, 0x0f, 0xf8, 0x1f,
   0xfc, 0xf0, 0x07, 0xf8, 0x1f, 0xfc, 0xf9, 0x03, 0xf8, 0x1f, 0xf8, 0xff,
   0x01, 0xf8, 0x1f, 0xf0, 0xff, 0x00, 0xf8, 0x3e, 0xf0, 0x7f, 0x00, 0xf8,
   0x3e, 0xe0, 0x3f, 0x00, 0x7c, 0x3e, 0x80, 0x0f, 0x00, 0x7c, 0x7e, 0x00,
   0x0f, 0x00, 0x7e, 0x7c, 0x00, 0x00, 0x00, 0x3e, 0xfc, 0x00, 0x00, 0x00,
   0x3f, 0xf8, 0x01, 0x00, 0x00, 0x1f, 0xf8, 0x01, 0x00, 0x80, 0x1f, 0xf0,
   0x07, 0x00, 0xc0, 0x0f, 0xe0, 0x0f, 0x00, 0xf0, 0x0f, 0xe0, 0x3f, 0x00,
   0xf8, 0x07, 0xc0, 0xff, 0x00, 0xff, 0x03, 0x00, 0xff, 0xff, 0xff, 0x00,
   0x00, 0xfe, 0xff, 0x7f, 0x00, 0x00, 0xf8, 0xff, 0x1f, 0x00, 0x00, 0xe0,
   0xff, 0x07, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00 };


const PROGMEM byte outputBasic[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00, 0x00, 0xfc, 0xff, 0x07,
   0x00, 0x00, 0x7f, 0xc0, 0x1f, 0x00, 0x00, 0x0f, 0x00, 0x1e, 0x00, 0x00,
   0x07, 0x00, 0x38, 0x00, 0x00, 0x0f, 0x00, 0x3c, 0x00, 0x00, 0x7f, 0xc0,
   0x3f, 0x00, 0x00, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xfb, 0xff, 0x3b, 0x00,
   0x00, 0x83, 0x7f, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03,
   0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38,
   0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00,
   0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00,
   0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x07, 0x00, 0x3c, 0x00,
   0x00, 0x3f, 0x80, 0x1f, 0x00, 0x00, 0xfe, 0xff, 0x1f, 0x00, 0x00, 0xfc,
   0xff, 0x07, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00 };

const PROGMEM byte outputArrow[] = {
   0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00,
   0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0xf8,
   0x00, 0x00, 0x00, 0xc0, 0xff, 0x01, 0x00, 0x00, 0xf0, 0xff, 0x01, 0x00,
   0x00, 0xf8, 0xff, 0x01, 0x00, 0x00, 0x7c, 0x78, 0x00, 0x00, 0x00, 0x1c,
   0x7c, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x00, 0x00, 0x00, 0x0e, 0x1e, 0x00,
   0x00, 0x00, 0x0e, 0x0c, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00,
   0x0e, 0x00, 0x00, 0x00, 0x30, 0x8e, 0x01, 0x00, 0x00, 0x7c, 0xce, 0x07,
   0x00, 0x00, 0x7f, 0xce, 0x1f, 0x00, 0x00, 0x0f, 0x0e, 0x1e, 0x00, 0x00,
   0x07, 0x00, 0x38, 0x00, 0x00, 0x0f, 0x00, 0x3c, 0x00, 0x00, 0x7f, 0xc0,
   0x3f, 0x00, 0x00, 0xff, 0xff, 0x3f, 0x00, 0x00, 0xfb, 0xff, 0x3b, 0x00,
   0x00, 0x83, 0x7f, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03,
   0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38,
   0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00,
   0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x03, 0x00,
   0x38, 0x00, 0x00, 0x03, 0x00, 0x38, 0x00, 0x00, 0x07, 0x00, 0x3c, 0x00,
   0x00, 0x3f, 0x80, 0x1f, 0x00, 0x00, 0xfe, 0xff, 0x1f, 0x00, 0x00, 0xfc,
   0xff, 0x07, 0x00, 0x00, 0xc0, 0x7f, 0x00, 0x00 };



#endif