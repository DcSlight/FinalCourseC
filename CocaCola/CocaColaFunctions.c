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
