#define USE_TI89
#define USE_TI92PLUS
#define USE_V200
#define SAVE_SCREEN

#include <compat.h>
#include <ctype.h>
#include <graph.h>
#include <kbd.h>
#include <stdio.h>
#include <stdlib.h>

// Number added to a key when 2nd is pressed
#define KEY_2ND (4096)
// Number returned when the Home key is pressed
#define KEY_HOME (277)

// Height of one line, in pixels
#define LINE_HEIGHT (8)
// Number of lines to show
#define LINES (LCD_HEIGHT / LINE_HEIGHT + 1)
// x-position of the ion's name, in pixels
#define NAME_X (0)
// x-position of the ion's formula, in pixels
#define FORMULA_X (100)
// x-position of the ion's charge, in pixels
#define CHARGE_X (140)

// Key values returned by ngetchx(), mapped to 'a'-'z'
const short keymap[] = {
	'=',
	'(',
	')',
	',',
	'/',
	'|',
	'7',
	'8',
	'9',
	'*',
	149, // the 'EE' ('k') key
	'4',
	'5',
	'6',
	'-',
	KEY_STO,
	'1',
	'2',
	'3',
	't',
	'+',
	'0',
	'.',
	'x',
	'y',
	'z',
};

struct ion {
	char *name;
	char *formula;
	char *charge;
};

const struct ion ions[] = {
	{"Acetate", "C2H3O2", "-1"},
	{"Aluminum", "Al", "+3"},
	{"Amide", "NH2", "-1"},
	{"Ammonium", "NH4", "+1"},
	{"Antimony (III,V)", "Sb", "+1"},
	{"Arsenate, Ortho-", "AsO4", "-3"},
	{"Arsenic (III,V)", "As", "+1"},
	{"Arsenite", "AsO3", "-3"},
	{"Barium", "Ba", "+2"},
	{"Benzoate", "C7H5O2", "-1"},
	{"Beryllium", "Be", "+2"},
	{"Bismuth", "Bi", "+3"},
	{"Bisulfate", "HSO4", "-1"},
	{"Borate", "BO3", "-3"},
	{"Boron", "B", "+3"},
	{"Bromate", "BrO3", "-1"},
	{"Bromide", "Br", "-1"},
	{"Bromite, Hypo-", "BrO", "-1"},
	{"Cadmium", "Cd", "+2"},
	{"Calcium", "Ca", "+2"},
	{"Carbonate", "CO3", "-2"},
	{"Carbonate, Bi-", "HCO3", "-1"},
	{"Cerium (III,IV)", "Ce", "+1"},
	{"Cesium", "Cs", "+1"},
	{"Chlorate", "ClO3", "-1"},
	{"Chlorate, Per-", "ClO4", "-1"},
	{"Chloride", "Cl", "-1"},
	{"Chlorite", "ClO2", "-1"},
	{"Chlorite, Hypo-", "ClO", "-1"},
	{"Chromate", "CrO4", "-2"},
	{"Chromate, Di-", "Cr2O7", "-2"},
	{"Chromium (II,III)", "Cr", "+1"},
	{"Citrate", "C6H5O7", "-1"},
	{"Cobalt (II,III)", "Co", "+1"},
	{"Copper (I,II)", "Cu", "+1"},
	{"Cyanate", "OCN", "-1"},
	{"Cyanate, Thio-", "SCN", "-1"},
	{"Cyanide", "CN", "-1"},
	{"Diammine silver (I)", "Ag(NH3)2", "+1"},
	{"Dihydrogen phosphate", "H2PO4", "-1"},
	{"Fluoride", "F", "-1"},
	{"Formate", "CHO2", "-1"},
	{"Gold (I,III)", "Au", "+1"},
	{"Hexacyanoferrate(II)", "Fe(CN)6", "-4"},
	{"Hexacyanoferrate(III)", "Fe(CN)6", "-3"},
	{"Hydride", "H", "-1"},
	{"Hydrogen", "H", "+1"},
	{"Hydrogen carbonate", "HCO3", "-1"},
	{"Hydrogen phosphate", "HPO4", "-2"},
	{"Hydrogen sulfate", "HSO4", "-1"},
	{"Hydrogen sulfite", "HSO3", "-1"},
	{"Hydronium", "H3O", "+1"},
	{"Hydroxide", "OH", "-1"},
	{"Iodate", "IO3", "-1"},
	{"Iodide", "I", "-1"},
	{"Iron (II,III)", "Fe", "+1"},
	{"Lead (II,IV)", "Pb", "+1"},
	{"Lithium", "Li", "+1"},
	{"Magnesium", "Mg", "+2"},
	{"Manganate", "MnO4", "-2"},
	{"Manganate, Per-", "MnO4", "-1"},
	{"Manganese (II,IV,VII)", "Mn", "+1"},
	{"Mercury (I)", "Hg2", "+2"},
	{"Mercury (II)", "Hg", "+2"},
	{"Molybdate", "MoO4", "-2"},
	{"Molybdenum (II,III,IV,V,VI)", "Mo", "+1"},
	{"Nickel", "Ni", "+2"},
	{"Nitrate", "NO3", "-1"},
	{"Nitrite", "NO2", "-1"},
	{"Oxalate", "C2O4", "-2"},
	{"Oxide", "O", "-2"},
	{"Oxide, Per-", "O2", "-2"},
	{"Phosphate", "PO4", "-3"},
	{"Phosphate, Hypo-", "P2O6", "-4"},
	{"Phosphate, Meta-", "PO3", "-1"},
	{"Phosphate, Ortho-", "PO4", "-3"},
	{"Phosphate, Pyro-", "P2O7", "-4"},
	{"Phosphite, Hypo-", "H2PO2", "-1"},
	{"Phosphite, Ortho-", "PO3", "-3"},
	{"Platinum (II,IV)", "Pt", "+1"},
	{"Potassium", "K", "+1"},
	{"Propionate", "C3H5O2", "-1"},
	{"Selenide", "Se", "-2"},
	{"Selenite", "SeO3", "-2"},
	{"Silicate, Meta-", "SiO3", "-2"},
	{"Silicate, Ortho-", "SiO4", "-2"},
	{"Silver", "Ag", "+1"},
	{"Sodium", "Na", "+1"},
	{"Strontium", "Sr", "+2"},
	{"Sulfate", "SO4", "-2"},
	{"Sulfate, Thio-", "S2O3", "-2"},
	{"Sulfide", "S", "-2"},
	{"Sulfite", "SO3", "-2"},
	{"Tartarate", "C4H4O6", "-2"},
	{"Telluride", "Te", "-2"},
	{"Thallium (I,III)", "Tl", "+1"},
	{"Tin (II,IV)", "Sn", "+1"},
	{"Titanium (II,III,IV)", "Ti", "+1"},
	{"Zinc", "Zn", "+2"},
	{"Zirconium (II,III,IV)", "Zr", "+1"},
};
const int ions_length = 100;

