#pragma once

namespace SoLoud {
	class AudioAttenuator {
	public:
		virtual float attenuate(float aDistance, float aMinDistance, float aMaxDistance, float aRolloffFactor) = 0;
	};
}

class BoyAudioAttenuator: public SoLoud::AudioAttenuator {
public:
    virtual float attenuate(float aDistance, float aMinDistance, float aMaxDistance, float aRolloffFactor);
};