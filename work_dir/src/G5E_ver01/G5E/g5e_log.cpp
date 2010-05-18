#include "g5e_log.h"
void g5e_log_msg(const char *bgcolor, const char *type, const char *msg, ...)
{
	char message[512];		
	char time[64];
	va_list	ap;					


	if (msg == NULL)				
		return;						

	va_start(ap, msg);					
		vsprintf_s(message,sizeof(message), msg, ap);			
	va_end(ap);	
	
	timestamp(time);
	FILE *log;
	fopen_s(&log,"g5e_log.html","r");
	if(log == NULL)
	{if(!g5e_log_clearinit()) return;}
	else fclose(log);
	fopen_s(&log,"g5e_log.html","a");
	if(log == NULL) return;
	fprintf(log,"<tr><td bgcolor='%s'><b>%s</b></td><td bgcolor='%s'><b>%s</b></td><td bgcolor='%s'>%s</td></tr>",bgcolor, time ,bgcolor, type, bgcolor, message);
	fclose(log);
}
bool g5e_log_clearinit()
{
	FILE *log;
	fopen_s(&log,"g5e_log.html","w");
	if(log == NULL) return false;
	fprintf(log,"<html>\n<head>\n<title>    G5E Logfile</title>\n</head>\n<body bgcolor='FFFACD'>\n<font size='10' face='Verdana'>\n<b>G5E Logfile</b>\n</font>\n<br>\n<br>\n<table border='1'>\n<tr><td width='130' bgcolor='FFE4B5'><b>Time:</b></td><td width='100' bgcolor='FFE4B5'><b>Type:</b></td><td width='400' bgcolor='FFE4B5'><b>Message:</b></td></tr>\n");
	fclose(log);
	return true;
}