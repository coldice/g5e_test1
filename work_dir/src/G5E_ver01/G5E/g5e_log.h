#include <stdio.h>
#include <stdarg.h>
#include "g5e_time.h"
/* **************************** Logfunctions ***************************** */

#define LOG_ERROR(message) g5e_log_msg("FF0000", "ERROR", message);
#define LOG_SUCCESS(message) g5e_log_msg("00FF00", "SUCCESS", message);
#define LOG_MESH(did, name, id) g5e_log_msg("00FF00", "MESH", "%s Mesh '%s' with the ID '%d'",did, name, id);
#define LOG_VALUE(message, value) g5e_log_msg("FFFACD", "VALUE", message, value);
#define LOG_MATRIX4(matrix) g5e_log_msg("FFFACD", "MATRIX4", "<PRE>%f	%f	%f	%f<br>%f	%f	%f	%f<br>%f	%f	%f	%f<br>%f	%f	%f	%f</PRE>",matrix.a[0], matrix.a[1], matrix.a[2], matrix.a[3], matrix.a[4], matrix.a[5], matrix.a[6], matrix.a[7], matrix.a[8], matrix.a[9], matrix.a[10], matrix.a[11], matrix.a[12], matrix.a[13], matrix.a[14], matrix.a[15]);
#define LOG_MATRIX3(matrix) g5e_log_msg("FFFACD", "MATRIX3", "<PRE>%f	%f	%f<br>%f	%f	%f<br>%f	%f	%f</PRE>",matrix.a[0], matrix.a[1], matrix.a[2], matrix.a[3], matrix.a[4], matrix.a[5], matrix.a[6], matrix.a[7], matrix.a[8]);
#define LOG_VECTOR3(vector3) g5e_log_msg("FFFACD", "VECTOR3", "<PRE>%f	%f	%f</PRE>",vector3.v1, vector3.v2, vector3.v3);
#define LOG_VECTOR4(vector) g5e_log_msg("FFFACD", "VECTOR4", "<PRE>%f	%f	%f	%f</PRE>",vector.v1, vector.v2, vector.v3, vector.v4);

/* **************************** ERROR Values ***************************** */
#define G5E_SUCCESS 1000
#define G5E_INVALID_VECTOR 1001
#define G5E_INVALID_VALUE 1002
#define G5E_INVALID_OBJECT 1003

void g5e_log_msg(const char *bgcolor, const char *type, const char *msg, ...);

bool g5e_log_clearinit();