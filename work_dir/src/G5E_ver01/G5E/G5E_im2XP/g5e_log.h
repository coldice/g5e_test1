#include <stdio.h>
#include <stdarg.h>
#include "g5e_time.h"
/* **************************** Logfunctions ***************************** */

#define LOG_ERROR(message) g5e_log_msg("FF0000", "ERROR", message);
#define LOG_SUCCESS(message) g5e_log_msg("00FF00", "SUCCESS", message);
#define LOG_VALUE(message, value) g5e_log_msg("FFFACD", "VALUE", message, value);
#define LOG_MATRIX4(matrix) g5e_log_msg("FFFACD", "MATRIX4", "<PRE>%f	%f	%f	%f<br>%f	%f	%f	%f<br>%f	%f	%f	%f<br>%f	%f	%f	%f</PRE>",matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7], matrix[8], matrix[9], matrix[10], matrix[11], matrix[12], matrix[13], matrix[14], matrix[15]);
#define LOG_MATRIX3(matrix) g5e_log_msg("FFFACD", "MATRIX3", "<PRE>%f	%f	%f<br>%f	%f	%f<br>%f	%f	%f</PRE>",matrix[0], matrix[1], matrix[2], matrix[3], matrix[4], matrix[5], matrix[6], matrix[7], matrix[8]);
#define LOG_VECTOR3(vector) g5e_log_msg("FFFACD", "VECTOR3", "<PRE>%f	%f	%f</PRE>",vector[0], vector[1], vector[2]);
#define LOG_VECTOR4(vector) g5e_log_msg("FFFACD", "VECTOR4", "<PRE>%f	%f	%f	%f</PRE>",vector[0], vector[1], vector[2], vector[3]);

/* **************************** ERROR Values ***************************** */
#define G5E_SUCCESS 1000
#define G5E_INVALID_VECTOR 1001

void g5e_log_msg(const char *bgcolor, const char *type, const char *msg, ...);
bool g5e_log_clearinit();