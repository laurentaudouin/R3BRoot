#ifndef NEULAND_DIGITIZING_ENGINE_H
#define NEULAND_DIGITIZING_ENGINE_H

#include "Rtypes.h"
#include <map>
#include <memory>
#include <vector>

namespace Neuland
{
    namespace Digitizing
    {
        struct PMTHit
        {
            Double_t time;
            Double_t light;

            bool operator<(const PMTHit& rhs) const { return (time < rhs.time); }

            PMTHit() = default;
            PMTHit(Double_t mcTime, Double_t mcLight, Double_t dist);
        };

        class Channel
        {
          public:
            virtual ~Channel() = default; // FIXME: Root doesn't like pure virtual destructors (= 0;)
            virtual void AddHit(Double_t mcTime, Double_t mcLight, Double_t dist) = 0;
            virtual bool HasFired() const = 0;
            virtual Double_t GetQDC() const = 0;
            virtual Double_t GetTDC() const = 0;
            virtual Double_t GetEnergy() const = 0;

          protected:
            std::vector<PMTHit> fPMTHits;
        };

        class Paddle
        {
          public:
            Paddle(std::unique_ptr<Channel> l, std::unique_ptr<Channel> r);
            void DepositLight(Double_t time, Double_t light, Double_t dist);

            bool HasFired() const;
            bool HasHalfFired() const;
            Double_t GetEnergy() const;
            Double_t GetTime() const;
            Double_t GetPosition() const;

            const Channel* GetLeftChannel() const { return fLeftChannel.get(); }
            const Channel* GetRightChannel() const { return fRightChannel.get(); }

          protected:
            std::unique_ptr<Channel> fLeftChannel;
            std::unique_ptr<Channel> fRightChannel;

          public:
            static constexpr Double_t gHalfLength = 135.;   // [cm]
            static constexpr Double_t gCMedium = 14.;       // speed of light in material in [cm/ns]
            static constexpr Double_t gAttenuation = 0.008; // light attenuation of plastic scintillator [1/cm]
            static constexpr Double_t gLambda = 1. / 2.1;
        };
    } // namespace Digitizing

    // abstract class, cannot be instantiated, to be used as a base class.
    class DigitizingEngine
    {
      public:
        virtual ~DigitizingEngine() = default; // FIXME: Root doesn't like pure virtual destructors (= 0;)
        virtual std::unique_ptr<Digitizing::Channel> BuildChannel() = 0;

        void DepositLight(Int_t paddle_id, Double_t time, Double_t light, Double_t dist);
        Double_t GetTriggerTime() const;
        std::map<Int_t, std::unique_ptr<Digitizing::Paddle>> ExtractPaddles();

      protected:
        std::map<Int_t, std::unique_ptr<Digitizing::Paddle>> paddles;
    };
} // namespace Neuland

#endif // NEULAND_DIGITIZING_ENGINE_H
