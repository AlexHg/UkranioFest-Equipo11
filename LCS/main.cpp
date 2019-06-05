/* Dynamic Programming implementation of LCS problem */
#include<iostream> 
#include<cstring> 
#include<cstdlib> 
using namespace std; 

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
void lcs( char *X, char *Y, int m, int n ) 
{ 
	int L[m+1][n+1]; 

	/* Following steps build L[m+1][n+1] in bottom up fashion. Note 
		that L[i][j] contains length of LCS of X[0..i-1] and Y[0..j-1] */
	for (int i=0; i<=m; i++) 
	{ 
		for (int j=0; j<=n; j++) 
		{ 
		if (i == 0 || j == 0) 
			L[i][j] = 0; 
		else if (X[i-1] == Y[j-1]) 
			L[i][j] = L[i-1][j-1] + 1; 
		else
			L[i][j] = max(L[i-1][j], L[i][j-1]); 
		} 
	} 

	// Following code is used to print LCS 
	int index = L[m][n]; 

	// Create a character array to store the lcs string 
	char lcs[index+1]; 
	lcs[index] = '\0'; // Set the terminating character 

	// Start from the right-most-bottom-most corner and 
	// one by one store characters in lcs[] 
	int i = m, j = n;
	while (i > 0 && j > 0) 
	{ 
		// If current character in X[] and Y are same, then 
		// current character is part of LCS 
		if (X[i-1] == Y[j-1]) 
		{ 
			lcs[index-1] = X[i-1]; // Put current character in result 
			i--; j--; index--;	 // reduce values of i, j and index 
		} 

		// If not same, then find the larger of two and 
		// go in the direction of larger value 
		else if (L[i-1][j] > L[i][j-1]) 
			i--; 
		else
			j--; 
	} 

	// Print the lcs 
	cout << lcs; 
} 

/* Driver program to test above function */
int main() 
{ 
	char X[] = "—Desde luego, desde luego. Tome asiento, por favor —Ingelstad iba sin parar y se dejó caer alegremente en una de las sillas y le señaló otra, invitándole a que se sentara. Glokta tardó cierto tiempo en acomodarse. Primero se agachó con cautela y luego fue moviendo las caderas hasta que dio con una postura en la que la espalda no le sometiera a un martirio constante—. ¿Y qué es lo quería tratar conmigo?"; 
	char Y[] = "Los cascos de los caballos golpeaban el arenoso sendero, las sillas crujían y los arneses tintineaban. El jineteiba sin parar de un lado para otro. El resto del mundo se desplazaba bajo ellos. El cielo del este se desangró, pasando del rojo a un rosa de ma tadero. El río surgió lentamente ante su vista, serpenteando entre los bosques otoñales que circundaban la base del empapado valle. Centelleante, como un ejército en marcha, corriendo rápido e implacable hacia el mar. Hacia Talins."; 
	int m = strlen(X); 
	int n = strlen(Y); 
	lcs(X, Y, m, n); 
	return 0; 
} 
