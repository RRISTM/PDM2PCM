#ifndef __PCM2PDM_H
#define __PCM2PDM_H

#include "main.h"

uint32_t pcm2pdm(uint16_t *inPcm, uint8_t *outPdm, uint32_t sizeIn, uint32_t oversample);

#endif // __PCM2PDM_H
