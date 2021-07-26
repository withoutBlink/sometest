#ifndef TOOLS_H
#define TOOLS_H

#include "src/wssrvroute.h"

class Tools
{
public:
	static Tools *Instance();

	void GetItemList();
	void InitUi();
	void Started();

private:
	Tools();
	~Tools();

private:
	static Tools *_This;
};

#endif // TOOLS_H
