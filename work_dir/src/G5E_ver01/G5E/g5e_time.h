#ifndef HIC_TIME
#define HIC_TIME
#include <time.h>
#include <stdio.h>
void timestamp(char *ret);

class G5ETimer
{
private:
	int starttime;
public:
	G5ETimer();
	~G5ETimer();
	bool check(double length, bool mode);
	void renew();
};
class G5ETime
{
private:
	int lasttime;
	
	double spf;
public:	
	G5ETime();
	void run();
	double getffps();
	int getifps();
	double getspf();
	double fps; //temporarely made public
};
#endif