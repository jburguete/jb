#include "jb_strings.h"

#if !INLINE_JBS_READ_STRING
int jbs_read_string(FILE *file,char *buffer) 
{return _jbs_read_string(file,buffer);}
#endif

#if !INLINE_JBS_SELECT_LANGUAGE
int jbs_select_language(char *language,int n)
{return _jbs_select_language(language,n);}
#endif
