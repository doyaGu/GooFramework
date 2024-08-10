#pragma once

class EnvironmentEvent {
};

class EnvironmentCallbacks {
	virtual ~EnvironmentCallbacks();
	virtual void update(float);
	virtual void inputEvent(EnvironmentEvent const&);
	virtual void onError(char const*);
};

class WogEnvironmentCallbacks : public EnvironmentCallbacks {
public:
};
