#ifndef EV3_UNIT_STATUS_H_
#define EV3_UNIT_STATUS_H_

class Status{
public:
	Status();
	~Status();

	int orientation;
	int x;
	int y;

	void setStatus(int _orientaion, int _x, int _y);
};

#endif