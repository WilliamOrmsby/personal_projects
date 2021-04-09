#include <stdio.h>

void convert_toc(FILE rhtml, char* msg){
	FILE *fp;
	fp = fopen("test.html", "r");
	char c;
	while (fgetc(fp) != EOF){
		
