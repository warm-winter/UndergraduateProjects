#include <stdio.h>
#include <stdlib.h>
#include "symtab.h"

/* 
A symbol table consists of the following components:

     - A hash table mapping identifiers to buckets.

     - Each bucket consists of a double-linked list of identifiers.
       Identifiers appear in scope order (from innermost to outermost)
       in the list.

     - A stack of scopes.  Each scope contains a doubly-linked list of all
       the identifiers in the scope.

     -  Hash nodes.  The elements of the lists have forward and backward
        list pointers for both hash table lists and scope lists.  Thus,
	we can find an identifier either through the stack of scopes or
	through the hashtable.
*/

/* Build an empty symbol table. */

SymTabP makeSymTable(int size) {
	HNodeP* bucketArray;
	int bucketCount, i;
	SymTabP symTab;
	
	bucketCount = size % 64;

	bucketArray = (HNodeP*)(malloc(bucketCount * sizeof(HNodeP)));

	for (i = 0; i < bucketCount; i++) {
		bucketArray[i] = 0;
	}

	symTab = (SymTabP)(malloc(sizeof(SymTab)));

	symTab->buckets  = bucketCount;
	symTab->bucketArray = bucketArray;
	symTab->scopeStack = 0;
	return(symTab);
}

/* A ScopeRec has slots for the next scope (the next field) and a list
of symbols in the current scpe (scopeStart).
*/
ScopeRecP makeScopeRec() {
	ScopeRecP val;

	val = (ScopeRecP)(malloc(sizeof(ScopeRec)));
	val->next = 0;
	val->scopeStart = 0;
	return(val);
}

/*
   A hashNode has pointers so that it can be inserted into a hash list (the
hnext and hprev pointers) and a scope list (the snext and sprev pointers).
*/
HNodeP makeHashNode() {
	HNodeP hashNode;

	hashNode = (HNodeP)(malloc(sizeof(HNode)));

	hashNode->snext = 0;
	hashNode->sprev = 0;
	hashNode->hnext = 0;
	hashNode->hprev = 0;
	
	return(hashNode);
}


int symTabHash(SymTabP symTab, int key) {
	return(key % symTab->buckets);
}

/*
   Entering a scope pushes an empty scopeRec on the stack of scopes.
*/
void symTabEnterScope(SymTabP symTab) {
	ScopeRecP scopeRec;

	scopeRec = makeScopeRec();

	scopeRec->next = symTab->scopeStack;
	symTab->scopeStack = scopeRec;
}

/*
    Exiting a scope pops a scopeRec from the stack.  The scopeRec is traversed
and all symbols are deleted from the hash table.
*/
void symTabExitScope(SymTabP symTab) {
	ScopeRecP scopeRec;
	HNodeP curNode, nextNode;
	int b;
	
	scopeRec = symTab->scopeStack;
	
	if (scopeRec) {
		curNode = scopeRec->scopeStart;
		while (curNode != 0) {
			nextNode = curNode->snext;
			if (curNode->hnext) {
				curNode->hnext->hprev = curNode->hprev;
			}

			if (curNode->hprev) {
				curNode->hprev->hnext = curNode->hnext;
			} else {
				b = symTabHash(symTab, curNode->key);
				symTab->bucketArray[b] = curNode->hnext;
			}
			free(curNode);
			curNode = nextNode;
		}
		symTab->scopeStack = scopeRec->next;
	}
}
			

/*
    Check if symbol "key" is already defined in the current scope.
*/  	
int symTabScopeCheckKey(SymTabP symTab, int key) {
	ScopeRecP scopeRec;
	HNodeP curNode;
	
	scopeRec = symTab->scopeStack;
	
	if (scopeRec) {
		curNode = scopeRec->scopeStart;
		while (curNode != 0) {
			if (curNode->key == key) {
				return(1);
			}
			curNode = curNode->snext;
		}
	}
	return(0);
}

