// QueueAndCalc.cpp : Defines the entry point for the console application.
// #include "ArrayListQueue.h"
//

#include <iostream>     // std::cout, std::ios
#include <sstream>      // std::ostringstream
#include<fstream>       // file streams 
#include<string>
#include<iosfwd>

#include "stdafx.h"
#include "DemoArrayQueue.h"
#include "ListQueue.h"  
#include "MeineZahl.h" 

using namespace std;

void testBits () ; 
	

/*
void printlistRecursive(Node * pNode ) {

	if(pNode->next != NULL ) {
		printlistRecursive( pNode->next); 
	}

	// deep first 
	cout << "deep first  Node value: [" << pNode->data << "] Address next: " << pNode->next  << " my node: " << pNode << endl; 
}
*/

int main(int argc, _TCHAR* argv[]) {

/*	Node * pNode = new Node(10,NULL); 
	Node * pNext = new Node(123, pNode);
	Node * pNext2 = new Node(1232, pNext);
	Node * pNext3 = new Node(12, pNext2);
	printlistRecursive(pNext3); 

	ListQueue<unsigned> lq;

	if( lq.isEmpty() ) {
		cout << "yes is empty " << endl; 
	}

	for (int i = 0; i < 5999; i++)
	{
		lq.enqueue( rand() ) ; 
	}
*/


	// teste den modulo operator % 
	int res = 110 % 100;   // 10 rest
	int res2 = 100 % 100;  //  0 rest
	int res3 = 2 % 10;     //  2 rest

	// jetzt können wir die list queue verwenden wie die queue
	// DemoArrayQueue mQueue; 
	QueueInterface<MeineZahl *> & mQueue = ListQueue<MeineZahl *>() ;  
	// QueueInterface<MeineZahl *> & mQueue = DemoArrayQueue<MeineZahl *>() ;  


	try {

	// fist size must be 0 
	int size = mQueue.size(); 
	cout << mQueue << endl; 

	int FOR_LOOP_MAX = 99;

	for (int i = 0; i < FOR_LOOP_MAX ; i++) {

		// siehe: http://www.cplusplus.com/reference/cstdlib/rand/
		int zufallszahl = rand(); //
		mQueue.enqueue( new MeineZahl(zufallszahl) ); 
	}

	ofstream myfile;
	myfile.open ("c://temp//example.txt",  ios::out | ios::app ); // out and append
	try {
		mQueue.dumpList( myfile );  // instead of cout 
	} catch(... ) {
		// catch to make sure we close the file
	}
	if( myfile.is_open() ) {
		myfile.close(); 
	}
	
	ostringstream streamToString ;  // is an output stream to a string class. string will allocate memory as required ! 
	mQueue.dumpList( streamToString );  // instead of cout 
	
	string dd = streamToString.str(); // underling string will be returned from ostream 

	cout << streamToString.str() << endl;  // gets the underlining string from stream and prints it again to standard out 



	for (int i = 0; i < 200; i++) {
		MeineZahl * temp = mQueue.dequeue(); 

		// siehe: http://www.cplusplus.com/reference/cstdlib/rand/
		int zufallszahl = rand(); // 
		mQueue.enqueue(new MeineZahl(zufallszahl) ); 

		int sizeNeu = mQueue.size();
		if(mQueue.size() != sizeNeu ) {
			throw 4; 
		}



	}

	while( ! mQueue.isEmpty() ) {
		MeineZahl *  temp = mQueue.dequeue(); 
	}
	cout << "END queue is: " << mQueue << endl; 

	bool emptyOrNot = mQueue.isEmpty();

	if( emptyOrNot == true ) {
		cout << "IS empty is: " << emptyOrNot << " info bool size : " << sizeof(bool) << endl; 
	} else {
		throw 3; // MUST be empty here !! 
	}


	cout << "END: " << mQueue << endl; 


	} catch(int & errorCode ) {
		cout << "errorCode: " << errorCode << endl; 
	} catch(...) {
		cout << "... allgemeiner fehler: " << endl; 
	}


	return 0;
}

