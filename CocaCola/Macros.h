#ifndef MACROS_H_
#define MACROS_H_

#define CHECK_CLOSE_RETURN(pFunc,pVal) {if(!pFunc(pVal)) return 0;}
#define CLOSE_FILE_RETURN(fp,msg) {printf("%s",msg); fclose(fp); return 0;}


#endif /* MACROS_H_ */