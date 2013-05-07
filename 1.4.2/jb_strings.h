#ifndef JB_STRINGS__H
#define JB_STRINGS__H 1

#include "jb_def.h"

#define strCharNull ""

#define STROK		0
#define STRCancel	(STROK+1)
#define STRError 	(STRCancel+1)
#define STRWarning	(STRError+1)

#define strOK jbs_strings[STROK]
#define strCancel jbs_strings[STRCancel]
#define strError jbs_strings[STRError]
#define strWarning jbs_strings[STRWarning]

#define JBS_STRINGS_BUFFER_SIZE 512

extern char *jbs_strings[];

static inline int _jbs_read_string(FILE *file,char *buffer)
{
	register int i,j,k;
	j=0;
	do
	{
		i=fgetc(file);
		if (i=='\\')
		{
			if (++j < JBS_STRINGS_BUFFER_SIZE-1)
			{
				k=fgetc(file);
				if (k=='n')
				{
					*(buffer++)=10;
					continue;
				}
				*(buffer++)=i;
				i=k;
			}
		}
		if (i==10 || i==EOF) break;
		*(buffer++)=i;
	}
	while (++j < JBS_STRINGS_BUFFER_SIZE-1);
	if (!j) return 0;
	*(buffer++)=0;
	return 1;
}

#if INLINE_JBS_READ_STRING
	#define jbs_read_string _jbs_read_string
#else
	int jbs_read_string(FILE*,char*);
#endif

static inline int _jbs_select_language(char *language,int n)
{
	register int i;
	char buffer[JBS_STRINGS_BUFFER_SIZE];
	FILE *file;
	file=fopen(language,"r");
	if (!file)
	{
		printf("Unable to open language file: %s\n",language);
		return 0;
	}
	for (i=0; i<n; ++i)
	{
		if (!jbs_read_string(file,buffer))
		{
			printf("Bad language file: %s\n",language);
			return 0;
		}
		jbs_strings[i]=g_strdup(buffer);
		if (!jbs_strings[i])
		{
			printf("Not enough memory to open language file: %s\n",language);
			return 0;
		}
	}
	fclose(file);
	return n;
}

#if INLINE_JBS_SELECT_LANGUAGE
	#define jbs_select_language _jbs_select_language
#else
	int jbs_select_language(char*,int);
#endif

#endif