// Indices to scroll to for each letter
const int indices[] = {
	0,
	8,
	18,
	38,
	40,
	40,
	42,
	43,
	53,
	56,
	56,
	56,
	58,
	66,
	69,
	72,
	82,
	82,
	82,
	93,
	98,
	98,
	98,
	98,
	98,
	98,
};

// Draws everything on the line specified and below; line is zero indexed
void scroll(int line) {
	clrscr();
	int i;
	FontSetSys(F_4x6);
	for (i = 0; i < LINES; ++i) {
		if (line + i < 0 || ions_length <= line + i) { // off the screen
			continue;
		} else {
			DrawStr(NAME_X, LINE_HEIGHT * i, ions[line + i].name, A_NORMAL);
			DrawStr(FORMULA_X, LINE_HEIGHT * i, ions[line + i].formula, A_NORMAL);
			DrawStr(CHARGE_X, LINE_HEIGHT * i, ions[line + i].charge, A_NORMAL);
		}
	}
}

// Keep line on the screen
inline int clamp(int line) {
	return min(ions_length - LINES + 1, max(line, 0));
}

// Returns the
int key_index(short key) {
	if (isalpha(key)) {
		return indices[tolower(key) - 'a'];
	}
	int i;
	for (i = 0; i < 26; ++i) {
		if (key == keymap[i] ||
		        key - KEY_2ND == keymap[i] ||
		        key - KEY_DIAMOND == keymap[i]) {
			return indices[i];
			// scroll(line = clamp(indices[i]));
			// break;
		}
	}
	return -1;
}

void _main() {
	FontSetSys(F_4x6);
	int line;
	scroll(line = 0);
	for (;;) {
		short key = ngetchx();
		if (key == KEY_ESC || key == KEY_HOME || key - KEY_2ND == KEY_ESC) {
			exit(0);
		} else if (key == KEY_UP) {
			scroll(line = clamp(--line)); // up one
			continue;
		} else if (key - KEY_2ND == KEY_UP) {
			scroll(line = clamp(line -= 5)); // up five
			continue;
		} else if (key - KEY_DIAMOND == KEY_UP) {
			scroll(line = clamp(line = 0)); // top
		} else if (key == KEY_DOWN) {
			scroll(line = clamp(++line)); // down one
			continue;
		} else if (key - KEY_2ND == KEY_DOWN) {
			scroll(line = clamp(line += 5)); // down five
			continue;
		} else if (key - KEY_DIAMOND == KEY_DOWN) {
			scroll(line = clamp(line = ions_length)); // bottom
		}

		// handle alphabetic keypresses
		int index;
		if ((index = key_index(key)) >= 0) {
			scroll(line = clamp(index));
		}
	}
}
