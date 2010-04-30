#include "g5e_time.h"
#include "g5e_std.h"


void timestamp(char *ret)
{
	time_t rawtime;
	struct tm *timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	sprintf_s(ret,64,"%d/%d/%d %d:%d:%d",timeinfo->tm_mon+1,timeinfo->tm_mday,timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min,timeinfo->tm_sec);
}
G5ETimer::G5ETimer()
{
	starttime = SDL_GetTicks();
}
bool G5ETimer::check(double length, bool mode)
{
	double diff = (double)(SDL_GetTicks() - starttime)/1000;
	if(diff>length)
	{
		if(mode) this->renew();
		return true;
	}
	else
	{
		return false;
	}
}
void G5ETimer::renew()
{
	starttime = SDL_GetTicks();
}
G5ETimer::~G5ETimer(){}
/*G5ETimer::G5ETimer()
{
	times = (unsigned int*)malloc(sizeof(unsigned int));
	cur = 0;
}
G5ETimer::~G5ETimer()
{
	free(times);
}
int G5ETimer::start()
{
	cur++;
	times = (unsigned int*)realloc(times, cur*sizeof(unsigned int));
	times[cur-1] = SDL_GetTicks();
	return cur-1;
}
bool G5ETimer::check(int id, double length, bool mode)
{
	double diff = (double)(SDL_GetTicks() - times[id])/1000;
	if(diff>length)
	{
		if(mode) this->renew(id);
		else this->stop(id);
		return true;
	}
	else
	{
		return false;
	}
}
void G5ETimer::renew(int id)
{
	times[id] = SDL_GetTicks();
}
void G5ETimer::stop(int id)
{
	for(int n = id;n<this->cur-1;n++)
	{
		times[n] = times[n-1];
	}
	cur--;
	times = (unsigned int*) realloc(times,(cur+1)*sizeof(unsigned int));
}
*/
G5ETime::G5ETime()
{
	lasttime = clock();
}
void G5ETime::run()
{
	int actualtime = SDL_GetTicks();
	this->spf = (double)(actualtime - this->lasttime)/1000.0f;
	if(spf==0) fps = 1000;
	else this->fps = 1/spf;
	lasttime = actualtime;
}
double G5ETime::getffps()
{
	return this->fps;
}
int G5ETime::getifps()	
{
	return (int)this->fps;
}
double G5ETime::getspf()
{
	return this->spf;
}