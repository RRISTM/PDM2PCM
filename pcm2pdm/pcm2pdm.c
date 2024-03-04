#include "pcm2pdm.h"

int32_t onePcm2PdmConversion(uint16_t sample, uint8_t *outPdm, uint32_t oversample, int32_t qe);


uint32_t pcm2pdm(uint16_t *inPcm, uint8_t *outPdm, uint32_t sizeIn, uint32_t oversample)
{
  static int32_t qe = 0;
  uint32_t o, i = 0, k;
  if (oversample % 8 != 0)
  {
    return 1;
  }
  for (i = 0; i < sizeIn; i++)
  {
    qe = onePcm2PdmConversion(inPcm[i],(uint8_t*) &outPdm[(oversample / 8) * i], oversample, qe);
  }

  return 0;
}

// function pdm(real[0..s] x, real qe = 0) // initial running error is zero
//   var int[0..s] y
//
//   for n from 0 to s
//       if x[n] >= qe
//           y[n] := 1
//       else
//           y[n] := -1
//       qe := y[n] - x[n] + qe
//
//   return y, qe

// int32_t onePcm2PdmConversion(uint16_t sample, uint8_t *outPdm, uint32_t oversample, int32_t qe)
// {

//   uint32_t o, i = 0, k = 0;
//   uint8_t outBit[8];

//   for (o = 0; o < oversample; o++)
//   {
//     if (i > 7)
//     {
//       i = 0;
//       k++;
//     }
//     if (sample >= qe)
//     {
//       outBit[i] = 1;
//       qe = 1 - sample + qe;
//     }
//     else
//     {
//       outBit[i] = 0;
//       qe = -1 - sample + qe;
//     }

//     qe = outBit[i] - sample + qe;
//     outPdm[k] |= outBit[i] << i;

//     i++;
//   }
//   return qe;
// }

// Encode samples into pulse-density modulation
// using a first-order sigma-delta modulator

//function pdm(real[0..s] x, real qe = 0) // initial running error is zero
//    var int[0..s] y
//
//    for n from 0 to s do
//        qe := qe + x[n]
//        if qe > 0 then
//            y[n] := 1
//        else
//            y[n] := −1
//        qe := qe - y[n]
//
//    return y, qe // return output and running error
#define MAX_RANGE 32768
int32_t onePcm2PdmConversion(uint16_t sample, uint8_t *outPdm, uint32_t oversample, int32_t qe)
{

  uint32_t o, i = 0, k = 0;
  uint8_t outBit[8];

  int32_t tempSample = sample - MAX_RANGE;
  outPdm[0]=0;
  for (o = 0; o < oversample; o++)
  {
    if (i > 7)
    {
      i = 0;
      k++;
      outPdm[k]=0;
    }

    qe = qe +tempSample;

    if (qe > 0)
    {
      outBit[i] = 1;
      qe = qe - MAX_RANGE;
    }
    else
    {
      outBit[i] = 0;
      qe = qe + MAX_RANGE;
    }

    outPdm[k] |= outBit[i] << i;

    i++;
  }
  return qe;
}