/*
   Find the current binding of identifier "key" in the symbol table.
*/
SymRec symTabProbe(SymTabP symTab, int key) {
	HNodeP curNode;
	int i;

	i = symTabHash(symTab, key);

	curNode = symTab->bucketArray[i];
	
	while (curNode != 0) {
		if (curNode->key == key) {
			return(curNode->sym);
		}
		curNode = curNode->hnext;
	}
	return(NULL);
}

/*
   Install "key" in the current scope with infomration "symRec"
*/
int symTabAddSym(SymTabP symTab, int key, SymRec symRec) {
	HNodeP newNode;
	int b;
	
	if (!symTab->scopeStack)
	  fatal_error("symTabAddSym: Symbol table must have at least one scope when symbol is added.  Use symTabEnterScope.");

	if (!symTabScopeCheckKey(symTab, key)) {
		newNode = makeHashNode();
		newNode->key = key;
		newNode->sym = symRec;

		b = symTabHash(symTab, key);

		newNode->hnext = symTab->bucketArray[b];
		if (newNode->hnext) {
			newNode->hnext->hprev = newNode;
		}
		symTab->bucketArray[b] = newNode;
		
		newNode->snext = symTab->scopeStack->scopeStart;
		symTab->scopeStack->scopeStart = newNode;
		if (newNode->snext) {
			newNode->snext->sprev = newNode;
		}

		return(1);
	} else {
		return(0);
	}
}

	

/*
    Print out the symbol table----useful for debugging.
*/	
void symTabDump(FILE* fp, SymTabP symTab) {
	int i;
	HNodeP curNode;
	ScopeRecP curScope;
	
	fprintf(fp, "Dumping buckets.\n");

	for (i = 0; i < symTab->buckets; i++) {
		if (symTab->bucketArray[i] != 0) {
			fprintf(fp, "Bucket %i:\t", i);
			curNode = symTab->bucketArray[i];
			do {
				fprintf(fp, " %i ", curNode->key);
				curNode = curNode->hnext;
			} while (curNode != 0);
			fprintf(fp, "\n");
		}
	}

	fprintf(fp, "Dumping scopes.\n");

	for (curScope = symTab->scopeStack, i = 0;
		curScope != 0;
		curScope = curScope->next, i++) {

		fprintf(fp, "Scope %i:\t", i);

		curNode = curScope->scopeStart;
		while (curNode != 0) {
			fprintf(fp, " %i ", curNode->key);
			curNode = curNode->snext;
		}
		fprintf(fp, "\n");
	}

}
		
			
/*
    Function to develop a key from the symbol name
*/
int Symbol_to_Key(Symbol s) {
    int key;                   /* key to be returned   */

    key = (int) s;
    return key;
}


/*
    function to add a symbol to the symbol table
*/
int AddSym(SymTabP symTab, Symbol s, TYPE t) {
    SymRec symRec;             /* symbol record     */
    NodeInfoP node;	       /* node info         */	 
    int key;                   /* key of the record */

    symRec = (SymRec) malloc(sizeof(SRec));
    node = (NodeInfoP) malloc(sizeof(NodeInfo));
    node->sym = s;
    node->type = t;
    symRec->node = node;
    key = Symbol_to_Key(s);

    return symTabAddSym(symTab, key, symRec);
}


/*
    function to check if the symbol is in the symbol table
*/
int inSymTab(SymTabP symTab, Symbol node) {
    int key;                   /* key of the record */

    key = Symbol_to_Key(node);
    return symTabScopeCheckKey(symTab, key);
}


/*
    function to find the type of the symbol
*/
TYPE symType(SymTabP symTab, Symbol node) {
    SymRec symRec;	       /* symbol record     */
    int key;                   /* key of the record */

    key = Symbol_to_Key(node);
    symRec = symTabProbe(symTab, key);
    if (!symRec) {
	printf("symbol \"%s\" was not found in the symbol table\n",
	       symbol_name(node));
	exit(1);
    }
    return symRec->node->type;
}
