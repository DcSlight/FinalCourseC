#ifndef MACROS_H_
#define MACROS_H_

#define CHECK_RETURN(pFunc,pVal) {if(!pFunc(pVal)) return 0;}
#define CLOSE_FILE_RETURN(fp,msg) {printf("%s",msg); fclose(fp); return 0;}
#define PRINT_TITLE(color,title) {\
	printf(color"\n---------------------------------------------------\n"ANSI_COLOR_RESET);\
	printf(color "\t  %s\n" ANSI_COLOR_RESET,title);\
	printf(color"---------------------------------------------------\n\n"ANSI_COLOR_RESET); }

#endif /* MACROS_H_ */