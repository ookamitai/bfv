#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MEM_SIZE 8

const char validchar[] = "><.,+-[]";
const char clearline[] = "\r                                                              ";
	
/*  type    var name */
	char	ch;								/* store the character */
	int		mem = 0;						/* single block of mem */
	int		mempos = 0;						/* pointer position */	
	char	memory[MEM_SIZE + 1] = ""; 	/* initialize a piece of mem */
	int		tmp = 0;
	int		interval = 300;
	int		left_bra = 0;
	int		right_bra = 0;
	int		offset = 0;
	char	output[4096] = "";
	FILE*	bff;
/* i think i wont mess up those pointers, hopefully */

void upd_console(){
	for(int k = 0; k <= MEM_SIZE; k++){
		if (k != mempos){
			printf("%04d|", memory[k] + 128);
		} else {
			printf(">%04d|", memory[k] + 128);
		}

	}
}

void initm(){
		for(int k = 0; k <= MEM_SIZE; k++){
		memory[k] = -128;
		}
}

void eval(char ch){
		if(strchr(validchar, ch) != NULL){
			printf("%c", ch);
			switch(ch){
				case '>':
					if (mempos != MEM_SIZE){
						mempos += 1;
					}
					break;
				case '<':
					if (mempos != 0){
						mempos -= 1;
					}
					break;
				case '.':
					printf("\nOut: %c\n", memory[mempos] + 128);
					break;
				case ',':
					scanf("%d", &tmp);
					memory[mempos] = tmp - 128;
					break;
				case '+':
					memory[mempos] += 1;
					break;
				case '-':
					memory[mempos] -= 1;
					break;
				case '[':
					left_bra = ftell(bff);
					if(memory[mempos] == -128){
						while(ch != ']'){
							ch = fgetc(bff);
						}
					}
					//printf("%p\n", &left_bra);
					break;
				case ']':
					right_bra = ftell(bff);
					//printf("%p\n", &right_bra);
					if(memory[mempos] != -128){
						fseek(bff, left_bra, SEEK_SET);
					}
					break;	
			}
}
}

int exec(FILE* file){
	
	initm();
	
	while ((ch = fgetc(file)) != EOF){
		Sleep(interval); /* for nicer visuals */
		eval(ch);
		printf("%s", clearline);
		printf("\r");
		upd_console();
	}
		fclose(file);
}


/* driver code here */ 
 
int main(int argc, char *argv[]) {
	
	if(argc != 2){
		fprintf(stderr, "Argument error.\nUSAGE: bfv [brainfuck file]\n");
		exit(1);
	}
	/* checks whether the number of those sent args is correct */
	
	bff = fopen(argv[1], "r");
	/* read the file using fopen and store it as a shitty pointer*/
	
	if(bff == NULL){
		fprintf(stderr, "File read error.\n");
		exit(2);
	}
	/* warn the user to check if he has intellectual disabilities */ 
	
	printf("Please specify time interval (in milliseconds):");
	scanf("%d", &interval);
	
	exec(bff);
	strcat(output, "\0");
	printf("\nOutput: %s", output);
	//printf("\n%s", output);
	return 0;
}

