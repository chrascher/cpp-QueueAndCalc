
#pragma once

#include <iostream>

#include "ExceptionBase.h" 


using namespace std;

class MeineZahlOverflowException : public ExceptionBase {
}; 

class MeineZahlUnderflowException : public ExceptionBase {
}; 

/*
   Meine Zahl ist ein Objekt mit eigenen Limits für den möglichen Wertebereich
   des Objekts.
   Temporäre objekte haben nur das limit von max_int und min int
   im zuweisungsoperator behält das bestehende objekt seine limits und 
   versucht nur den Wert der Übergebenen Objekte zu übernehmen. 
   
   Die Änderung der Werte wird zentral über die methode "addiereBetrag"
   durchgefürt, die privat methode berechne ergebnis und validerte Wertebereich
   stellen den internen Objektzustand nach Möglichkeiten sicher. 
   .. its just an example .. !! 
*/ 
class MeineZahl {

private: 
	int value;
	const int maxValue;  
	const int minValue;  

	MeineZahl * pMein; 

	int berechneErgebnis(int valueIn) const {
		int temp = this->value + valueIn; 
		validateWertebereich(temp); 
		return temp;
	}

	// test ob betrag addiert/subtrahiert werden kann, 
	// d.h. limit überschritten wird == oer und untergrenze wenn ok dann:
	void validateWertebereich(const int temp) const 
		throw(MeineZahlOverflowException,MeineZahlUnderflowException) {

		if(temp > maxValue ) {
			throw MeineZahlOverflowException();
		}
		if(temp < minValue ) {
			throw MeineZahlUnderflowException();
		}
	}

public:
	MeineZahl(int value, int maxVaue = INT_MAX, int minValue = INT_MIN )
		:maxValue(maxVaue), minValue(minValue) {
		this->value = value; 
	}

	~MeineZahl(void) {

		delete pMein; 

		// myMysqlDbHandle.close() ; 

	}

	MeineZahl& operator=(const  MeineZahl & inp ) 
		throw(MeineZahlOverflowException,MeineZahlUnderflowException) {

		try {
			validateWertebereich(inp.value); 
		} catch(MeineZahlUnderflowException & excUnderflow) {
			cout << "log den fehler ... mit mehr context info" << endl; 
		}

		this->value = inp.value;
		return *this; 
	}

	MeineZahl operator+ (const  MeineZahl & inp ) const {
		return MeineZahl( berechneErgebnis( inp.value ) );
	}


	MeineZahl & operator+= (const  MeineZahl & inp )
		throw(MeineZahlOverflowException,MeineZahlUnderflowException) {
	
		this->value = berechneErgebnis(value);

		return *this;
	}

	// prefix operator: must increment before assignemnt 
	MeineZahl & operator++ () 
		throw(MeineZahlOverflowException) {

		addiereBetrag(1); 
		return *this; 
	}

	// Postfix Operator: must increment after assignment, return temp object 
	MeineZahl operator++ (int a) 
		throw(MeineZahlOverflowException) {

		MeineZahl temp(*this);
		addiereBetrag(1); 
		return temp; 
	}

	MeineZahl & operator-- () 
		throw(MeineZahlUnderflowException) {

		addiereBetrag(-1); 
		return *this; 
	}


	void addiereBetrag( int value ) 
		throw(MeineZahlOverflowException,MeineZahlUnderflowException) {

		// test ob betrag addiert/subtrahiert werden kann, 
		// d.h. limit überschritten wird == oer und untergrenze 
		// wenn ok dann:
		this->value = berechneErgebnis(value);
	}

	bool operator< (const MeineZahl& rhs) const { 
		return value < rhs.value ; 
	}
	bool operator<= (const MeineZahl& rhs) const { 
		return value <= rhs.value ; 
	}
	bool operator> (const MeineZahl& rhs) const { 
		return value > rhs.value ; 
	}
	bool operator>= (const MeineZahl& rhs) const { 
		return value >= rhs.value ; 
	}


	int getBetrag() const {
		return this->value; 
	}

  friend ostream& operator<<(ostream& out, const MeineZahl &x);
  
  friend void teehaus (MeineZahl& zahl);

};