void testBits () {

	// bits 
	//  0     0   0   0  0  0  0  0  
	//  128  64  32  16  8  4  2  1 

 	signed int test = 4; 

	cout << "sizeof int in bytes is: " << sizeof(test) << endl; 

	test = test >> 1 ; 
	cout << "test is now: " << test  << " should be 2 " << endl; 

	test = test << 2 ; 

	cout << "test is now: " << test << " should be 2 * 2 *2 " << endl; 

	if( test & 0001 ) {
		cout << "first bit is set " << endl ; 
	}

	if( test & 8 ) {
		cout << "4. bit is set == 8 " << endl ; 
	}
	
	int mbit = 8 + 2 + 1 ; // 4. 2. 1. 

	// kombiniere bitweises und und logisches und: 
	if(mbit & 8 && mbit & 2 && mbit & 1 ) {
		cout << "4. 2. 1. (8+4+1) " << endl ; 
	}

	int bitdrei = 4; 
	int neu = mbit | bitdrei ; 

	cout << "Neuer Wert ist: " << neu << endl;  // 8 + 4 + 2 + 1 == 15 

	int neuUnd = mbit & bitdrei ; // kein logisches und da bei bitdrei nur bitdrei 

	cout << "Neuer Wert & ist expected 0 : " << neuUnd << endl;  // 8 + 4 + 2 + 1 == 15 

	//  XOR exlusives ODER, a oder b aber nicht beide 
	int neuXOR = mbit ^ bitdrei ; 

	cout << "Neuer Wert ^ : " << neuXOR << endl;  // 8 + 4 + 2 + 1 == 15 ist OK keien bit überlappungen

	int xorIn1 = 16;
	int xorIn2 = 16;

	int xort2out = xorIn1 ^ xorIn2; 

	cout << "XOR mit beiden 16 : " << xort2out << endl;  //  





}





/*

	std:queue<int> queue;
	queue.push(12); 

	------------------------------




		MeineZahl zahl(90);
	
		MeineZahl einnahmen(10 );
		MeineZahl ergebnis(0, 100, -10 ); 

		cout << "initial ergebnis : " << ergebnis << endl; 

		int betragTemp = (zahl + einnahmen).getBetrag();

		ergebnis = zahl + einnahmen; 

		ergebnis += zahl; 

		ergebnis++;
		cout << "neuer betrag: " << ergebnis << endl; 

		// beispiel aufruf der operator funktion direkt/manuell:
		if( zahl.operator<(ergebnis) ) { 
			cout << "super auch kleiner" << endl; 
		}
		// wäre auch möglich ppp = zahl.operator++(10);

		int alt = ergebnis.getBetrag(); 
		++ergebnis;
		++ergebnis;
		ergebnis--;
		ergebnis--;
		if(alt != ergebnis.getBetrag() ){
			throw ExceptionBase(); // error 2 mal plus und minus muss gleich sein 
		} else 
			cout << "neuer betrag: " << ergebnis << endl; 


		MeineZahl ppp(0); // ppp == plus plus operator tests
		ppp = zahl++;  // ppp muss noch den alten wert von zahl bekommen
		cout << "neuer betrag: " << ppp << endl; 
		ppp = ++zahl; // ppp muss schon den neuen wert von ++zahl bekommen 
		cout << "neuer betrag: " << ppp << endl; 

		// prüfe vergleichsoperatoren
		if(zahl < ergebnis ) {
			cout << "ja ist kleiner: " << zahl << " < " << ergebnis << endl; 
		}
		if(zahl <= ergebnis ) {
			cout << "ja ist <= : " << zahl << " <= " << ergebnis << endl; 
		}
		if( !(zahl >= ergebnis) ) {
			cout << "ja ist NOT >= : " << zahl << " >= " << ergebnis << endl; 
		}
		if( !(zahl > ergebnis) ) {
			cout << "ja ist NOT > : " << zahl << " > " << ergebnis << endl; 
		}


	} catch(MeineZahlOverflowException & overLimit) {
		cout << "overflow" << endl; 

	} catch(MeineZahlUnderflowException & underLimit) {
		cout << "underflow" << endl; 

	} catch( ... ) {
		cout << "Allgemeiner Fehler" << endl; 
	}





*/









/*


	// queue<int *> quue;
	// quue.push(new int(10));

	ArrayQueue<int,5> queue;

	if (queue.isEmpty()) {
		cout << "yes its empty" << endl; 
	}

	queue.enqueue( 10 );
	queue.enqueue( 11 );
	queue.enqueue(11);

	queue.dequeue();
	queue.dequeue();

	queue.enqueue(11);
	queue.enqueue(11);
	queue.enqueue(11);

	cout << queue.size() << endl;


	cout << queue.size() << endl;

	if (queue.isEmpty()) {
		cout << "yes its empty at the end " << endl;
	}




*/
