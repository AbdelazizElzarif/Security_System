
#ifndef SECURITY_TSSK_H_
#define SECURITY_TSSK_H_
#define  NofTasks 2
#define LED PINC0
#define TKEY 5
typedef struct{
	u8 *str;
	void(*fptr)(void);
}task_t;
void Security_Init(void);
void Security_Runabble(void);
void LedOnTask(void);
void Security_Acess(void);
Bool_t sring_Cmp(u8*str1,u8*str2);
void string_reverse(char *str);
int string_length(char *str);


#endif /* SECURITY_TSSK_H_ */