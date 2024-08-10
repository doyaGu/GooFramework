#pragma once

class Random {
public:
    virtual ~Random();
    virtual void SetSeed(int);

public:
  uint64_t field_8;
  uint64_t field_10;
  int field_18;
};


class WogRand : public Random {

};