# ions
ions is a program for 68k calculators  (TI-89/TI-89 Titanium, TI-92, and Voyage 200) that displays a list of common ions.

## Installation
Copy the appropriate file (`ions.89z` for TI-89/TI-89 Titanium, `ions.9xz` for TI-92, and `ions.v2z` for Voyage 200) using your favorite calculator linking program. ions is around 6 KB large, so make sure you have adequate space before copying.

## Usage
ions displays an alphabetically organized list of common ions, their formulae, and their charge. The up/down arrow keys will scroll the list, and these keys in conjunction with the 2nd and Diamond key will scroll by 10 and to the top/bottom, respectively. Any key with a letter on it may be used to quickly jump to the appropriate position (you don't have to use the Alpha key, but it doesn't hurt). The Esc key exits the program.

## Building
Building ions requires [TIGCC](http://tigcc.ticalc.org). To build ions, simply run `tigcc -O2 ions.c`, which should generate the program files.

## Customizing the list
ions comes bundled with a sample set of ions adapted and modified from the excellent [Ions](http://www.ticalc.org/archives/files/fileinfo/116/11688.html) program for the TI-86, originally compiled by Stephen Connell. These can be found in [ions.txt](ions.txt). If you'd like to modify this list:

1. Create a file with the format of `ions.txt` (or edit it); with the data for ions split into three lines:

		ion 1 name  
		ion 1 formula  
		ion 1 charge  
		ion 2 name  
		ion 2 formula  
		ion 2 charge  
		ion 3 name  
		ion 3 formula  
		…

2. Compile the utility program `ionconv.c` using your favorite C compiler.
3. Run `ionconv` on with your ions file as input: `ionconv inputfile [outputfile]`. If no output file is given, output is printed to standard out.
4. Output is printed in three sections: the ion definitions, the number of ions, and the scrolling indices. Copy and paste these to `ions[]`, `ions_length`, and `indices` in `ions.c`, respectively.
5. Follow the <a href="#building">Building</a> instructions.