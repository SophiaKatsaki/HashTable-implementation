//
// Created by Ioannis Baraklilis and Sophia Katsaki on 6/7/2020.
//

#include "HashTable.h"
#include <iostream>

#define N 1000003 // Μέγεθος Πίνακα Κατακερματισμού

HashTable::HashTable()
{
	ht= new Node [N]; //Δεσμεύω χώρο για τον πίνακα
}

HashTable::~HashTable()
{
	delete[] ht; //Αποδεσμεύω χώρο του πίνακα
}

long HashTable::Hash(const std::string &k) //Δημιουργία μίας αντιπροσωπευτικής τιμής για μία συμβολοσειρά και "περιορισμός" της σε μία θέση του πίνακα μεγέθους Ν
{
	unsigned long long val=0; // Αποθηκεύει την αντιπροσωπευτική τιμή
	unsigned long long mul=1; // Πολλαπλασιάζω κάθε χαρακτήρα της συμβολοσειράς με 5^θέση χαρακτήρα, η mul αποθηκεύει το 5^θέση
	long stringLast = k.length()-1; // Θέση τελευταίου χαρακτήρα = μήκος λέξης - 1
	if (stringLast>24) stringLast=24; // Δεν μπορεί να υπολογιστεί το hash λέξης μεγαλύτερης απο 25 χαρακτήρες (περιορισμός μνήμης)
	for (long i=stringLast;i>=0;i--)
	{
		val += mul * k[i]; // Πολλαπλασιάζω κάθε χαρακτήρα της συμβολοσειράς με 5^θέση χαρακτήρα
		mul *= 5; // Αυξάνω την δύναμη του mul
	}
	return val % N; // "Περιορίζω" την αντιπροσωπευτική τιμή
}

bool HashTable::p_search(const std::string &k, long &loc) //Αναζήτηση (ιδιωτική για χρήση εντός της κλάσης)
{
	long r=Hash(k); //Αρχική θέση που δίνει το Hash
	long c=0; // Αποτελεί μετρητή επαναλήψεων
	long inc=1; // Αποτελεί μεταβλητή "βήματος" αναζήτησης (τετραγωνικής)
	while (c!=N/2)
	{
		if (ht[r].word==k) // Η λέξη βρέθηκε στην θέση r. Ενημερώνω το loc και επιστρέφω true
		{
			loc = r;
			return true;
		}
		else if (ht[r].word=="") // Η θέση r βρέθηκε κενή, άρα δεν υπάρχει η λέξη στον πίνακα. Ενημερώνω το loc για την κενή θέση και επιστρέφω false
		{
			loc = r;
			return false;
		}

		c++; // Αυξάνω το βήμα επανάληψης
		r=(r+inc)%N; // Επόμενη θέση αναζήτησης
		inc+=2; // Αυξάνω βήματος αναζήτησης για επόμενη αναζήτηση
	}
	// Διαφορετικά, έχω c == N / 2 που σημαίνει ότι δεν υπάρχει η λέξη και ούτε κενό, θέτω loc=-1 και επιστρέφω false.
	loc=-1;
	return false;
}

const HashTable::Node* HashTable::Search(const std::string &k) // Δημόσια αναζήτηση (χρήση εκτός κλάσης) που επιστρέφω const δείκτη στο node όπου υπάρχει η λέξη ή nullptr αν δεν υπάρχει η λέξη στον πίνακα
{
	long l; // Η θέση του στοιχείο, αν τελικά βρεθεί
	bool b=p_search(k, l); // Αποθηκεύω την επιτυχία της αναζήτησης
	if (b) // Ελέγχω αν η λέξη υπάρχει, και επιστρέφω δείκτη στον κόμβο της
	{
		return &ht[l];
	}
	else // Διαφορετικά, επιστρέφω nullptr
		return nullptr;
}

bool HashTable::Insert(const std::string &k) // Συνάρτηση εισαγωγής του k στο hash table
{
	long loc;
	bool ex=p_search(k,loc); // Αναζητώ αν η λέξη υπάρχει ήδη
	if (ex) // Η λέξη υπάρχει
	{
		ht[loc].t_a++; // Αυξάνω αριθμό εμφανίσεων
		return true; // Εισαγωγή επιτυχής
	}
	else // Η λέξη δεν υπάρχει
	{
		if (loc!=-1) // Υπάρχει διαθέσιμη θέση
		{
			ht[loc] = Node(1,k); // Δημιουργώ και εισάγω νέο αντικείμενο
			return true; // Εισαγωγή επιτυχής
		}
		else // Δεν υπάρχει διαθέσιμη θέση
		{
			return false;
		}
	}
}
