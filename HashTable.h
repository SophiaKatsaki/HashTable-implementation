//
// Created by Ioannis Baraklilis and Sophia Katsaki on 6/7/2020.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#define N 1000003 // Ορίζω το μέγεθος του πίνακα ως μια σταθερά,πρώτος αριθμός (μειώνει την πιθανότητα συγκρούσεων),τουλάχιστον διπλάσιος από το σύνολο των αγγλικών λέξεων (απαραίτητο για τετραγωνική αναζήτηση)


class HashTable
{
public:
	class Node // Δημιουργώ μια δημόσια εσωτερική κλάση το Node, το οποίο περιλαμβάνει μια λέξη και τις φορές που αυτή εμφανίστηκε
	{
	public:
		std::string word; // Αποθηκεύει την λέξη του στοιχείου
		int t_a; // Αποθηκεύει τον αριθμό εμφανίσεων

		Node() // Ο default constructor
		{
			t_a=0; // "Κενό" αντικείμενο άρα καμία εμφάνιση
			word=""; // "Κενό" αντικείμενο άρα κενή συμβολοσειρά
		}

		Node(int t,std::string w) // Ο constructor με 2 ορίσματα, το πρώτο ανατίθεται ως τιμή του t_a και το δεύτερο ως τιμή του word
		{
			t_a=t;
			word=w;
		}

		friend std::ostream &operator<<(std::ostream &os, const Node &n){ // Τελεστής <<
			os << "Word: " << n.word << ", appeared: " << n.t_a << " times";
			return os;
		}
	};

	HashTable(); // Ο constructor
	~HashTable(); // Ο destructor

	const HashTable::Node* Search(const std::string & k); // Δημόσια αναζήτηση (για χρήση εκτός κλάσης, απο χρήστη) που ψάχνει μια λέξη και επιστρέφει δείκτη στο στοιχείο όπου βρίσκεται αποθηκευμένη, αλλιώς επιστρέφει nullptr
	bool Insert(const std::string & k); // Δημόσια συνάρτηση εισαγωγής που τοποθετεί μια λέξη στο Hash Table (ή αυξάνει τον μετρητή εμφανίσεων αν ήδη υπάρχει)


private:
	Node *ht; // Ο πίνακας όπου αποθηκεύονται τα στοιχεία του Hash Table

	bool p_search(const std::string & k, long &loc); // Iδιωτική (για χρήση εντός κλάσης, όχι απο χρήστη) αναζήτηση
	long Hash(const std::string &k); // Συνάρτηση εύρεσης της αντιπροσωπευτικής θέσης στον πίνακα για μια λέξη
};


#endif //HASHTABLE_H
