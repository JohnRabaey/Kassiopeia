#ifndef KGKGLINEARCONGRUENTIALGENERATOR_HH_
#define KGKGLINEARCONGRUENTIALGENERATOR_HH_

namespace KGeoBag
{
  class KGLinearCongruentialGenerator
  {
  public:
    KGLinearCongruentialGenerator();
    virtual ~KGLinearCongruentialGenerator() {}

    double Random() const;

  private:
    unsigned int fModulus;
    unsigned int fMultiplier;
    unsigned int fIncrement;
    mutable unsigned int fValue;
  };
}

#endif
