#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int cant_pos;
    int vidas_ini;
    int max_band;
    int max_prem;
    int max_vid_ext;
    int max_oasis;
    int max_tormenta;
}tConfig;



int cargarConfig(tConfig*);


#endif // CONFIG_H_
