﻿
#include <iostream>
#include "SyntacticAnalysis.h"
int main()
{
	string file_name = "G1.in";
	SyntacticAna SA(file_name);
	SA.show_res();
	SA.solve();
	
	return 0;
}
