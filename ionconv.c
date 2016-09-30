#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define IONS_SIZE 1000
#define NAME_SIZE 50
#define FORMULA_SIZE 15
#define CHARGE_SIZE 5
#define ALPHABET "abcdefghijklmnopqrstuvwxyz\x7E"
#define ALPHA_SIZE 26

struct ion {
	char name[NAME_SIZE];
	char formula[FORMULA_SIZE];
	char charge[CHARGE_SIZE];
};

int ion_comp(const void *ion1, const void* ion2) {
	return strcasecmp(((struct ion*)ion1)->name, ((struct ion*)ion2)->name);
}

int main(int argc, char **argv) {
	FILE *input;
	FILE *output;
	switch (argc) {
	case 0:
	case 1:
		printf("ionconv usage:\nionconv inputfile [outputfile]\n");
		return 1;
	case 2:
		input = fopen(argv[1], "r");
		output = stdout;
		break;
	default:
		if (!(input = fopen(argv[1], "r"))) {
			printf("Could not read from %s\n", argv[1]);
			return 2;
		}
		output = fopen(argv[2], "w+");
		break;
	}
	char name[NAME_SIZE], formula[FORMULA_SIZE], charge[CHARGE_SIZE];
	struct ion ions[IONS_SIZE];
	int i;
	for (i = 0; fgets(name, NAME_SIZE, input) &&
	        fgets(formula, FORMULA_SIZE, input) &&
	        fgets(charge, CHARGE_SIZE, input); ++i) {
		// trim newlines
		strtok(name, "\n");
		strtok(formula, "\n");
		strtok(charge, "\n");
		strcpy(ions[i].name, name);
		strcpy(ions[i].formula, formula);
		strcpy(ions[i].charge, charge);
	}
	qsort(ions, i, sizeof(*ions), *ion_comp);
	int total_ions = i;
	for (i = 0; i < total_ions; ++i) {
		fprintf(output, "{\"%s\", \"%s\", \"%s\"},\n", ions[i].name, ions[i].formula, ions[i].charge);
	}
	fprintf(output, "\n");
	fprintf(output, "%d\n\n", total_ions);
	char *letter = ALPHABET;
	for (i = 0; i < total_ions; ++i) {
		char first = tolower(*ions[i].name);
		while (first >= *letter) {
			letter++;
			fprintf(output, "%d,\n", i);
		}
	}
}
