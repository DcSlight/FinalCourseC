#include "CocaColaFunctions.h"

void printLOGO()
{
	printf(ANSI_COLOR_RED"%s%s%s%s%s%s%s%s%s%s%s%s%s",
		"        __                              ___   __        .ama     ,\n",
		"      ,d888a                          ,d88888888888ba.  ,88\"I)   d\n",
		"     a88']8i                         a88\".8\"8)   `\"8888:88  \" _a8'\n",
		"   .d8P' PP                        .d8P'.8  d)      \"8:88:baad8P'\n",
		"  ,d8P' ,ama,   .aa,  .ama.g ,mmm  d8P' 8  .8'        88):888P'\n",
		" ,d88' d8[ \"8..a8\"88 ,8I\"88[ I88' d88   ]IaI\"        d8[\n",
		" a88' dP \"bm8mP8'(8'.8I  8[      d88'    `\"         .88\n",
		",88I ]8'  .d'.8     88' ,8' I[  ,88P ,ama    ,ama,  d8[  .ama.g\n",
		"[88' I8, .d' ]8,  ,88B ,d8 aI   (88',88\"8)  d8[ \"8. 88 ,8I\"88[\n",
		"]88  `888P'  `8888" "88P\"8m\"    I88 88[ 8[ dP \"bm8m88[.8I  8[\n",
		"]88,          _,,aaaaaa,_       I88 8\"  8 ]P'  .d' 88 88' ,8' I[\n",
		"`888a,.  ,aadd88888888888bma.   )88,  ,]I I8, .d' )88a8B ,d8 aI\n",
		"  \"888888PP\"'        `8""""""8   \"888PP'  `888P'  `88P\"88P\"8m\"\n"ANSI_COLOR_RESET);
}

void cocaColaLinkWebsite()
{
	printf(ANSI_COLOR_GREEN"\nFor more information: %s\n\n", WEBSITE_LINK ANSI_COLOR_RESET);
}

void findSecretRecipe()
{
	int option;
	char str[] = { 0xb6 , 0x8b,0xdf,0x96,0x8c,0xdf,0x8c,0x8b,0x96,0x93,0x93,0xdf,0x9e,0xdf,0x8c,0x9a,0x9c,0x8d,0x9a,0x8b,0x00};
	printf(ANSI_COLOR_CYAN"\n---------------------------------------------------------------------\n"ANSI_COLOR_RESET);
	printf("Do you want to be the first to find the secret receipt of Coca Cola?\n");
	printf("John Stith Pemberton invented the CocaCola formula in 1886.\n");
	printf("\nThe encrypted secret is: |%s|\n", str);
	printf("\nTo decrypt the secret please pick a key\n");
	printf(ANSI_COLOR_YELLOW"For yellow key press 1\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_RED"For red key press 2\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_BLUE"For blue key press 3\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_MAGENTA"For pink key press 4\n"ANSI_COLOR_RESET);
	printf(ANSI_COLOR_GREEN"For green key press 5\n"ANSI_COLOR_RESET);
	scanf("%d", &option);
	switch (option)
	{
	case 1:
		yellowKey(str);
		break;
	case 2:
		redKey(str);
		break;
	case 3:
		blueKey(str);
		break;
	case 4:
		pinkKey(str);
		break;
	case 5:
		greenKey(str);
		break;
	default:
		printf("Not valid\n");
		break;
	}
	printf("Text after encryption: |%s|\n", str);
	printf(ANSI_COLOR_CYAN"---------------------------------------------------------------------\n"ANSI_COLOR_RESET);

}


void redKey(char* str)
{
	while (*str != '\0')
	{
		*str <<= 2;
		str++;
	}
}


void yellowKey(char* str)
{
	while (*str != '\0')
	{
		*str ^= 68;
		str++;
	}
}

void greenKey(char* str)
{
	while (*str != '\0')
	{
		*str |= 168;
		str++;
	}
}

void pinkKey(char* str)
{
	while (*str != '\0')
	{
		*str ^= 255;
		str++;
	}
}

void blueKey(char* str)
{
	while (*str != '\0')
	{
		*str &= 153;
		str++;
	}
}




