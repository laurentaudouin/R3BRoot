#ifndef R3BNEULANDCALDATA_H
#define R3BNEULANDCALDATA_H

#include "TObject.h"
#include <iostream>

class R3BNeulandCalData : public TObject
{
  public:
    R3BNeulandCalData() = default;
    R3BNeulandCalData(Int_t barId, Int_t side, Double_t time, Int_t qdc);

    Int_t GetBarId() const { return fBarId; }
    Int_t GetSide() const { return fSide; }
    Double_t GetTime() const { return fTime; }
    Int_t GetQdc() const { return fQdc; }

    void Print(const Option_t*) const override;

  private:
    Int_t fBarId;
    Int_t fSide;
    Double_t fTime;
    Int_t fQdc;

    ClassDefOverride(R3BNeulandCalData, 1)
};

std::ostream& operator<<(std::ostream&, const R3BNeulandCalData&); // Support easy printing

#endif // R3BNEULANDCALDATA_H
