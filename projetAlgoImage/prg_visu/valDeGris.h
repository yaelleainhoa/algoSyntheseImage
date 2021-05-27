#ifndef __VALDEGRIS_H
#define __VALDEGRIS_H

#include <string>
using namespace std;

typedef struct {
    int w;
    int h;
    int valeursDeGris[500][500];
} HeightMap;

#ifdef __cplusplus
extern "C"{
void defineHeight(HeightMap * heightMap, string map);
}
#endif

#endif